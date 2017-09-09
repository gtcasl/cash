#define CATCH_CONFIG_MAIN
#include "common.h"

static void begin_test() {
  static int test_number = 0;
  std::cout << "running test #" << test_number++ << " ..." << std::endl;
}

bool runtest(const std::function<ch_bit<1>()>& test, ch_tick ticks) {
  assert(ticks > 0);
  begin_test();
  
  ch_bus1 ret;
  ch_device dev(test, ret);
  ch_simulator sim(dev);

  sim.run([&](ch_tick t)->bool {
    // std::cout << "t" << tick << ": ret=" << ret << std::endl;
    if (t > 0 && !static_cast<bool>(ret))
      return false;
    return (t < ticks);
  });

  bool bRet = static_cast<bool>(ret);
  assert(bRet);
  return bRet;
}

bool runtestx(const std::function<bool()>& test) {
  begin_test();
  bool bRet = test();
  assert(bRet);
  return bRet;
}
