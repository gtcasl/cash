#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace cash::internal;

assertimpl::assertimpl(const lnode& src, const std::string& msg)
  : ioimpl(op_assert, src.get_ctx(), 1)
  , msg_(msg) {
  srcs_.emplace_back(src);
}

const bitvector& assertimpl::eval(ch_cycle t) {
  const bitvector& bits = srcs_[0].eval(t);
  CH_CHECK(bits[0], "assertion failure at cycle %ld, %s", t, msg_.c_str());  
  return bits;
}

void assertimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
}

void cash::internal::ch_assert(const ch_bitbase<1>& l, const std::string& msg) {
  new assertimpl(get_node(l), msg);
}
