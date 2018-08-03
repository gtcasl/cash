#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "traits.h"
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
  : lnodeimpl(ctx, type_sel, size, sloc)
  , has_key_(false) {
  if (key) {
    has_key_ = true;
    srcs_.emplace_back(key);
  }
}

bool selectimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const selectimpl&>(other);
    return (this->has_key() == _other.has_key());
  }
  return false;
}

std::size_t selectimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();
  auto n = this->srcs().size();  
  if (n > 0) {
    ret.fields.srcs = n;
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
      if (n > 2) {
        ret.fields.arg2 = this->src(2).id();
      }
    }
  }
  return ret.value;
}

void selectimpl::eval() {
  uint32_t i, last(srcs_.size() - 1);
  if (has_key_) {
    auto& key = srcs_[0].data();
    for (i = 1; i < last; i += 2) {
      if (key == srcs_[i].data())
        break;
    }
  } else {
    for (i = 0; i < last; i += 2) {
      if (srcs_[i].data().word(0))
        break;
    }
  }
  data_ = (i < last) ? srcs_[i+1].data() : srcs_[last].data();
}

void selectimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << (has_key_ ? "case" : "sel") << data_.size();
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
    out << " = " << data_;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* select_impl::eval(const lnode& value) {
  auto& stmts = stmts_;
  const auto& stmt = stmts.top();
  auto key = key_.empty() ? nullptr : key_.impl();
  auto sel = ctx_curr()->create_node<selectimpl>(stmt.value.size(), key, sloc_);
  while (!stmts.empty()) {
    const auto& stmt = stmts.top();
    // the case predicate should be a scalar value
    assert(!key || type_lit == stmt.pred.impl()->type());
    sel->srcs().push_back(stmt.pred);
    sel->srcs().push_back(stmt.value);
    stmts.pop();
  }
  sel->srcs().push_back(value);
  return sel;
}
