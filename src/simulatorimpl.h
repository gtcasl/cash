#pragma once

#include "device.h"
#include "context.h"

namespace ch {
namespace internal {

class clock_driver {
public:
  clock_driver(bool value) : value_(value) {}

  void add_node(lnodeimpl* node);

  void flip();

  bool is_empty() const {
    return nodes_.empty();
  }

private:
  std::vector<lnodeimpl*> nodes_;
  bool value_;
};

class simulatorimpl : public refcounted {
public:
  simulatorimpl(const std::initializer_list<const device*>& devices);
  virtual ~simulatorimpl();

  void add_device(const device& device);

  virtual void tick(ch_tick t);

  void run(const std::function<bool(ch_tick t)>& callback);

  void run(ch_tick ticks);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t);

protected:

  virtual void ensureInitialize();

  std::unordered_set<context*> contexts_;
  bool initialized_;
  clock_driver clk_;
  clock_driver reset_;
};

}
}
