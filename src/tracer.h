#pragma once

#include "simulator.h"

namespace ch {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  template <typename... Devices>
  ch_tracer(std::ostream& out, const device& device, const Devices&... more)
    : ch_tracer(out, {get_ctx(device), get_ctx(more)...})
  {}

  template <typename... Devices>
  ch_tracer(const std::string& file, const device& device, const Devices&... more)
    : ch_tracer(file, {get_ctx(device), get_ctx(more)...})
  {}

  ch_tracer(std::ostream& out) : ch_tracer(out, {}) {}

  ch_tracer(const std::string& file) : ch_tracer(file, {}) {}

  ~ch_tracer();

protected:

  ch_tracer(std::ostream& out, const std::initializer_list<context*>& contexts);

  ch_tracer(const std::string& file, const std::initializer_list<context*>& contexts);

  ch_tracer(simulatorimpl* impl);
};

}
}

