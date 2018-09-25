#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "proxyimpl.h"
#include "ioimpl.h"
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

}
}

compiler::compiler(context* ctx) : ctx_(ctx) {}

void compiler::run() {
  size_t orig_num_nodes, dce_nodes, cse_nodes, pxc_nodes;

  DBG(2, "compiling %s (#%d) ...\n", ctx_->name().c_str(), ctx_->id());

  orig_num_nodes = ctx_->nodes().size();

  dce_nodes = this->dead_code_elimination();

  this->build_node_map();

  cse_nodes = this->common_subexpressions_elimination();

  pxc_nodes = this->proxies_coalescing();
  
  this->syntax_check();
  
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
  CH_UNUSED(orig_num_nodes, dce_nodes, cse_nodes, pxc_nodes);
#endif  

  DBG(2, "*** deleted %lu DCE nodes\n", dce_nodes);
  DBG(2, "*** deleted %lu CSE nodes\n", cse_nodes);
  DBG(2, "*** deleted %lu PXC nodes\n", pxc_nodes);

  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After optimization: %lu\n", ctx_->nodes().size());
}

void compiler::build_node_map() {
  for (auto node : ctx_->nodes()) {
    for (auto& src : node->srcs()) {
      node_map_[src.id()].emplace(&src);
    }
  }
}

size_t compiler::dead_code_elimination() {
  ordered_set<lnodeimpl*> live_nodes;
  std::unordered_map<proxyimpl*, std::unordered_set<uint32_t>> used_proxy_sources;

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
        if (used_proxy_sources.count(proxy) != 0) {
          auto& uses = used_proxy_sources.at(proxy);
          if (0 == uses.count(i))
            continue;
         }
      }

      // gather used proxy sources
      bool new_proxy_source = false;      
      if (type_proxy == src_impl->type()) {
        auto src_proxy = reinterpret_cast<proxyimpl*>(src_impl);
        auto& uses = used_proxy_sources[src_proxy];
        if (proxy) {
          for (auto& curr : src_proxy->ranges()) {
            uint32_t curr_end = curr.dst_offset + curr.length;
            for (auto& range : proxy->ranges()) {
              if (range.src_idx == i) {
                // do ranges overlap?
                uint32_t src_end = range.src_offset + range.length;
                if (range.src_offset < curr_end && src_end > curr.dst_offset) {
                  auto ret = uses.insert(curr.src_idx);
                  if (ret.second) {
                    new_proxy_source = true;
                  }
                }
              }
            }
          }
        } else {
          for (auto& curr : src_proxy->ranges()) {
            auto ret = uses.insert(curr.src_idx);
            if (ret.second) {
              new_proxy_source = true;
            }
          }
        }
      }

      // add to live list
      auto ret = live_nodes.insert(src_impl);
      if (ret.second || new_proxy_source) {
        // we have a new live node, add it to working set
        working_set.emplace_back(src_impl);
      }
    }
    working_set.pop_front();
  }

  // remove unused proxy sources
  for (auto p : used_proxy_sources) {
    auto proxy = reinterpret_cast<proxyimpl*>(p.first);
    auto& srcs = proxy->srcs();
    // traverse the sources in reverse order
    for (int i = srcs.size() - 1; i >= 0; --i) {
      if (0 == p.second.count(i)) {
        proxy->erase_source(srcs.begin() + i);
      };
    }
  }

  // delete dead nodes
  size_t deleted = 0;
  for (auto it = ctx_->nodes().begin(),
            end = ctx_->nodes().end(); it != end;) {
    if (0 == live_nodes.count(*it)) {
      it = ctx_->delete_node(it);
      ++deleted;
    } else {
      ++it;
    }
  }

  assert(ctx_->nodes().size() == live_nodes.size());

  return deleted;
}

size_t compiler::common_subexpressions_elimination() {
  size_t deleted = 0;
  typedef std::decay_t<decltype(ctx_->nodes())> nodes_type;
  std::vector<nodes_type::iterator> deleted_list;
  std::unordered_set<cse_key_t, cse_hash_t> cse_table;

  auto find_cse = [&](const nodes_type::iterator& it)->bool {
    auto node = *it;
    if (0 == node->hash())
      return false;
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

  bool changed;
  do {
    changed = false;
    auto& nodes = ctx_->nodes();
    for (auto it = nodes.begin(), end = nodes.end(); it != end;) {
      changed |= find_cse(it++);
    }
    if (changed) {
      deleted += deleted_list.size();
      for (auto it = deleted_list.rbegin(), end = deleted_list.rend(); it != end;) {
        ctx_->delete_node(*it++);
      }
      deleted_list.clear();
      cse_table.clear();
    }
  } while (changed);

  return deleted;
}

size_t compiler::proxies_coalescing() {
  size_t deleted = 0;

  // coalesce identity proxies
  for (auto it = ctx_->proxies().begin(),
       end = ctx_->proxies().end(); it != end;) {
    auto proxy = *it++;
    if (!proxy->is_identity())
      continue;
    // replace identity proxy's uses with proxy's source
    this->map_replace_target(proxy, proxy->src(0).impl());
    this->map_delete(proxy);
    // delete proxy
    auto p_it = std::find(ctx_->nodes().begin(), ctx_->nodes().end(), proxy);
    ctx_->delete_node(p_it);
    ++deleted;
  }

  // coalesce single range proxies
  std::set<proxyimpl*> detached_list;
  bool changed;
  do {
    std::unordered_map<proxyimpl*, std::vector<proxyimpl::range_t>> src_proxies;
    std::unordered_map<const lnode*, lnodeimpl*> src_nodes;
    changed = false;

    for (auto it = ctx_->proxies().begin(),
         end = ctx_->proxies().end(); it != end;) {
      auto dst_proxy = *it++;

      src_proxies.clear();

      for (auto& src : dst_proxy->srcs()) {
        if (type_proxy != src.impl()->type())
          continue;
        auto src_proxy = reinterpret_cast<proxyimpl*>(src.impl());
        if (src_proxies.count(src_proxy))
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
          src_nodes.emplace(&src, src.impl());
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

        changed = true;
      }
    }
  } while (changed);

  for (auto d_it = detached_list.rbegin(), end = detached_list.rend(); d_it != end;) {
    auto node = *d_it++;
    auto m_it = node_map_.find(node->id());
    if (m_it != node_map_.end()) {
      if (m_it->second.empty()) {
        this->map_delete(node);
        auto d_it = std::find(ctx_->nodes().begin(), ctx_->nodes().end(), node);
        ctx_->delete_node(d_it);
        ++deleted;
      }
    }
  }

  return deleted;
}

void compiler::map_replace_target(lnodeimpl* from, lnodeimpl* to) {
  // update all nodes pointing to source to now point to target
  // and unregister source's references
  auto from_it = node_map_.find(from->id());
  assert(from_it != node_map_.end());
  auto& to_refs = node_map_.at(to->id());
  for (auto node : from_it->second) {
    *const_cast<lnode*>(node) = to;
    to_refs.emplace(node);
  }
}

void compiler::map_delete(lnodeimpl* node) {
  auto it = node_map_.find(node->id());
  assert(it != node_map_.end());
  for (auto& src : node->srcs()) {
    node_map_[src.id()].erase(&src);
  }
  node_map_.erase(it);
}

void compiler::syntax_check() {
  // check for un-initialized nodes
  auto& undefs = ctx_->undefs();
  if (undefs.size()) {
#define LCOV_EXCL_START
    ctx_->dump_ast(std::cerr);
    for (auto undef : undefs) {
      for (auto node : ctx_->nodes()) {
        auto ret = std::find_if(node->srcs().begin(), node->srcs().end(),
                     [undef](const lnode& x)->bool { return x.id() == undef->id(); });
        if (ret != node->srcs().end()) {
          if (platform::self().cflags() & cflags::dump_ast) {
            ctx_->dump_ast(std::cerr);
          }
          fprintf(stderr, "error: un-initialized variable %s\n", node->debug_info().c_str());
          break;
        }
      }
    }
    std::abort();
#define LCOV_EXCL_END
  }
}
