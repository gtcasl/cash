#define CATCH_CONFIG_MAIN
#include "common.h"

bool runtest(const std::function<ch_logic()>& test, ch_cycle cycles) {
  ch_signal ret;
  ch_device dev(test, ret);
  ch_simulator sim(dev);
  sim.run([&](ch_cycle cycle)->bool {    
    //std::cout << "t" << cycle << ": ret=" << ret << std::endl; 
    if (cycle > 0 && !static_cast<bool>(ret))
      return false;    
    return (cycle < cycles);
  });
  return static_cast<bool>(ret);
}
