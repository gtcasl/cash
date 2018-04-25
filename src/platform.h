#pragma once

#include "common.h"

namespace ch {
namespace internal {

class platform {
public:  

  platform();

  ~platform();

  static const platform& self();
  
  int dbg_level() const;
  
  int dbg_node() const;

  int dbg_verilog() const;
  
  int dump_ast() const;
  
  int dump_cfg() const;

  const std::string& lib_path() const;
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
