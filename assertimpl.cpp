#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

assertimpl::assertimpl(lnodeimpl* src, const std::string& msg)
  : ioimpl("assert", src->get_ctx(), 1)
  , m_msg(msg) {
  m_srcs.emplace_back(src);
}

const bitvector& assertimpl::eval(ch_cycle t) {
  const bitvector& bits = m_srcs[0].eval(t);
  CHDL_CHECK(bits[0], "assertion failure at cycle %ld, %s", t, m_msg.c_str());  
}

void chdl_internal::ch_assert(const ch_logicbase& l, const std::string& msg) {
  ctx_curr()->register_gtap(new assertimpl(l.get_node().get_impl(), msg));  
}
