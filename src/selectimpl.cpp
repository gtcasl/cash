#include "selectimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "traits.h"
#include "context.h"

using namespace ch::internal;

///////////////////////////////////////////////////////////////////////////////

void ch::internal::begin_branch(const lnode& key) {
  auto sloc = get_source_location();
  ctx_curr()->begin_branch(key.impl(), sloc);
}

void ch::internal::begin_branch() {
  auto sloc = get_source_location();
  ctx_curr()->begin_branch(nullptr, sloc);
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
  : lnodeimpl(ctx, type_sel, size, sloc, "")
  , has_key_(false) {
  if (key) {
    this->add_src(key);
    has_key_ = true;
  }
}

lnodeimpl* selectimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  lnodeimpl* key = nullptr;
  if (this->has_key()) {
    key = cloned_nodes.at(this->key().id());
  }
  auto node = ctx->create_node<selectimpl>(this->size(), key, sloc_);
  for (uint32_t i = (has_key_ ? 1 : 0); i < this->srcs().size(); ++i) {
    auto src = cloned_nodes.at(this->src(i).id());
    node->add_src(src);
  }
  return node;
}


bool selectimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const selectimpl&>(other);
    return (has_key_ == _other.has_key_);
  }
  return false;
}

void selectimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << (this->has_key() ? "case" : "sel") << this->size();
  auto n = this->srcs().size();
  if (n > 0) {
    out << "(";
    for (uint32_t i = 0; i < n; ++i) {
      if (i > 0) {
        out << ", ";
      }
      out << "#" << this->src(i).id();
    }
    out << ")";
  }
}

///////////////////////////////////////////////////////////////////////////////

lnode select_impl::emit(const lnode& value) {
  auto& stmts = stmts_;
  auto key = key_.empty() ? nullptr : key_.impl();
  auto sloc = get_source_location();
  auto sel = ctx_curr()->create_node<selectimpl>(value.size(), key, sloc);
  for (auto& stmt : stmts) {
    assert(!key || type_lit == stmt.first.impl()->type()); // case's predicate should be literal
    sel->add_src(stmt.first);
    sel->add_src(stmt.second);
  }
  sel->add_src(value);
  return sel;
}
