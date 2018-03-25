#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "proxyimpl.h"
#include "ioimpl.h"
#include "context.h"
#include "mem.h"

using namespace ch::internal;

compiler::compiler(context* ctx) : ctx_(ctx) {}

void compiler::run() {
  size_t orig_num_nodes, dead_nodes, identity_nodes;
  CH_UNUSED(orig_num_nodes, dead_nodes, identity_nodes);

  DBG(2, "compiling %s ...\n", ctx_->get_name().c_str());

  orig_num_nodes = ctx_->get_nodes().size();

  dead_nodes = this->dead_code_elimination();

  this->build_node_map();

  identity_nodes = this->remove_identity_nodes();

  DBG(2, "*** deleted %lu dead nodes\n", dead_nodes);
  DBG(2, "*** deleted %lu identity nodes\n", identity_nodes);
  
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

  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After optimization: %lu\n", ctx_->get_nodes().size());
}

void compiler::syntax_check() {
  // check for un-initialized nodes
  auto& undefs = ctx_->get_undefs();
  if (undefs.size()) {
    ctx_->dump_ast(std::cerr, 1);    
    for (auto undef : undefs) {
      for (auto node : ctx_->get_nodes()) {
        auto ret = std::find_if(node->get_srcs().begin(), node->get_srcs().end(),
                     [undef](const lnode& x)->bool { return x.get_id() == undef->get_id(); });
        if (ret != node->get_srcs().end()) {
          fprintf(stderr, "error: un-initialized variable '%s%d' (#%d)",
                  node->get_name().c_str(), node->get_size(), node->get_id());
          if (node->get_var_id() != 0) {
            fprintf(stderr, " (@var%d)", node->get_var_id());
          }
          fprintf(stderr, " in module '%s'", ctx_->get_name().c_str());
          auto& sloc = node->get_source_location();
          if (!sloc.is_empty()) {
            fprintf(stderr, " (%s:%d)\n", sloc.file(), sloc.line());
          }
          break;
        }
      }
    }
    std::abort();
  }
}

size_t compiler::dead_code_elimination() {
  std::unordered_map<proxyimpl*, std::unordered_set<uint32_t>> used_proxy_sources;
  live_nodes_t live_nodes(ctx_->compute_live_nodes());
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());

  while (!working_set.empty()) {
    auto node = working_set.front();
    auto proxy = dynamic_cast<proxyimpl*>(node);

    auto& srcs = node->get_srcs();
    for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
      auto src_impl = srcs[i].get_impl();
      assert(src_impl->get_ctx() == ctx_);

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
      if (type_proxy == src_impl->get_type()) {
        auto src_proxy = dynamic_cast<proxyimpl*>(src_impl);
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
    auto proxy = dynamic_cast<proxyimpl*>(p.first);
    auto& srcs = proxy->get_srcs();
    // traverse the sources in reverse order
    for (int i = srcs.size() - 1; i >= 0; --i) {
      if (0 == p.second.count(i)) {
        proxy->erase_source(srcs.begin() + i);
      };
    }
  }

  // delete dead nodes
  auto deleted = this->remove_dead_nodes(live_nodes);
  assert(ctx_->get_nodes().size() == live_nodes.size());

  // update nodes in topological order
  auto it_dst = ctx_->get_nodes().begin();
  for (auto it = live_nodes.rbegin(),
       end = live_nodes.rend(); it != end;) {
    *it_dst++ = *it++;
  }

  return deleted;
}

size_t compiler::remove_dead_nodes(const live_nodes_t& live_nodes) {
  size_t deleted = 0;
  for (auto it = ctx_->get_nodes().begin(),
       end = ctx_->get_nodes().end(); it != end;) {
    auto node = *it;
    if (0 == live_nodes.count(node)) {
      it = ctx_->destroyNode(it);
      ++deleted;      
    } else {
      ++it;
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
  for (auto& cd : ctx_->get_cdomains()) {
    for (auto& ev : cd->get_sensitivity_list()) {
      auto& sg = ev.get_signal();
      node_map_[sg.get_id()].push_back(&sg);
    }
  }
}

size_t compiler::remove_identity_nodes() {
  size_t deleted = 0;
  for (auto it = ctx_->get_proxies().begin(),
       end = ctx_->get_proxies().end(); it != end;) {
    proxyimpl* const proxy = *it++;
    if (proxy->is_identity()) {
      auto& src = proxy->get_src(0);
      auto src_impl = src.get_impl();

      // remove proxy from source's refs
      auto& src_refs = node_map_[src_impl->get_id()];
      for (auto s_it = src_refs.begin(), s_end = src_refs.end(); s_it != s_end; ++s_it) {
        if (*s_it == &src) {
          src_refs.erase(s_it);
          break;
        }
      }

      // replace proxy's uses with proxy's source      
      {
        auto p_it = node_map_.find(proxy->get_id());
        assert(p_it != node_map_.end());
        for (auto node : p_it->second) {
          const_cast<lnode*>(node)->set_impl(src_impl);

          // update source refs
          src_refs.push_back(node);
        }
        node_map_.erase(p_it);
      }

      {
        auto n_it = std::find(ctx_->get_nodes().begin(), ctx_->get_nodes().end(), proxy);
        assert(n_it != ctx_->get_nodes().end());
        ctx_->destroyNode(n_it);
      }

      ++deleted;
    }
  }
  return deleted;
}
