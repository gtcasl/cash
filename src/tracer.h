#pragma once

#include "simulator.h"

namespace ch {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  template <typename... Modules>
  ch_tracer(std::ostream& out, const module& module, const Modules&... more)
    : ch_tracer(out, {get_ctx(module), get_ctx(more)...})
  {}

  template <typename... Modules>
  ch_tracer(const char* file, const module& module, const Modules&... more)
    : ch_tracer(file, {get_ctx(module), get_ctx(more)...})
  {}

  ch_tracer(std::ostream& out) : ch_tracer(out, {}) {}

  ch_tracer(const char* file) : ch_tracer(file, {}) {}

  ~ch_tracer();

protected:

  ch_tracer(std::ostream& out, const std::initializer_list<context*>& contexts);

  ch_tracer(const char* file, const std::initializer_list<context*>& contexts);

  ch_tracer(simulatorimpl* impl);
};

}
}

