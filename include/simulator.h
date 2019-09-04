#pragma once

#include "device.h"

namespace ch {
namespace internal {

class simulatorimpl;

class ch_simulator {
public:  
  
  ch_simulator();

  ch_simulator(const std::vector<device_base>& devices);

  template <typename... Devices>
  ch_simulator(const device_base& first, const Devices&... more)
    : ch_simulator(std::vector<device_base>{first, (more)...})
  {}

  ch_simulator(const ch_simulator& other);

  ch_simulator(ch_simulator&& other);

  virtual ~ch_simulator();

  ch_simulator& operator=(const ch_simulator& other);

  ch_simulator& operator=(ch_simulator&& other);
  
  void run(ch_tick ticks = 1);

  ch_tick run(const std::function<bool(ch_tick t)>& callback, uint32_t steps = 1);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t, uint32_t count = 1);

  void eval();

protected:

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
