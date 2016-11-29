#pragma once

class platform {
public:
  
  platform();
  
  uint32_t get_dbg_level() const {
    return m_dbg_level;
  }
  
  uint32_t get_dbg_node() const {
    return m_dbg_node;
  }
  
  uint32_t get_dump_ast() const {
    return m_dump_ast;
  }
  
  uint32_t get_dump_cfg() const {
    return m_dump_cfg;
  }
  
  static const platform& self();
  
private:  
  
  uint32_t m_dbg_level;
  uint32_t m_dbg_node;
  uint32_t m_dump_ast;  
  uint32_t m_dump_cfg;
};
