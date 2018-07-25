#pragma once

#include "simulator.h"

namespace ch {
namespace internal {

class ch_tracer : public ch_simulator {
public:

  ch_tracer() {}

  ch_tracer(const ch_device_list& devices);

  template <typename... Devices>
  ch_tracer(const device& first, const Devices&... more)
    : ch_tracer(ch_device_list{first, (more)...})
  {}

  ch_tracer(const ch_tracer& other);

  ch_tracer(ch_tracer&& other);

  ~ch_tracer();

  ch_tracer& operator=(const ch_tracer& other);

  ch_tracer& operator=(ch_tracer&& other);

  void toText(const std::string& file);

  void toVCD(const std::string& file);

  void toTestBench(const std::string& file, const std::string& module);

protected:

  ch_tracer(simulatorimpl* impl);
};

}
}

