#pragma once

#include "simulator.h"

namespace ch {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  ch_tracer() {}

  ch_tracer(std::ostream& out, const ch_device_list& devices);

  ch_tracer(const std::string& file, const ch_device_list& devices);

  template <typename... Devices>
  ch_tracer(std::ostream& out, const device& first, const Devices&... more)
    : ch_tracer(out, ch_device_list{first, (more)...})
  {}

  template <typename... Devices>
  ch_tracer(const std::string& file, const device& first, const Devices&... more)
    : ch_tracer(file, ch_device_list{first, (more)...})
  {}

  ch_tracer(const ch_tracer& tracer);

  ch_tracer(ch_tracer&& tracer);

  ~ch_tracer();

  ch_tracer& operator=(const ch_tracer& tracer);

  ch_tracer& operator=(ch_tracer&& tracer);

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>)>
  void add_trace(const std::string& name, const U& var) {
    this->add_trace(name, scalar_accessor::buffer(var));
  }

protected:

  ch_tracer(simulatorimpl* impl);

  void add_trace(const std::string& name, const scalar_buffer_ptr& buffer);
};

}
}

