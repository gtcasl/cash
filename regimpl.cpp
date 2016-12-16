#include "regimpl.h"
#include "context.h"
#include "reg.h"

using namespace std;
using namespace chdl_internal;

regimpl::regimpl(lnodeimpl* next)
  : lnodeimpl(op_reg, next->get_ctx(), next->get_size()) {
  context* ctx = next->get_ctx();
  
  lnodeimpl* clk = ctx->get_clk();  
  m_cd = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
  m_cd->add_use(this);

  m_srcs.emplace_back(next);
  m_srcs.emplace_back(clk);
}

regimpl::~regimpl() {
  m_cd->remove_use(this);
}

void regimpl::tick(ch_cycle t) { 
  m_value = m_q_next;
}

void regimpl::tick_next(ch_cycle t) {
  m_q_next = m_srcs[0].eval(t);
}

const bitvector& regimpl::eval(ch_cycle t) {
  return m_value; 
}

// LCOV_EXCL_START
void regimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

///////////////////////////////////////////////////////////////////////////////

latchimpl::latchimpl(lnodeimpl* next,
                     lnodeimpl* init,
                     lnodeimpl* enable,                 
                     lnodeimpl* reset)
  : lnodeimpl(op_latch, next->get_ctx(), next->get_size()) {
  context* ctx = next->get_ctx();
  
  m_cd = ctx->create_cdomain(
    {clock_event(enable, EDGE_ANY), clock_event(next, EDGE_ANY),
     clock_event(reset, EDGE_ANY), clock_event(init, EDGE_ANY)});
  m_cd->add_use(this);

  m_srcs.emplace_back(next);
  m_srcs.emplace_back(init);
  m_srcs.emplace_back(enable);
  m_srcs.emplace_back(reset);  
}

latchimpl::~latchimpl() {
  m_cd->remove_use(this);
}

void latchimpl::tick(ch_cycle t) { 
  //--
}

void latchimpl::tick_next(ch_cycle t) {
  if (m_srcs[3].eval(t)[0]) {
    m_value = m_srcs[1].eval(t);
  } else if (m_srcs[2].eval(t)[0]) {
    m_value = m_srcs[0].eval(t);
  }
}

const bitvector& latchimpl::eval(ch_cycle t) {
  return m_value; 
}

// LCOV_EXCL_START
void latchimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

///////////////////////////////////////////////////////////////////////////////

ch_logic chdl_internal::ch_clock() {
  return ch_logic(ctx_curr()->get_clk());
}

void chdl_internal::ch_pushclock(const ch_logicbase& clk) {
  ctx_curr()->push_clk(clk.get_node().get_impl());
}

void chdl_internal::ch_popclock() {
  ctx_curr()->pop_clk();
}

ch_logic chdl_internal::ch_reset() {
  return ch_logic(ctx_curr()->get_reset());
}

void chdl_internal::ch_pushreset(const ch_logicbase& reset) {
  ctx_curr()->push_reset(reset.get_node().get_impl());
}

void chdl_internal::ch_popreset() {
  ctx_curr()->pop_reset();
}

lnodeimpl* chdl_internal::createRegNode(lnodeimpl* next) {
  return new regimpl(next);
}

lnodeimpl* chdl_internal::createLatchNode(lnodeimpl* next, 
                                       lnodeimpl* init, 
                                       lnodeimpl* enable, 
                                       lnodeimpl* reset) {
  return new latchimpl(next, init, enable, reset);
}

lnodeimpl* chdl_internal::createReadyNode(lnodeimpl* node) {
  TODO("Not yet implemented!");
}

lnodeimpl* chdl_internal::createValidNode(lnodeimpl* node) {
  TODO("Not yet implemented!");
}
