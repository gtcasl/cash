#pragma once

#include "device.h"

namespace ch {
namespace internal {

class simulatorimpl;

class ch_simulator {
public:  
  
  ch_simulator();

  ch_simulator(const ch_device_list& devices);

  template <typename... Devices>
  ch_simulator(const device& first, const Devices&... more)
    : ch_simulator(ch_device_list{first, (more)...})
  {}

  ch_simulator(const ch_simulator& simulator);

  ch_simulator(ch_simulator&& simulator);

  virtual ~ch_simulator();

  ch_simulator& operator=(const ch_simulator& simulator);

  ch_simulator& operator=(ch_simulator&& simulator);
  
  void run(ch_tick ticks = 1);

  ch_tick run(const std::function<bool(ch_tick t)>& callback);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t, uint32_t count = 1);

  void eval(ch_tick t);

protected:

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
