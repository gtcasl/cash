#pragma once

#include "device.h"
#include "context.h"
#include "snodeimpl.h"

namespace cash {
namespace internal {

class simulatorimpl : public refcounted {
public:
  simulatorimpl(const std::initializer_list<const ch_device*>& devices);
  virtual ~simulatorimpl();

  void add_device(const ch_device& device);

  virtual void tick(ch_tick t);

  void run(const std::function<bool(ch_tick t)>& callback);

  void run(ch_tick ticks);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t);

protected:

  virtual void ensureInitialize();

  std::unordered_set<context*> contexts_;
  bool initialized_;
  snodeimpl* clk_;
  snodeimpl* reset_;
};

}
}
