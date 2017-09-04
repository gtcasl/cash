#pragma once

#include "common.h"

namespace cash {
namespace internal {

class platform {
public:
  
  platform();
  
  int get_dbg_level() const {
    return dbg_level_;
  }
  
  int get_dbg_node() const {
    return dbg_node_;
  }
  
  int get_dump_ast() const {
    return dump_ast_;
  }
  
  int get_dump_cfg() const {
    return dump_cfg_;
  }
  
  static const platform& self();
  
private:

  class Impl;
  
  int dbg_level_;
  int dbg_node_;
  int dump_ast_;
  int dump_cfg_;
};

}
}
