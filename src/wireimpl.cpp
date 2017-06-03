#include "wireimpl.h"
#include "wire.h"

using namespace std;
using namespace cash::detail;

wireimpl::wireimpl(lnodeimpl* src)
  : lnodeimpl(op_wire, src->get_ctx(), src->get_size())
  , ctime_(~0ull) {
  srcs_.emplace_back(src);
}

const bitvector& wireimpl::eval(ch_cycle t) {
  if (ctime_ != t) {
    ctime_ = t;
    value_ = srcs_[0].eval(t);
  }
  return value_;
}

void wireimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

lnodeimpl* cash::detail::createWireNode(lnodeimpl* src) {
  return new wireimpl(src);
}
