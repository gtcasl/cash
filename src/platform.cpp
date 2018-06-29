#include "platform.h"

using namespace ch::internal;

class platform::Impl {
  int dbg_level_;
  int dbg_wall_;
  int dbg_node_;
  int dbg_verilog_;
  int dump_ast_;
  int dump_cfg_;
  std::string lib_path_;

  Impl()
    : dbg_level_(0)
    , dbg_wall_(0)
    , dbg_node_(0)
    , dbg_verilog_(0)
    , dump_ast_(0)
    , dump_cfg_(0) {

    auto dbg_level = std::getenv("CASH_DEBUG_LEVEL");
    if (dbg_level) {
      dbg_level_ = atol(dbg_level);
    }

    auto dbg_wall = std::getenv("CASH_DEBUG_WALL");
    if (dbg_wall) {
      dbg_wall_ = atol(dbg_wall);
    }

    auto dbg_node = std::getenv("CASH_DEBUG_NODE");
    if (dbg_node) {
      dbg_node_ = atol(dbg_node);
    }

    auto dbg_verilog = std::getenv("CASH_DEBUG_VERILOG");
    if (dbg_verilog) {
      dbg_verilog_ = atol(dbg_verilog);
    }

    auto dump_ast = std::getenv("CASH_DUMP_AST");
    if (dump_ast) {
      dump_ast_ = atol(dump_ast);
    }

    auto dump_cfg = std::getenv("CASH_DUMP_CFG");
    if (dump_cfg) {
      dump_cfg_ = atol(dump_cfg);
    }

    auto lib_path = std::getenv("CASH_HOME");
    if (lib_path) {
      lib_path_ = lib_path;
    }
  }

  friend class platform;
};

platform::platform() {
  impl_ = new Impl();
}

platform::~platform() {
  delete impl_;
}

int platform::dbg_level() const {
  return impl_->dbg_level_;
}

int platform::dbg_wall() const {
  return impl_->dbg_wall_;
}

int platform::dbg_node() const {
  return impl_->dbg_node_;
}

int platform::dbg_verilog() const {
  return impl_->dbg_verilog_;
}

int platform::dump_ast() const {
  return impl_->dump_ast_;
}

int platform::dump_cfg() const {
  return impl_->dump_cfg_;
}

const std::string& platform::lib_path() const {
  return impl_->lib_path_;
}

const platform& platform::self() {
  static platform s_instance;
  return s_instance;
}
