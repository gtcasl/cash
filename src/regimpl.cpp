#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "litimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

regimpl::regimpl(context* ctx,
                 unsigned length,
                 lnodeimpl* next,
                 lnodeimpl* enable,
                 lnodeimpl* init_data,
                 lnodeimpl* cd,
                 lnodeimpl* reset,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next->size(), sloc)
  , length_(length)
  , enable_idx_(-1)
  , reset_idx_(-1)
  , initdata_idx_(-1) {
  if (nullptr == cd) {
    cd = ctx->current_cd(sloc);
  }
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  if (enable) {
    enable_idx_ = this->add_src(enable);
  }

  if (init_data) {
    if (nullptr == reset) {
      reset = ctx->current_reset(sloc);
    }
    reset_idx_ = this->add_src(reset);
    initdata_idx_ = this->add_src(init_data);
  }
}

lnodeimpl* regimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto cd = cloned_nodes.at(this->cd().id());
  auto next = cloned_nodes.at(this->next().id());
  lnodeimpl* enable = nullptr;
  if (this->has_enable()) {
    enable = cloned_nodes.at(this->enable().id());
  }
  lnodeimpl* init_data = nullptr;
  lnodeimpl* reset = nullptr;
  if (this->has_init_data()) {
    init_data = cloned_nodes.at(this->init_data().id());
    reset = cloned_nodes.at(this->reset().id());
  }
  return ctx->create_node<regimpl>(length_, next, enable, init_data, cd, reset, sloc_);
}

uint64_t regimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  ret.fields.op = this->length();
  auto n = this->srcs().size();
  if (n > 0) {
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
    }
  }
  return ret.value;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_pushcd(const ch_bit<1>& clk,
                             const ch_bit<1>& reset,
                             bool pos_edge,
                             const source_location& sloc) {
  auto lclk = get_lnode(clk);
  auto lrst = get_lnode(reset);
  lclk.impl()->ctx()->push_cd(lclk, lrst, pos_edge, sloc);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_bit<1> ch::internal::ch_clock(const source_location& sloc) {
  auto cd = ctx_curr()->current_cd(sloc);
  return make_type<ch_bit<1>>(cd->clk(), sloc);
}

ch_bit<1> ch::internal::ch_reset(const source_location& sloc) {
  auto reset = ctx_curr()->current_reset(sloc);
  return make_type<ch_bit<1>>(reset, sloc);
}

///////////////////////////////////////////////////////////////////////////////

logic_buffer ch::internal::createRegNode(unsigned size,
                                         const source_location& sloc) {
  logic_buffer ret(size, sloc);
  auto ctx = ctx_curr();
  auto next = ctx->create_node<proxyimpl>(ret.data(), sloc);
  auto reg = ctx->create_node<regimpl>(1, next, nullptr, nullptr, nullptr, nullptr, sloc);
  ret.write(0, reg, 0, size, sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(const lnode& init_data,
                                         const source_location& sloc) {
  logic_buffer ret(init_data.size(), sloc);
  auto ctx = init_data.impl()->ctx();
  auto next = ctx->create_node<proxyimpl>(ret.data(), sloc);
  auto reg = ctx->create_node<regimpl>(1, next, nullptr, init_data.impl(), nullptr, nullptr, sloc);
  ret.write(0, reg, 0, init_data.size(), sloc);
  return ret;
}

logic_buffer ch::internal::copyRegNode(const lnode& node, const source_location& sloc) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  auto ctx = proxy->ctx();
  auto next = reg->next().impl();
  auto enable = reg->has_enable() ? reg->enable().impl() : nullptr;
  auto init_data = reg->has_init_data() ? reg->init_data().impl() : nullptr;
  auto new_reg = ctx->create_node<regimpl>(reg->length(), next, enable, init_data, nullptr, nullptr, sloc);
  return logic_buffer(new_reg, sloc);
}

logic_buffer ch::internal::getRegNextNode(const lnode& node) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  return logic_buffer(lnode(proxy->size(), reg->next(), 0, proxy->sloc()));
}


logic_buffer ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next.impl(), nullptr, nullptr, nullptr, nullptr, sloc);
  return logic_buffer(reg, sloc);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next.impl(), enable.impl(), nullptr, nullptr, nullptr, sloc);
  return logic_buffer(reg, sloc);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next.impl(), nullptr, init_data.impl(), nullptr, nullptr, sloc);
  return logic_buffer(reg, sloc);
}

logic_buffer ch::internal::createRegNext(const lnode& next,
                                         const lnode& init_data,
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next.impl(), enable.impl(), init_data.impl(), nullptr, nullptr, sloc);
  return logic_buffer(reg, sloc);
}
