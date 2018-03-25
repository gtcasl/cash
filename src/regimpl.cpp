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
  , tick_(~0ull) {
  cd_->add_use(this);
  srcs_.emplace_back(reset);
  srcs_.emplace_back(init);
  srcs_.emplace_back(next);

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
  q_next_ = srcs_[0].eval(t)[0] ? srcs_[1].eval(t) : srcs_[2].eval(t);
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

lnodeimpl* ch::internal::createRegNode(const lnode& next,
                                       const lnode& init) {
  auto ctx = next.get_ctx();
  auto cd = ctx->create_cdomain({clock_event(ctx->get_clk(), true)});
  return ctx->createNode<regimpl>(cd, next, init, ctx_curr()->get_reset());
}
