#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "context.h"
#include "arithm.h"

using namespace std;
using namespace cash::detail;

selectimpl::selectimpl(const lnode& cond, const lnode& true_, const lnode& false_)
  : lnodeimpl(op_select, cond->get_ctx(), true_->get_size())
  , ctime_(~0ull) {
  srcs_.emplace_back(cond);
  srcs_.emplace_back(true_);
  srcs_.emplace_back(false_);
}

const bitvector& selectimpl::eval(ch_cycle t) {
  if (ctime_ != t) {
    ctime_ = t;
    value_ = srcs_[0].eval(t)[0] ? srcs_[1].eval(t) : srcs_[2].eval(t);
  }
  return value_;
}

void selectimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

lnodeimpl* cash::detail::createSelectNode(lnodeimpl* test,
                                          lnodeimpl* a,
                                          lnodeimpl* b) {
  return new selectimpl(test, a, b);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* select_impl::eval(lnodeimpl* value) {
  lnodeimpl* curr = value;
  stmts_t* stmts = stmts_;
  if (key_) {
    while (!stmts->empty()) {
      const stmt_t& stmt = stmts->top();
      lnodeimpl* cond = createAluNode(alu_op_eq, 1, key_, stmt.cond);
      curr = createSelectNode(cond, stmt.value, curr);
      stmts->pop();
    } 
  } else {
    while (!stmts->empty()) {
      const stmt_t& stmt = stmts->top();
      curr = createSelectNode(stmt.cond, stmt.value, curr);
      stmts->pop();
    }
  }
  return curr;
}

///////////////////////////////////////////////////////////////////////////////

if_t::if_t(lnodeimpl* cond, func_t func) {
  ctx_curr()->begin_branch();
  this->eval(cond, func);
}

if_t::~if_t() {
  ctx_curr()->end_branch();
}

void if_t::eval(lnodeimpl* cond, func_t func) {
  context* const ctx = ctx_curr();
  ctx->begin_block(cond);
  func();
  ctx->end_block();
}

///////////////////////////////////////////////////////////////////////////////

switch_impl::switch_impl(lnodeimpl* key) : key_(key) {
  ctx_curr()->begin_branch();
}

switch_impl::~switch_impl() {
  ctx_curr()->end_branch();
}

void switch_impl::eval(lnodeimpl* cond, func_t func) {
  context* const ctx = key_->get_ctx();
  ctx->begin_block(cond ? createAluNode(alu_op_eq, 1, key_, cond) : nullptr);
  func();
  ctx->end_block();
}
