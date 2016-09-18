#include "assertimpl.h"
#include "assertion.h"
#include "context.h"
#include "ioimpl.h"

using namespace std;
using namespace chdl_internal;

assertion::assertion(context* ctx, const ch_node& src, const std::string& msg)
  : m_msg(msg)
  , m_x(src) {
  assert(src.get_size() == 1);
  ctx->gtaps.emplace_back(new outputimpl(src, fstring("assert%d", ctx->gtaps.size())));
}

void assertion::eval(ch_cycle t) {
  const bitvector& bits = m_x.eval(t);
  if (!bits.get_bit(0)) {
    CHDL_ABORT("assertion failure at cycle %ld, %s", t, m_msg.c_str());
  }
}

void chdl_internal::ch_assert(const ch_logic& l, const std::string& msg) {
  ctx_curr()->create_assertion(get_node(l), msg);  
}
