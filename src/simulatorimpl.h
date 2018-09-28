#pragma once

#include "device.h"
#include "context.h"

namespace ch {
namespace internal {

class clock_driver {
public:

  clock_driver(bool value = false) : value_(value) {}

  void add_signal(inputimpl* node);

  void eval();

  bool empty() const {
    return nodes_.empty();
  }

protected:

  std::vector<inputimpl*> nodes_;
  bool value_;
};

class time_driver {
public:

  time_driver(bool value = false) : value_(value) {}

  void add_signal(inputimpl* node);

  void eval();

  bool empty() const {
    return nodes_.empty();
  }

protected:

  std::vector<inputimpl*> nodes_;
  uint64_t value_;
};

class sim_driver : public refcounted {
public:

  sim_driver() {}

  virtual ~sim_driver() {}

  virtual void initialize(const std::vector<lnodeimpl*>&) = 0;

  virtual void eval() = 0;
};

class simulatorimpl : public refcounted {
public:

  simulatorimpl(const ch_device_list& devices);

  virtual ~simulatorimpl();

  ch_tick run(const std::function<bool(ch_tick t)>& callback);

  ch_tick reset(ch_tick t);

  ch_tick step(ch_tick t);

  ch_tick step(ch_tick t, uint32_t count);

  void run(ch_tick num_ticks);

  virtual void eval();

protected:

  void initialize();

  std::vector<context*> contexts_;
  clock_driver clk_driver_;
  clock_driver reset_driver_;
  time_driver time_driver_;
  sim_driver* sim_driver_;
};

}
}
