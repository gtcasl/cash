#include "common.h"
#include <limits>

static int g_test_number = 0;

static bool begin_test(const ch::internal::source_location& sloc) {
  ++g_test_number;
  auto testid = std::getenv("CASH_TESTID");
  if (testid) {
    auto id = atol(testid);
    if (id != 0 && g_test_number != id)
      return false;
  }
  std::cout << "running test #" << g_test_number << " (" << sloc << ") ..." << std::endl;
  return true;
}

static bool end_test(bool passed) {
  if (!passed) {
    std::cout << "error: test #" << g_test_number << " failed!" << std::endl;
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

RetCheck& RetCheck::operator&=(const sloc_arg<bool>& value) {
  if (!value.data) {
    std::cout << "error: test #" << g_test_number << " failed! (" << value.sloc << ")" << std::endl;
    std::abort();
  }
  count_ = value.data ? (count_ + 1) : std::numeric_limits<int>::min();
  return *this;
}

bool TESTG(const std::function<ch_bool ()>& test,
           ch_tick cycles,
           const ch::internal::source_location& sloc) {
  if (!begin_test(sloc))
    return true;

  bool ret = true;

  auto callback = [&](){  
    ch_device<TestRunner> device(test);
    ch_simulator sim(device);  

    auto ticks = (0 == cycles) ? 1 : (cycles * 2);  
    auto steps = (0 == cycles) ? 1 : 2;    

    sim.run([&](ch_tick t)->bool {
      ret &= (cycles != 0 && t == 0) || static_cast<bool>(device.io.out);
    #ifndef NDEBUG
      if (!ret) {
        std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
      }
    #endif
      return (t < ticks);
    }, steps);
  };

  CHECK_THROWS_AS(callback(), std::domain_error);  
  
  return end_test(ret);;
}

bool TEST(const std::function<ch_bool ()>& test,
          ch_tick cycles,
          const ch::internal::source_location& sloc) {
  if (!begin_test(sloc))
    return true;

  ch_device<TestRunner> device(test);
  ch_simulator sim(device);  

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);  
  auto steps = (0 == cycles) ? 1 : 2;
  bool ret = true;

  sim.run([&](ch_tick t)->bool {
    ret &= (cycles != 0 && t == 0) || static_cast<bool>(device.io.out);
  #ifndef NDEBUG
    if (!ret) {
      std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
    }
  #endif
    return (t < ticks);
  }, steps);

  return end_test(ret);
}

bool TEST1(const std::function<ch_bool (const ch_int8&)>& test,
           ch_tick cycles,
           const ch::internal::source_location& sloc) {
  if (!begin_test(sloc))
    return true;

  ch_device<TestRunner1> device(test);
  ch_simulator sim(device);

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);
  auto steps = (0 == cycles) ? 1 : 2;
  bool ret = true;

  device.io.in1 = 1;

  sim.run([&](ch_tick t)->bool {
    ret &= (cycles != 0 && t == 0) || static_cast<bool>(device.io.out);
  #ifndef NDEBUG
    if (!ret) {
      std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
    }
  #endif    
    return (t < ticks);
  }, steps);

  return end_test(ret);
}

bool TEST2(const std::function<ch_bool (const ch_int8&, const ch_int8&)>& test,
           ch_tick cycles,
           const ch::internal::source_location& sloc) {
  if (!begin_test(sloc))
    return true;

  ch_device<TestRunner2> device(test);
  ch_simulator sim(device);

  auto ticks = (0 == cycles) ? 1 : (cycles * 2);
  auto steps = (0 == cycles) ? 1 : 2;
  bool ret = true;

  device.io.in1 = 1;
  device.io.in2 = 2;

  sim.run([&](ch_tick t)->bool {
    ret &= (cycles != 0 && t == 0) || static_cast<bool>(device.io.out);
  #ifndef NDEBUG
    if (!ret) {
      std::cout << "t" << t << ": ret=" << device.io.out << std::endl;
    }
  #endif
    return (t < ticks);
  }, steps);

  return end_test(ret);
}

bool TESTX(const std::function<bool()>& test,
           const ch::internal::source_location& sloc) {
  if (!begin_test(sloc))
    return true;
  
  auto ret = test();

  return end_test(ret);
}

bool checkVerilog(const std::string& file) {
  int ret = system(stringf("iverilog %s -o %s.iv", file.c_str(), file.c_str()).c_str())
          | system(stringf("! vvp %s.iv | grep 'ERROR' || false", file.c_str()).c_str());
  return (0 == ret);
}
