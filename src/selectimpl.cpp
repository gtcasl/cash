#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "arithm.h"
#include "context.h"

using namespace cash::internal;

selectimpl::selectimpl(const lnode& pred, const lnode& _true, const lnode& _false)
  : lnodeimpl(op_select, pred.get_ctx(), _true.get_size())
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

lnodeimpl* cash::internal::createSelectNode(
    const lnode& pred,
    const lnode& _true,
    const lnode& _false) {
  return new selectimpl(pred, _true, _false);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* select_impl::eval(const lnode& value) {
  lnodeimpl* curr = nullptr;
  auto& stmts = stmts_;
  if (!key_.is_empty()) {
    while (!stmts.empty()) {
      const auto& stmt = stmts.top();
      lnode pred(createAluNode(alu_op_eq, key_, stmt.pred));
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

if_t::if_t(const lnode& pred, func_t func) {
  ctx_curr()->begin_branch();
  this->eval(pred, func);
}

if_t::~if_t() {
  ctx_curr()->end_branch();
}

void if_t::eval(const lnode& pred, func_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(pred.get_impl());
  func();
  ctx->end_block();
}

void if_t::eval(func_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block();
  func();
  ctx->end_block();
}

///////////////////////////////////////////////////////////////////////////////

switch_impl::switch_impl(const lnode& key) : key_(key) {
  ctx_curr()->begin_branch();
}

switch_impl::~switch_impl() {
  ctx_curr()->end_branch();
}

void switch_impl::eval(const lnode& pred, func_t func) {
  auto ctx = key_.get_ctx();
  ctx->begin_block(createAluNode(alu_op_eq, key_, pred));
  func();
  ctx->end_block();
}

void switch_impl::eval(func_t func) {
  auto ctx = key_.get_ctx();
  ctx->begin_block();
  func();
  ctx->end_block();
}
