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
  , key_idx_(-1) {
  if (key) {
    key_idx_ = this->add_src(key);
  }
}

lnodeimpl* selectimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  lnodeimpl* key = nullptr;
  if (this->has_key()) {
    key = cloned_nodes.at(this->key().id());
  }
  auto node = ctx->create_node<selectimpl>(size_, key, sloc_);
  for (uint32_t i = key_idx_ + 1; i < srcs_.size(); ++i) {
    auto src = cloned_nodes.at(srcs_[i].id());
    node->add_src(src);
  }
  return node;
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
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
      if (n > 2) {
        ret.fields.op = this->src(2).id();
      }
    }
  }
  return ret.value;
}

void selectimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << (this->has_key() ? "case" : "sel") << size_;
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
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* select_impl::emit(const lnode& value) {
  auto& stmts = stmts_;
  const auto& stmt = stmts.top();
  auto key = key_.empty() ? nullptr : key_.impl();
  auto sel = ctx_curr()->create_node<selectimpl>(stmt.value.size(), key, sloc_);
  while (!stmts.empty()) {
    const auto& stmt = stmts.top();
    // the case predicate should be a literal value
    assert(!key || type_lit == stmt.pred.impl()->type());
    sel->srcs().push_back(stmt.pred);
    sel->srcs().push_back(stmt.value);
    stmts.pop();
  }
  sel->srcs().push_back(value);
  return sel;
}
