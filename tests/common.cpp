#include "common.h"
#include <limits>

static int g_test_number = 0;

static bool begin_test() {
  ++g_test_number;
  auto testid = std::getenv("CASH_TESTID");
  if (testid) {
    auto id = atol(testid);
    if (id != 0 && g_test_number != id)
      return false;
  }
  std::cout << "running test #" << g_test_number << " ..." << std::endl;
  return true;
}

static bool end_test(bool passed, const ch::internal::source_location& sloc) {
  if (!passed) {
    std::cout << "error: test #" << g_test_number << " failed! (" << sloc << ")" << std::endl;
    std::abort();
  }
  return passed;
}

struct TestRunner {
  __io (
    __out (ch_bool) out
  );

  TestRunner(const std::function<ch_bool ()>& test)
    : test_(test)
  {}

  void describe() {
    io.out = test_();
  }

  const std::function<ch_bool()> test_;
};

struct TestRunner1 {
  __io (
    __in (ch_int8) in1,
    __out (ch_bool) out
  );

  TestRunner1(const std::function<ch_bool (const ch_int8&)>& test)
    : test_(test)
  {}

  void describe() {
    io.out = test_(io.in1);
  }

  const std::function<ch_bool(const ch_int8&)> test_;
};

struct TestRunner2 {
  __io (
    __in (ch_int8) in1,
    __in (ch_int8) in2,
    __out (ch_bool) out
  );

  TestRunner2(const std::function<ch_bool (const ch_int8&, const ch_int8&)>& test)
    : test_(test)
  {}

  void describe() {
    io.out = test_(io.in1, io.in2);
  }

  const std::function<ch_bool(const ch_int8&, const ch_int8&)> test_;
};

RetCheck& RetCheck::operator&=(const sloc_proxy<bool>& value) {
  if (!value.value) {
    std::cout << "error: test #" << g_test_number << " failed! (" << value.sloc << ")" << std::endl;
    std::abort();
  }
  count_ = value.value ? (count_ + 1) : std::numeric_limits<int>::min();
  return *this;
}

bool TEST(const std::function<ch_bool ()>& test,
          ch_tick cycles,
          const ch::internal::source_location& sloc) {
  if (!begin_test())
    return true;

  ch_device<TestRunner> device(test);
  ch_simulator sim(device);  

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);  
  bool ret = true;

  sim.run([&](ch_tick t)->bool {
  #ifndef NDEBUG
    std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
  #endif
    ret &= (bool)device.io.out;
    return (t < ticks);
  });

  return end_test(ret, sloc);
}

bool TEST1(const std::function<ch_bool (const ch_int8&)>& test,
           ch_tick cycles,
           const ch::internal::source_location& sloc) {
  if (!begin_test())
    return true;

  ch_device<TestRunner1> device(test);
  ch_simulator sim(device);

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);
  bool ret = true;

  device.io.in1 = 1;

  sim.run([&](ch_tick t)->bool {
  #ifndef NDEBUG
    std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
  #endif
    ret &= (bool)device.io.out;
    return (t < ticks);
  });

  return end_test(ret, sloc);
}

bool TEST2(const std::function<ch_bool (const ch_int8&, const ch_int8&)>& test,
           ch_tick cycles,
           const ch::internal::source_location& sloc) {
  if (!begin_test())
    return true;

  ch_device<TestRunner2> device(test);
  ch_simulator sim(device);

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);
  bool ret = true;

  device.io.in1 = 1;
  device.io.in2 = 2;

  sim.run([&](ch_tick t)->bool {
  #ifndef NDEBUG
    std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
  #endif
    ret &= (bool)device.io.out;
    return (t < ticks);
  });

  return end_test(ret, sloc);
}

bool TESTX(const std::function<bool()>& test,
           const ch::internal::source_location& sloc) {
  if (!begin_test())
    return true;
  return end_test(test(), sloc);
}

bool checkVerilog(const std::string& file) {
  int ret = system(stringf("iverilog %s -o %s.iv", file.c_str(), file.c_str()).c_str())
          | system(stringf("! vvp %s.iv | grep 'ERROR' || false", file.c_str()).c_str());
  return (0 == ret);
}
