#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

assertimpl::assertimpl(const ch_node& src, const std::string& msg)
  : ioimpl("assert", src.get_ctx(), 1)
  , m_msg(msg) {
  m_srcs.emplace_back(src);
}

const bitvector& assertimpl::eval(ch_cycle t) {
  const bitvector& bits = m_srcs[0].eval(t);
  if (!bits.get_bit(0)) {
    CHDL_ABORT("assertion failure at cycle %ld, %s", t, m_msg.c_str());
  }
}

void chdl_internal::ch_assert(const ch_logic& l, const std::string& msg) {
  ctx_curr()->gtaps.emplace_back(new assertimpl(l, msg));  
}
