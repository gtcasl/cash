#include "regimpl.h"
#include "reg.h"
#include "select.h"
#include "context.h"

using namespace ch::internal;

regimpl::regimpl(context* ctx,
                 cdomain* cd,
                 const lnode& next,
                 const lnode& init,
                 const lnode& reset)
  : lnodeimpl(ctx, type_reg, next.get_size())
  , cd_(cd)
  , next_idx_(-1)
  , init_idx_(-1)
  , reset_idx_(-1)
  , enable_idx_(-1) {
  cd_->add_use(this);

  next_idx_ = srcs_.size();
  srcs_.emplace_back(next);

  init_idx_ = srcs_.size();
  srcs_.emplace_back(init);

  reset_idx_ = srcs_.size();
  srcs_.emplace_back(reset);

  this->get_signals(cd);
}

regimpl::regimpl(context* ctx,
                 cdomain* cd,
                 const lnode& next,
                 const lnode& init,
                 const lnode& reset,
                 const lnode& enable)
  : lnodeimpl(ctx, type_reg, next.get_size())
  , cd_(cd)
  , next_idx_(-1)
  , init_idx_(-1)
  , reset_idx_(-1)
  , enable_idx_(-1) {
  cd_->add_use(this);

  next_idx_ = srcs_.size();
  srcs_.emplace_back(next);

  init_idx_ = srcs_.size();
  srcs_.emplace_back(init);

  reset_idx_ = srcs_.size();
  srcs_.emplace_back(reset);

  enable_idx_ = srcs_.size();
  srcs_.emplace_back(enable);

  this->get_signals(cd);
}

void regimpl::get_signals(cdomain* cd) {
  auto& sensitivity_list = cd->get_sensitivity_list();
  for (auto& e : sensitivity_list) {
    const auto& signal = e.get_signal();
    bool already_added = false;
    for (auto& src : srcs_) {
      if (src.get_id() == signal.get_id()) {
        already_added = true;
        break;
      }
    }
    if (!already_added) {
      srcs_.emplace_back(signal);
    }
  }
}

regimpl::~regimpl() {
  cd_->remove_use(this);
}

void regimpl::tick(ch_tick t) { 
  CH_UNUSED(t);
  value_ = q_next_;
}

void regimpl::tick_next(ch_tick t) {
  if (reset_idx_ != -1 && srcs_[reset_idx_].eval(t)[0]) {
    q_next_ = srcs_[init_idx_].eval(t);
    if (cd_->is_asynchronous(srcs_[reset_idx_])) {
      value_ = q_next_;
    }
  } else if (enable_idx_ != -1) {
    if (srcs_[enable_idx_].eval(t)[0]) {
      q_next_ = srcs_[next_idx_].eval(t);
      if (cd_->is_asynchronous(srcs_[enable_idx_])) {
        value_ = q_next_;
      }
    }
  } else {
    q_next_ = srcs_[next_idx_].eval(t);
  }
}

const bitvector& regimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return value_; 
}

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> ch::internal::ch_getClock() {
  return make_type<ch_bit<1>>(ctx_curr()->get_clk());
}

void ch::internal::pushClock(const lnode& clk) {
  ctx_curr()->push_clk(clk);
}

void ch::internal::ch_popClock() {
  ctx_curr()->pop_clk();
}

const ch_bit<1> ch::internal::ch_getReset() {
  return make_type<ch_bit<1>>(ctx_curr()->get_reset());
}

void ch::internal::pushReset(const lnode& reset) {
  ctx_curr()->push_reset(reset);
}

void ch::internal::ch_popReset() {
  ctx_curr()->pop_reset();
}

lnodeimpl* ch::internal::createRegNode(const lnode& next, const lnode& init) {
  auto ctx = next.get_ctx();
  auto cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
  return ctx->createNode<regimpl>(cd, next, init, ctx_curr()->get_reset());
}

lnodeimpl* ch::internal::createLatchNode(
    const lnode& next,
    const lnode& init,
    const lnode& enable,
    const lnode& reset) {
  auto ctx = next.get_ctx();
  auto cd = ctx->create_cdomain({
    clock_event(enable, EDGE_ANY),
    clock_event(next, EDGE_ANY),
    clock_event(reset, EDGE_ANY),
    clock_event(init, EDGE_ANY)});
  return ctx->createNode<regimpl>(cd, next, init, reset, enable);
}
