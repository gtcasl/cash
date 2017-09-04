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

  virtual ~ch_simulator();
  
  void add_device(const ch_device& device);

  void step(ch_cycle t);
  
  void run(const std::function<bool(ch_cycle time)>& callback);
  
  void run(ch_cycle cycles = 20);

  ch_cycle reset(ch_cycle t);

  void tick(ch_cycle t);

protected:

  ch_simulator(const std::initializer_list<const ch_device*>& devices);

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
