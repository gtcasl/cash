#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace ch::internal;

assertimpl::assertimpl(context* ctx, const lnode& cond, const std::string& msg)
  : ioimpl(ctx, type_assert, 0)
  , msg_(msg)
  , predicated_(false) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate();
    if (pred) {
      srcs_.emplace_back(pred);
      predicated_ = true;
    }
  }
  srcs_.emplace_back(cond);
}

const bitvector& assertimpl::eval(ch_tick t) {
  if (!predicated_ || srcs_[0].eval(t)[0]) {
    auto& cond = srcs_[predicated_ ? 1: 0].eval(t);
    CH_CHECK(cond[0], "assertion failure at tick %ld, %s", t, msg_.c_str());
  }
  return value_;
}

void ch::internal::createAssertNode(const lnode& pred, const std::string& msg) {
  pred.ctx()->create_node<assertimpl>(pred, msg);
}
