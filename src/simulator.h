#pragma once

#include "module.h"

namespace ch {
namespace internal {

class simulatorimpl;

class ch_simulator {
public:  
  
  template <typename... Modules>
  ch_simulator(const module& module, const Modules&... more)
    : ch_simulator({get_ctx(module), get_ctx(more)...})
  {}

  ch_simulator() : ch_simulator({}) {}

  ch_simulator(const ch_simulator& simulator);

  virtual ~ch_simulator();

  ch_simulator& operator=(const ch_simulator& simulator);
  
  void add_module(const module& module);

  ch_tick step(ch_tick t);
  
  void run(const std::function<bool(ch_tick t)>& callback);
  
  void run(ch_tick ticks = 1);

  ch_tick reset(ch_tick t);

  void tick(ch_tick t);

protected:

  ch_simulator(const std::initializer_list<context*>& contexts);

  ch_simulator(simulatorimpl* impl);

  simulatorimpl* impl_;
};

}
}
