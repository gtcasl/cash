#pragma once

#include "device.h"
#include "context.h"

namespace ch {
namespace internal {

class clock_driver {
public:

  clock_driver(bool value = false) : value_(value) {}

  void add_signal(lnodeimpl* node);

  void flip();

  bool empty() const {
    return nodes_.empty();
  }

protected:

  std::vector<lnodeimpl*> nodes_;
  bool value_;
};

class simulatorimpl : public refcounted {
public:

  simulatorimpl(const ch_device_list& devices);

  virtual ~simulatorimpl();

  ch_tick run(const std::function<bool(ch_tick t)>& callback);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t);

  ch_tick step(ch_tick t, uint32_t count);

  void run(ch_tick ticks);

  virtual void eval(ch_tick t);

protected:

  void initialize();

  std::unordered_set<context*> contexts_;
  clock_driver clk_driver_;
  clock_driver reset_driver_;
  std::vector<lnodeimpl*> run_list_;
};

}
}
