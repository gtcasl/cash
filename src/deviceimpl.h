#pragma once

#include "context.h"

namespace cash {
namespace internal {

class deviceimpl {
public:
  deviceimpl();

  ~deviceimpl();

  void begin_context();

  void end_context();

  void compile();

  context* get_ctx() const {
    return ctx_;
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
  context* old_ctx_;
};

}
}
