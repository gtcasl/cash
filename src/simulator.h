#pragma once

#include "device.h"

namespace cash {
namespace internal {

class simulatorimpl;

class ch_simulator {
public:  
  
  template<typename ...Devices>
  ch_simulator(const ch_device& device, const Devices&... more)
    : ch_simulator({&device, &more...})
  {}

  ch_simulator() : ch_simulator({}) {}

  virtual ~ch_simulator();
  
  void add_device(const ch_device& device);

  ch_tick step(ch_tick t);
  
  void run(const std::function<bool(ch_tick t)>& callback);
  
  void run(ch_tick ticks = 20);

  ch_tick reset(ch_tick t);

  void tick(ch_tick t);

protected:

  ch_simulator(const std::initializer_list<const ch_device*>& devices);

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
