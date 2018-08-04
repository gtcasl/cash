#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

regimpl::regimpl(context* ctx,
                 unsigned length,
                 const lnode& next,
                 const lnode& enable,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc)
  , enable_idx_(-1)
  , init_idx_(-1)
  , reset_idx_(-1)
  , pipe_(length - 1, bitvector(next.size())) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  // add enable predicate
  if (enable.impl()->type() != type_lit) {
    enable_idx_ = this->add_src(enable);
  } else {
    // the constant value should be one
    assert(1 == enable.impl()->data().word(0));
  }

  // initialize with dirty content
  data_.deadbeef();
}

regimpl::regimpl(context* ctx,
                 unsigned length,
                 const lnode& next,                 
                 const lnode& enable,
                 const lnode& init,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc)
  , enable_idx_(-1)
  , init_idx_(-1)
  , reset_idx_(-1)
  , pipe_(length - 1, bitvector(next.size())) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  // add enable predicate
  if (enable.impl()->type() != type_lit) {
    enable_idx_ = this->add_src(enable);
  } else {
    // the constant value should be one
    assert(1 == enable.impl()->data().word(0));
  }

  init_idx_ = this->add_src(init);
  reset_idx_ = this->add_src(ctx->current_reset(sloc));
}

std::size_t regimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  auto n = this->srcs().size();
  if (n > 0) {
    ret.fields.srcs = n;
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
      if (n > 2) {
        ret.fields.arg2 = this->src(2).id();
      }
    }
  }
  return ret.value;
}

void regimpl::eval() {
  // check clock transition
  auto cd = reinterpret_cast<cdimpl*>(this->cd().impl());
  if (0 == cd->data().word(0))
    return;

  // check reset state
  if (this->has_init() && this->reset().data().word(0)) {
    data_ = this->init().data();
    for (auto& p : pipe_) {
      p = data_;
    }
    return;
  }

  // check enable state
  int enable = this->has_enable() ? this->enable().data().word(0) : 1;
  if (!enable)
    return;

  // advance pipeline
  bitvector* value = &data_;
  if (!pipe_.empty()) {
    auto last = pipe_.size() - 1;
    data_ = pipe_[last];
    for (int i = last; i > 0; --i) {
      pipe_[i] = pipe_[i-1];
    }
    value = &pipe_[0];
  }
  // push next value
  *value = this->next().data();
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_pushcd(const ch_bit<1>& clk,
                             const ch_bit<1>& reset,
                             bool posedge,
                             const source_location& sloc) {
  auto lclk = get_lnode(clk);
  auto lrst = get_lnode(reset);
  lclk.impl()->ctx()->push_cd(lclk, lrst, posedge, sloc);
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
  auto reg = ctx->create_node<regimpl>(1, next, bitvector(1,1), sloc);
  ret.write(0, reg, 0, size, sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(const lnode& init,
                                         const source_location& sloc) {
  logic_buffer ret(init.size(), sloc);
  auto ctx = init.impl()->ctx();
  auto next = ctx->create_node<proxyimpl>(ret.data(), sloc);
  auto reg = ctx->create_node<regimpl>(1, next, bitvector(1,1), init, sloc);
  ret.write(0, reg, 0, init.size(), sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(const lnode& next,
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next, enable, sloc);
  return logic_buffer(reg, sloc);
}

logic_buffer ch::internal::createRegNode(const lnode& next,
                                         unsigned length,
                                         const lnode& enable,
                                         const lnode& init,
                                         const source_location& sloc) {
  auto ctx = next.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length, next, enable, init, sloc);
  return logic_buffer(reg, sloc);
}

logic_buffer ch::internal::copyRegNode(const lnode& node, const source_location& sloc) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  auto ctx = proxy->ctx();
  regimpl* new_reg;
  auto enable = reg->has_enable() ? reg->enable() : lnode(bitvector(1,1));
  if (reg->has_init()) {
    new_reg = ctx->create_node<regimpl>(reg->length(), reg->next(), enable, reg->init(), sloc);
  } else {
    new_reg = ctx->create_node<regimpl>(reg->length(), reg->next(), enable, sloc);
  }
  return logic_buffer(new_reg, sloc);
}

logic_buffer ch::internal::getRegNextNode(const lnode& node) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  return logic_buffer(lnode(proxy->size(), reg->next(), 0, proxy->sloc()));
}
