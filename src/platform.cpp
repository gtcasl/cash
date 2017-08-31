#include "common.h"
#include "platform.h"

using namespace cash::internal;

platform::platform()
  : dbg_level_(0)
  , dbg_node_(0)
  , dump_ast_(0)
  , dump_cfg_(0) {
  const char* dbg_level = std::getenv("CASH_DEBUG_LEVEL");
  if (dbg_level)
    dbg_level_ = atol(dbg_level);
  
  const char* dbg_node = std::getenv("CASH_DEBUG_NODE");
  if (dbg_node)
    dbg_node_ = atol(dbg_node);
  
  const char* dump_ast = std::getenv("CASH_DUMP_AST");
  if (dump_ast)
    dump_ast_ = atol(dump_ast);  
  
  const char* dump_cfg = std::getenv("CASH_DUMP_CFG");
  if (dump_cfg)
    dump_cfg_ = atol(dump_cfg);  
}

const platform& platform::self() {
  static platform s_instance;
  return s_instance;
}
