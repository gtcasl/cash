#include "debug.h"
#include "assertimpl.h"
#include "timeimpl.h"
#include "context.h"

using namespace ch::internal;

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       const std::string& msg,
                       const source_info& srcinfo)
  : ioimpl(ctx, type_assert, 0, "", srcinfo)
  , msg_(msg)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(srcinfo);
  this->add_src(sys_time);
  auto pred = ctx_->get_predicate(srcinfo);
  if (pred) {
    pred_idx_ = this->add_src(pred);
  }
}

assertimpl::assertimpl(context* ctx,
                       lnodeimpl* cond,
                       lnodeimpl* pred,
                       const std::string& msg,
                       const source_info& srcinfo)
  : ioimpl(ctx, type_assert, 0, "", srcinfo)
  , msg_(msg)
  , pred_idx_(-1) {
  this->add_src(cond);
  auto sys_time = ctx->create_time(srcinfo);
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
  return ctx->create_node<assertimpl>(cond, pred, msg_, srcinfo_);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::createAssertNode(const lnode& cond, 
                                    const std::string& msg,
                                    const source_info& srcinfo) {
  ctx_curr()->create_node<assertimpl>(cond.impl(), msg, srcinfo);
}