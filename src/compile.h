#pragma once

#include "context.h"

namespace ch {
namespace internal {

class compiler {
public:  

  compiler(context* ctx);

  void compile();

  void build_eval_context(context* eval_ctx);

  void build_eval_list(std::vector<lnodeimpl*>& eval_list);

  static void build_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id);
  
protected:

  typedef std::unordered_map<uint32_t, std::unordered_set<const lnode*>> node_map_t;

  void build_node_map();

  size_t dead_code_elimination();

  void check_undefs();

  size_t gates_optimization();

  size_t common_subexpressions_elimination();

  size_t proxies_coalescing();

  void map_replace_target(lnodeimpl* from, lnodeimpl* to);

  void map_delete(lnodeimpl* node);

  void delete_map_source(lnodeimpl* node);  

  node_map_t node_map_;

  context* ctx_;
};

}
}
