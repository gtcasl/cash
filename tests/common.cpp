#include "common.h"

static void begin_test() {
  static int test_number = 0;
  std::cout << "running test #" << test_number++ << " ..." << std::endl;
}

struct TestRunner {
  __io (
    __out(ch_bool) out
  );
  TestRunner(const std::function<ch_bool ()>& test) : test_(test) {}
  void describe() {
    io.out = test_();
  }
  const std::function<ch_bool()> test_;
};

bool runtest(const std::function<ch_bool ()>& test, ch_tick ticks) {
  assert(ticks > 0);
  begin_test();

  ch_device<TestRunner> device(test);
  ch_simulator sim(device);

  sim.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
    if (t > 0 && !(bool)device.io.out)
      return false;
    return (t < ticks);
  });

  bool bRet = (bool)device.io.out;
  assert(bRet);
  return bRet;
}

bool runtestx(const std::function<bool()>& test) {
  begin_test();
  bool bRet = test();
  assert(bRet);
  return bRet;
}

bool checkVerilog(const std::string& file) {
  int ret = system(stringf("iverilog %s -o %s.iv", file.c_str(), file.c_str()).c_str())
          | system(stringf("vvp %s.iv", file.c_str()).c_str());
  assert(0 == ret );
  return (0 == ret);
}
