#include "assertimpl.h"
#include "timeimpl.h"
#include "assertion.h"
#include "context.h"

using namespace ch::internal;

void ch::internal::ch_assert(const ch_bit<1>& cond, const std::string& msg,
                             const source_location& sloc) {
  auto lcond = get_lnode(cond).impl();
  lcond->ctx()->create_node<assertimpl>(lcond, msg, sloc);
}

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       const std::string& msg,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, sloc)
  , msg_(msg)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(sloc);
  this->add_src(sys_time);
  if (ctx_->conditional_enabled(this)) {
    auto pred = ctx_->create_predicate(sloc);
    if (pred) {
      pred_idx_ = this->add_src(pred);
    }
  }
}

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       lnodeimpl* pred,
                       const std::string& msg,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, sloc)
  , msg_(msg)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(sloc);
  this->add_src(sys_time);
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }  
}

lnodeimpl* assertimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto cond = cloned_nodes.at(this->cond().id());
  lnodeimpl* pred = nullptr;
  if (this->has_pred()) {
    pred = cloned_nodes.at(this->pred().id());
  }
  return ctx->create_node<assertimpl>(cond, pred, msg_, sloc_);
}
