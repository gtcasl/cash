#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "arithm.h"
#include "context.h"

using namespace ch::internal;

///////////////////////////////////////////////////////////////////////////////

void ch::internal::begin_branch() {
  ctx_curr()->begin_branch();
}

void ch::internal::end_branch() {
  ctx_curr()->end_branch();
}

void ch::internal::cond_block(const lnode& pred, fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(pred.get_impl());
  func();
  ctx->end_block();
}

void ch::internal::cond_block(fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block();
  func();
  ctx->end_block();
}

///////////////////////////////////////////////////////////////////////////////

selectimpl::selectimpl(context* ctx,
                       const lnode& pred,
                       const lnode& _true,
                       const lnode& _false)
  : lnodeimpl(ctx, type_sel, _true.get_size())
  , tick_(~0ull) {
  assert(pred.get_size() == 1);
  assert(_true.get_size() == _false.get_size());
  srcs_.emplace_back(pred);
  srcs_.emplace_back(_true);
  srcs_.emplace_back(_false);
}

const bitvector& selectimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = srcs_[0].eval(t)[0] ? srcs_[1].eval(t) : srcs_[2].eval(t);
  }
  return value_;
}

lnodeimpl* select_impl::eval(const lnode& value) {
  lnodeimpl* curr = nullptr;
  auto& stmts = stmts_;
  if (!key_.is_empty()) {
    while (!stmts.empty()) {
      const auto& stmt = stmts.top();
      lnode pred(createAluNode(alu_eq, key_, stmt.pred));
      curr = createSelectNode(pred, stmt.value, curr ? lnode(curr) : value);
      stmts.pop();
    }
  } else {
    while (!stmts.empty()) {
      const auto& stmt = stmts.top();
      curr = createSelectNode(stmt.pred, stmt.value, curr ? lnode(curr) : value);
      stmts.pop();
    }
  }
  return curr;
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createSelectNode(
    const lnode& pred,
    const lnode& _true,
    const lnode& _false) {
  return pred.get_ctx()->createNode<selectimpl>(pred, _true, _false);
}
