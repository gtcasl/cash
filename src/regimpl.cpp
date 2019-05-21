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

  if (enable) {
    enable_idx_ = this->add_src(enable);
  }

  if ((platform::self().cflags() & cflags::reg_init)
   && !init_data) {
    assert(!reset);
    reset = ctx->current_reset(sloc);
    init_data = ctx->create_literal(sdata_type(size, 0));
  }

  if (init_data) {
    assert(reset);
    reset_idx_ = this->add_src(reset);
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
                                   bool pos_edge) {
  auto sloc = get_source_location();
  clock.impl()->ctx()->push_cd(clock, reset, pos_edge, sloc);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_bit<1> ch::internal::ch_clock() {
  CH_SOURCE_LOCATION(1);
  auto sloc = get_source_location();
  auto clk = ctx_curr()->current_clock(sloc);
  return make_type<ch_bit<1>>(clk);
}

ch_bit<1> ch::internal::ch_reset() {
  CH_SOURCE_LOCATION(1);
  auto sloc = get_source_location();
  auto rst = ctx_curr()->current_reset(sloc);
  return make_type<ch_bit<1>>(rst);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createRegNode(unsigned size, const std::string& name,
                                         const sloc_getter&) {
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto cd   = ctx->current_cd(sloc);
  auto next = ctx->create_node<proxyimpl>(size, sloc, name);
  auto reg  = ctx->create_node<regimpl>(
        size, 1, cd, nullptr, nullptr, next, nullptr, sloc, name);
  next->write(0, reg, 0, size);
  return reg;
}

lnodeimpl* ch::internal::createRegNode(const lnode& init_data,
                                         const std::string& name,
                                         const sloc_getter&) {
  auto sloc = get_source_location();
  auto ctx  = init_data.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto rst  = ctx->current_reset(sloc);
  auto next = ctx->create_node<proxyimpl>(init_data.size(), sloc, name);
  auto reg  = ctx->create_node<regimpl>(
        next->size(), 1, cd, rst  , nullptr, next, init_data.impl(), sloc, name);
  next->write(0, reg, 0, init_data.size());
  return reg;
}

lnodeimpl* ch::internal::copyRegNode(const lnode& node,
                                       const std::string& name,
                                       const sloc_getter&) {
  auto sloc   = get_source_location();
  auto reg    = reinterpret_cast<regimpl*>(node.impl());
  auto ctx    = reg->ctx();
  auto cd     = ctx->current_cd(sloc);
  auto rst    = ctx->current_reset(sloc);
  auto next   = reg->next().impl();
  auto enable = reg->has_enable() ? reg->enable().impl() : nullptr;
  auto init_data = reg->has_init_data() ? reg->init_data().impl() : nullptr;
  auto new_reg = ctx->create_node<regimpl>(
        next->size(), reg->length(), cd, rst, enable, next, init_data, sloc, name);
  return new_reg;
}

lnodeimpl* ch::internal::getRegNextNode(const lnode& node) {
  return reinterpret_cast<regimpl*>(node.impl())->next().impl();
}

lnodeimpl* ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const std::string& name) {
  auto sloc = get_source_location();
  auto ctx  = next.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto reg  = ctx->create_node<regimpl>(
        next.size(), length, cd, nullptr, nullptr, next.impl(), nullptr, sloc, name);
  return ctx->create_node<proxyimpl>(reg, sloc, name);
}

lnodeimpl* ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const lnode& enable,
                                         const std::string& name) {
  auto sloc = get_source_location();
  auto ctx  = next.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto reg  = ctx->create_node<regimpl>(
        next.size(), length, cd, nullptr, enable.impl(), next.impl(), nullptr, sloc, name);
  return ctx->create_node<proxyimpl>(reg, sloc, name);
}

lnodeimpl* ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const std::string& name) {
  auto sloc = get_source_location();
  auto ctx  = next.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto rst  = ctx->current_reset(sloc);

  lnodeimpl* reg = nullptr;
  if (0 == (platform::self().cflags() & cflags::disable_sro)) {
    reg  = ctx->create_node<regimpl>(
          next.size(), length, cd, rst , nullptr, next.impl(), init_data.impl(), sloc, name);
  } else {
    while (length--){
      if (reg) {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , nullptr, reg, init_data.impl(), sloc, name);
      } else {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , nullptr, next.impl(), init_data.impl(), sloc, name);
      }
    }
  }
  return ctx->create_node<proxyimpl>(reg, sloc, name);
}

lnodeimpl* ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const lnode& enable,
                                         const std::string& name) {
  auto sloc = get_source_location();
  auto ctx  = next.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto rst  = ctx->current_reset(sloc);

  lnodeimpl* reg = nullptr;
  if (0 ==(platform::self().cflags() & cflags::disable_sro)) {
    reg  = ctx->create_node<regimpl>(
        next.size(), length, cd, rst, enable.impl(), next.impl(), init_data.impl(), sloc, name);
  } else {
    while (length--){
      if (reg) {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , enable.impl(), reg, init_data.impl(), sloc, name);
      } else {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , enable.impl(), next.impl(), init_data.impl(), sloc, name);
      }
    }
  }
  return ctx->create_node<proxyimpl>(reg, sloc, name);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::beginPipe(uint32_t length,
                             const std::vector<int>& bounds) {
  CH_UNUSED(length, bounds);
  CH_TODO();
}

void ch::internal::beginPipe(uint32_t length,
                             const lnode& enable,
                             const std::vector<int>& bounds) {
  CH_UNUSED(length, enable, bounds);
  CH_TODO();
}

void ch::internal::endPipe(const lnode& ret) {
  CH_UNUSED(ret);
  CH_TODO();
}
