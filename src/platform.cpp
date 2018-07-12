#include "platform.h"

using namespace ch::internal;

class platform::Impl {
  int dbg_level_;
  int dbg_node_;
  int cflags_;

  Impl()
    : dbg_level_(0)
    , dbg_node_(0)
    , cflags_(0) {

    auto dbg_level = std::getenv("CASH_DEBUG_LEVEL");
    if (dbg_level) {
      dbg_level_ = atol(dbg_level);
    }

    auto dbg_node = std::getenv("CASH_DEBUG_NODE");
    if (dbg_node) {
      dbg_node_ = atol(dbg_node);
    }

    auto cflags = std::getenv("CASH_CFLAGS");
    if (cflags) {
      cflags_ = atol(cflags);
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

int platform::dbg_node() const {
  return impl_->dbg_node_;
}

ch::internal::cflags platform::cflags() const {
  return ch::internal::cflags(impl_->cflags_);
}

const platform& platform::self() {
  static platform s_instance;
  return s_instance;
}
