#include "common.h"

#ifdef NDEBUG

auto remove_numbers(const std::string& str) {
  std::stringstream in, out;
  std::string word;
  int64_t number;
  in << str;
  while (!in.eof()) {
    in >> word;
    if (!(std::stringstream(word) >> std::hex >> number))
      out << word;
  }
  return out.str();
}

static bool verify_asm(const char* program) {
#if defined(LLVMJIT)
  std::cout << "verifying llvmjit assembly for '" << program << "'..." << std::endl;
#elif defined(LIBJIT)
  std::cout << "verifying libjit assembly for '" << program << "'..." << std::endl;
#endif

  auto cmd = stringf("cd ../examples && CASH_CFLAGS=8 ../bin/%s", program);
  int ret = system(cmd.c_str());
  if (ret != 0) {    
    std::cout << "error: command '" << cmd << "', returned exitcode " << ret << std::endl;
    return false;
  }

#if defined(LLVMJIT)
  auto ref_file_path = stringf("res/jitregress/%s_llvm.asm", program);
#elif defined(LIBJIT)
  auto ref_file_path = stringf("res/jitregress/%s_libjit.asm", program);
#endif

  std::string asm_file_path("../examples/simjit.asm");

  std::ifstream asm_file(asm_file_path);
  if (!asm_file.is_open()) {
    std::cout << "error: couldn't open file '" << asm_file_path << "'";
    return false;
  }

  std::ifstream ref_file(ref_file_path);
  if (!ref_file.is_open()) {
    std::cout << "error: couldn't open file '" << ref_file_path << "'";
    return false;
  }

  std::string asm_line, ref_line;
  int line = 1;
  while (std::getline(asm_file, asm_line)
      && std::getline(ref_file, ref_line)) {
    asm_line = remove_numbers(asm_line);
    ref_line = remove_numbers(ref_line);
    if (asm_line != ref_line) {
      std::cout << "error: (line " << line << ") actual='" << asm_line << "', expected='" << ref_line << "'" << std::endl;
      return false;
    }
    ++line;
  }

  if (std::getline(asm_file, asm_line)) {
    std::cout << "error: (line " << line << ") actual='" << asm_line << "', expected=none" << std::endl;
    return false;
  }

  if (std::getline(ref_file, ref_line)) {
    std::cout << "error: (line " << line << ") actual=none, expected='" << ref_line << "'" << std::endl;
    return false;
  }

  return true;
}

TEST_CASE("jitregress", "[jitregress]") {
  SECTION("asm", "[asm]") {
    TESTX([]()->bool {
      RetCheck ret;
      ret &= verify_asm("fifo");
      ret &= verify_asm("matmul");
      ret &= verify_asm("aes");
      ret &= verify_asm("fft");
      ret &= verify_asm("sobel");
      ret &= verify_asm("vectoradd");
      return ret;
    });
  }
}

#endif
