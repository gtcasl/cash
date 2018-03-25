#pragma once

#include "device.h"
#include "context.h"

namespace ch {
namespace internal {

class clock_driver {
public:

  clock_driver() : value_(false) {}

  void add_signal(lnodeimpl* node);

  void flip();

  bool is_empty() const {
    return nodes_.empty();
  }

protected:

  std::vector<lnodeimpl*> nodes_;
  bool value_;
};

class simulatorimpl : public refcounted {
public:

  simulatorimpl(const std::initializer_list<context*>& contexts);

  virtual ~simulatorimpl();

  void add_device(const device& device);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t);

  ch_tick step(ch_tick t, unsigned count);  

  ch_tick run(const std::function<bool(ch_tick t)>& callback);

  void run(ch_tick ticks);

protected:

  virtual void ensureInitialize();

  virtual void tick(ch_tick t);

  std::unordered_set<context*> contexts_;
  bool initialized_;
  clock_driver clk_driver_;
  clock_driver reset_driver_;
};

}
}
