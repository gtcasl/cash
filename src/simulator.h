#pragma once

#include "device.h"

namespace ch {
namespace internal {

class simulatorimpl;

class ch_simulator {
public:  
  
  template <typename... Devices>
  ch_simulator(const device& device, const Devices&... more)
    : ch_simulator({&device, &more...})
  {}

  ch_simulator() : ch_simulator({}) {}

  ch_simulator(const ch_simulator& simulator);

  virtual ~ch_simulator();

  ch_simulator& operator=(const ch_simulator& simulator);
  
  void add_device(const device& device);

  ch_tick step(ch_tick t);
  
  void run(const std::function<bool(ch_tick t)>& callback);
  
  void run(ch_tick ticks = 20);

  ch_tick reset(ch_tick t);

  void tick(ch_tick t);

protected:

  ch_simulator(const std::initializer_list<const device*>& devices);

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
