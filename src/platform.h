#pragma once

#include "common.h"

namespace ch {
namespace internal {

class platform {
public:  
  platform();
  ~platform();

  static const platform& self();
  
  int get_dbg_level() const;
  
  int get_dbg_node() const;
  
  int get_dump_ast() const;
  
  int get_dump_cfg() const;

  const std::string& get_lib_path() const;
  
protected:
  class Impl;
  Impl* impl_;
};

}
}
