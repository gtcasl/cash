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

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value)>
  void add_trace(const std::string& name, const U& var) {
    this->add_trace(name, scalar_accessor::buffer(var));
  }

protected:

  ch_tracer(std::ostream& out, const std::initializer_list<context*>& contexts);

  ch_tracer(const std::string& file, const std::initializer_list<context*>& contexts);

  ch_tracer(simulatorimpl* impl);

  void add_trace(const std::string& name, const scalar_buffer_ptr& buffer);
};

}
}

