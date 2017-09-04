#pragma once

#include "context.h"

namespace cash {
namespace internal {

class deviceimpl {
public:
  deviceimpl() {
    ctx_ = ctx_create();
  }

  ~deviceimpl() {
    ctx_->release();
    ctx_ = nullptr;
  }

  void begin_context() {
    ctx_set(ctx_);
  }

  void end_context();

  context* get_ctx() const {
    return ctx_;
  }

  lnodeimpl* bind_input(const snode& bus) const {
    return ctx_->bind_input(bus);
  }

  snodeimpl* bind_output(const lnode& output) const {
    return ctx_->bind_output(output);
  }

  snodeimpl* get_tap(const std::string& name, uint32_t size) const {
    return ctx_->get_tap(name, size);
  }

  void to_verilog(const std::string& module_name, std::ostream& out) {
    ctx_->to_verilog(module_name, out);
  }

  void dump_stats(std::ostream& out) {
    ctx_->dump_stats(out);
  }

private:
  context* ctx_;
};

}
}
