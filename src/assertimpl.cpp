#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace cash::internal;

assertimpl::assertimpl(const lnode& pred, const std::string& msg)
  : ioimpl(op_assert, pred.get_ctx(), 0)
  , msg_(msg)
  , predicated_(false) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->get_predicate(this, 0, 0);
    if (pred) {
      srcs_.emplace_back(pred);
      predicated_ = true;
    }
  }
  srcs_.emplace_back(pred);
}

const bitvector& assertimpl::eval(ch_tick t) {
  if (!predicated_ || srcs_[0].eval(t)[0]) {
    const bitvector& cond = srcs_[predicated_ ? 1: 0].eval(t);
    CH_CHECK(cond[0], "assertion failure at tick %ld, %s", t, msg_.c_str());
  }
  return value_;
}

void assertimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
}

void cash::internal::createAssertNode(const lnode& pred, const std::string& msg) {
  new assertimpl(pred, msg);
}
