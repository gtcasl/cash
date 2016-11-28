#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "context.h"
#include "arithm.h"

using namespace std;
using namespace chdl_internal;

selectimpl::selectimpl(lnodeimpl* test, lnodeimpl* a, lnodeimpl* b) 
  : lnodeimpl("select", a->get_ctx(), a->get_size()), m_ctime(~0ull) {
  m_srcs.emplace_back(test);
  m_srcs.emplace_back(a);
  m_srcs.emplace_back(b);
}

const bitvector& selectimpl::eval(ch_cycle t) {
  if (m_ctime != t) {
    m_ctime = t;
    m_value = m_srcs[0].eval(t)[0] ? m_srcs[1].eval(t) : m_srcs[2].eval(t);
  }
  return m_value;
}

// LCOV_EXCL_START
void selectimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END

lnodeimpl* chdl_internal::createSelectNode(lnodeimpl* test, lnodeimpl* a, lnodeimpl* b) {
  return new selectimpl(test, a, b);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* select_impl::eval(lnodeimpl* value) {
  lnodeimpl* curr = value;
  stmts_t* stmts = m_stmts;
  if (m_key) {
    while (!stmts->empty()) {
      const stmt_t& stmt = stmts->top();
      curr = createSelectNode(createAluNode(op_eq, 1, m_key, stmt.cond), stmt.value, curr);
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
  cond->get_ctx()->begin_branch();
  this->eval(cond, func);
}

if_t::~if_t() {
  ctx_curr()->end_branch();
}

void if_t::eval(lnodeimpl* cond, func_t func) {
  context* const ctx = ctx_curr();
  ctx->begin_cond(cond);
  func();
  ctx->end_cond();
}

///////////////////////////////////////////////////////////////////////////////

switch_impl::switch_impl(lnodeimpl* key) : m_key(key) {
  m_key->get_ctx()->begin_branch();
}

switch_impl::~switch_impl() {
  m_key->get_ctx()->end_branch();
}

void switch_impl::eval(lnodeimpl* cond, func_t func) {
  context* const ctx = m_key->get_ctx();
  ctx->begin_cond(cond ? createAluNode(op_eq, 1, m_key, cond) : nullptr);
  func();
  ctx->end_cond();
}
