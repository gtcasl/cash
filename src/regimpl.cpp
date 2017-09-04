#include "regimpl.h"
#include "reg.h"
#include "select.h"
#include "context.h"

using namespace cash::internal;

regimpl::regimpl(const lnode& next)
  : lnodeimpl(op_reg, next.get_ctx(), next.get_size()) {
  context* ctx = next.get_ctx();
  lnodeimpl* clk = ctx->get_clk();

  cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
  cd_->add_use(this);

  srcs_.emplace_back(next);
  srcs_.emplace_back(clk);
}

regimpl::~regimpl() {
  cd_->remove_use(this);
}

void regimpl::tick(ch_cycle t) { 
  CH_UNUSED(t);
  value_ = q_next_;
}

void regimpl::tick_next(ch_cycle t) {
  q_next_ = srcs_[0].eval(t);
}

const bitvector& regimpl::eval(ch_cycle t) {
  CH_UNUSED(t);
  return value_; 
}

void regimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

latchimpl::latchimpl(const lnode& next,
                     const lnode& init,
                     const lnode& enable,
                     const lnode& reset)
  : lnodeimpl(op_latch, next.get_ctx(), next.get_size()) {
  assert(next.get_size() == init.get_size());
  assert(enable.get_size() == 1);
  assert(reset.get_size() == 1);
  context* ctx = next.get_ctx();

  cd_ = ctx->create_cdomain(
    {clock_event(enable, EDGE_ANY), clock_event(next, EDGE_ANY),
     clock_event(reset, EDGE_ANY), clock_event(init, EDGE_ANY)});
  cd_->add_use(this);

  srcs_.emplace_back(next);
  srcs_.emplace_back(init);
  srcs_.emplace_back(enable);
  srcs_.emplace_back(reset);  
}

latchimpl::~latchimpl() {
  cd_->remove_use(this);
}

void latchimpl::tick(ch_cycle t) { 
  CH_UNUSED(t);
}

void latchimpl::tick_next(ch_cycle t) {
  if (srcs_[3].eval(t)[0]) {
    value_ = srcs_[1].eval(t);
  } else if (srcs_[2].eval(t)[0]) {
    value_ = srcs_[0].eval(t);
  }
}

const bitvector& latchimpl::eval(ch_cycle t) {
  CH_UNUSED(t);
  return value_; 
}

void latchimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

const ch_bit<1> cash::internal::ch_clock() {
  return make_bit<1>(ctx_curr()->get_clk());
}

void cash::internal::ch_push_clock(const ch_bitbase<1>& clk) {
  ctx_curr()->push_clk(get_node(clk));
}

void cash::internal::ch_pop_clock() {
  ctx_curr()->pop_clk();
}

const ch_bit<1> cash::internal::ch_reset() {
  return make_bit<1>(ctx_curr()->get_reset());
}

void cash::internal::ch_push_reset(const ch_bitbase<1>& reset) {
  ctx_curr()->push_reset(get_node(reset));
}

void cash::internal::ch_pop_reset() {
  ctx_curr()->pop_reset();
}

lnodeimpl* cash::internal::createRegNode(const lnode& next, const lnode& init) {
  lnodeimpl* reset = ctx_curr()->get_reset();
  return new regimpl(createSelectNode(reset, init, next));
}

lnodeimpl* cash::internal::createLatchNode(
    const lnode& next,
    const lnode& init,
    const lnode& enable,
    const lnode& reset) {
  return new latchimpl(next, init, enable, reset);
}

lnodeimpl* cash::internal::createReadyNode(const lnode& node) {
  CH_UNUSED(node);
  CH_TODO();
}

lnodeimpl* cash::internal::createValidNode(const lnode& node) {
  CH_UNUSED(node);
  CH_TODO();
}
