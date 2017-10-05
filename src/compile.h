#pragma once

#include "context.h"

namespace ch {
namespace internal {

class compiler {
public:  
  compiler(context* ctx);
  
  void run();
  
protected:
  
  size_t dead_code_elimination();

  size_t remove_identity_nodes();
  
  void syntax_check();

  size_t remove_dead_nodes(const live_nodes_t& live_nodes);

  void build_node_map();

  node_map_t node_map_;

  context* ctx_;
};

}
}
