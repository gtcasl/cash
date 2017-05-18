#pragma once

namespace cash {
namespace detail {

class platform {
public:
  
  platform();
  
  uint32_t get_dbg_level() const {
    return dbg_level_;
  }
  
  uint32_t get_dbg_node() const {
    return dbg_node_;
  }
  
  uint32_t get_dump_ast() const {
    return dump_ast_;
  }
  
  uint32_t get_dump_cfg() const {
    return dump_cfg_;
  }
  
  static const platform& self();
  
private:  
  
  uint32_t dbg_level_;
  uint32_t dbg_node_;
  uint32_t dump_ast_;  
  uint32_t dump_cfg_;
};

}
}
