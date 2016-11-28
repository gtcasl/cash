#include "opt.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "context.h"
#include "mem.h"

using namespace std;
using namespace chdl_internal;

optimizer::optimizer(context* ctx) : m_ctx(ctx) {}

void optimizer::optimize() {
  size_t orig_num_nodes = m_ctx->m_nodes.size();
  
  m_ctx->get_live_nodes(m_live_nodes);
  
  this->dead_node_elimination();
  
#ifndef NDEBUG
  // dump nodes
  uint32_t dump_ast = platform::self().get_dump_ast();
  if (dump_ast) {
    m_ctx->dumpAST(std::cerr, dump_ast);
  }
#endif
  
  DBG(2, "Before optimization: %lu\n", orig_num_nodes);
  DBG(2, "After dead code elimination: %lu\n", m_ctx->m_nodes.size());  
}

bool optimizer::dead_node_elimination() {
  set<lnodeimpl*> live_nodes = m_live_nodes;    
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  
  while (!working_set.empty()) {
    lnodeimpl* nimpl = working_set.front();      
    for (auto& src : nimpl->get_srcs()) {
      lnodeimpl* src_impl = src.get_impl();
      auto iter = live_nodes.emplace(src_impl);
      if (iter.second)
        working_set.emplace_back(src_impl);
    }    
    working_set.pop_front();
  }
  
  return (this->remove_dead_nodes(live_nodes) != 0);
}

size_t optimizer::remove_dead_nodes(const std::set<lnodeimpl*>& live_nodes) {
  size_t deleted = 0;
  auto& nodes = m_ctx->m_nodes;
  auto iter = nodes.begin();
  while (iter != nodes.end()) {
    if (live_nodes.count(*iter) == 0) {
      lnodeimpl* node = *iter;
      DBG(3, "*** deleting node: %s%d(#%d)!\n", node->get_name().c_str(), node->get_size(), node->get_id());
      iter = m_ctx->erase_node(iter);
      ++deleted;      
    } else {
      ++iter;
    }
  }
  return deleted;
}
