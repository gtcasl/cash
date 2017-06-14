#define CATCH_CONFIG_MAIN
#include "common.h"

static void begin_test() {
  static int test_number = 0;
  std::cout << "running test #" << test_number++ << " ..." << std::endl;
}

bool runtest(const std::function<ch_bit<1>()>& test, ch_cycle cycles) {
  begin_test();
  
  ch_bus1 ret;
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

bool runtestx(const std::function<bool()>& test) {
  begin_test();
  return test();
}
