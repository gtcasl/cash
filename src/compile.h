#pragma once

#include "context.h"

namespace ch {
namespace internal {

class compiler {
public:  

  compiler(context* ctx);
  
  void run();
  
protected:

  typedef std::unordered_map<uint32_t, std::list<const lnode*>> node_map_t;

  void build_node_map();

  size_t dead_code_elimination();

  size_t gates_optimization();

  size_t common_subexpressions_elimination();

  size_t proxies_coalescing();

  void replace_map_sources(lnodeimpl* source, lnodeimpl* target);

  void delete_map_source(lnodeimpl* node);

  void syntax_check();

  node_map_t node_map_;

  context* ctx_;
};

}
}
