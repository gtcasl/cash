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
  size_t orig_num_nodes, dead_nodes, cse_nodes, identity_nodes;
  CH_UNUSED(orig_num_nodes, dead_nodes, cse_nodes, identity_nodes);

  DBG(2, "compiling %s (#%d) ...\n", ctx_->name().c_str(), ctx_->id());

  orig_num_nodes = ctx_->nodes().size();

  dead_nodes = this->dead_code_elimination();

  this->build_node_map();

  cse_nodes = this->common_subexpressions_elimination();

  identity_nodes = this->remove_identity_nodes();
  
  this->syntax_check();
  
#ifndef NDEBUG
  // dump nodes
  int dump_ast_level = platform::self().dump_ast();
  if (dump_ast_level) {
    ctx_->dump_ast(std::cerr, dump_ast_level);
  }

  // dump tap's CFG
  int dump_cfg_level = platform::self().dump_cfg();
  if (dump_cfg_level) {
    for (auto node : ctx_->taps()) {
      std::cout << "CFG dump for tap variable: " << node->name() << std::endl;
      ctx_->dump_cfg(node, std::cout, dump_cfg_level);
    }
  }
#endif  

  DBG(2, "*** deleted %lu dead nodes\n", dead_nodes);
  DBG(2, "*** deleted %lu CSE nodes\n", cse_nodes);
  DBG(2, "*** deleted %lu identity nodes\n", identity_nodes);

  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After optimization: %lu\n", ctx_->nodes().size());
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

  // run DCE
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
      this->replace_map_sources(node, p_it->node);
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

void compiler::build_node_map() {
  for (auto node : ctx_->nodes()) {
    for (auto& src : node->srcs()) {
      node_map_[src.id()].push_back(&src);
    }
  }
}

void compiler::replace_map_sources(lnodeimpl* source, lnodeimpl* target) {
  auto& t_refs = node_map_.at(target->id());
  auto s_it = node_map_.find(source->id());
  assert(s_it != node_map_.end());
  for (auto node : s_it->second) {
    *const_cast<lnode*>(node) = target;
    t_refs.push_back(node);
  }
  for (auto& src : source->srcs()) {
    node_map_[src.id()].remove(&src);
  }
  node_map_.erase(s_it);
}

size_t compiler::remove_identity_nodes() {
  size_t deleted = 0;
  for (auto it = ctx_->proxies().begin(),
       end = ctx_->proxies().end(); it != end;) {
    proxyimpl* const proxy = *it++;
    if (proxy->is_identity()) {
      // replace proxy's uses with proxy's source
      this->replace_map_sources(proxy, proxy->src(0).impl());
      // delete proxy
      auto p_it = std::find(ctx_->nodes().begin(), ctx_->nodes().end(), proxy);
      ctx_->delete_node(p_it);
      ++deleted;
    }
  }
  return deleted;
}

void compiler::syntax_check() {
  // check for un-initialized nodes
  auto& undefs = ctx_->undefs();
  if (undefs.size()) {
#define LCOV_EXCL_START
    ctx_->dump_ast(std::cerr, 1);
    for (auto undef : undefs) {
      for (auto node : ctx_->nodes()) {
        auto ret = std::find_if(node->srcs().begin(), node->srcs().end(),
                     [undef](const lnode& x)->bool { return x.id() == undef->id(); });
        if (ret != node->srcs().end()) {
          int dump_ast_level = platform::self().dump_ast();
          if (dump_ast_level) {
            ctx_->dump_ast(std::cerr, dump_ast_level);
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
