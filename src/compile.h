#pragma once

#include "context.h"

namespace ch {
namespace internal {

typedef std::unordered_map<uint32_t, std::list<const lnode*>> node_map_t;

class compiler {
public:  

  compiler(context* ctx);
  
  void run();
  
protected:

  size_t dead_code_elimination();

  size_t remove_identity_nodes();
  
  void syntax_check();

  size_t remove_dead_nodes(const live_nodes_t& live_nodes);

  size_t do_cse();

  void build_node_map();

  void replace_map_sources(lnodeimpl* source, lnodeimpl* target);

  void delete_map_source(lnodeimpl* node);

  node_map_t node_map_;

  context* ctx_;
};

}
}
