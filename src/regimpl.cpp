#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "litimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

regimpl::regimpl(context* ctx,
                 uint32_t size,
                 uint32_t length,
                 lnodeimpl* cd,
                 lnodeimpl* reset,
                 lnodeimpl* enable,
                 lnodeimpl* next,                 
                 lnodeimpl* init_data,
                 const source_location& sloc,
                 const std::string& name)
  : lnodeimpl(ctx, type_reg, size, sloc, name)
  , length_(length)
  , reset_idx_(-1)
  , enable_idx_(-1)
  , initdata_idx_(-1) {
  this->add_src(cd);
  this->add_src(next);
  if (reset) {
    reset_idx_ = this->add_src(reset);
  }
  if (enable) {
    enable_idx_ = this->add_src(enable);
  }
  if (init_data) {
    initdata_idx_ = this->add_src(init_data);
  }
}

lnodeimpl* regimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto cd = cloned_nodes.at(this->cd().id());
  auto next = cloned_nodes.at(this->next().id());
  lnodeimpl* reset = nullptr;
  lnodeimpl* enable = nullptr;
  lnodeimpl* init_data = nullptr;
  if (this->has_reset()) {
    reset = cloned_nodes.at(this->reset().id());
  }
  if (this->has_enable()) {
    enable = cloned_nodes.at(this->enable().id());
  }
  if (this->has_init_data()) {
    init_data = cloned_nodes.at(this->init_data().id());
  }
  return ctx->create_node<regimpl>(
        this->size(), length_, cd, reset, enable, next, init_data, sloc_, name_);
}

bool regimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const regimpl&>(other);
    return (length_ == _other.length_);
  }
  return false;
}

void regimpl::print(std::ostream& out) const {
  if (length_ > 1) {
    out << "#" << id_ << " <- pipe" << this->size();
    out << "(" << length_;
    for (uint32_t i = 0; i < this->srcs().size(); ++i) {
      out << ", ";
      out << "#" << this->src(i).id();
    }
    out << ")";
  } else {
    lnodeimpl::print(out);
  }
}


///////////////////////////////////////////////////////////////////////////////

void ch::internal::pushClockDomain(const lnode& clock,
                                   const lnode& reset,
                                   bool pos_edge,
                                   const source_location& sloc) {
  clock.impl()->ctx()->push_cd(clock, reset, pos_edge, sloc);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_bit<1> ch::internal::ch_clock(const source_location& sloc) {
  auto clk = ctx_curr()->current_clock(sloc);
  return make_type<ch_bit<1>>(clk, sloc);
}

ch_bit<1> ch::internal::ch_reset(const source_location& sloc) {
  auto rst = ctx_curr()->current_reset(sloc);
  return make_type<ch_bit<1>>(rst, sloc);
}

///////////////////////////////////////////////////////////////////////////////

logic_buffer ch::internal::createRegNode(unsigned size,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  logic_buffer ret(size, sloc, "ch_reg_" + id);
  auto ctx  = ctx_curr();
  auto cd   = ctx->current_cd(sloc);
  auto next = ctx->create_node<proxyimpl>(ret, sloc, "ch_reg_next_" + id);
  auto reg  = ctx->create_node<regimpl>(
        size, 1, cd, nullptr, nullptr, next, nullptr, sloc, id);
  ret.write(0, reg, 0, size, sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(const lnode& init_data,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  logic_buffer ret(init_data.size(), sloc, "ch_reg_" + id);
  auto ctx  = init_data.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto rst  = ctx->current_reset(sloc);
  auto next = ctx->create_node<proxyimpl>(ret, sloc, "ch_reg_next_" + id);
  auto reg  = ctx->create_node<regimpl>(
        next->size(), 1, cd, rst  , nullptr, next, init_data.impl(), sloc, id);
  ret.write(0, reg, 0, init_data.size(), sloc);
  return ret;
}

logic_buffer ch::internal::copyRegNode(const lnode& node,
                                       const source_location& sloc,
                                       const std::string& name) {
  auto id = identifier_from_typeid(name);
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg   = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  auto ctx   = proxy->ctx();
  auto cd    = ctx->current_cd(sloc);
  auto rst   = ctx->current_reset(sloc);
  auto next  = reg->next().impl();
  auto enable = reg->has_enable() ? reg->enable().impl() : nullptr;
  auto init_data = reg->has_init_data() ? reg->init_data().impl() : nullptr;
  auto new_reg = ctx->create_node<regimpl>(
        next->size(), reg->length(), cd, rst, enable, next, init_data, sloc, id);
  return logic_buffer(new_reg, sloc, "ch_reg_" + id);
}

logic_buffer ch::internal::getRegNextNode(const lnode& node) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  return logic_buffer(lnode(proxy->size(), reg->next(), 0, proxy->sloc()));
}


logic_buffer ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  auto ctx = next.impl()->ctx();
  auto cd  = ctx->current_cd(sloc);
  auto reg = ctx->create_node<regimpl>(
        next.size(), length, cd, nullptr, nullptr, next.impl(), nullptr, sloc, id);
  return logic_buffer(reg, sloc, "ch_reg_" + id);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  auto ctx = next.impl()->ctx();
  auto cd  = ctx->current_cd(sloc);
  auto reg = ctx->create_node<regimpl>(
        next.size(), length, cd, nullptr, enable.impl(), next.impl(), nullptr, sloc, id);
  return logic_buffer(reg, sloc, "ch_reg_" + id);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  auto ctx = next.impl()->ctx();
  auto cd  = ctx->current_cd(sloc);
  auto rst = ctx->current_reset(sloc);
  auto reg = ctx->create_node<regimpl>(
        next.size(), length, cd, rst , nullptr, next.impl(), init_data.impl(), sloc, id);
  return logic_buffer(reg, sloc, "ch_reg_" + id);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc,
                                         const std::string& name) {
  auto id = identifier_from_typeid(name);
  auto ctx = next.impl()->ctx();
  auto cd  = ctx->current_cd(sloc);
  auto rst = ctx->current_reset(sloc);
  auto reg = ctx->create_node<regimpl>(
        next.size(), length, cd, rst, enable.impl(), next.impl(), init_data.impl(), sloc, id);
  return logic_buffer(reg, sloc, "ch_reg_" + id);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::beginPipe(uint32_t length, const std::vector<int>& bounds) {
  CH_UNUSED(length, bounds);
  CH_TODO();
}

void ch::internal::beginPipe(uint32_t length, const lnode& enable, const std::vector<int>& bounds) {
  CH_UNUSED(length, enable, bounds);
  CH_TODO();
}

void ch::internal::endPipe(const lnode& ret) {
  CH_UNUSED(ret);
  CH_TODO();
}
