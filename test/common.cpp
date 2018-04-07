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

int syscall(const std::string& cmd) {
  char buf[1024];
  FILE *fp = popen(cmd.c_str(), "r");
  if (nullptr == fp)
    return -1;
  while (fgets(buf, 1024, fp)) {
    std::cout << buf;
  }
  int status = pclose(fp);
  if (-1 == status)
    return -1;
  return WEXITSTATUS(status);
}

int syscall(const std::string& cmd, std::string& output) {
  char charBuf;
  std::ostringstream outBuffer;
  FILE *fp = popen(cmd.c_str(), "r");
  if (nullptr == fp)
    return -1;
  while ((charBuf = fgetc(fp)) != EOF) {
    outBuffer << charBuf;
  }
  int status = pclose(fp);
  if (-1 == status)
    return -1;
  output = outBuffer.str();
  return WEXITSTATUS(status);
}

bool checkVerilog(const std::string& file) {
  int ret = syscall(fstring("iverilog %s -o %s.iv 2>&1 | grep \".*syntax error.*\"", file.c_str(), file.c_str()));
  if (ret != 1) {
    assert(false);
    return false;
  }
  ret = syscall(fstring("vvp %s.iv", file.c_str()));
  assert(0 == ret );
  return (0 == ret);
}
