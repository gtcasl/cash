#include "platform.h"

using namespace ch::internal;

struct platform::Impl {
  int dbg_level;
  int dbg_node;
  int dump_ast;
  int dump_cfg;
  std::string lib_path;

  Impl()
    : dbg_level(0)
    , dbg_node(0)
    , dump_ast(0)
    , dump_cfg(0) {
    auto _dbg_level = std::getenv("CASH_DEBUG_LEVEL");
    if (_dbg_level)
      dbg_level = atol(_dbg_level);

    auto _dbg_node = std::getenv("CASH_DEBUG_NODE");
    if (_dbg_node)
      dbg_node = atol(_dbg_node);

    auto _dump_ast = std::getenv("CASH_DUMP_AST");
    if (_dump_ast)
      dump_ast = atol(_dump_ast);

    auto _dump_cfg = std::getenv("CASH_DUMP_CFG");
    if (_dump_cfg)
      dump_cfg = atol(_dump_cfg);

    auto _lib_path = std::getenv("CASH_PATH");
    if (_lib_path)
      lib_path = _lib_path;
  }
};

platform::platform() {
  impl_ = new Impl();
}

platform::~platform() {
  delete impl_;
}

int platform::get_dbg_level() const {
  return impl_->dbg_level;
}

int platform::get_dbg_node() const {
  return impl_->dbg_node;
}

int platform::get_dump_ast() const {
  return impl_->dump_ast;
}

int platform::get_dump_cfg() const {
  return impl_->dump_cfg;
}

const char* platform::get_lib_path() const {
  return impl_->lib_path.c_str();
}

const platform& platform::self() {
  static platform s_instance;
  return s_instance;
}
