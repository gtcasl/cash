#include "opt.h"
#include "litimpl.h"
#include "regimpl.h"
#include "aluimpl.h"
#include "context.h"
#include "mem.h"

using namespace std;
using namespace chdl_internal;

optimizer::optimizer(context* ctx) : m_ctx(ctx) {}

optimizer::~optimizer() {}

void optimizer::optimize() {
  cerr << "Before optimization: " << m_ctx->nodes.size() << endl;
  
  m_ctx->get_live_nodes(m_live_nodes);
  
  this->dead_node_elimination();
  cerr << "After dead node elimination: " << m_ctx->nodes.size() << endl;
  
  // syntax check
  m_ctx->syntax_check();
  
  // dump nodes
  m_ctx->dumpNodes(cout);
}

bool optimizer::dead_node_elimination() {
  set<lnodeimpl*> live_nodes = m_live_nodes;    
  std::list<lnodeimpl*> working_set(live_nodes.begin(), live_nodes.end());
  
  while (!working_set.empty()) {
    lnodeimpl* nimpl = working_set.front();      
    for (auto& src : nimpl->get_srcs()) {
      lnodeimpl* src_impl = get_impl<lnodeimpl>(src);
      assert(src_impl);
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
  auto& nodes = m_ctx->nodes;
  auto iter = nodes.begin();
  while (iter != nodes.end()) {
    if (live_nodes.count(*iter) == 0) {
      iter = m_ctx->erase_node(iter);
      ++deleted;      
    } else {
      ++iter;
    }
  }
  return deleted;
}
