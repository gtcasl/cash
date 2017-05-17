#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace std;
using namespace cash_internal;

assertimpl::assertimpl(lnodeimpl* src, const std::string& msg)
  : ioimpl(op_assert, src->get_ctx(), 1)
  , msg_(msg) {
  srcs_.emplace_back(src);
}

const bitvector& assertimpl::eval(ch_cycle t) {
  const bitvector& bits = srcs_[0].eval(t);
  CH_CHECK(bits[0], "assertion failure at cycle %ld, %s", t, msg_.c_str());  
}

void cash_internal::ch_assert(const ch_logicbase& l, const std::string& msg) {
  new assertimpl(l.get_node().get_impl(), msg);  
}
