#include "common.h"

static void begin_test() {
  static int test_number = 0;
  std::cout << "running test #" << test_number++ << " ..." << std::endl;
}

struct TestRunner {
  __io (
    (ch_out<ch_bit1>) out
  );
  TestRunner(const std::function<ch_bit<1>()>& test) : test_(test) {}
  void describe() {
    io.out = test_();
  }
  const std::function<ch_bit<1>()> test_;
};

bool runtest(const std::function<ch_bit<1>()>& test, ch_tick ticks) {
  assert(ticks > 0);
  begin_test();

  ch_module<TestRunner> module(test);
  ch_simulator sim(module);

  sim.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": ret=" << module->io.out << std::endl;
    if (t > 0 && !ch_peek<bool>(module->io.out))
      return false;
    return (t < ticks);
  });

  bool bRet = ch_peek<bool>(module->io.out);
  assert(bRet);
  return bRet;
}

bool runtestx(const std::function<bool()>& test) {
  begin_test();
  bool bRet = test();
  assert(bRet);
  return bRet;
}
