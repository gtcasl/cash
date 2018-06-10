#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace ch::internal;

assertimpl::assertimpl(context* ctx,
                       const lnode& cond,
                       const std::string& msg,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, "", sloc)
  , msg_(msg)
  , predicated_(false)
  , tick_(0) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate();
    if (pred) {
      srcs_.emplace_back(pred);
      predicated_ = true;
    }
  }
  srcs_.emplace_back(cond);
}

void assertimpl::initialize() {
  tick_ = 0;
}

void assertimpl::eval() {
  if (!predicated_ || srcs_[0].data().word(0)) {
    auto pred = srcs_[predicated_ ? 1 : 0].data().word(0);
    CH_CHECK(pred, "assertion failure at tick %ld, %s", tick_, msg_.c_str());
  }
  tick_++;
}

void ch::internal::createAssertNode(const lnode& pred,
                                    const std::string& msg,
                                    const source_location& sloc) {
  pred.impl()->ctx()->create_node<assertimpl>(pred, msg, sloc);
}
