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
  , message_(msg)
  , pred_idx_(-1)
  , cond_idx_(-1) {
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate(sloc);
    if (pred) {
      pred_idx_ = this->add_src(pred);
    }
  }
  cond_idx_ = this->add_src(cond);
}
