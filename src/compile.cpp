#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "proxyimpl.h"
#include "ioimpl.h"
#include "context.h"
#include "mem.h"

using namespace ch::internal;

compiler::compiler(context* ctx) : ctx_(ctx) {
  node_map_ = ctx_->get_io_map();
}

void compiler::run() {
  DBG(2, "compiling %s ...\n", ctx_->get_name());

  size_t orig_num_nodes = ctx_->get_nodes().size();
  
  size_t dead_nodes = this->dead_code_elimination();

  this->build_node_map();

  size_t identity_nodes = this->remove_identity_nodes();
  
  this->syntax_check();
  
#ifndef NDEBUG
  // dump nodes
  int dump_ast_level = platform::self().get_dump_ast();
  if (dump_ast_level) {
    ctx_->dump_ast(std::cerr, dump_ast_level);
  }

  // dump tap's CFG
  int dump_cfg_level = platform::self().get_dump_cfg();
  if (dump_cfg_level) {
    for (auto node : ctx_->get_taps()) {
      std::cout << "CFG dump for tap variable: " << node->get_name() << std::endl;
      ctx_->dump_cfg(node, std::cout, dump_cfg_level);
    }
  }
#endif
  
  DBG(2, "*** deleted %lu dead nodes\n", dead_nodes);
  DBG(2, "*** deleted %lu identity nodes\n", identity_nodes);
  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After optimization: %lu\n", ctx_->get_nodes().size());
}

void compiler::syntax_check() {
  // check for un-initialized nodes
  const auto& undefs = ctx_->get_undefs();
  if (undefs.size()) {
    ctx_->dump_ast(std::cerr, 1);    
    for (auto node : undefs) {
      fprintf(stderr, "error: un-initialized node %s%d(#%d)!\n", to_string(node->get_type()), node->get_size(), node->get_id());
    }
    if (1 == undefs.size())
      CH_ABORT("1 node has not been initialized.");
    else
      CH_ABORT("%zd nodes have not been initialized.", undefs.size());
  }
}

size_t compiler::dead_code_elimination() {
  std::unordered_map<proxyimpl*, std::unordered_set<uint32_t>> used_proxy_sources;
  live_nodes_t live_nodes(ctx_->compute_live_nodes());
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());

  while (!working_set.empty()) {
    lnodeimpl* node = working_set.front();
    auto proxy = dynamic_cast<proxyimpl*>(node);

    auto& srcs = node->get_srcs();
    for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
      lnodeimpl* src_impl = srcs[i].get_impl();

      // skip external sources
      if (src_impl->get_ctx() != ctx_) {
        ports_.emplace(node->get_id());
        continue;
      }

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
      auto src_proxy = dynamic_cast<proxyimpl*>(src_impl);
      if (src_proxy) {
        auto& uses = used_proxy_sources[src_proxy];
        if (proxy) {
          for (auto& curr : src_proxy->get_ranges()) {
            uint32_t curr_end = curr.dst_offset + curr.length;
            for (auto& range : proxy->get_ranges()) {
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
          for (auto& curr : src_proxy->get_ranges()) {
            uses.insert(curr.src_idx);
          }
        }
      }

      // add to live list
      auto ret = live_nodes.emplace(src_impl);
      if (ret.second || new_proxy_source) {
        // we have a new live node, add it to working set
        working_set.emplace_back(src_impl);
      }
    }
    working_set.pop_front();
  }

  // remove unused proxy sources
  for (auto p : used_proxy_sources) {
    auto proxy = dynamic_cast<proxyimpl*>(p.first);
    auto& srcs = proxy->get_srcs();
    // traverse the sources in reverse order
    for (int i = srcs.size() - 1; i >= 0; --i) {
      if (0 == p.second.count(i)) {
        proxy->erase_source(srcs.begin() + i);
      };
    }
  }

  return this->remove_dead_nodes(live_nodes);
}

size_t compiler::remove_dead_nodes(
    const std::unordered_set<lnodeimpl*>& live_nodes) {
  size_t deleted = 0;
  for (auto iter = ctx_->get_nodes().begin(),
       iterEnd = ctx_->get_nodes().end(); iter != iterEnd;) {
    lnodeimpl* const node = *iter++;
    if (0 == live_nodes.count(node)) {
      delete node;
      ++deleted;      
    }
  }

  return deleted;
}

void compiler::build_node_map() {
  for (auto node : ctx_->get_nodes()) {
    for (auto& src : node->get_srcs()) {
      node_map_[src.get_id()].push_back(&src);
    }
  }
}

size_t compiler::remove_identity_nodes() {
  size_t deleted = 0;
  for (auto iter = ctx_->get_proxies().begin(),
       iterEnd = ctx_->get_proxies().end(); iter != iterEnd;) {
    proxyimpl* const proxy = *iter++;
    if (proxy->is_identity()
     && 0 == ports_.count(proxy->get_id())) {
      auto& src = proxy->get_src(0);
      auto src_impl = src.get_impl();

      // remove proxy from source's refs
      auto& src_refs = node_map_[src_impl->get_id()];
      for (auto it = src_refs.begin(), end = src_refs.end(); it != end; ++it) {
        if (*it == &src) {
          src_refs.erase(it);
          break;
        }
      }

      // replace proxy's uses with proxy's source      
      auto it = node_map_.find(proxy->get_id());
      assert(it != node_map_.end());
      for (auto node : it->second) {
        const_cast<lnode*>(node)->set_impl(src_impl);

        // update source refs
        src_refs.push_back(node);
      }
      node_map_.erase(it);
      delete proxy;
      ++deleted;
    }
  }
  return deleted;
}
