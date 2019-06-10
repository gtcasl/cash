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

  bool dead_code_elimination();

  bool prune_identity_proxies();

  bool constant_folding();

  bool subexpressions_elimination();

  bool proxies_coalescing();

  bool branch_coalescing();

  lnodeimpl* constant_fold(proxyimpl* node);
  lnodeimpl* constant_fold(selectimpl* node);
  lnodeimpl* constant_fold(opimpl* node);
  lnodeimpl* constant_fold_bitwise(opimpl* node);

  context* ctx_;
};

}
}
