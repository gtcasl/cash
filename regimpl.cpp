#include "regimpl.h"
#include "context.h"
#include "reg.h"

using namespace std;
using namespace chdl_internal;

regimpl::regimpl(const ch_node& next)
  : nodeimpl(next.get_ctx(), next.get_size())
  , m_q(next.get_size())
  , m_ctime(~0ull)
{
  context* ctx = next.get_ctx();
  
  ch_node clk = ctx->get_clk();  
  m_cd = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
  m_cd->add_use(this);
  m_cd->release();

  m_srcs.emplace_back(next);
  m_srcs.emplace_back(clk);
}

regimpl::~regimpl() {
  m_cd->remove_use(this);
}

const bitvector& regimpl::eval(ch_cycle t) {
  return m_q; 
}

void regimpl::print(ostream& out) const {
  TODO();
}

void regimpl::print_vl(ostream& out) const {
  TODO();
}

void regimpl::tick(ch_cycle t) { 
  m_q = m_next_q;
}

void regimpl::tick_next(ch_cycle t) {
  m_next_q = m_srcs[0].eval(t);
}

///////////////////////////////////////////////////////////////////////////////

latchimpl::latchimpl(const ch_node& next,
                     const ch_node& init,
                     const ch_node& enable,                 
                     const ch_node& reset)
  : nodeimpl(next.get_ctx(), next.get_size())
  , m_q(next.get_size())
  , m_ctime(~0ull)
{
  context* ctx = next.get_ctx();
  
  m_cd = ctx->create_cdomain(
    {clock_event(enable, EDGE_ANY), clock_event(next, EDGE_ANY),
     clock_event(reset, EDGE_ANY), clock_event(init, EDGE_ANY)});
  m_cd->add_use(this);
  m_cd->release();

  m_srcs.emplace_back(next);
  m_srcs.emplace_back(init);
  m_srcs.emplace_back(enable);
  m_srcs.emplace_back(reset);  
}

latchimpl::~latchimpl() {
  m_cd->remove_use(this);
}

const bitvector& latchimpl::eval(ch_cycle t) {
  return m_q; 
}

void latchimpl::print(ostream& out) const {
  TODO();
}

void latchimpl::print_vl(ostream& out) const {
  TODO();
}

void latchimpl::tick(ch_cycle t) { 
  //--
}

void latchimpl::tick_next(ch_cycle t) {
  if (m_srcs[3].eval(t).get_bit(0)) {
    m_q = m_srcs[1].eval(t);
  } else if (m_srcs[2].eval(t).get_bit(0)) {
    m_q = m_srcs[0].eval(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_logic chdl_internal::ch_clock() {
  return ch_logic(ctx_curr()->get_clk());
}

void chdl_internal::ch_pushclock(const ch_logic& clk) {
  TODO();
}

void chdl_internal::ch_popclock() {
  TODO();
}

ch_logic chdl_internal::ch_reset() {
  return ch_logic(ctx_curr()->get_reset());
}

void chdl_internal::ch_pushreset(const ch_logic& reset) {
  TODO();
}

void chdl_internal::ch_popreset() {
  TODO();
}

ch_node chdl_internal::createRegNode(const ch_node& next) {
  return ch_node(new regimpl(next));
}

ch_node chdl_internal::createLatchNode(const ch_node& next, 
                                       const ch_node& init, 
                                       const ch_node& enable, 
                                       const ch_node& reset) {
  return ch_node(new latchimpl(next, init, enable, reset));
}

ch_node chdl_internal::createReadyNode(const ch_node& node) {
  TODO();
}

ch_node chdl_internal::createValidNode(const ch_node& node) {
  TODO();
}
