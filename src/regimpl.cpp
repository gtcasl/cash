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
                 const std::string& name,
                 const source_location& sloc)
  : lnodeimpl(ctx->node_id(), type_reg, size, ctx, name, sloc)
  , length_(length)
  , reset_idx_(-1)
  , enable_idx_(-1)
  , initdata_idx_(-1) {
    
  this->add_src(cd);
  this->add_src(next);

  if ((platform::self().cflags() & cflags::force_reg_init)
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

  if (enable) {
    enable_idx_ = this->add_src(enable);
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
  if (this->has_init_data()) {
    init_data = cloned_nodes.at(this->init_data().id());
  }
  if (this->has_enable()) {
    enable = cloned_nodes.at(this->enable().id());
  }
  return ctx->create_node<regimpl>(
        this->size(), length_, cd, reset, enable, next, init_data, name_, sloc_);
}

void regimpl::set_enable(lnodeimpl* node) {
  assert(enable_idx_ == -1);
  enable_idx_ = this->add_src(node);
}

lnodeimpl* regimpl::remove_enable() {
  assert(this->has_enable() && is_literal_one(this->enable().impl()));
  auto ret = this->enable().impl();
  this->remove_src(enable_idx_);
  enable_idx_ = -1;
  return ret;
}

bool regimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto& _other = reinterpret_cast<const regimpl&>(other);
    return (length_ == _other.length_);
  }
  return false;
}

void regimpl::print(std::ostream& out) const {
  if (length_ > 1) {
    out << "#" << id_ << " <- pipe" << this->size();
    out << "(" << length_;
    for (uint32_t i = 0; i < this->num_srcs(); ++i) {
      out << ", ";
      out << "#" << this->src(i).id();
    }
    out << ")";
  } else {
    lnodeimpl::print(out);
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createRegNode(unsigned size, const std::string& name) {
  CH_API_ENTRY(2);
  auto sloc = get_source_location();
  auto ctx  = ctx_curr();
  auto cd   = ctx->current_cd(sloc);
  auto next = ctx->create_node<proxyimpl>(size, name, sloc);
  auto reg  = ctx->create_node<regimpl>(
        size, 1, cd, nullptr, nullptr, next, nullptr, name, sloc);
  next->write(0, reg, 0, size);
  return reg;
}

lnodeimpl* ch::internal::createRegNode(const lnode& init_data, const std::string& name) {
  CH_API_ENTRY(2);
  auto sloc = get_source_location();
  auto ctx  = init_data.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto rst  = ctx->current_reset(sloc);
  auto next = ctx->create_node<proxyimpl>(init_data.size(), name, sloc);
  auto reg  = ctx->create_node<regimpl>(
        next->size(), 1, cd, rst  , nullptr, next, init_data.impl(), name, sloc);
  next->write(0, reg, 0, init_data.size());
  return reg;
}

lnodeimpl* ch::internal::copyRegNode(const lnode& node, const std::string& name) {
  CH_API_ENTRY(2);
  auto sloc   = get_source_location();
  auto reg    = reinterpret_cast<regimpl*>(node.impl());
  auto ctx    = reg->ctx();
  auto cd     = ctx->current_cd(sloc);
  auto rst    = ctx->current_reset(sloc);
  auto next   = reg->next().impl();
  auto enable = reg->has_enable() ? reg->enable().impl() : nullptr;
  auto init_data = reg->has_init_data() ? reg->init_data().impl() : nullptr;
  auto new_reg = ctx->create_node<regimpl>(
        next->size(), reg->length(), cd, rst, enable, next, init_data, name, sloc);
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
        next.size(), length, cd, nullptr, nullptr, next.impl(), nullptr, name, sloc);
  return ctx->create_node<proxyimpl>(reg, name, sloc);
}

lnodeimpl* ch::internal::createRegNext(const lnode& next,
                                       unsigned length,
                                       const lnode& enable,
                                       const std::string& name) {
  auto sloc = get_source_location();
  auto ctx  = next.impl()->ctx();
  auto cd   = ctx->current_cd(sloc);
  auto enable_impl = is_literal_one(enable.impl()) ? nullptr : enable.impl();
  auto reg  = ctx->create_node<regimpl>(
        next.size(), length, cd, nullptr, enable_impl, next.impl(), nullptr, name, sloc);
  return ctx->create_node<proxyimpl>(reg, name, sloc);
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
          next.size(), length, cd, rst , nullptr, next.impl(), init_data.impl(), name, sloc);
  } else {
    while (length--){
      if (reg) {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , nullptr, reg, init_data.impl(), name, sloc);
      } else {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , nullptr, next.impl(), init_data.impl(), name, sloc);
      }
    }
  }
  return ctx->create_node<proxyimpl>(reg, name, sloc);
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
  auto enable_impl = is_literal_one(enable.impl()) ? nullptr : enable.impl();

  lnodeimpl* reg = nullptr;
  if (0 ==(platform::self().cflags() & cflags::disable_sro)) {
    reg  = ctx->create_node<regimpl>(
        next.size(), length, cd, rst, enable_impl, next.impl(), init_data.impl(), name, sloc);
  } else {
    while (length--){
      if (reg) {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , enable_impl, reg, init_data.impl(), name, sloc);
      } else {
        reg  = ctx->create_node<regimpl>(
              next.size(), 1, cd, rst , enable_impl, next.impl(), init_data.impl(), name, sloc);
      }
    }
  }
  return ctx->create_node<proxyimpl>(reg, name, sloc);
}
