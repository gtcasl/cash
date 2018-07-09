#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

logic_buffer ch::internal::createRegNode(unsigned size, const source_location& sloc) {
  auto ctx = ctx_curr();
  auto reg = ctx->create_node<regimpl>(
        ctx->create_node<proxyimpl>(size, sloc), sloc);
  logic_buffer ret(reg, sloc);
  reg->next().write(0, ret.data(), 0, size, sloc);
  return ret;
}

logic_buffer ch::internal::createRegNode(const lnode& init, const source_location& sloc) {
  auto ctx = init.impl()->ctx();
  auto reg = ctx->create_node<regimpl>(
        ctx->create_node<proxyimpl>(init.size(), sloc), init, sloc);
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
    new_reg = ctx->create_node<regimpl>(reg->next(), reg->init(), sloc);
  } else {
    new_reg = ctx->create_node<regimpl>(reg->next(), sloc);
  }
  return logic_buffer(new_reg, sloc);
}

logic_buffer ch::internal::createRegNextNode(const lnode& node) {
  auto proxy = reinterpret_cast<proxyimpl*>(node.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  return logic_buffer(lnode(proxy->size(), reg->next(), 0, proxy->sloc()));
}

///////////////////////////////////////////////////////////////////////////////

regimpl::regimpl(context* ctx, const lnode& next, const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  // initialize with dirty content
  value_.deadbeef();
}

regimpl::regimpl(context* ctx,
                 const lnode& next,
                 const lnode& init,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);
  srcs_.emplace_back(init);
  srcs_.emplace_back(ctx->current_reset(sloc));
}

regimpl::~regimpl() {}

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
  if (0 == cd->value().word(0))
    return;

  if (this->has_init()) {
    value_ = (this->reset().data().word(0) ? this->init() : this->next()).data();
  } else {
    value_ = this->next().data();
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
