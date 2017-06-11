#pragma once

#include "lnode.h"

namespace cash {
namespace detail {

class ch_compiler {
public:  
  ch_compiler(context* ctx);
  
  void run();
  
protected:  
  
  bool dead_code_elimination();
  
  void syntax_check();

  size_t remove_dead_nodes(const std::set<lnodeimpl*>& live_nodes);  

  std::set<lnodeimpl*> live_nodes_;
  context* ctx_;
};

}
}
