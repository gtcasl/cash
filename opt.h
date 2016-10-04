#pragma once

#include "lnode.h"

namespace chdl_internal {

class context;

class optimizer {
public:  
  optimizer(context* ctx);  
  virtual ~optimizer();
  
  void optimize();
  
protected:  
  
  bool dead_node_elimination();

  size_t remove_dead_nodes(const std::set<lnodeimpl*>& live_nodes);  
  
  std::set<lnodeimpl*> m_live_nodes;
  context* m_ctx;
};

}
