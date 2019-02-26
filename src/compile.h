#pragma once

#include "context.h"

namespace ch {
namespace internal {

class compiler {
public:  

  compiler(context* ctx);

  void optimize();

  void create_merged_context(context* ctx);

  void build_eval_list(std::vector<lnodeimpl*>& eval_list);

  static bool build_bypass_list(std::unordered_set<uint32_t>& out, context* ctx, uint32_t cd_id);
  
protected:

  typedef std::unordered_map<uint32_t, std::unordered_set<const lnode*>> node_map_t;

  void build_node_map();

  void build_node_map(lnodeimpl* node);

  void check_undefs();

  bool dead_code_elimination();

  bool constant_folding();

  bool subexpressions_elimination();

  bool prune_identity_proxies();

  bool proxies_coalescing();

  lnodeimpl* constant_fold(proxyimpl* node);
  lnodeimpl* constant_fold(selectimpl* node);
  lnodeimpl* constant_fold(aluimpl* node);
  lnodeimpl* constant_fold_bitwise(aluimpl* node);

  void map_replace_target(lnodeimpl* from, lnodeimpl* to);
  void map_delete(lnodeimpl* node);

  node_map_t node_map_;

  context* ctx_;
};

}
}
