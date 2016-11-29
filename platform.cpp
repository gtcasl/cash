#include "common.h"
#include "platform.h"

platform::platform()
  : m_dbg_level(1)  
  , m_dbg_node(0)
  , m_dump_ast(0)
  , m_dump_cfg(0) {
  const char* dbg_level = std::getenv("CHDL_DEBUG_LEVEL");
  if (dbg_level)
    m_dbg_level = atol(dbg_level);
  
  const char* dbg_node = std::getenv("CHDL_DEBUG_NODE");
  if (dbg_node)
    m_dbg_node = atol(dbg_node);
  
  const char* dump_ast = std::getenv("CHDL_DUMP_AST");
  if (dump_ast)
    m_dump_ast = atol(dump_ast);  
  
  const char* dump_cfg = std::getenv("CHDL_DUMP_CFG");
  if (dump_cfg)
    m_dump_cfg = atol(dump_cfg);  
}

const platform& platform::self() {
  static platform s_instance;
  return s_instance;
}
