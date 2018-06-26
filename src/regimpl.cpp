#include "reg.h"
#include "regimpl.h"
#include "proxyimpl.h"
#include "cdimpl.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

reg_buffer::reg_buffer(uint32_t size, const source_location& sloc)
  : logic_buffer(
      ctx_curr()->create_node<regimpl>(
        ctx_curr()->create_node<proxyimpl>(size, sloc), sloc),
      sloc) {
  this->write(0, value_, 0, size, sloc);
}

reg_buffer::reg_buffer(const lnode& data, const source_location& sloc)
  : logic_buffer(
      ctx_curr()->create_node<regimpl>(
        ctx_curr()->create_node<proxyimpl>(data.size(), sloc), data, sloc),
      sloc) {
  this->write(0, value_, 0, data.size(), sloc);
}

void reg_buffer::write(uint32_t dst_offset,
                       const lnode& data,
                       uint32_t src_offset,
                       uint32_t length,
                       const source_location& sloc) {
  auto proxy = reinterpret_cast<proxyimpl*>(value_.impl());
  auto reg = reinterpret_cast<regimpl*>(proxy->src(0).impl());
  reg->next().write(dst_offset, data, src_offset, length, sloc);
}

///////////////////////////////////////////////////////////////////////////////

regimpl::regimpl(context* ctx, const lnode& next, const source_location& sloc)
  : lnodeimpl(ctx, type_reg, next.size(), sloc) {
  auto cd = ctx->current_cd(sloc);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);

  // initialize with dirty content
  this->next().data().deadbeef();
}

regimpl::regimpl(context* ctx,
                 const lnode& next,
                 const lnode& init,
                 const source_location& sloc)
  : regimpl(ctx, next, sloc) {
  srcs_.emplace_back(init);
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
    value_ = (cd->rst().data().word(0) ? this->init() : this->next()).data();
  } else {
    value_ = this->next().data();
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_pushcd(const ch_bit<1>& clk,
                             const ch_bit<1>& rst,
                             bool posedge,
                             const source_location& sloc) {
  auto ctx = ctx_curr();
  auto _cd = ctx->create_cdomain(get_lnode(clk), get_lnode(rst), posedge, sloc);
  ctx->push_cd(_cd);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_bit<1> ch::internal::ch_clock(const source_location& sloc) {
  auto cd = ctx_curr()->current_cd(sloc);
  return make_type<ch_bit<1>>(cd->clk(), sloc);
}

ch_bit<1> ch::internal::ch_reset(const source_location& sloc) {
  auto cd = ctx_curr()->current_cd(sloc);
  return make_type<ch_bit<1>>(cd->rst(), sloc);
}
