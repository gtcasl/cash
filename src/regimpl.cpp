#include "regimpl.h"
#include "reg.h"
#include "select.h"
#include "context.h"

using namespace cash::internal;

regimpl::regimpl(cdomain* cd,
                 const lnode& next,
                 const lnode& init,
                 const lnode& reset)
  : lnodeimpl(op_reg, next.get_ctx(), next.get_size())
  , cd_(cd)
  , next_id_(-1)
  , init_id_(-1)
  , reset_id_(-1)
  , enable_id_(-1) {
  cd_->add_use(this);

  next_id_ = srcs_.size();
  srcs_.emplace_back(next);

  init_id_ = srcs_.size();
  srcs_.emplace_back(init);

  reset_id_ = srcs_.size();
  srcs_.emplace_back(reset);

  this->get_signals(cd);
}

regimpl::regimpl(cdomain* cd,
                 const lnode& next,
                 const lnode& init,
                 const lnode& reset,
                 const lnode& enable)
  : lnodeimpl(op_reg, next.get_ctx(), next.get_size())
  , cd_(cd)
  , next_id_(-1)
  , init_id_(-1)
  , reset_id_(-1)
  , enable_id_(-1) {
  cd_->add_use(this);

  next_id_ = srcs_.size();
  srcs_.emplace_back(next);

  init_id_ = srcs_.size();
  srcs_.emplace_back(init);

  reset_id_ = srcs_.size();
  srcs_.emplace_back(reset);

  enable_id_ = srcs_.size();
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
  if (reset_id_ != -1 && srcs_[reset_id_].eval(t)[0]) {
    q_next_ = srcs_[init_id_].eval(t);
    if (cd_->is_asynchronous(srcs_[reset_id_]))
      value_ = q_next_;
  } else if (enable_id_ != -1) {
    if (srcs_[enable_id_].eval(t)[0]) {
      q_next_ = srcs_[next_id_].eval(t);
      if (cd_->is_asynchronous(srcs_[enable_id_]))
        value_ = q_next_;
    }
  } else {
    q_next_ = srcs_[next_id_].eval(t);
  }
}

const bitvector& regimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return value_; 
}

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> cash::internal::ch_getClock() {
  return make_bit<1>(ctx_curr()->get_clk());
}

void cash::internal::pushClock(const lnode& clk) {
  ctx_curr()->push_clk(clk);
}

void cash::internal::ch_popClock() {
  ctx_curr()->pop_clk();
}

const ch_bit<1> cash::internal::ch_getReset() {
  return make_bit<1>(ctx_curr()->get_reset());
}

void cash::internal::pushReset(const lnode& reset) {
  ctx_curr()->push_reset(reset);
}

void cash::internal::ch_popReset() {
  ctx_curr()->pop_reset();
}

lnodeimpl* cash::internal::createRegNode(const lnode& next, const lnode& init) {
  auto ctx = next.get_ctx();
  auto cd = ctx->create_cdomain({clock_event(ctx->get_clk(), EDGE_POS)});
  return new regimpl(cd, next, init, ctx_curr()->get_reset());
}

lnodeimpl* cash::internal::createLatchNode(
    const lnode& next,
    const lnode& init,
    const lnode& enable,
    const lnode& reset) {
  auto cd = next.get_ctx()->create_cdomain({
    clock_event(enable, EDGE_ANY),
    clock_event(next, EDGE_ANY),
    clock_event(reset, EDGE_ANY),
    clock_event(init, EDGE_ANY)});
  return new regimpl(cd, next, init, reset, enable);
}

lnodeimpl* cash::internal::createReadyNode(const lnode& node) {
  CH_UNUSED(node);
  CH_TODO();
}

lnodeimpl* cash::internal::createValidNode(const lnode& node) {
  CH_UNUSED(node);
  CH_TODO();
}
