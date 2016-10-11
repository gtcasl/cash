#define CATCH_CONFIG_MAIN
#include "common.h"

bool runtest(const std::function<ch_logic()>& test, ch_cycle cycles) {
  ch_signal ret;
  ch_device dev(test, ret);
  ch_simulator sim(dev);
  sim.run(cycles);
  return static_cast<bool>(ret);
}
