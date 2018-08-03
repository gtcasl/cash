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
                 const lnode& /*enable*/,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc)
  , length_(length) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  // initialize with dirty content
  data_.deadbeef();
}

regimpl::regimpl(context* ctx,
                 unsigned length,
                 const lnode& next,                 
                 const lnode& /*enable*/,
                 const lnode& init,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc)
  , length_(length) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);
  srcs_.emplace_back(init);
  srcs_.emplace_back(ctx->current_reset(sloc));
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

  if (this->has_init()) {
    data_ = (this->reset().data().word(0) ? this->init() : this->next()).data();
  } else {
    data_ = this->next().data();
  }
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
                                         unsigned length,
                                         const lnode& enable,
                                         const source_location& sloc) {
  auto ctx = ctx_curr();
  auto reg = ctx->create_node<regimpl>(length,
        ctx->create_node<proxyimpl>(size, sloc), enable, sloc);
  logic_buffer ret(reg, sloc);
  reg->next().write(0, ret.data(), 0, size, sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(unsigned length,
                                         const lnode& enable,
                                         const lnode& init,
                                         const source_location& sloc) {
  auto ctx = init.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(length,
        ctx->create_node<proxyimpl>(init.size(), sloc), enable, init, sloc);
  logic_buffer ret(reg, sloc);
  reg->next().write(0, ret.data(), 0, init.size(), sloc);
  return ret;
}

logic_buffer ch::internal::copyRegNode(const lnode& node, const source_location& sloc) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  auto ctx = proxy->ctx();
  regimpl* new_reg;
  if (reg->has_init()) {
    new_reg = ctx->create_node<regimpl>(reg->length(), reg->next(), reg->enable(), reg->init(), sloc);
  } else {
    new_reg = ctx->create_node<regimpl>(reg->length(), reg->next(), reg->enable(), sloc);
  }
  return logic_buffer(new_reg, sloc);
}

logic_buffer ch::internal::getRegNextNode(const lnode& node) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  return logic_buffer(lnode(proxy->size(), reg->next(), 0, proxy->sloc()));
}
