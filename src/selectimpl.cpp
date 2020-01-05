#include "selectimpl.h"
#include "litimpl.h"
#include "select.h"
#include "if.h"
#include "switch.h"
#include "traits.h"
#include "context.h"

using namespace ch::internal;

///////////////////////////////////////////////////////////////////////////////

void ch::internal::begin_branch(const lnode& key, const source_location& sloc) {
  ctx_curr()->begin_branch(key.impl(), sloc);
}

void ch::internal::begin_branch(const source_location& sloc) {
  ctx_curr()->begin_branch(nullptr, sloc);
}

void ch::internal::end_branch() {
  ctx_curr()->end_branch();
}

void ch::internal::cond_block(const lnode& pred, fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(pred.impl());
  func();
  ch_cout.flush();
  ctx->end_block();
}

void ch::internal::cond_block(fvoid_t func) {
  auto ctx = ctx_curr();
  ctx->begin_block(nullptr);
  func();
  ch_cout.flush();
  ctx->end_block();
}

///////////////////////////////////////////////////////////////////////////////

selectimpl::selectimpl(context* ctx,
                       uint32_t size,
                       lnodeimpl* key,
                       const source_location& sloc)
  : lnodeimpl(ctx->node_id(), type_sel, size, ctx, "", sloc)
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
  for (uint32_t i = (has_key_ ? 1 : 0); i < this->num_srcs(); ++i) {
    auto src = cloned_nodes.at(this->src(i).id());
    node->add_src(src);
  }
  return node;
}


bool selectimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto& _other = reinterpret_cast<const selectimpl&>(other);
    return (has_key_ == _other.has_key_);
  }
  return false;
}

void selectimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << (this->has_key() ? "case" : "sel") << this->size();
  auto n = this->num_srcs();
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

lnode select_impl::emit(const lnode& def_value) {
  auto& stmts = stmts_;
  auto key  = key_.empty() ? nullptr : key_.impl();
  auto sel  = ctx_curr()->create_node<selectimpl>(def_value.size(), key, sloc_);
  if (key) {
    // insert switch cases in ascending order
    for (auto& stmt : stmts) {
      auto pred = stmt.first.impl();
      assert(type_lit == pred->type()); // the case predicate should be a literal value
      auto& ipred = reinterpret_cast<litimpl*>(pred)->value();
      uint32_t i = 1;
      for (; i < sel->num_srcs(); i += 2) {
        auto& sel_ipred = reinterpret_cast<litimpl*>(sel->src(i).impl())->value();
        CH_CHECK(sel_ipred != ipred, "duplicate switch case");
        if (sel_ipred > ipred) {
          sel->insert_src(i, stmt.second.impl());
          sel->insert_src(i, pred);
          break;
        }
      }
      if (i == sel->num_srcs()) {
        assert(pred->size() == key->size());
        assert(stmt.second.size() == sel->size());
        sel->add_src(pred);
        sel->add_src(stmt.second.impl());
      }
    }
  } else {
    for (auto& stmt : stmts) {
      assert(stmt.first.size() == 1);
      assert(stmt.second.size() == sel->size());
      sel->add_src(stmt.first.impl());
      sel->add_src(stmt.second.impl());
    }
  }
  sel->add_src(def_value.impl());
  return sel;
}
