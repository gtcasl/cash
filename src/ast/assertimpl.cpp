#include "debug.h"
#include "assertimpl.h"
#include "timeimpl.h"
#include "context.h"

using namespace ch::internal;

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       const std::string& message,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, "", sloc)
  , message_(message)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(sloc);
  this->add_src(sys_time);
  auto pred = ctx_->get_predicate(sloc);
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }
}

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       lnodeimpl* pred,
                       const std::string& message,
                       const source_location& sloc)
  : ioimpl(ctx, type_assert, 0, "", sloc)
  , message_(message)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(sloc);
  this->add_src(sys_time);
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }  
}

lnodeimpl* assertimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto cond = cloned_nodes.at(this->cond().id());
  lnodeimpl* pred = nullptr;
  if (this->has_pred()) {
    pred = cloned_nodes.at(this->pred().id());
  }
  return ctx->create_node<assertimpl>(cond, pred, message_, sloc_);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::createAssertNode(const lnode& cond, 
                                    const std::string& message,
                                    const source_location& sloc) {
  ctx_curr()->create_node<assertimpl>(cond.impl(), message, sloc);
}
