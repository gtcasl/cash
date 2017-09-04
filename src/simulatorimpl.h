#pragma once

#include "device.h"
#include "context.h"
#include "snodeimpl.h"

namespace cash {
namespace internal {

class simulatorimpl {
public:
  simulatorimpl(const std::initializer_list<const ch_device*>& devices);
  virtual ~simulatorimpl();

  void add_device(const ch_device& device);

  virtual void tick(ch_cycle t);

  void run(const std::function<bool(ch_cycle time)>& callback);

  void run(ch_cycle cycles);

  ch_cycle reset(ch_cycle t);

  void step(ch_cycle t);

protected:

  virtual void ensureInitialize();

  std::unordered_set<context*> contexts_;
  bool initialized_;
  snodeimpl* clk_;
  snodeimpl* reset_;
};

}
}
