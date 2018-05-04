#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "arithm.h"
#include "context.h"

using namespace ch::internal;

///////////////////////////////////////////////////////////////////////////////

void ch::internal::begin_branch(lnodeimpl* key, const source_location& sloc) {
  ctx_curr()->begin_branch(key, sloc);
}

void ch::internal::end_branch() {
  ctx_curr()->end_branch();
}

void ch::internal::cond_block(const lnode& pred, fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(pred.impl());
  func();
  ctx->end_block();
}

void ch::internal::cond_block(fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(nullptr);
  func();
  ctx->end_block();
}

///////////////////////////////////////////////////////////////////////////////

selectimpl::selectimpl(context* ctx,
                       uint32_t size,
                       lnodeimpl* key,
                       const source_location& sloc)
  : lnodeimpl(ctx, type_sel, size, 0, "", sloc)
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
  : lnodeimpl(ctx, type_sel, _true.size())
  , tick_(~0ull)
  , has_key_(false) {
  assert(1 == pred.size());
  assert(_true.size() == _false.size());
  srcs_.emplace_back(pred);
  srcs_.emplace_back(_true);
  srcs_.emplace_back(_false);
}

bool selectimpl::equals(const lnodeimpl& rhs) const {
  if (lnodeimpl::equals(rhs)) {
    auto _rhs = reinterpret_cast<const selectimpl&>(rhs);
    return (this->has_key() == _rhs.has_key());
  }
  return false;
}

std::size_t selectimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  auto n = this->srcs().size();
  if (n > 0) {
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
    }
  }
  return ret.value;
}

const bitvector& selectimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    uint32_t i, last(srcs_.size() - 1);
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
  out << "#" << id_ << " <- " << (has_key_ ? "case" : "if") << value_.size();
  uint32_t n = srcs_.size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0) {
        out << ", ";
      }
      out << "#" << srcs_[i].id();
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
  if (!key_.empty()) {
    while (!stmts.empty()) {
      const auto& stmt = stmts.top();
      lnode pred(createAluNode(op_eq, 1, key_, stmt.pred));
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
  return pred.ctx()->create_node<selectimpl>(pred, _true, _false);
}
