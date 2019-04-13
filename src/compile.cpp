#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "opimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "ioimpl.h"
#include "bindimpl.h"
#include "timeimpl.h"
#include "context.h"
#include "ordered_set.h"
#include "mem.h"

using namespace ch::internal;

namespace ch {
namespace internal {

struct cse_key_t {

  lnodeimpl* node;

  cse_key_t(lnodeimpl* p_node) : node(p_node) {}

  bool operator==(const cse_key_t& other) const {
    return this->node->equals(*other.node);
  }
};

struct cse_hash_t {
  std::size_t operator()(const cse_key_t& key) const {
    return key.node->hash();
  }
};

class node_tracker {
public:
  node_tracker(context* ctx) : ctx_(ctx) {
    size_ = ctx->nodes().size();
  }

  size_t deleted() {
    auto cur_size = ctx_->nodes().size();
    auto count = size_ - cur_size;
    size_ = cur_size;
    return count;
  }

  size_t current() {
    return size_;
  }

private:
  context* ctx_;
  size_t size_;
};

struct interval_t {
  uint32_t start;
  uint32_t end;

  interval_t(uint32_t start, uint32_t end) : start(start), end(end) {}

  bool overlaps(const interval_t& other) const {
    return (other.start < this->end) && (this->start < other.end);
  }

  auto intersection(const interval_t& other) const {
    interval_t ret{0, 0};
    if (!overlaps(other))
      return ret;
    if (other.start <= this->start && other.end >= this->end) {
      // rhs fully overlaps lhs
      ret = *this;
    } else if (other.start < this->start) {
      // rhs overlaps on the left
      ret.start = this->start;
      ret.end = other.end;
    } else if (other.end > this->end) {
      // rhs overlaps on the right,
      ret.start = other.start;
      ret.end = this->end;
    } else {
      // rhs fully included
      ret = other;
    }
    return ret;
  }
};

}
}

compiler::compiler(context* ctx) : ctx_(ctx) {}

void compiler::optimize() {
  size_t cfo_total(0), dce_total(0), cse_total(0), pip_total(0), pcx_total(0), bro_total(0);

  CH_DBG(2, "compiling %s (#%d) ...\n", ctx_->name().c_str(), ctx_->id());

  node_tracker tracker(ctx_);
  size_t orig_num_nodes = tracker.current();

  this->dead_code_elimination();
  dce_total = tracker.deleted();

  this->map_initialize();

  for (;;) {
    bool changed = false;
    changed |= this->constant_folding();
    auto cfo = tracker.deleted();
    changed |= this->subexpressions_elimination();
    auto cse = tracker.deleted();
    changed |= this->prune_identity_proxies();
    auto pip = tracker.deleted();
    changed |= this->proxies_coalescing();
    auto pcx = tracker.deleted();
    changed |= this->branch_coalescing();
    auto bro = tracker.deleted();

    if (!changed)
      break;

    cfo_total += cfo;
    cse_total += cse;
    pip_total += pip;
    pcx_total += pcx;
    bro_total += bro;
  }

#ifndef NDEBUG
  // dump nodes
  if (platform::self().cflags() & cflags::dump_ast) {
    ctx_->dump_ast(std::cout);
  }

  // dump tap's CFG
  if (platform::self().cflags() & cflags::dump_cfg) {
    for (auto node : ctx_->taps()) {
      std::cout << "CFG dump for tap variable: " << node->name() << std::endl;
      ctx_->dump_cfg(node, std::cout);
    }
  }
#else
  CH_UNUSED(orig_num_nodes, dce_total);
#endif

  CH_DBG(2, "*** deleted %lu DCE nodes\n", dce_total);
  CH_DBG(2, "*** deleted %lu CFO nodes\n", cfo_total);
  CH_DBG(2, "*** deleted %lu CSE nodes\n", cse_total);
  CH_DBG(2, "*** deleted %lu PIP nodes\n", pip_total);
  CH_DBG(2, "*** deleted %lu PCX nodes\n", pcx_total);
  CH_DBG(2, "*** deleted %lu BRO nodes\n", bro_total);
  CH_DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  CH_DBG(2, "After optimization: %lu\n", tracker.current());
}

bool compiler::dead_code_elimination() {
  CH_DBG(3, "Begin Compiler::DCE\n");

  bool changed = false;

  std::vector<lnodeimpl*> undefs;
  ordered_set<lnodeimpl*> live_nodes;
  std::unordered_map<proxyimpl*, std::unordered_set<uint32_t>> used_proxy_sources;
  std::unordered_map<uint32_t, std::unordered_set<proxyimpl*>> proxy_users;

  //--
  auto remove_unused_proxy_sources = [&](proxyimpl* proxy, uint32_t src_idx) {
    // gather unused source positions
    std::vector<interval_t> unused_pos;
    for (auto& range : proxy->ranges()) {
      if (range.src_idx == src_idx) {
        unused_pos.emplace_back(range.dst_offset, range.dst_offset + range.length);
      }
    }

    // remove unused source
    proxy->erase_source(src_idx, true);

    // update proxy users' ranges
    for (auto use : proxy_users.at(proxy->id())) {
      uint32_t i = 0;
      for (uint32_t n = use->srcs().size(); i < n; ++i) {
        if (use->src(i).id() == proxy->id())
          break;
      }
      assert(i != use->srcs().size());
      for (auto& range : use->ranges()) {
        if (range.src_idx == i) {
          uint32_t r = 0;
          for (auto& pos : unused_pos) {
            if (range.src_offset >= pos.end) {
              r += (pos.end - pos.start);
            }
          }
          range.src_offset -= r;
        }
      }
    }
  };

  // get permanent live nodes
  for (auto node : ctx_->inputs()) {
    live_nodes.insert(node);
  }
  for (auto node : ctx_->outputs()) {
    live_nodes.insert(node);
  }
  for (auto node : ctx_->taps()) {
    live_nodes.insert(node);
  }
  for (auto node : ctx_->gtaps()) {
    live_nodes.insert(node);
  }

  // build live nodes set
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  while (!working_set.empty()) {
    auto node = working_set.front();
    auto proxy = dynamic_cast<proxyimpl*>(node);

    auto& srcs = node->srcs();
    for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
      auto src_impl = srcs[i].impl();
      assert(src_impl->ctx() == ctx_);

      // skip unused proxy sources
      if (proxy) {
        auto it = used_proxy_sources.find(proxy);
        if (it != used_proxy_sources.end()
         && 0 == it->second.count(i))
          continue;
      }

      // gather used proxy sources
      bool is_new_proxy_src = false;
      if (type_proxy == src_impl->type()) {
        auto src_proxy = reinterpret_cast<proxyimpl*>(src_impl);        
        auto& uses = used_proxy_sources[src_proxy];
        if (proxy) {
          proxy_users[src_proxy->id()].insert(proxy);
          for (auto& curr : src_proxy->ranges()) {
            uint32_t curr_end = curr.dst_offset + curr.length;
            for (auto& range : proxy->ranges()) {
              if (range.src_idx == i) {
                // do ranges overlap?
                uint32_t src_end = range.src_offset + range.length;
                if (range.src_offset < curr_end && src_end > curr.dst_offset) {
                  auto ret = uses.insert(curr.src_idx);
                  if (ret.second) {
                    is_new_proxy_src = true;
                  }
                }
              }
            }
          }
        } else {
          for (auto& curr : src_proxy->ranges()) {
            auto ret = uses.insert(curr.src_idx);
            if (ret.second) {
              is_new_proxy_src = true;
            }
          }
        }
      }

      // add to live list
      auto ret = live_nodes.insert(src_impl);
      if (ret.second || is_new_proxy_src) {
        // we have a new live node, add it to working set
        working_set.push_back(src_impl);

        // check for undefined proxies
        if (!is_new_proxy_src
         && type_proxy == src_impl->type()
         && !reinterpret_cast<proxyimpl*>(src_impl)->check_fully_initialized()) {
          undefs.push_back(src_impl);
          if (proxy) {
            undefs.push_back(proxy);
          }
        }
      }
    }
    working_set.pop_front();
  }

  // remove unused proxy sources
  for (auto p : used_proxy_sources) {
    auto proxy = reinterpret_cast<proxyimpl*>(p.first);
    auto& srcs = proxy->srcs();
    // traverse the sources in reverse order (for efficiency)
    for (int i = srcs.size() - 1; i >= 0; --i) {
      if (0 == p.second.count(i)) {
        remove_unused_proxy_sources(proxy, i);
      };
    }
  }

  // delete dead nodes
  for (auto it = ctx_->nodes().begin(),
            end = ctx_->nodes().end(); it != end;) {
    if (0 == live_nodes.count(*it)) {
      it = ctx_->delete_node(it);
      changed = true;
    } else {
      ++it;
    }
  }

  // check for un-initialized nodes
  if (!undefs.empty()) {
    bool found = false;
    for (auto node : undefs) {
      auto proxy = reinterpret_cast<proxyimpl*>(node);
      if (!proxy->check_fully_initialized()) {
        found = true;
        break;
      }
    }
    if (found) {
    #define LCOV_EXCL_START
    #ifndef NDEBUG
      // dump nodes
      if (platform::self().cflags() & cflags::dump_ast) {
        ctx_->dump_ast(std::cout);
      }
    #endif
      for (auto node : undefs) {
        auto proxy = reinterpret_cast<proxyimpl*>(node);
        if (proxy->check_fully_initialized())
          continue;
        fprintf(stderr, "error: un-initialized variable %s\n", proxy->debug_info().c_str());
      }
      std::abort();
    #define LCOV_EXCL_END
    }
  }

  assert(ctx_->nodes().size() == live_nodes.size());

  CH_DBG(3, "End Compiler::DCE\n");

  return changed;
}

bool compiler::constant_folding() {
  if (platform::self().cflags() & cflags::disable_cfo)
    return false;

  CH_DBG(3, "Begin Compiler::CFO\n");

  std::set<lnodeimpl*> deleted_list;
  std::unordered_set<uint32_t> visited_nodes;

  auto replace_constant = [&](lnodeimpl* from, lnodeimpl* to) {
    if (nullptr == to)
      return;
    this->map_replace_target(from, to);
    this->map_delete(from);
    deleted_list.insert(from);
    for (auto& src : from->srcs()) {
      deleted_list.insert(src.impl());
    }
  };

  std::function<void (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node) {
    if (visited_nodes.count(node->id()))
      return;
    visited_nodes.emplace(node->id());

    bool is_constant = true;
    for (auto& src : node->srcs()) {
      auto src_impl = src.impl();
      dfs_visit(src_impl);
      is_constant &= (type_lit == src_impl->type());
    }

    switch (node->type()) {
    case type_sel: {
      auto sel = reinterpret_cast<selectimpl*>(node);
      if (!is_constant) {
        if (sel->has_key()) {
          is_constant = (type_lit == sel->key().impl()->type());
        } else {
          is_constant = true;
          for (uint32_t i = 0, l = sel->srcs().size() - 1; i < l; i += 2) {
            is_constant &= (type_lit == sel->src(i).impl()->type());
          }
        }
      }
      if (is_constant) {
        replace_constant(sel, this->constant_fold(sel));
      }
      break;
    }
    case type_proxy: {
      if (is_constant) {
        auto proxy = reinterpret_cast<proxyimpl*>(node);
        replace_constant(proxy, this->constant_fold(proxy));
      }
      break;
    }
    case type_op: {
      auto alu = reinterpret_cast<opimpl*>(node);
      if (is_constant) {
        replace_constant(alu, this->constant_fold(alu));
      } else
      if (op_flags::bitwise == CH_OP_CLASS(alu->op())
       && op_flags::binary == CH_OP_ARY(alu->op())) {
        replace_constant(alu, this->constant_fold_bitwise(alu));
      }
      break;
    }
    default:
      break;
    }
  };

  // visit output nodes
  for (auto node : ctx_->outputs()) {
    dfs_visit(node);
  }
  for (auto node : ctx_->taps()) {
    dfs_visit(node);
  }
  for (auto node : ctx_->gtaps()) {
    dfs_visit(node);
  }

  // process deleted nodes
  for (auto dn : deleted_list) {
    auto m_it = node_map_.find(dn->id());
    if (m_it != node_map_.end()) {
      if (!m_it->second.empty())
        continue;
      this->map_delete(dn);
    }
    assert(node_map_.find(dn->id()) == node_map_.end());
    ctx_->delete_node(dn);
  }

  CH_DBG(3, "End Compiler::CFO\n");

  return deleted_list.size();
}

lnodeimpl* compiler::constant_fold(proxyimpl* node) {
  sdata_type tmp(node->size());
  for (auto& range : node->ranges()) {
    auto dst_idx = range.dst_offset / bitwidth_v<block_type>;
    auto dst_lsb = range.dst_offset % bitwidth_v<block_type>;
    auto src_impl = node->src(range.src_idx).impl();
    assert(type_lit == src_impl->type());
    auto src_data = reinterpret_cast<litimpl*>(src_impl)->value().words();
    bv_copy(tmp.words() + dst_idx, dst_lsb, src_data, range.src_offset, range.length);
  }
  return ctx_->create_literal(tmp);
}

lnodeimpl* compiler::constant_fold(opimpl* node) {
  sdata_type tmp(node->size());

  const block_type* src0_data = nullptr;
  uint32_t src0_size = 0;
  const block_type* src1_data = nullptr;
  uint32_t src1_size = 0;

  // access source node data
  if (node->srcs().size() > 0) {
    auto src0_impl = node->src(0).impl();
    assert(type_lit == src0_impl->type());
    src0_data = reinterpret_cast<litimpl*>(src0_impl)->value().words();
    src0_size = node->src(0).size();
    if (node->srcs().size() > 1) {
      auto src1_impl = node->src(1).impl();
      assert(type_lit == src1_impl->type());
      src1_data = reinterpret_cast<litimpl*>(src1_impl)->value().words();
      src1_size = node->src(1).size();
    }
  }

  using SDBA = DefaultBitAccessor<block_type, true>;
  using UDBA = DefaultBitAccessor<block_type, false>;

  bool is_signed = node->is_signed();

  switch (node->op()) {
  case ch_op::eq:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), bv_eq<true, block_type, SDBA>(src0_data, src0_size, src1_data, src1_size));
    } else {
     bv_assign_scalar(tmp.words(), bv_eq<false, block_type, UDBA>(src0_data, src0_size, src1_data, src1_size));
    }
    break;
  case ch_op::ne:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), !bv_eq<true, block_type, SDBA>(src0_data, src0_size, src1_data, src1_size));
    } else {
     bv_assign_scalar(tmp.words(), !bv_eq<false, block_type, UDBA>(src0_data, src0_size, src1_data, src1_size));
    }
    break;
  case ch_op::lt:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), bv_lt<true, block_type, SDBA>(src0_data, src0_size, src1_data, src1_size));
    } else {
     bv_assign_scalar(tmp.words(), bv_lt<false, block_type, UDBA>(src0_data, src0_size, src1_data, src1_size));
    }
    break;
  case ch_op::gt:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), bv_lt<true, block_type, SDBA>(src1_data, src1_size, src0_data, src0_size));
    } else {
     bv_assign_scalar(tmp.words(), bv_lt<false, block_type, UDBA>(src1_data, src1_size, src0_data, src0_size));
    }
    break;
  case ch_op::le:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), !bv_lt<true, block_type, SDBA>(src1_data, src1_size, src0_data, src0_size));
    } else {
     bv_assign_scalar(tmp.words(), !bv_lt<false, block_type, UDBA>(src1_data, src1_size, src0_data, src0_size));
    }
    break;
  case ch_op::ge:
    if (is_signed) {
      bv_assign_scalar(tmp.words(), !bv_lt<true, block_type, SDBA>(src0_data, src0_size, src1_data, src1_size));
    } else {
     bv_assign_scalar(tmp.words(), !bv_lt<false, block_type, UDBA>(src0_data, src0_size, src1_data, src1_size));
    }
    break;
  case ch_op::notl:
    bv_assign_scalar(tmp.words(), bv_notl(src0_data, src0_size));
    break;
  case ch_op::andl:
    bv_assign_scalar(tmp.words(), bv_andl(src0_data, src0_size, src1_data, src1_size));
    break;
  case ch_op::orl:
    bv_assign_scalar(tmp.words(), bv_orl(src0_data, src0_size, src1_data, src1_size));
    break;
  case ch_op::inv:
    if (is_signed) {
      bv_inv<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size);
    } else {
      bv_inv<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size);
    }
    break;
  case ch_op::andb:
    if (is_signed) {
      bv_and<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_and<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::orb:
    if (is_signed) {
      bv_or<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_or<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::xorb:
    if (is_signed) {
      bv_xor<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_xor<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::andr:
    bv_assign_scalar(tmp.words(), bv_andr_vector(src0_data, src0_size));
    break;
  case ch_op::orr:
    bv_assign_scalar(tmp.words(), bv_orr_vector(src0_data, src0_size));
    break;
  case ch_op::xorr:
    bv_assign_scalar(tmp.words(), bv_xorr_vector(src0_data, src0_size));
    break;
  case ch_op::shl: {
    auto dist = bv_cast<uint32_t>(src1_data, src1_size);
    bv_shl_vector(tmp.words(), tmp.size(), src0_data, src0_size, dist);
  } break;
  case ch_op::shr: {
    auto dist = bv_cast<uint32_t>(src1_data, src1_size);
    if (is_signed) {
      bv_shr<true>(tmp.words(), tmp.size(), src0_data, src0_size, dist);
    } else {
      bv_shr<false>(tmp.words(), tmp.size(), src0_data, src0_size, dist);
    }
  } break;
  case ch_op::neg:
    if (is_signed) {
      bv_neg<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size);
    } else {
      bv_neg<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size);
    }
    break;
  case ch_op::add:
    if (is_signed) {
      bv_add<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_add<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::sub:
    if (is_signed) {
      bv_sub<true, block_type, SDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_sub<false, block_type, UDBA>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::mul:
    if (is_signed) {
      bv_mul<true>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_mul<false>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::div:
    if (is_signed) {
      bv_div<true>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_div<false>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::mod:
    if (is_signed) {
      bv_mod<true>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    } else {
      bv_mod<false>(tmp.words(), tmp.size(), src0_data, src0_size, src1_data, src1_size);
    }
    break;
  case ch_op::pad:
    if (is_signed) {
      bv_pad<true>(tmp.words(), tmp.size(), src0_data, src0_size);
    } else {
      bv_pad<false>(tmp.words(), tmp.size(), src0_data, src0_size);
    }
    break;

  default:
    CH_ABORT("invalid opcode");
  }
  return ctx_->create_literal(tmp);
}

lnodeimpl* compiler::constant_fold_bitwise(opimpl* node) {
  auto src0 = node->src(0).impl();
  auto src1 = node->src(1).impl();

  bool src0_is_zero = (type_lit == src0->type()) && reinterpret_cast<litimpl*>(src0)->value().is_zero();
  bool src0_is_ones = (type_lit == src0->type()) && reinterpret_cast<litimpl*>(src0)->value().is_ones();
  bool src1_is_zero = (type_lit == src1->type()) && reinterpret_cast<litimpl*>(src1)->value().is_zero();
  bool src1_is_ones = (type_lit == src1->type()) && reinterpret_cast<litimpl*>(src1)->value().is_ones();

  switch (node->op()) {
  case ch_op::andb:
    if (node->size() == src0->size() && src0_is_zero) {
      return src0;
    } else
    if (node->size() == src1->size() && src1_is_zero) {
      return src1;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src0_is_ones) {
      return src1;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src1_is_ones) {
      return src0;
    }
    break;
  case ch_op::orb:
    if (node->size() == src1->size() && src0_is_zero) {
      return src1;
    } else
    if (node->size() == src0->size() && src1_is_zero) {
      return src0;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src0_is_ones) {
      return src0;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src1_is_ones) {
      return src1;
    }
    break;
  case ch_op::xorb:
    if (node->size() == src1->size() && src0_is_zero) {
      return src1;
    } else
    if (node->size() == src0->size() && src1_is_zero) {
      return src0;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src0_is_ones) {
      auto inv = ctx_->create_node<opimpl>(ch_op::inv, node->size(), false, src1, node->sloc());
      this->map_add_node_srcs(inv);
      return inv;
    } else
    if (node->size() == src0->size() && node->size() == src1->size() && src1_is_ones) {
      auto inv = ctx_->create_node<opimpl>(ch_op::inv, node->size(), false, src0, node->sloc());
      this->map_add_node_srcs(inv);
      return inv;
    }
    break;
  default:
    break;
  }
  return nullptr;
}

lnodeimpl* compiler::constant_fold(selectimpl* node) {
  if (node->has_key()) {
    auto key_impl = node->key().impl();
    assert(type_lit == key_impl->type());
    auto key_data = reinterpret_cast<litimpl*>(key_impl)->value().words();
    auto key_size = key_impl->size();

    uint32_t i = 1;
    for (uint32_t l = node->srcs().size() - 1; i < l; i += 2) {
      auto src_impl = node->src(i).impl();
      assert(type_lit == src_impl->type());
      assert(key_size == src_impl->size());
      auto src_data = reinterpret_cast<litimpl*>(src_impl)->value().words();
      if (bv_eq<false, block_type, ClearBitAccessor<block_type>>(key_data, key_size, src_data, key_size)) {
        return node->src(i+1).impl();
      }
    }
    return node->src(i).impl();
  } else {
    uint32_t i = 0;
    for (uint32_t l = node->srcs().size() - 1; i < l; i += 2) {
      auto src_impl = node->src(i).impl();
      assert(type_lit == src_impl->type());
      auto src_data = reinterpret_cast<litimpl*>(src_impl)->value().words();
      if (static_cast<bool>(src_data[0])) {
        return node->src(i+1).impl();
      }
    }
    return node->src(i).impl();
  }
}

bool compiler::subexpressions_elimination() {
  if (platform::self().cflags() & cflags::disable_cse)
    return false;

  CH_DBG(3, "Begin Compiler::CSE\n");

  bool changed = false;

  std::vector<node_list_view::iterator> deleted_list;
  std::unordered_set<cse_key_t, cse_hash_t> cse_table;

  auto apply_cse = [&](const node_list_view::iterator& it)->bool {
    auto node = *it;
    switch (node->type()) {
    default:
      return false;
    case type_cd:
    case type_proxy:
    case type_sel:
    case type_op:
    case type_reg:
      break;
    }
    auto p_it = cse_table.find(node);
    if (p_it != cse_table.end()) {      
      this->map_replace_target(node, p_it->node);
      this->map_delete(node);
      deleted_list.push_back(it);
      return true;
    }
    cse_table.insert(node);
    return false;
  };

  auto& nodes = ctx_->nodes();

  for (auto it = nodes.begin(), end = nodes.end(); it != end;) {
    changed |= apply_cse(it++);
  }

  if (changed) {
    for (auto it = deleted_list.begin(), end = deleted_list.end(); it != end;) {
      ctx_->delete_node(*it++);
    }
    deleted_list.clear();
    cse_table.clear();
  }

  CH_DBG(3, "End Compiler::CSE\n");

  return changed;
}

bool compiler::prune_identity_proxies() {
  if (platform::self().cflags() & cflags::disable_pip)
    return false;

  CH_DBG(3, "Begin Compiler::PIP\n");

  bool changed = false;

  for (auto it = ctx_->proxies().begin(),
       end = ctx_->proxies().end(); it != end;) {
    auto proxy = reinterpret_cast<proxyimpl*>(*it++);
    if (!proxy->is_identity())
      continue;
    // replace identity proxy's uses with proxy's source
    this->map_replace_target(proxy, proxy->src(0).impl());
    this->map_delete(proxy);
    // delete proxy
    ctx_->delete_node(proxy);
    changed = true;
  }

  CH_DBG(3, "End Compiler::PIP\n");

  return changed;
}

bool compiler::proxies_coalescing() {
  if (platform::self().cflags() & cflags::disable_pcx)
    return false;

  CH_DBG(3, "Begin Compiler::PCX\n");

  auto is_muli_range = [&](proxyimpl* proxy, uint32_t offset, uint length) {
    assert(offset + length <= proxy->size());
    auto end = offset + length;
    for (auto& range : proxy->ranges()) {
      auto range_end = range.dst_offset + range.length;
      if (range_end <= offset
      || end <= range.dst_offset)
        continue;
      return (offset < range.dst_offset || end > range_end);
    }
    return false;
  };

  auto are_adjacent_sources = [&](proxyimpl* proxy,
                                  const proxyimpl::range_t& r0,
                                  const proxyimpl::range_t& r1) {
    if (r0.src_idx == r1.src_idx)
      return false;
    auto s0 = proxy->src(r0.src_idx).impl();
    auto s1 = proxy->src(r1.src_idx).impl();
    auto p0 = reinterpret_cast<proxyimpl*>(s0);
    auto p1 = reinterpret_cast<proxyimpl*>(s1);
    if (s0->type() != type_proxy
     || s1->type() != type_proxy
     || p0->ranges().size() > 1
     || p1->ranges().size() > 1)
      return false;
    auto& p0r = p0->range(0);
    auto& p1r = p1->range(0);
    return (p0->src(p0r.src_idx).id() == p1->src(p1r.src_idx).id()
         && r0.src_offset + r0.length == p0->size()
         && 0 == r1.src_offset
         && p0r.src_offset + p0r.length == p1r.src_offset);
  };

  auto is_useful_proxy = [&](proxyimpl* proxy, proxyimpl* src_proxy) {
    if (src_proxy->is_identity())
      return false;
    for (uint32_t i = 0, n = proxy->ranges().size(); i < n; ++i) {
      auto& range = proxy->range(i);
      if (proxy->src(range.src_idx).id() != src_proxy->id())
        continue;
      if (range.length != src_proxy->size()
       && !is_muli_range(src_proxy, range.src_offset, range.length))
        return false;
      if (i > 0) {
        if (are_adjacent_sources(proxy, proxy->range(i-1), range))
          return false;
      }
      if (i + 1 < n) {
        if (are_adjacent_sources(proxy, range, proxy->range(i+1)))
          return false;
      }
    }
    return true;
  };

  bool changed = false;

  std::set<proxyimpl*> detached_list;
  bool found;
  do {
    std::unordered_map<proxyimpl*, std::vector<proxyimpl::range_t>> src_proxies;
    std::unordered_map<const lnode*, lnodeimpl*> src_nodes;
    found = false;

    for (auto it = ctx_->proxies().begin(),
         end = ctx_->proxies().end(); it != end;) {
      auto dst_proxy = reinterpret_cast<proxyimpl*>(*it++);

      src_proxies.clear();

      for (auto& src : dst_proxy->srcs()) {
        if (type_proxy != src.impl()->type())
          continue;        

        auto src_proxy = reinterpret_cast<proxyimpl*>(src.impl());
        if (src_proxies.count(src_proxy))
          continue;

        // skip useful proxies
        auto use_count = node_map_.at(src_proxy->id()).size();
        if (use_count > 1
         && is_useful_proxy(dst_proxy, src_proxy))
          continue;

        auto& upd_ranges = src_proxies[src_proxy];
        for (auto& dst_range : dst_proxy->ranges()) {
          if (dst_proxy->src(dst_range.src_idx).id() != src_proxy->id())
            continue;
          for (auto& src_range : src_proxy->ranges()) {
            int32_t delta  = src_range.dst_offset - dst_range.src_offset;
            uint32_t start = std::max<int32_t>(dst_range.dst_offset + delta, 0);
            uint32_t end   = std::max<int32_t>(dst_range.dst_offset + delta + src_range.length, 0);
            interval_t src_iv{start, end};
            interval_t dst_iv{dst_range.dst_offset, dst_range.dst_offset + dst_range.length};
            auto shared_iv = dst_iv.intersection(src_iv);
            if (shared_iv.start == shared_iv.end)
              continue;
            proxyimpl::range_t upd_range;
            upd_range.src_idx    = src_range.src_idx;
            upd_range.dst_offset = shared_iv.start;
            upd_range.src_offset = src_range.src_offset - std::min(delta, 0);
            upd_range.length     = shared_iv.end - shared_iv.start;
            upd_ranges.emplace_back(upd_range);
          }
        }
      }

      if (!src_proxies.empty()) {
        // capture source nodes
        src_nodes.clear();
        for (auto& src : dst_proxy->srcs()) {
          src_nodes[&src] = src.impl();
        }

        for (auto src_proxy_p : src_proxies) {
          auto src_proxy = src_proxy_p.first;
          for (auto range : src_proxy_p.second) {
            dst_proxy->add_source(
              range.dst_offset,
              src_proxy->src(range.src_idx),
              range.src_offset,
              range.length);
          }
          detached_list.insert(src_proxy);
        }

        // update node map to reflect modified nodes
        for (auto& src : dst_proxy->srcs()) {
          auto it = src_nodes.find(&src);
          if (it != src_nodes.end()) {
            if (src.impl() != it->second) {
              // src still exists but its value changed
              node_map_.at(it->second->id()).erase(&src);
              node_map_.at(src.id()).emplace(&src);
            }
            src_nodes.erase(it); // remove from list
          } else {
            // new src was added
            node_map_.at(src.id()).emplace(&src);
          }
        }

        // unregister remaining deleted nodes
        for (auto& src_p : src_nodes) {
          node_map_.at(src_p.second->id()).erase(src_p.first);
        }

        found = true;
        changed = true;
      }
    }
  } while (found);

  for (auto d_it = detached_list.rbegin(), end = detached_list.rend(); d_it != end;) {
    auto node = *d_it++;
    auto m_it = node_map_.find(node->id());
    if (m_it != node_map_.end()) {
      if (m_it->second.empty()) {
        this->map_delete(node);
        ctx_->delete_node(node);
      }
    }
  }  

  CH_DBG(3, "End Compiler::PCX\n");

  return changed;
}

bool compiler::branch_coalescing() {
  if (platform::self().cflags() & cflags::disable_bro)
    return false;

  CH_DBG(3, "Begin Compiler::BRO\n");

  bool changed = false;

  //--
  auto remove_node_src = [&](lnodeimpl* node, uint32_t index) {
    auto impl0 = node->src(index + 0).impl();
    auto impl1 = node->src(index + 1).impl();

    this->map_remove_node_srcs(node);
    node->remove_src(index + 1); // higher index first
    node->remove_src(index + 0);
    this->map_add_node_srcs(node);

    if (0 == node_map_.count(impl0->id())) {
      ctx_->delete_node(impl0);
    }

    if (0 == node_map_.count(impl1->id())) {
      ctx_->delete_node(impl1);
    }

    changed = true;
  };

  //--
  auto coalesce_branch = [&](selectimpl* sel)->lnodeimpl* {
    auto has_key = sel->has_key();
    auto start = has_key ? 1 : 0;

    // skip paths with value equal to default value
    {
      auto df_value = sel->srcs().back();
      lnodeimpl* skip_pred = nullptr;
      std::vector<uint32_t> deleted; // ensure deletion from high to low indices
      for (uint32_t i = start, n = sel->srcs().size() - 1; i < n; i += 2) {
        auto pred  = sel->src(i+0).impl();
        auto value = sel->src(i+1).impl();
        if (value == df_value) {
          if (!has_key) {
            if (skip_pred) {
              skip_pred = ctx_->create_node<opimpl>(ch_op::orb, 1, false, skip_pred, pred, sel->sloc());
              this->map_add_node_srcs(skip_pred);
            } else {
              skip_pred = pred;
            }
          }
          deleted.push_back(i);
        } else {
          if (skip_pred) {
            skip_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, skip_pred, sel->sloc());
            this->map_add_node_srcs(skip_pred);
            pred = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred, skip_pred, sel->sloc());
            this->map_add_node_srcs(pred);

            this->map_remove_node_srcs(sel);
            sel->set_src(i+0, pred);
            this->map_add_node_srcs(sel);

            skip_pred = nullptr;
          }
        }
      }

      for (auto it = deleted.rbegin(); it != deleted.rend();) {
        remove_node_src(sel, *it++);
      }
    }

    // merge conditional select blocks with same values
    if (!has_key) {
      ordered_set<uint32_t> dups; // ensure deletion from high to low indices
      for (uint32_t i = 0, n = sel->srcs().size() - 1; i < n; i += 2) {
        auto pred1  = sel->src(i+0).impl();
        auto value1 = sel->src(i+1).impl();
        auto m = i;

        for (uint32_t j = i + 2; j < n; j += 2) {
          auto value2 = sel->src(j+1).impl();
          if (value2 == value1) {
            dups.insert(j);
            m = j;
          }
        }

        if (!dups.empty()) {
          lnodeimpl* skip_pred = nullptr;
          for (uint32_t j = i + 2; j < m; j += 2) {
            if (dups.count(j) != 0)
              continue;
            auto pred2 = sel->src(j+0).impl();
            if (skip_pred) {
              skip_pred = ctx_->create_node<opimpl>(ch_op::orb, 1, false, skip_pred, pred2, sel->sloc());
              this->map_add_node_srcs(skip_pred);
            } else {
              skip_pred = pred2;
            }
          }

          for (auto dup : dups) {
            pred1 = ctx_->create_node<opimpl>(ch_op::orb, 1, false, pred1, sel->src(dup).impl(), sel->sloc());
            this->map_add_node_srcs(pred1);
          }

          if (skip_pred) {
            skip_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, skip_pred, sel->sloc());
            this->map_add_node_srcs(skip_pred);
            pred1 = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred1, skip_pred, sel->sloc());
            this->map_add_node_srcs(pred1);
          }

          this->map_remove_node_srcs(sel);
          sel->set_src(i+0, pred1);
          this->map_add_node_srcs(sel);

          for (auto it = dups.rbegin(); it != dups.rend();) {
            remove_node_src(sel, *it++);
            n -= 2; // update size
          }

          dups.clear();
        }
      }
    }

    if (1 == sel->srcs().size()) {
      return sel->src(0).impl();
    }

    // coallesce cascading ternary branches sharing the same default value
    // p2 ? (p1 ? t1 : f1) : f1 => (p1 & p2) ? t1 : f1;
    uint32_t sel_num_srcs = has_key ? 4 : 3;
    if (sel->srcs().size() == sel_num_srcs) {
      auto _true = dynamic_cast<selectimpl*>(sel->src(sel_num_srcs-2).impl());
      if (_true) {
        auto true_has_key = _true->has_key();
        uint32_t true_num_srcs = true_has_key ? 4 : 3;
        if (_true->num_srcs() == true_num_srcs
         && _true->src(true_num_srcs-1) == sel->src(sel_num_srcs-1).impl()) {
          // combine predicates
          auto pred0 = sel->src(sel_num_srcs-3).impl();
          if (has_key) {
            pred0 = ctx_->create_node<opimpl>(ch_op::eq, 1, false, sel->key().impl(), pred0, sel->sloc());
            this->map_add_node_srcs(pred0);
          }
          auto pred1 = _true->src(true_num_srcs-3).impl();
          if (true_has_key) {
            // create predicate
            pred1 = ctx_->create_node<opimpl>(ch_op::eq, 1, false, pred1, _true->src(1).impl(), sel->sloc());
            this->map_add_node_srcs(pred1);
          }
          auto pred = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred0, pred1, sel->sloc());
          this->map_add_node_srcs(pred);

          this->map_remove_node_srcs(_true);
          if (true_has_key) {
            _true->remove_key();
          }
          _true->set_src(0, pred);
          this->map_add_node_srcs(_true);

          return _true;
        }
      }
    }

    // convert tenary switches to branches
    if (has_key && 4 == sel->srcs().size()) {
      auto pred = ctx_->create_node<opimpl>(ch_op::eq, 1, false, sel->src(0).impl(), sel->src(1).impl(), sel->sloc());
      this->map_add_node_srcs(pred);
      this->map_remove_node_srcs(sel);
      sel->remove_key();
      sel->set_src(0, pred);
      this->map_add_node_srcs(sel);
      changed = true;
      return nullptr;
    }

    // eliminate ternary branches with constant boolean sources
    if (1 == sel->size()
     && 3 == sel->srcs().size()
     && type_lit == sel->src(1).impl()->type()
     && type_lit == sel->src(2).impl()->type()) {
      if (static_cast<bool>(reinterpret_cast<litimpl*>(sel->src(1).impl())->value())) {
        return sel->src(0).impl();
      } else {
        auto pred = sel->src(0).impl();
        auto inv_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, pred, sel->sloc());
        this->map_add_node_srcs(inv_pred);
        return inv_pred;
      }
    }

    return nullptr;
  };

  for (auto it = ctx_->sels().begin(), end = ctx_->sels().end(); it != end;) {
    auto sel = reinterpret_cast<selectimpl*>(*it++);
    auto x = coalesce_branch(sel);
    if (x) {
      map_replace_target(sel, x);
      this->map_delete(sel);
      ctx_->delete_node(sel);
      changed = true;
    }
  }

  return changed;
}

void compiler::create_merged_context(context* ctx) {
  //--
  std::list<std::string> node_path;

  //--
  auto full_name = [&](lnodeimpl* node) {
    std::stringstream ss;
    for (auto p : node_path) {
      ss << p << ".";
    }
    ss << node->name();
    return ss.str();
  };

  //--
  std::function<void (context*, clone_map&)> visit = [&](context* curr, clone_map& map) {
    //--
    std::unordered_map<proxyimpl*, lnodeimpl*> placeholders;

    //--
    auto ensure_placeholder = [&](const lnode& node) {
      //assert(node.impl()->type() != type_undef);
      if (map.count(node.id()) != 0)
        return;
      auto placeholder = ctx_->create_node<proxyimpl>(node.size(), node.sloc(), node.name());
      placeholders[placeholder] = node.impl();
      map[node.id()] = placeholder;
    };

    //--
    for (auto node : curr->nodes()) {
      switch (node->type()) {
      case type_bind: {
        auto bind = reinterpret_cast<bindimpl*>(node);
        clone_map sub_map;
        for (auto& s : bind->srcs()) {
          auto bs = reinterpret_cast<bindportimpl*>(s.impl());
          ensure_placeholder(bs->src(0));
          sub_map[s.id()] = map.at(bs->src(0).id());
        }
        node_path.push_back(stringf("%s_%d", bind->module()->name().c_str(), bind->id()));
        visit(bind->module(), sub_map);
        node_path.pop_back();
        for (auto& o : bind->outputs()) {
          auto bo = reinterpret_cast<bindportimpl*>(o.impl());
          map[o.id()] = sub_map.at(bo->ioport().id());
        }
      } break;
      case type_input: {
        auto input = reinterpret_cast<inputimpl*>(node);
        if (curr->parent()) {
          for (auto p : input->bindports()) {
            auto it = map.find(p->id());
            if (it != map.end()) {
              map[input->id()] = it->second;
              break;
            }
          }
        } else {
          lnodeimpl* eval_node;
          if (input->name() == "clk") {
            eval_node = ctx_->current_clock(input->sloc());
          } else if (input->name() == "reset") {
            eval_node = ctx_->current_reset(input->sloc());
          } else {
            eval_node = input->clone(ctx_, map);
            eval_node->name() = full_name(eval_node);
          }
          map[input->id()] = eval_node;
        }
      } break;
      case type_output: {
        auto output = reinterpret_cast<outputimpl*>(node);
        ensure_placeholder(output->src(0));
        if (curr->parent()) {
          map[output->id()] = map.at(output->src(0).id());
        } else {
          auto eval_node = output->clone(ctx_, map);
          eval_node->name() = full_name(eval_node);
          map[output->id()] = eval_node;
        }
      } break;
      case type_mem: {
        auto eval_node = node->clone(ctx_, map);
        map[node->id()] = eval_node;
      } break;
      case type_tap: {
        auto tap = reinterpret_cast<tapimpl*>(node);
        ensure_placeholder(tap->src(0));
        auto eval_node = tap->clone(ctx_, map);
        eval_node->name() = full_name(eval_node);
        map[tap->id()] = eval_node;
      } break;
      case type_bindin:
      case type_bindout:
        // skip
        break;
      default: {
        // assign placeholders
        for (auto& src : node->srcs()) {
          ensure_placeholder(src);
        }
        auto eval_node = node->clone(ctx_, map);
        map[node->id()] = eval_node;
      } break;
      }
    }

    // resolve placeholders
    for (auto placeholder : placeholders) {
      auto src = map.at(placeholder.second->id());
      placeholder.first->add_source(0, src, 0, src->size());
    }
  };

  CH_DBG(2, "create merged context for %s (#%d) ...\n", ctx->name().c_str(), ctx->id());

  clone_map map;
  node_path.push_back(stringf("%s_%d", ctx->name().c_str(), ctx->id()));
  visit(ctx, map);

  node_path.pop_back();
}

void compiler::build_eval_list(std::vector<lnodeimpl*>& eval_list) {
  std::unordered_set<uint32_t> visited_nodes;
  std::unordered_set<uint32_t> cyclic_nodes;
  std::unordered_set<lnodeimpl*> update_list;
  std::unordered_set<lnodeimpl*> uninitialized_regs;

  /*//--
  std::unordered_set<uint32_t> relocated_nodes;
  auto relocate_node = [&](uint32_t nidx) {
    auto node = eval_list.at(nidx);
    if (type_cd == node->type()
     || is_snode_type(node->type())
     || relocated_nodes.count(node->id()))
        return;

    for (auto& src : node->srcs()) {
      if (type_lit != src.impl()->type())
        return;
    }

    for (uint32_t i = nidx + 1; i < eval_list.size(); ++i) {
      auto curr = eval_list.at(i);
      bool is_used = false;
      for (auto& src : node->srcs()) {
        if (src.id() == curr->id()) {
          is_used = true;
          break;
        }
      }
      if (!is_used) {
        for (auto& src : curr->srcs()) {
          if (src.id() == node->id()) {
            is_used = true;
            break;
          }
        }
      }
      if (is_used) {
        uint32_t k = i - 1;
        if (k > nidx) {
          // move node closer to use
          for (uint32_t j = nidx; j < k; ++j) {
            eval_list.at(j) = eval_list.at(j+1);
          }
          eval_list.at(k) = node;
          relocated_nodes.insert(node->id());
        }
        return;
      }
    }
  };*/

  //--
  std::function<bool (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node)->bool {
    if (visited_nodes.count(node->id())) {
      // if a node depends on an update node, it also needs to be updated.
      return (update_list.count(node) != 0);
    }

    // check for cycles
    if (cyclic_nodes.count(node->id())) {
      // handling register cycles
      if (is_snode_type(node->type())) {
        // Detect uninitialized registers
        if (type_reg == node->type()
         && !reinterpret_cast<regimpl*>(node)->has_init_data())
          uninitialized_regs.insert(node);
        return true;
      }
#define LCOV_EXCL_START
      if (platform::self().cflags() & cflags::dump_ast) {
        for (auto _node : eval_list) {
          std::cerr << _node->ctx()->id() << ": ";
          _node->print(std::cerr);
          std::cerr << std::endl;
        }
      }
      fprintf(stderr, "error: found a cycle on variable %s\n", node->debug_info().c_str());
      std::abort();
      return false;
#define LCOV_EXCL_END
    }
    cyclic_nodes.insert(node->id());

    // visit source nodes
    bool update = false;
    for (auto& src : node->srcs()) {
      update |= dfs_visit(src.impl());
    }
    if (update) {
      // a cycle exists in dependent path, this node should be updated
      update_list.insert(node);
    }

    eval_list.push_back(node);
    visited_nodes.insert(node->id());

    return update;
  };

  CH_DBG(2, "build evaluation list for %s (#%d) ...\n", ctx_->name().c_str(), ctx_->id());

  assert(0 == ctx_->bindings().size());

  // move system time evaluation to the end
  auto sys_time = ctx_->sys_time();
  if (sys_time) {
    visited_nodes.insert(sys_time->id());
  }

  // enable cycle detection for sequential nodes
  for (auto node : ctx_->snodes()) {
    cyclic_nodes.insert(node->id());
  }

  // visit clock cdomain nodes
  for (auto node : ctx_->cdomains()) {
    dfs_visit(node);
  }

  // visit sequential nodes dependencies
  for (auto node : ctx_->snodes()) {
    for (auto& src : node->srcs()) {
      dfs_visit(src.impl());
    }
  }

  {
    // make a copy of the update list and empty it
    std::unordered_set<lnodeimpl*> update_list2;
    std::swap(update_list2, update_list);

    // disable cycle detection for sequential nodes
    for (auto node : ctx_->snodes()) {
      cyclic_nodes.erase(node->id());
    }

    // visit sequential nodes
    auto old_size = eval_list.size();
    for (auto node : ctx_->snodes()) {
      dfs_visit(node);
    }

    // sort recently inserted sequential node in reverse dependency order
    std::reverse(eval_list.begin() + old_size, eval_list.end());

    // invalidate all update nodes to force re-insertion
    for (auto node : update_list2) {
      cyclic_nodes.erase(node->id());
      visited_nodes.erase(node->id());
    }
    update_list2.clear();
  }

  // visit output nodes
  for (auto node : ctx_->outputs()) {
    dfs_visit(node);
  }
  for (auto node : ctx_->taps()) {
    dfs_visit(node);
  }
  for (auto node : ctx_->gtaps()) {
    dfs_visit(node);
  }

  if (sys_time) {
    visited_nodes.erase(sys_time->id());
    dfs_visit(sys_time);
  }

  /*// compress nodes distance
  for (uint32_t i = 0; i < eval_list.size(); ++i) {
    relocate_node(i);
  }*/

  if (platform::self().cflags() & cflags::dump_ast) {
    for (auto node : eval_list) {
      std::cout << node->ctx()->id() << ": ";
      node->print(std::cerr);
      std::cout << std::endl;
    }
    std::cout << "total nodes: " << eval_list.size() << std::endl;
  }

  if (!uninitialized_regs.empty()
   && (platform::self().cflags() & cflags::check_reg)) {
    for (auto node : uninitialized_regs) {
      fprintf(stderr, "warning: uninitialized register %s\n", node->debug_info().c_str());
    }
  }
}

bool compiler::build_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id) {
  std::unordered_set<uint32_t> visited_nodes;
  bool has_data_nodes = false;

  std::function<bool (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node)->bool {
    if (visited_nodes.count(node->id())) {
      return (out.count(node->id()) != 0);
    }
    visited_nodes.emplace(node->id());

    auto type = node->type();
    bool changed = false;

    if (is_snode_type(type)) {
      if (cd_id == get_snode_cd(node)->id())
        return false;
      // update changeset here in case there is a cycle with the source nodes
      out.emplace(node->id());
      changed = true;
    } else
    if (type_output == type
     || type_tap == type) {
      // mark constant outputs as changed      
      changed = (type_lit == node->src(0).impl()->type());
    }

    switch (type) {
    case type_cd:
    case type_input:
    case type_time:
    case type_print:
      changed = true;
      [[fallthrough]];
    default:
      // visit source nodes
      for (auto& src : node->srcs()) {
        changed |= dfs_visit(src.impl());
      }
      break;
    }

    if (changed) {
      out.emplace(node->id());

      switch (node->type()) {
      case type_output:
      case type_tap:
      case type_time:
      case type_assert:
      case type_print:
        break;
      default:
        has_data_nodes = true;
        break;
      }
    }

    return changed;
  };

  // visit output nodes`
  for (auto node : ctx->outputs()) {
    dfs_visit(node);
  }
  for (auto node : ctx->taps()) {
    dfs_visit(node);
  }
  for (auto node : ctx->gtaps()) {
    dfs_visit(node);
  }
  auto sys_time = ctx->sys_time();
  if (sys_time) {
    dfs_visit(sys_time);
  }

  return !has_data_nodes;
}

///////////////////////////////////////////////////////////////////////////////

void compiler::map_initialize() {
  for (auto node : ctx_->nodes()) {
    this->map_add_node_srcs(node);
  }
}

void compiler::map_add_node_srcs(lnodeimpl* node) {
  for (auto& src : node->srcs()) {
    node_map_[src.id()].emplace(&src);
  }
}

void compiler::map_remove_node_srcs(lnodeimpl* node) {
  [[maybe_unused]] size_t n;
  for (auto& src : node->srcs()) {
    auto it = node_map_.find(src.id());
    assert(it != node_map_.end());
    n = it->second.erase(&src);
    assert(n);
  }
}

void compiler::map_delete(lnodeimpl* node) {
  map_remove_node_srcs(node);
  auto it = node_map_.find(node->id());
  assert(it != node_map_.end());
  assert(it->second.empty());
  node_map_.erase(it);
}

void compiler::map_replace_target(lnodeimpl* from, lnodeimpl* to) {
  // update all nodes pointing to source to now point to target
  // and unregister source's references
  assert(from != to);
  auto from_it = node_map_.find(from->id());
  assert(from_it != node_map_.end());
  auto& to_refs = node_map_[to->id()];
  for (auto node : from_it->second) {
    *const_cast<lnode*>(node) = to;
    to_refs.emplace(node);
  }
  from_it->second.clear();
}
