#include "compile.h"
#include "litimpl.h"
#include "cdimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "opimpl.h"
#include "selectimpl.h"
#include "proxyimpl.h"
#include "ioimpl.h"
#include "bindimpl.h"
#include "timeimpl.h"
#include "context.h"
#include "ordered_set.h"
#include "interval.h"
#include "mem.h"

using namespace ch::internal;

namespace ch {
namespace internal {

struct placeholder_user_t {
  lnodeimpl* node;
  uint32_t src_idx;

  placeholder_user_t(uint32_t src_idx)
    : node(nullptr)
    , src_idx(src_idx)
  {}

  placeholder_user_t(lnodeimpl* node, uint32_t src_idx)
    : node(node)
    , src_idx(src_idx)
  {}
};

class placeholder_node : public lnodeimpl {
public:
  placeholder_node(uint32_t id,
                   uint32_t size,
                   context* ctx,
                   const std::string& name,
                   const source_location& sloc)
    : lnodeimpl(id, type_none, size, ctx, name, sloc)
  {}

  lnodeimpl* clone(context*, const clone_map&) const override {
    assert(false);
    return nullptr;
  }

  std::list<placeholder_user_t> users;
};

struct cse_key_t {

  lnodeimpl* node;

  cse_key_t(lnodeimpl* p_node) : node(p_node) {}

  auto operator==(const cse_key_t& other) const {
    return this->node->equals(*other.node);
  }

  struct hash_type {
    std::size_t operator()(const cse_key_t& key) const {
      return key.node->hash();
    }
  };
};

class node_tracker {
public:
  node_tracker(context* ctx) : ctx_(ctx) {
    size_ = ctx->nodes().size();
  }

  size_t deleted() {
    auto cur_size = ctx_->nodes().size();
    auto count = (cur_size < size_) ? (size_ - cur_size) : 0;
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

class node_deleter {
public:
  node_deleter(context* ctx) : ctx_(ctx) {}

  void add(lnodeimpl* node) {
    assert(nullptr == node->users());
    nodes_.emplace_back(node);
  }

  void apply() {
    for (auto node : nodes_) {
      this->delete_node(node);
    }
  }

private:

  void delete_node(lnodeimpl* node) {
    if (deleted_.count(node))
      return;

    // gather source nodes
    std::vector<lnodeimpl*> srcs;
    for (auto& src : node->srcs()) {
      srcs.emplace_back(src.impl());
    }

    // delete node
    ctx_->delete_node(node);
    deleted_.emplace(node);

    // delete unreferenced source nodes
    for (auto src : srcs) {
      if (deleted_.count(src)
       || src->users() != nullptr)
        continue;
      this->delete_node(src);
    }
  }

  std::vector<lnodeimpl*> nodes_;
  std::unordered_set<lnodeimpl*> deleted_;
  context* ctx_;
};

}
}

compiler::compiler(context* ctx) : ctx_(ctx) {}

void compiler::optimize() {
  size_t cfo_total(0), dce_total(0), cse_total(0), pip_total(0), pcx_total(0), bro_total(0), rpo_total(0);

  CH_DBG(2, "compiling %s (#%d) ...\n", ctx_->name().c_str(), ctx_->id());

  node_tracker tracker(ctx_);
  auto orig_num_nodes = tracker.current();

  this->dead_code_elimination();
  dce_total = tracker.deleted();

  ctx_->dump_cfg(std::cout);

  // run optimization passes
  bool changed =true;
  if (ctx_->parent()
   && (platform::self().cflags() & cflags::merged_only_opt) != 0) {
    changed = false;
  }

  for (;changed;) {
    changed = this->prune_identity_proxies();
    ctx_->dump_cfg(std::cout);
    pip_total += tracker.deleted();
    ctx_->dump_cfg(std::cout);
    changed |= this->proxies_coalescing();
    ctx_->dump_cfg(std::cout);
    pcx_total += tracker.deleted();
    ctx_->dump_cfg(std::cout);
    changed |= this->constant_folding();
    ctx_->dump_cfg(std::cout);
    cfo_total += tracker.deleted();
    ctx_->dump_cfg(std::cout);
    changed |= this->subexpressions_elimination();
    ctx_->dump_cfg(std::cout);
    cse_total += tracker.deleted();
    ctx_->dump_cfg(std::cout);
    changed |= this->branch_coalescing();
    ctx_->dump_cfg(std::cout);
    bro_total += tracker.deleted();
    ctx_->dump_cfg(std::cout);
    changed |= this->register_promotion();
    ctx_->dump_cfg(std::cout);
    rpo_total += tracker.deleted();
  }

#ifndef NDEBUG
  // dump nodes
  if (platform::self().cflags() & cflags::dump_cfg) {
    ctx_->dump_cfg(std::cout);
  }

  // dump tap's CFG
  if (platform::self().cflags() & cflags::debug_cfg) {
    for (auto node : ctx_->taps()) {
      std::cout << "CFG dump for tap variable: " << node->name() << std::endl;
      ctx_->debug_cfg(node, std::cout);
    }
  }
#else
  CH_UNUSED(orig_num_nodes, dce_total);
#endif

  CH_DBG(2, "*** deleted %lu DCE nodes\n", dce_total);
  CH_DBG(2, "*** deleted %lu PIP nodes\n", pip_total);
  CH_DBG(2, "*** deleted %lu PCX nodes\n", pcx_total);
  CH_DBG(2, "*** deleted %lu CFO nodes\n", cfo_total);
  CH_DBG(2, "*** deleted %lu CSE nodes\n", cse_total);
  CH_DBG(2, "*** deleted %lu BRO nodes\n", bro_total);
  CH_DBG(2, "*** deleted %lu RPO nodes\n", rpo_total);
  CH_DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  CH_DBG(2, "After optimization: %lu\n", tracker.current());
}

bool compiler::dead_code_elimination() {
  CH_DBG(3, "Begin Compiler::DCE\n");

  bool changed = false;

  ordered_set<lnodeimpl*> live_nodes;
  std::unordered_map<uint32_t, std::unordered_set<proxyimpl*>> proxy_users;
  std::unordered_map<proxyimpl*, std::unordered_map<uint32_t, interval_t>> used_proxy_sources;
  ordered_set<proxyimpl*> sparse_proxies;

  //--
  auto remove_unused_proxy_sources = [&](proxyimpl* proxy, uint32_t src_idx) {
    // gather unused source positions
    std::vector<range_t> unused_pos;
    for (auto& range : proxy->ranges()) {
      if (range.src_idx == src_idx) {
        unused_pos.emplace_back(range.dst_offset, range.dst_offset + range.length);
      }
    }

    // remove unused source
    proxy->erase_source(src_idx, false);
    sparse_proxies.insert(proxy);

    // update proxy users' ranges
    for (auto use : proxy_users.at(proxy->id())) {
     uint32_t src_idx = 0;
      for (uint32_t n = use->num_srcs(); src_idx < n; ++src_idx) {
        if (use->src(src_idx).id() == proxy->id())
          break;
      }

      assert(src_idx != use->num_srcs());
      for (auto it = use->ranges().begin(); it != use->ranges().end();) {
        if (it->src_idx != src_idx) {
          ++it;
          continue;
        }

        interval_t s_iv(it->src_offset, it->src_offset + it->length);
        for (auto& pos : unused_pos) {
          s_iv -= pos;
        }

        // has the interval changed?
        if (s_iv.ranges.size() != 1
         || s_iv.ranges[0].start != it->src_offset
         || s_iv.ranges[0].end != it->src_offset + it->length) {
          // insert new ranges
          for (auto& r : s_iv.ranges) {
            proxyimpl::range_t nr;
            nr.src_idx = src_idx;
            nr.src_offset = r.start;
            nr.dst_offset += (r.start - it->src_offset);
            nr.length = r.end - r.start;
            auto ret = use->ranges().insert(it, nr);
            it = std::next(ret);
          }

          // remove original range
          it = use->ranges().erase(it);
        } else {
          ++it;
        }
      }

      if (use->has_sparse_range()) {
        sparse_proxies.insert(use);
      }
    }
  };

  //--
  auto fix_sparse_proxies = [&](proxyimpl* proxy) {
    uint32_t size = 0;
    for (auto& pr : proxy->ranges()) {
      auto delta = pr.dst_offset - size;
      if (delta != 0) {
        for (auto use : proxy_users.at(proxy->id())) {
          for (auto& ur : use->ranges()) {
            if (use->src(ur.src_idx).id() != proxy->id())
              continue;

            range_t _ur(ur.src_offset, ur.src_offset + ur.length);
            range_t _pr(pr.dst_offset, pr.dst_offset + pr.length);
            if (!_ur.overlaps(_pr))
              continue;

            if (ur.src_offset >= delta) {
              ur.src_offset -= delta;
            } else {
              auto d = delta - ur.src_offset;
              ur.src_offset = 0;
              ur.dst_offset += d;
              ur.length -= d;
            }
          }
        }
        assert(pr.dst_offset >= delta);
        pr.dst_offset -= delta;
      }
      size += pr.length;
    }
    proxy->resize(size);
  };

  //--
  auto create_bypass = [&](lnodeimpl* node) {
    return ctx_->create_bypass(node);
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
    if (node->size() != 0)
      continue;
    live_nodes.insert(node);
  }
  for (auto node : ctx_->ext_nodes()) {
    if (nullptr == node->users())
      continue;
    live_nodes.insert(node);
  }

  // build live nodes set
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  while (!working_set.empty()) {
    auto node = working_set.front();
    auto proxy = dynamic_cast<proxyimpl*>(node);

    auto use_info_it = (proxy != nullptr) ? used_proxy_sources.find(proxy) :
                                            used_proxy_sources.end();

    auto& srcs = node->srcs();
    for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
      auto src_impl = srcs[i].impl();
      if (src_impl->ctx() != ctx_) {
        src_impl = create_bypass(src_impl);
        node->set_src(i, src_impl);
      }

      // skip unused proxy sources
      interval_t use_interval;
      if (use_info_it != used_proxy_sources.end()) {
        auto it = use_info_it->second.find(i);
        if (it == use_info_it->second.end())
          continue;
        use_interval = it->second;
      } else {
        if (nullptr == proxy) {
          use_interval = src_impl->size();
        }
      }

      // gather used proxy sources
      bool is_new_used_proxy_src = false;
      if (type_proxy == src_impl->type()) {
        auto src_proxy = reinterpret_cast<proxyimpl*>(src_impl);        
        auto& used_srcs = used_proxy_sources[src_proxy];
        if (proxy) {
          // track proxies user nodes
          proxy_users[src_proxy->id()].insert(proxy);

          // determine the use interval for its sources
          for (auto& src_range : src_proxy->ranges()) {
            for (auto& p_r : proxy->ranges()) {
              if (p_r.src_idx != i)
                continue;

              auto s_range = range_t(src_range.dst_offset,
                                     src_range.dst_offset + src_range.length);
              auto p_range = range_t(p_r.src_offset,
                                     p_r.src_offset + p_r.length);
              auto i_range = p_range & s_range;
              if (i_range.empty())
                continue;

              interval_t d_interval(i_range);
              if (!use_interval.empty()) {
                d_interval &= use_interval;
                if (d_interval.empty())
                  continue;
                use_interval -= d_interval;
              }

              auto s_interval = d_interval + (src_range.src_offset - src_range.dst_offset);
              auto ret = used_srcs.find(src_range.src_idx);
              if (ret == used_srcs.end()) {
                used_srcs.emplace(src_range.src_idx, s_interval);
                is_new_used_proxy_src = true;
              } else {
                auto u_iv = ret->second + s_interval;
                if (u_iv != ret->second) {
                  ret->second = u_iv;
                  is_new_used_proxy_src = true;
                }
              }              
            }
          }
        } else {
          for (auto& src_range : src_proxy->ranges()) {
            auto s_range = range_t(src_range.dst_offset,
                                   src_range.dst_offset + src_range.length);
            auto d_interval = use_interval & s_range;
            if (d_interval.empty())
              continue;
            use_interval -= d_interval;

            auto s_interval = d_interval + (src_range.src_offset - src_range.dst_offset);
            auto ret = used_srcs.find(src_range.src_idx);
            if (ret == used_srcs.end()) {
              used_srcs.emplace(src_range.src_idx, s_interval);
              is_new_used_proxy_src = true;
            } else {
              auto u_iv = ret->second + s_interval;
              if (u_iv != ret->second) {
                ret->second = u_iv;
                is_new_used_proxy_src = true;
              }
            }            
          }
        }

        if (!use_interval.empty()) {
        #ifndef NDEBUG
          if (platform::self().cflags() & cflags::dump_cfg) {
            ctx_->dump_cfg(std::cout);
          }
        #endif
          throw std::domain_error(sstreamf() << "uninitialized variable " << node->debug_info());
        }
      }

      // add to live list
      auto ret = live_nodes.insert(src_impl);
      if (ret.second || is_new_used_proxy_src) {
        // we have a new live node, add it to working set
        working_set.push_back(src_impl);

        if (ret.second
         && proxy
         && proxy->has_sparse_range()) {
          sparse_proxies.insert(proxy);
        }
      }
    }
    working_set.pop_front();
  }

  // remove unused proxy sources
  for (auto p : used_proxy_sources) {
    auto proxy = reinterpret_cast<proxyimpl*>(p.first);
    // traverse the sources in reverse order (for efficient removal)
    for (int i = proxy->num_srcs() - 1; i >= 0; --i) {
      if (p.second.count(i) != 0)
        continue;
      remove_unused_proxy_sources(proxy, i);
    }
  }

  // delete dead nodes
  for (auto it = ctx_->nodes().begin(),
           end = ctx_->nodes().end(); it != end;) {
    auto node = *it;
    if (0 == live_nodes.count(node)) {
      it = ctx_->delete_node(it);
      changed = true;
    } else {
      ++it;
    }
  }

  // fix sparse proxies
  for (auto p : sparse_proxies) {
    fix_sparse_proxies(p);
  }

  assert(ctx_->nodes().size() == live_nodes.size());

  CH_DBG(3, "End Compiler::DCE\n");

  return changed;
}

bool compiler::constant_folding() {
  if (platform::self().cflags() & cflags::disable_cfo)
    return false;

  CH_DBG(3, "Begin Compiler::CFO\n");

  std::unordered_set<uint32_t> visited_nodes;
  std::vector<lnodeimpl*> deleted_list;
  bool changed = false;

  auto replace_constant = [&](lnodeimpl* from, lnodeimpl* to) {
    if (nullptr == to)
      return;    
    changed = true;
    if (from == to)
      return; // internal node change
    from->replace_uses(to);
    deleted_list.push_back(from);
  };

  auto constant_fold_proxy = [&](proxyimpl* node)->lnodeimpl* {
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
  };

  auto constant_fold_op_full = [&](opimpl* node)->lnodeimpl* {
    sdata_type tmp(node->size());

    const block_type* src0_data = nullptr;
    uint32_t src0_size = 0;
    const block_type* src1_data = nullptr;
    uint32_t src1_size = 0;

    // access source node data
    if (node->num_srcs() > 0) {
      auto src0_impl = node->src(0).impl();
      assert(type_lit == src0_impl->type());
      src0_data = reinterpret_cast<litimpl*>(src0_impl)->value().words();
      src0_size = node->src(0).size();
      if (node->num_srcs() > 1) {
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
    default:
      assert(false);
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
      bv_assign_scalar(tmp.words(), bv_not(src0_data, src0_size));
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
    }
    return ctx_->create_literal(tmp);
  };

  auto constant_fold_op_partial = [&](opimpl* node)->lnodeimpl* {
    auto src0 = node->src(0).impl();
    auto src1 = node->src(1).impl();

    bool src0_is_zero = (type_lit == src0->type()) && reinterpret_cast<litimpl*>(src0)->value().is_zero();
    bool src0_is_ones = (type_lit == src0->type()) && reinterpret_cast<litimpl*>(src0)->value().is_ones();
    bool src1_is_zero = (type_lit == src1->type()) && reinterpret_cast<litimpl*>(src1)->value().is_zero();
    bool src1_is_ones = (type_lit == src1->type()) && reinterpret_cast<litimpl*>(src1)->value().is_ones();

    switch (node->op()) {
    case ch_op::andb:
      if (src0_is_zero || src1_is_zero) {
        return ctx_->create_literal(sdata_type(node->size(), 0));
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
        return ctx_->create_node<opimpl>(ch_op::inv, node->size(), false, src1, node->sloc());
      } else
      if (node->size() == src0->size() && node->size() == src1->size() && src1_is_ones) {
        return ctx_->create_node<opimpl>(ch_op::inv, node->size(), false, src0, node->sloc());
      }
      break;
    case ch_op::mul:
      if (src0_is_zero || src1_is_zero) {
        return ctx_->create_literal(sdata_type(node->size(), 0));
      }
      break;
    case ch_op::shl:
    case ch_op::shr:
    case ch_op::div:
    case ch_op::mod:
      if (src0_is_zero) {
        return ctx_->create_literal(sdata_type(node->size(), 0));
      }
      break;
    case ch_op::lt:
      if (src1_is_zero && !node->is_signed()) {
        return ctx_->create_literal(sdata_type(1, false));
      }
      break;
    case ch_op::gt:
      if (src0_is_zero && !node->is_signed()) {
        return ctx_->create_literal(sdata_type(1, false));
      }
      break;
    case ch_op::ge:
      if (src1_is_zero && !node->is_signed()) {
        return ctx_->create_literal(sdata_type(1, true));
      }
      break;
    case ch_op::le:
      if (src0_is_zero && !node->is_signed()) {
        return ctx_->create_literal(sdata_type(1, true));
      }
      break;
    case ch_op::eq:
      if (src0_is_zero) {
        return ctx_->create_node<opimpl>(ch_op::notl, node->size(), node->is_signed(), src1, node->sloc());
      } else if (src1_is_zero) {
        return ctx_->create_node<opimpl>(ch_op::notl, node->size(), node->is_signed(), src0, node->sloc());
      }
      break;
    case ch_op::ne:
      if (src0_is_zero) {
        return ctx_->create_node<opimpl>(ch_op::orr, node->size(), node->is_signed(), src1, node->sloc());
      } else if (src1_is_zero) {
        return ctx_->create_node<opimpl>(ch_op::orr, node->size(), node->is_signed(), src0, node->sloc());
      }
      break;
    default:
      break;
    }
    return nullptr;
  };

  auto constant_fold_select = [&](selectimpl* node)->lnodeimpl* {
    if (node->has_key()) {
      auto key_impl = node->key().impl();
      assert(type_lit == key_impl->type());
      auto key_data = reinterpret_cast<litimpl*>(key_impl)->value().words();
      auto key_size = key_impl->size();

      uint32_t i = 1;
      for (uint32_t n = node->num_srcs() - 1; i < n; i += 2) {
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
      for (uint32_t n = node->num_srcs() - 1; i < n; i += 2) {
        auto src_impl = node->src(i).impl();
        if (type_lit == src_impl->type()) {
          auto src_data = reinterpret_cast<litimpl*>(src_impl)->value().words();
          if (static_cast<bool>(src_data[0])) {
            if (0 == i)
              return node->src(i+1).impl();
            deleted_list.push_back(node->remove_src(i)); // remove predicate
            // remove remaining cases
            for (uint32_t j = n - 1; j > i; --j) {
              node->remove_src(j);
            }
            n = i + 1;
          } else {
            // remove this case
            deleted_list.push_back(node->remove_src(i));
            deleted_list.push_back(node->remove_src(i));
            n -= 2;
          }
        }
      }
      return node;
    }
  };

  auto constant_fold_register = [&](regimpl* node)->lnodeimpl* {
    if (reinterpret_cast<cdimpl*>(node->cd().impl())->clk().impl()->type() == type_lit) {
      throw std::domain_error(sstreamf() << "constant register clock signal" << node->debug_info());
    }
    if (node->has_reset()
     && node->reset().impl()->type() == type_lit) {
      throw std::domain_error(sstreamf() << "constant register reset signal" << node->debug_info());
    }
    if (!node->has_init_data()
     && node->next().id() == node->id()) {
        fprintf(stderr, "warning: uninitialized register %s\n", node->debug_info().c_str());
    }
    if (node->has_enable()) {
      if (is_literal_one(node->enable().impl())) {
        auto enable = node->remove_enable();
        if (!enable->users()) {
          deleted_list.push_back(enable);
        }
        return node;
      } else
      if (is_literal_zero(node->enable().impl())) {
        if (!node->has_init_data()) {
          fprintf(stderr, "warning: uninitialized register %s\n", node->debug_info().c_str());
        }
        node->set_next(node);
        auto enable = node->remove_enable();
        if (!enable->users()) {
          deleted_list.push_back(enable);
        }
        return node;
      }
    }
    if (node->next().impl()->type() == type_lit
     && (!node->has_init_data()
      || (node->next().id() == node->init_data().id()))) {
      return node->next().impl();
    }
    return nullptr;
  };

  std::function<void (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node) {
    if (visited_nodes.count(node->id()))
      return;
    visited_nodes.emplace(node->id());

    for (auto& src : node->srcs()) {
      dfs_visit(src.impl());
    }

    bool is_constant_all = true;
    bool is_constant_partial = false;
    for (auto& src : node->srcs()) {
      auto src_impl = src.impl();
      bool is_constant = (src_impl->type() == type_lit);
      is_constant_partial |= is_constant;
      is_constant_all &= is_constant;
    }

    switch (node->type()) {
    case type_proxy: {
      if (is_constant_all) {
        auto proxy = reinterpret_cast<proxyimpl*>(node);
        replace_constant(proxy, constant_fold_proxy(proxy));
      }
      break;
    }
    case type_op: {
      auto alu = reinterpret_cast<opimpl*>(node);
      if (is_constant_all) {
        replace_constant(alu, constant_fold_op_full(alu));
      } else
      if (is_constant_partial
       && op_flags::binary == CH_OP_ARY(alu->op())) {
        replace_constant(alu, constant_fold_op_partial(alu));
      }
      break;
    }
    case type_sel: {
      auto sel = reinterpret_cast<selectimpl*>(node);
      if (!is_constant_all) {
        if (sel->has_key()) {
          is_constant_all = (type_lit == sel->key().impl()->type());
        } else {
          for (uint32_t i = 0, l = sel->num_srcs() - 1; i < l; i += 2) {
            is_constant_all |= (type_lit == sel->src(i).impl()->type());
          }
        }
      }
      if (is_constant_all) {
        replace_constant(sel, constant_fold_select(sel));
      }
      break;
    }
    case type_reg: {
      if (is_constant_partial) {
        auto reg = reinterpret_cast<regimpl*>(node);
        replace_constant(reg, constant_fold_register(reg));
      }
      break;
    }
    case type_msrport:
    case type_mwport: {
      auto mport = reinterpret_cast<memportimpl*>(node);
      if (mport->has_enable()
       && is_literal_one(mport->enable().impl())) {
        auto impl = mport->remove_enable();
        if (!impl->users()) {
          deleted_list.push_back(impl);
        }
        changed = true;
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
    if (node->size() != 0)
      continue;
    dfs_visit(node);
  }
  for (auto node : ctx_->ext_nodes()) {
    dfs_visit(node);
  }

  // process deleted nodes
  node_deleter deleter(ctx_);
  for (auto node : deleted_list) {
    if (nullptr == node->users())
      deleter.add(node);
  }
  deleter.apply();

  CH_DBG(3, "End Compiler::CFO\n");

  return changed;
}

bool compiler::subexpressions_elimination() {
  if (platform::self().cflags() & cflags::disable_cse)
    return false;

  CH_DBG(3, "Begin Compiler::CSE\n");

  std::unordered_set<uint32_t> visited_nodes;
  std::unordered_set<cse_key_t, cse_key_t::hash_type> cse_table;
  std::vector<lnodeimpl*> deleted_list;
  bool changed = false;

  std::function<void (lnodeimpl*)> dfs_visit = [&](lnodeimpl* node) {
    if (visited_nodes.count(node->id()))
      return;
    visited_nodes.emplace(node->id());

    for (auto& src : node->srcs()) {
      dfs_visit(src.impl());
    }

    switch (node->type()) {
    default:
      break;
    case type_cd:
    case type_proxy:
    case type_sel:
    case type_op:
    case type_reg: {
      auto it = cse_table.find(node);
      if (it != cse_table.end()) {
        node->replace_uses(it->node);
        deleted_list.push_back(node);
        changed = true;
      } else {
        cse_table.insert(node);
      }
    } break;
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
    if (node->size() != 0)
      continue;
    dfs_visit(node);
  }
  for (auto node : ctx_->ext_nodes()) {
    dfs_visit(node);
  }

  // process deleted nodes
  node_deleter deleter(ctx_);
  for (auto deleted : deleted_list) {
    deleter.add(deleted);
  }
  deleter.apply();

  CH_DBG(3, "End Compiler::CSE\n");

  return changed;
}

bool compiler::prune_identity_proxies() {
  if (platform::self().cflags() & cflags::disable_pip)
    return false;

  CH_DBG(3, "Begin Compiler::PIP\n");

  node_deleter deleter(ctx_);
  bool changed = false;

  for (auto node : ctx_->proxies()) {
    auto proxy = reinterpret_cast<proxyimpl*>(node);
    if (!proxy->is_identity())
      continue;

    // replace identity proxy's uses with proxy's source
    auto src = proxy->src(0).impl();
    proxy->replace_uses(src);    
    deleter.add(proxy);
    changed = true;
  }

  deleter.apply();

  CH_DBG(3, "End Compiler::PIP\n");

  return changed;
}

bool compiler::proxies_coalescing() {
  if (platform::self().cflags() & cflags::disable_pcx)
    return false;

  CH_DBG(3, "Begin Compiler::PCX\n");

  auto is_multi_range = [&](proxyimpl* proxy,
                            uint32_t offset,
                            uint32_t length) {
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
       && !is_multi_range(src_proxy, range.src_offset, range.length))
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
    std::unordered_map<proxyimpl*, std::vector<proxyimpl::range_t>> src_proxy_upds;
    found = false;

    for (auto it = ctx_->proxies().begin(),
             end = ctx_->proxies().end(); it != end;) {
      auto dst_proxy = reinterpret_cast<proxyimpl*>(*it++);

      bool has_upd_ranges = false;

      for (auto& src : dst_proxy->srcs()) {
        if (type_proxy != src.impl()->type())
          continue;        

        auto src_proxy = reinterpret_cast<proxyimpl*>(src.impl());
        if (src_proxy_upds.count(src_proxy))
          continue;

        // skip useful proxies
        if (src_proxy->users() != nullptr
         && is_useful_proxy(dst_proxy, src_proxy))
          continue;

        auto& upd_ranges = src_proxy_upds[src_proxy];
        for (auto& dst_range : dst_proxy->ranges()) {
          if (dst_proxy->src(dst_range.src_idx).id() != src_proxy->id())
            continue;

          for (auto& src_range : src_proxy->ranges()) {
            int32_t delta  = src_range.dst_offset - dst_range.src_offset;
            uint32_t start = std::max<int32_t>(dst_range.dst_offset + delta, 0);
            uint32_t end   = std::max<int32_t>(dst_range.dst_offset + delta + src_range.length, 0);
            range_t src_iv(start, end);
            range_t dst_iv(dst_range.dst_offset,
                           dst_range.dst_offset + dst_range.length);
            auto shared_iv = dst_iv & src_iv;
            if (shared_iv.empty())
              continue;

            proxyimpl::range_t upd_range;
            upd_range.src_idx    = src_range.src_idx;
            upd_range.dst_offset = shared_iv.start;
            upd_range.src_offset = src_range.src_offset - std::min(delta, 0);
            upd_range.length     = shared_iv.end - shared_iv.start;
            upd_ranges.emplace_back(upd_range);
            has_upd_ranges = true;
          }
        }
      }

      if (has_upd_ranges) {
        for (auto src_proxy_upd : src_proxy_upds) {
          auto src_proxy = src_proxy_upd.first;
          if (!src_proxy_upd.second.empty()) {
            for (auto range : src_proxy_upd.second) {
              dst_proxy->add_source(
                range.dst_offset,
                src_proxy->src(range.src_idx).impl(),
                range.src_offset,
                range.length);
            }
            detached_list.insert(src_proxy);
          }
        }

        src_proxy_upds.clear();
        found = true;
        changed = true;
      }
    }
  } while (found);

  // delete unreferenced detached nodes
  node_deleter deleter(ctx_);
  for (auto node : detached_list) {
    if (nullptr == node->users())
      deleter.add(node);
  }  
  deleter.apply();

  CH_DBG(3, "End Compiler::PCX\n");

  return changed;
}

bool compiler::branch_coalescing() {
  if (platform::self().cflags() & cflags::disable_bro)
    return false;

  CH_DBG(3, "Begin Compiler::BRO\n");

  node_deleter deleter(ctx_);
  bool changed = false;

  //--
  auto remove_node_src = [&](lnodeimpl* node, uint32_t index) {
    auto impl0 = node->src(index + 0).impl();
    auto impl1 = node->src(index + 1).impl();

    node->remove_src(index + 1); // higher index first
    node->remove_src(index + 0);
    if (nullptr == impl0->users()) {
      deleter.add(impl0);
    }
    if (nullptr == impl1->users()) {
      deleter.add(impl1);
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
      for (uint32_t i = start, n = sel->num_srcs() - 1; i < n; i += 2) {
        auto pred  = sel->src(i+0).impl();
        auto value = sel->src(i+1).impl();
        if (value == df_value) {
          if (!has_key) {
            if (skip_pred) {
              skip_pred = ctx_->create_node<opimpl>(ch_op::orb, 1, false, skip_pred, pred, sel->sloc());
            } else {
              skip_pred = pred;
            }
          }
          deleted.push_back(i);
        } else {
          if (skip_pred) {
            skip_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, skip_pred, sel->sloc());
            pred = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred, skip_pred, sel->sloc());
            sel->set_src(i+0, pred);
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
      for (uint32_t i = 0, n = sel->num_srcs() - 1; i < n; i += 2) {
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
            } else {
              skip_pred = pred2;
            }
          }

          for (auto dup : dups) {
            pred1 = ctx_->create_node<opimpl>(ch_op::orb, 1, false, pred1, sel->src(dup).impl(), sel->sloc());
          }

          if (skip_pred) {
            skip_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, skip_pred, sel->sloc());
            pred1 = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred1, skip_pred, sel->sloc());
          }

          sel->set_src(i+0, pred1);

          for (auto it = dups.rbegin(); it != dups.rend();) {
            remove_node_src(sel, *it++);
            n -= 2; // update size
          }

          dups.clear();
        }
      }
    }

    // is default only select
    uint32_t sel_def_size = sel->has_key() ? 2 : 1;
    if (sel->num_srcs() == sel_def_size)
      return sel->src(sel_def_size - 1).impl();

    // coallesce cascading ternary branches sharing the same default value
    // p2 ? (p1 ? t1 : f1) : f1 => (p1 & p2) ? t1 : f1;
    uint32_t sel_num_srcs = has_key ? 4 : 3;
    if (sel->num_srcs() == sel_num_srcs) {
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
          }
          auto pred1 = _true->src(true_num_srcs-3).impl();
          if (true_has_key) {
            // create predicate
            pred1 = ctx_->create_node<opimpl>(ch_op::eq, 1, false, pred1, _true->src(1).impl(), sel->sloc());
          }
          auto pred = ctx_->create_node<opimpl>(ch_op::andb, 1, false, pred0, pred1, sel->sloc());
          if (true_has_key) {
            _true->remove_key();
          }
          _true->set_src(0, pred);

          return _true;
        }
      }
    }

    // convert tenary switches to branches
    if (has_key && 4 == sel->num_srcs()) {
      auto pred = ctx_->create_node<opimpl>(ch_op::eq, 1, false, sel->src(0).impl(), sel->src(1).impl(), sel->sloc());
      sel->remove_key();
      sel->set_src(0, pred);
      changed = true;
      return nullptr;
    }

    // eliminate ternary branches with constant boolean sources
    if (1 == sel->size()
     && 3 == sel->num_srcs()
     && type_lit == sel->src(1).impl()->type()
     && type_lit == sel->src(2).impl()->type()) {
      if (static_cast<bool>(reinterpret_cast<litimpl*>(sel->src(1).impl())->value())) {
        return sel->src(0).impl();
      } else {
        auto pred = sel->src(0).impl();
        auto inv_pred = ctx_->create_node<opimpl>(ch_op::inv, 1, false, pred, sel->sloc());
        return inv_pred;
      }
    }

    return nullptr;
  };

  for (auto node : ctx_->sels()) {
    auto sel = reinterpret_cast<selectimpl*>(node);
    auto x = coalesce_branch(sel);
    if (x) {
      sel->replace_uses(x);
      deleter.add(sel);
      changed = true;
    }
  }

  deleter.apply();

  return changed;
}

bool compiler::register_promotion() {
  if (platform::self().cflags() & cflags::disable_rpo)
    return false;

  CH_DBG(3, "Begin Compiler::RPO\n");

  node_deleter deleter(ctx_);
  bool changed = false;

  for (auto node : ctx_->snodes()) {
    if (node->type() != type_reg)
      continue;

    auto reg = reinterpret_cast<regimpl*>(node);
    if (reg->has_enable())
      continue;

    auto next = reg->next().impl();
    if (next->type() == type_sel
     && next->srcs().size() == 3
     && next->src(2).impl() == reg) {
      reg->set_enable(next->src(0).impl());
      reg->set_src(1, next->src(1).impl());
      if (nullptr == next->users())
        deleter.add(next);
      changed = true;
    }
  }

  deleter.apply();

  CH_DBG(3, "End Compiler::RPO\n");

  return changed;
}

void compiler::create_merged_context(context* ctx, bool verbose_tracing) {
  //--
  std::list<std::string> node_path;

  //--
  auto full_name = [&](lnodeimpl* node) {
    std::stringstream ss;
    for (auto p : node_path) {
      ss << p << "/";
    }
    ss << node->name();
    return ss.str();
  };

  //--
  std::unordered_map<uint32_t, lnodeimpl*> bypass_nodes;

  //--
  std::function<void (context*, clone_map&)>
      visit = [&](context* curr, clone_map& map) {
    //--
    std::vector<std::unique_ptr<placeholder_node>> placeholders;
    std::unordered_map<uint32_t, std::vector<lnodeimpl**>> unresolved_nodes;

    //--
    auto ensure_placeholder = [&](lnodeimpl* node, uint32_t src_idx) {
      auto& src = node->src(src_idx);
      auto it = map.find(src.id());
      if (it != map.end()) {
        auto cloned_src = it->second;
        // check if it is a placeholder
        if (type_none == cloned_src->type()) {
          auto placeholder = reinterpret_cast<placeholder_node*>(cloned_src);
          auto& user = placeholder->users.emplace_back(src_idx);
          unresolved_nodes[node->id()].emplace_back(&user.node);
        }
        return;
      }

      // create new placeholder
      auto placeholder = std::make_unique<placeholder_node>(src.id(), src.size(), curr, src.name(), src.sloc());
      auto& user = placeholder->users.emplace_back(src_idx);
      unresolved_nodes[node->id()].emplace_back(&user.node);

      map[src.id()] = placeholder.get();
      placeholders.emplace_back(std::move(placeholder));
    };

    //--
    auto update_map = [&](uint32_t id, lnodeimpl* node) {
      map[id] = node;
      {
        auto it = unresolved_nodes.find(id);
        if (it != unresolved_nodes.end()) {
          for (auto& entry : it->second) {
            *entry = node;
          }
        }
      }
      {
        auto it = bypass_nodes.find(id);
        if (it != bypass_nodes.end()) {
          it->second = node;
        }
      }
    };

    // load bypass nodes
    for (auto node : curr->btaps()) {
      auto bypass = reinterpret_cast<bypassimpl*>(node);
      bypass_nodes[bypass->target()->id()] = nullptr;
    }

    //--
    for (auto node : curr->nodes()) {
      switch (node->type()) {
      case type_bind: {
        clone_map sub_map;
        auto bind = reinterpret_cast<bindimpl*>(node);        
        auto module = bind->module();

        // map module inputs to bind inputs
        for (auto input : module->inputs()) {
          bool found = false;
          for (auto bp : reinterpret_cast<inputimpl*>(input)->bindports()) {
            for (auto& bi : bind->inputs()) {
              if (bp->id() == bi.id()) {
                auto bi_impl = reinterpret_cast<bindportimpl*>(bi.impl());
                ensure_placeholder(bi_impl, 0);
                sub_map[input->id()] = map.at(bi_impl->src(0).id());
                found = true;
                break;
              }
            }
            if (found)
              break;
          }
          assert(found);
        }

        node_path.push_back(stringf("%s_%d", bind->module()->name().c_str(), bind->id()));
        visit(bind->module(), sub_map);
        node_path.pop_back();

        // map bindoutputs to module outputs
        for (auto& bo : bind->outputs()) {
          auto bo_impl = reinterpret_cast<bindportimpl*>(bo.impl());
          auto bo_port = bo_impl->ioport().impl();
          auto bo_value = sub_map.at(bo_port->src(0).id());
          update_map(bo.id(), bo_value);
        }
      } break;
      case type_bindin:
      case type_bindout:
        // skip
        break;
      case type_input: {
        auto input = reinterpret_cast<inputimpl*>(node);
        if (curr->parent() != nullptr) {
          if (verbose_tracing) {
            auto name = full_name(input);
            auto target = map.at(input->id());
            auto tap = ctx_->create_node<tapimpl>(target, name, input->sloc());
            if (type_none == target->type()) {
              reinterpret_cast<placeholder_node*>(target)->users.emplace_back(tap, 0);
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
            eval_node->rename(full_name(eval_node));
          }
          update_map(input->id(), eval_node);
        }
      } break;
      case type_output: {        
        auto output = reinterpret_cast<outputimpl*>(node);
        ensure_placeholder(output, 0);
        if (curr->parent() != nullptr) {
          if (verbose_tracing) {
            auto name = full_name(output);
            auto target = map.at(output->src(0).id());
            auto tap = ctx_->create_node<tapimpl>(target, name, output->sloc());
            if (type_none == target->type()) {
              reinterpret_cast<placeholder_node*>(target)->users.emplace_back(tap, 0);
            }
          }
        } else {
          auto eval_node = output->clone(ctx_, map);
          eval_node->rename(full_name(eval_node));
          update_map(output->id(), eval_node);
        }
      } break;
      case type_mem:
      case type_udfc:
      case type_udfs: {
        auto eval_node = node->clone(ctx_, map);
        update_map(node->id(), eval_node);
      } break;
      case type_tap: {
        auto tap = reinterpret_cast<tapimpl*>(node);
        ensure_placeholder(tap, 0);
        auto eval_node = tap->clone(ctx_, map);
        eval_node->rename(full_name(eval_node));
        update_map(tap->id(), eval_node);
      } break;
      case type_bypass: {
        auto bypass = reinterpret_cast<bypassimpl*>(node);
        auto eval_node = bypass_nodes.at(bypass->target()->id());
        // bypass nodes are created after describe() call,
        // so value should have computed by this point
        assert(eval_node);
        update_map(node->id(), eval_node);
      } break;
      default: {
        for (uint32_t i = 0; i < node->num_srcs(); ++i) {
          ensure_placeholder(node, i);
        }
        auto eval_node = node->clone(ctx_, map);
        update_map(node->id(), eval_node);
      } break;
      }
    }

    // resolve placeholders
    std::list<placeholder_node*> placeholder_list;
    for (auto& placeholder : placeholders) {
      placeholder_list.emplace_back(placeholder.get());
    }
    while (!placeholder_list.empty()) {
      auto placeholder = placeholder_list.front();
      placeholder_list.pop_front();
      auto cloned_src = map.at(placeholder->id());
      assert(placeholder != cloned_src);
      for (auto& user : placeholder->users) {
        auto target = user.node;
        if (nullptr == target)
          continue;

        assert(target->type() != type_none);
        if (type_none == target->src(user.src_idx).impl()->type()) {
          assert(target->src(user.src_idx).impl() == placeholder);
          target->set_src(user.src_idx, cloned_src);
          if (type_none == cloned_src->type()) {
            auto p = reinterpret_cast<placeholder_node*>(cloned_src);
            p->users.emplace_back(target, user.src_idx);
            if (p->ctx() == curr && 1 == p->users.size()) {
              placeholder_list.emplace_back(p);
            }
          }
        }
      }
      placeholder->users.clear();
    }
  };

  CH_DBG(2, "create merged context for %s (#%d) ...\n", ctx->name().c_str(), ctx->id());

  clone_map map;
  if (ctx_->name() != ctx->name()) {
    node_path.push_back(stringf("%s_%d", ctx->name().c_str(), ctx->id()));
    visit(ctx, map);
    node_path.pop_back();
  } else {
    visit(ctx, map);
  }
}

void compiler::build_eval_list(std::vector<lnodeimpl*>& eval_list) {
  std::unordered_set<uint32_t> visited_nodes;
  std::unordered_set<uint32_t> cyclic_nodes;
  std::unordered_set<lnodeimpl*> update_list;
  std::unordered_set<lnodeimpl*> uninitialized_regs;

  //--
  std::function<bool (lnodeimpl*, lnodeimpl*, std::unordered_set<uint32_t>&)>
      print_cycle =[&](lnodeimpl* node, lnodeimpl* target, std::unordered_set<uint32_t>& map)->bool {
    if (map.count(node->id()))
      return false;
    map.insert(node->id());
    if (node->type() == type_reg) {
      map.insert(reinterpret_cast<regimpl*>(node)->next().id());
    }
    if (node == target)
      return true;
    for (auto& src : node->srcs()) {
      auto ret = print_cycle(src.impl(), target, map);
      if (ret) {
        std::cout << "  path: " << src.impl()->debug_info() << std::endl;
        return true;
      }
    }
    return false;
  };

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
      if (platform::self().cflags() & cflags::dump_cfg) {
        for (auto _node : eval_list) {
          std::cerr << _node->ctx()->id() << ": ";
          _node->print(std::cerr);
          std::cerr << std::endl;
        }
      }
      std::cout << "found a cycle on variable " << node->debug_info() << std::endl;
      {
        std::unordered_set<uint32_t> visited;
        for (auto& src : node->srcs()) {
          auto ret = print_cycle(src.impl(), node, visited);
          if (ret) {
            std::cout << "  path: " << src.impl()->debug_info() << std::endl;
            break;
          }
        }
      }
      throw std::domain_error(sstreamf() << "found a cycle on variable " << node->debug_info());
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
    if (node->size() != 0)
      continue;
    dfs_visit(node);
  }

  if (sys_time) {
    visited_nodes.erase(sys_time->id());
    dfs_visit(sys_time);
  }

  if (platform::self().cflags() & cflags::dump_cfg) {
    for (auto node : eval_list) {
      std::cout << node->ctx()->id() << ": ";
      node->print(std::cerr);
      std::cout << std::endl;
    }
    std::cout << "total nodes: " << eval_list.size() << std::endl;
  }

  if (!uninitialized_regs.empty()
   && (platform::self().cflags() & cflags::check_reg_init)) {
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

      switch (type) {
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
    if (node->size() != 0)
      continue;
    dfs_visit(node);
  }
  auto sys_time = ctx->sys_time();
  if (sys_time) {
    dfs_visit(sys_time);
  }

  return !has_data_nodes;
}
