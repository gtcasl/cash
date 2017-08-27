#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "proxyimpl.h"
#include "context.h"
#include "mem.h"

using namespace std;
using namespace cash::detail;

ch_compiler::ch_compiler(context* ctx) : ctx_(ctx) {}

void ch_compiler::run() {
  size_t orig_num_nodes = ctx_->nodes_.size();

  ctx_->get_live_nodes(live_nodes_);
  
  this->dead_code_elimination();
  
  this->syntax_check();
  
#ifndef NDEBUG
  // dump nodes
  int dump_ast_level = platform::self().get_dump_ast();
  if (dump_ast_level) {
    ctx_->dump_ast(std::cerr, dump_ast_level);
  }
#endif
  
  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After dead code elimination: %lu\n", ctx_->nodes_.size());  
}

void ch_compiler::syntax_check() {
  // check for un-initialized nodes
  const auto& undefs = ctx_->undefs_;
  if (undefs.size()) {
    ctx_->dump_ast(std::cerr, 1);    
    for (auto node : undefs) {
      fprintf(stderr, "error: un-initialized node %s%d(#%d)!\n", node->get_name(), node->get_size(), node->get_id());
    }
    if (1 == undefs.size())
      CH_ABORT("1 node has not been initialized.");
    else
      CH_ABORT("%zd nodes have not been initialized.", undefs.size());
  }
}

bool ch_compiler::dead_code_elimination() {
  std::unordered_map<proxyimpl*, std::unordered_set<uint32_t>> proxy_used_sources;
  std::unordered_set<lnodeimpl*> live_nodes = live_nodes_;
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  
  while (!working_set.empty()) {
    lnodeimpl* node = working_set.front();
    auto& srcs = node->get_srcs();

    // delete unused proxy sources
    auto proxy = dynamic_cast<proxyimpl*>(node);
    if (proxy) {
      if (proxy_used_sources.count(proxy)) {
        auto& uses = proxy_used_sources.at(proxy);
        uint32_t i = 0;
        for (auto it = srcs.begin(); it != srcs.end();) {
          if (0 == uses.count(i++)) {
            it = proxy->erase_source(it);
          } else {
            ++it;
          }
        }
      }
    }

    for (uint32_t i = 0, n = srcs.size(); i < n; ++i) {
      lnodeimpl* src_impl = srcs[i].get_impl();

      // special handling for proxy nodes
      auto src_proxy = dynamic_cast<proxyimpl*>(src_impl);
      if (src_proxy) {
        auto& uses = proxy_used_sources[src_proxy];
        if (proxy) {
          for (auto& curr : src_proxy->get_ranges()) {
            uint32_t curr_end = curr.dst_offset + curr.src_length;
            for (auto& range : proxy->get_ranges()) {
              if (range.src_idx == i) {
                uint32_t src_end = range.src_offset + range.src_length;
                // do ranges overlap?
                if (range.src_offset < curr_end && src_end > curr.dst_offset) {
                  uses.insert(curr.src_idx);
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

      auto ret = live_nodes.emplace(src_impl);
      if (ret.second) {
        // we have a new live node, add it to working set
        working_set.emplace_back(src_impl);
      }
    }    
    working_set.pop_front();
  }
  
  return (this->remove_dead_nodes(live_nodes) != 0);
}

size_t ch_compiler::remove_dead_nodes(const std::unordered_set<lnodeimpl*>& live_nodes) {
  size_t deleted = 0;
  for (auto iter = ctx_->nodes_.begin(),
       iterEnd = ctx_->nodes_.end(); iter != iterEnd;) {
    lnodeimpl* const node = *iter++;
    if (0 == live_nodes.count(node)) {            
      delete node;
      ++deleted;      
    }
  }
  return deleted;
}
