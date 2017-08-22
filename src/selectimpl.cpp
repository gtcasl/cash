#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "context.h"
#include "arithm.h"

using namespace std;
using namespace cash::detail;

selectimpl::selectimpl(const lnode& cond, const lnode& true_, const lnode& false_)
  : lnodeimpl(op_select, cond.get_ctx(), true_.get_size())
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

lnodeimpl* cash::detail::createSelectNode(
    const lnode& test,
    const lnode& a,
    const lnode& b) {
  return new selectimpl(test, a, b);
}

///////////////////////////////////////////////////////////////////////////////

if_t::if_t(const lnode& cond, func_t func) {
  ctx_curr()->begin_branch();
  this->eval(cond, func);
}

if_t::~if_t() {
  ctx_curr()->end_branch();
}

void if_t::eval(const lnode& cond, func_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(cond.get_impl());
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

void switch_impl::eval(const lnode& cond, func_t func) {
  auto ctx = key_.get_ctx();
  ctx->begin_block(createAluNode(alu_op_eq, key_, cond));
  func();
  ctx->end_block();
}

void switch_impl::eval(func_t func) {
  auto ctx = key_.get_ctx();
  ctx->begin_block(nullptr);
  func();
  ctx->end_block();
}
