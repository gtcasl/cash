#include "assertimpl.h"
#include "assertion.h"
#include "context.h"

using namespace ch::internal;

void ch::internal::ch_assert(const ch_bit<1>& pred, const std::string& msg,
                             const source_location& sloc) {
  auto lpred = get_lnode(pred);
  lpred.impl()->ctx()->create_node<assertimpl>(lpred, msg, sloc);
}

assertimpl::assertimpl(context* ctx,
                       const lnode& cond,
                       const std::string& msg,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, sloc)
  , msg_(msg)
  , predicated_(false)
  , tick_(0) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate(sloc);
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
  if (!predicated_ || static_cast<bool>(srcs_[0].data())) {
    auto pred = static_cast<bool>(srcs_[predicated_ ? 1 : 0].data());
    if (!pred) {
      fprintf(stderr, "assertion failure at tick %ld, %s (%s:%d)\n", tick_, msg_.c_str(), sloc_.file(), sloc_.line());
      std::abort();
    }
  }
  tick_++;
}
