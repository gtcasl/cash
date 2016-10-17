#include "regimpl.h"
#include "context.h"
#include "reg.h"

using namespace std;
using namespace chdl_internal;

regimpl::regimpl(const lnode& next)
  : lnodeimpl("reg", next.get_ctx(), next.get_size())
  , m_q(next.get_size())
  , m_ctime(~0ull)
{
  context* ctx = next.get_ctx();
  
  const lnode& clk = ctx->get_clk();  
  m_cd = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
  m_cd->add_use(this);

  m_srcs.emplace_back(next);
  m_srcs.emplace_back(clk);
}

regimpl::~regimpl() {
  m_cd->remove_use(this);
}

const bitvector& regimpl::eval(ch_cycle t) {
  return m_q; 
}

void regimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}

void regimpl::tick(ch_cycle t) { 
  m_q = m_next_q;
}

void regimpl::tick_next(ch_cycle t) {
  m_next_q = m_srcs[0].eval(t);
}

///////////////////////////////////////////////////////////////////////////////

latchimpl::latchimpl(const lnode& next,
                     const lnode& init,
                     const lnode& enable,                 
                     const lnode& reset)
  : lnodeimpl("latch", next.get_ctx(), next.get_size())
  , m_q(next.get_size())
  , m_ctime(~0ull)
{
  context* ctx = next.get_ctx();
  
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

const bitvector& latchimpl::eval(ch_cycle t) {
  return m_q; 
}

void latchimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}

void latchimpl::tick(ch_cycle t) { 
  //--
}

void latchimpl::tick_next(ch_cycle t) {
  if (m_srcs[3].eval(t)[0]) {
    m_q = m_srcs[1].eval(t);
  } else if (m_srcs[2].eval(t)[0]) {
    m_q = m_srcs[0].eval(t);
  }
}

///////////////////////////////////////////////////////////////////////////////

ch_logic chdl_internal::ch_clock() {
  return ch_logic(ctx_curr()->get_clk());
}

void chdl_internal::ch_pushclock(const ch_logicbase& clk) {
  ctx_curr()->push_clk(clk);
}

void chdl_internal::ch_popclock() {
  ctx_curr()->pop_clk();
}

ch_logic chdl_internal::ch_reset() {
  return ch_logic(ctx_curr()->get_reset());
}

void chdl_internal::ch_pushreset(const ch_logicbase& reset) {
  ctx_curr()->push_reset(reset);
}

void chdl_internal::ch_popreset() {
  ctx_curr()->pop_reset();
}

lnode chdl_internal::createRegNode(const lnode& next) {
  return lnode(new regimpl(next));
}

lnode chdl_internal::createLatchNode(const lnode& next, 
                                       const lnode& init, 
                                       const lnode& enable, 
                                       const lnode& reset) {
  return lnode(new latchimpl(next, init, enable, reset));
}

lnode chdl_internal::createReadyNode(const lnode& node) {
  TODO("Not yet implemented!");
}

lnode chdl_internal::createValidNode(const lnode& node) {
  TODO("Not yet implemented!");
}
