#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "arithm.h"
#include "context.h"

using namespace ch::internal;

///////////////////////////////////////////////////////////////////////////////

void ch::internal::begin_branch(lnodeimpl* key) {
  ctx_curr()->begin_branch(key);
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

selectimpl::selectimpl(context* ctx, uint32_t size, lnodeimpl* key)
  : lnodeimpl(ctx, type_sel, size)
  , tick_(~0ull)
  , has_key_(false) {
  if (key) {
    has_key_ = true;
    srcs_.emplace_back(key);
  }
}

selectimpl::selectimpl(context* ctx,
                       const lnode& pred,
                       const lnode& _true,
                       const lnode& _false)
  : lnodeimpl(ctx, type_sel, _true.get_size())
  , tick_(~0ull)
  , has_key_(false) {
  assert(1 == pred.get_size());
  assert(_true.get_size() == _false.get_size());
  srcs_.emplace_back(pred);
  srcs_.emplace_back(_true);
  srcs_.emplace_back(_false);
}

const bitvector& selectimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    uint32_t i;
    uint32_t last = srcs_.size() - 1;
    if (has_key_) {
      auto& key = srcs_[0].eval(t);
      for (i = 1; i < last; i += 2) {
        if (key == srcs_[i].eval(t))
          break;
      }
    } else {
      for (i = 0; i < last; i += 2) {
        if (srcs_[i].eval(t)[0])
          break;
      }
    }
    value_ = (i < last) ? srcs_[i+1].eval(t) : srcs_[last].eval(t);
  }
  return value_;
}

void selectimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << (has_key_ ? "case" : "if") << value_.get_size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0) {
        out << ", ";
      }
      out << "#" << srcs_[i].get_id();
    }
    out << ")";
  }
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

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
