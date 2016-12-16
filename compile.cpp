#include "compile.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "context.h"
#include "mem.h"

using namespace std;
using namespace chdl_internal;

ch_compiler::ch_compiler(context* ctx) : m_ctx(ctx) {}

void ch_compiler::run() {
  size_t orig_num_nodes = m_ctx->m_nodes.size();
  
  m_ctx->get_live_nodes(m_live_nodes);
  
  this->dead_code_elimination();
  
  this->syntax_check();
  
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

void ch_compiler::syntax_check() {
  // check for un-initialized nodes
  const auto& undefs = m_ctx->m_undefs;
  if (undefs.size()) {
    m_ctx->dumpAST(std::cerr, 1);    
    for (auto node : undefs) {
      fprintf(stderr, "error: un-initialized node %s%d(#%d)!\n", node->get_name(), node->get_size(), node->get_id());
    }
    if (undefs.size() == 1)
      CHDL_ABORT("1 node has not been initialized.");
    else
      CHDL_ABORT("%zd nodes have not been initialized.", undefs.size());
  }
}

bool ch_compiler::dead_code_elimination() {
  set<lnodeimpl*> live_nodes = m_live_nodes;    
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  
  while (!working_set.empty()) {
    lnodeimpl* const nimpl = working_set.front();      
    for (auto& src : nimpl->get_srcs()) {
      lnodeimpl* const src_impl = src.get_impl();
      auto iter = live_nodes.emplace(src_impl);
      if (iter.second)
        working_set.emplace_back(src_impl);
    }    
    working_set.pop_front();
  }
  
  return (this->remove_dead_nodes(live_nodes) != 0);
}

size_t ch_compiler::remove_dead_nodes(const std::set<lnodeimpl*>& live_nodes) {
  size_t deleted = 0;
  auto& nodes = m_ctx->m_nodes;
  auto iter = nodes.begin();
  while (iter != nodes.end()) {
    auto iterCur = iter++;
    lnodeimpl* const node = *iterCur;
    if (0 == live_nodes.count(node)) {            
      delete node;
      ++deleted;      
    }
  }
  return deleted;
}
