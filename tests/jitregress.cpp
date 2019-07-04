#include "common.h"

#ifdef NDEBUG

#pragma GCC diagnostic ignored "-Wunused-function"

static bool verify_asm(const char* program, int lines) {
  auto cmd = stringf("cd ../examples && CASH_CFLAGS=8 ../bin/%s", program);
  std::cout << cmd << std::endl;
  int ret = system(cmd.c_str());
  if (ret != 0) {
    std::cout << "error: command returned exitcode " << ret << std::endl;
    return false;
  }

  int num_lines = 0;
  std::ifstream asm_file("../examples/simjit.asm");
  if (!asm_file.is_open()) {
    std::cout << "error: couldn't open file \'../examples/simjit.asm\'";
    return false;
  }

  std::string line;
  while (std::getline(asm_file, line)) {
    ++num_lines;
  }

  if (num_lines != lines) {
    std::cout << "error: lines count missmatch: actual=" << num_lines << ", expected=" << lines << std::endl;
    return false;
  }

  return true;
}

#pragma GCC diagnostic pop

TEST_CASE("jitregress", "[jitregress]") {
  SECTION("asm-size", "[asm-size]") {
    TESTX([]()->bool {
      RetCheck ret;
    #if defined(LLVMJIT)
      ret &= verify_asm("fifo", 97);
      ret &= verify_asm("matmul", 538);
      ret &= verify_asm("aes", 3378);
      ret &= verify_asm("fft", 931);
      ret &= verify_asm("sobel", 411);
    #elif defined(LIBJIT)
      ret &= verify_asm("fifo", 162);
      ret &= verify_asm("matmul", 817);
      ret &= verify_asm("aes", 4935);
      ret &= verify_asm("fft", 1342);
      ret &= verify_asm("sobel", 627);
    #endif
      return ret;
    });
  }
}

#endif
