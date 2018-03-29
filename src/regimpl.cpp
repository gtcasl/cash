#include "regimpl.h"
#include "reg.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

regimpl::regimpl(context* ctx, const lnode& next, const lnode& init)
  : lnodeimpl(ctx, type_reg, next.get_size())
  , tick_(~0ull) {
  auto cd = ctx->current_cd();
  cd->add_reg(this);
  srcs_.emplace_back(cd);  
  srcs_.emplace_back(next);
  srcs_.emplace_back(init);
}

regimpl::regimpl(context* ctx, const lnode& next)
  : lnodeimpl(ctx, type_reg, next.get_size())
  , tick_(~0ull) {
  auto cd = ctx->current_cd();
  cd->add_reg(this);
  srcs_.emplace_back(cd);
  srcs_.emplace_back(next);
}

regimpl::~regimpl() {
  this->detach();
}

void regimpl::detach() {
  if (!srcs_[0].is_empty()) {
    reinterpret_cast<cdimpl*>(srcs_[0].get_impl())->remove_reg(this);
    srcs_[0].clear();
  }
}

void regimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  value_ = q_next_;
}

void regimpl::tick_next(ch_tick t) {
  if (this->has_init()) {
    auto& reset = reinterpret_cast<cdimpl*>(srcs_[0].get_impl())->get_reset();
    q_next_ = reset.eval(t)[0] ? srcs_[2].eval(t) : srcs_[1].eval(t);
  } else {
    q_next_ = srcs_[1].eval(t);
  }
}

const bitvector& regimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return value_; 
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createRegNode(const lnode& next, const lnode& init) {
  auto ctx = next.get_ctx();
  return ctx->create_node<regimpl>(next, init);
}

lnodeimpl* ch::internal::createRegNode(const lnode& next) {
  auto ctx = next.get_ctx();
  return ctx->create_node<regimpl>(next);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::ch_pushcd(const ch_bit<1>& clock,
                             const ch_bit<1>& reset,
                             bool posedge) {
  auto ctx = ctx_curr();
  auto _cd = ctx->create_cdomain(get_lnode(clock), get_lnode(reset), posedge);
  ctx->push_cd(_cd);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}

ch_bit<1> ch::internal::ch_clock() {
  auto cd = ctx_curr()->current_cd();
  return make_type<ch_bit<1>>(cd->get_clock());
}

ch_bit<1> ch::internal::ch_reset() {
  auto cd = ctx_curr()->current_cd();
  return make_type<ch_bit<1>>(cd->get_reset());
}
