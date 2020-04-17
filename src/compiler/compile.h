#pragma once

#include "context.h"

namespace ch {
namespace internal {

class compiler {
public:  

  compiler(context* ctx);

  void optimize();

  bool isNodeSecureFromSrcs(lnodeimpl *Node);

  bool verifyOutputs();

  void create_merged_context(context* ctx, bool verbose_tracing = false);

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

  bool register_promotion();

  context* ctx_;
};

}
}
