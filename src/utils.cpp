#include <stdarg.h>
#include <cxxabi.h>
#include <execinfo.h>
#include <regex>
#include "common.h"
#include "platform.h"

using namespace ch::internal;

std::string ch::internal::stringf(const char* format, ...) {
  static constexpr uint32_t STACK_BUFFER_SIZE = 1024;

  std::string result;
  char stack_buffer[STACK_BUFFER_SIZE];
  auto buffer = stack_buffer;
  bool is_heap_buffer = false;

  va_list args_orig, args_copy;
  va_start(args_orig, format);

  va_copy(args_copy, args_orig);
  size_t size = vsnprintf(buffer, STACK_BUFFER_SIZE, format, args_copy) + 1;
  va_end(args_copy);

  if (size > STACK_BUFFER_SIZE) {
    buffer = new char[size];
    is_heap_buffer = true;
    va_copy(args_copy, args_orig);
    vsnprintf(buffer, size, format, args_copy);
    va_end(args_copy);
  }

  va_end(args_orig);

  result.assign(buffer);
  if (is_heap_buffer)
    delete[] buffer;

  return result;
}

std::vector<std::string> ch::internal::split(const std::string& str, char delimiter) {
  std::vector<std::string> out;
  size_t pos = 0;
  while (pos < str.size()) {
    auto index = str.find(delimiter, pos);
    if (index == std::string::npos)
      break;
    out.push_back(str.substr(pos, index - pos));
    pos = index + 1;
  }
  out.push_back(str.substr(pos));
  return out;
}


void ch::internal::dbprint(int level, const char* format, ...) {
  if (level > platform::self().dbg_level())
    return;
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

std::string ch::internal::identifier_from_string(const std::string& name) {
  auto ret(name);
  auto not_identifier = [&](auto x){ return !isalnum(x) && (x != '_'); };
  std::replace_if(ret.begin(), ret.end(), not_identifier, '_');
  return ret;
}

std::string ch::internal::identifier_from_typeid(const std::string& name) {
  int status;
  char* demangled = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
  CH_CHECK(0 == status, "abi::__cxa_demangle() failed");
  std::string ret(demangled);
  ::free(demangled);
  // remove namespace prefix
  auto tmp = std::regex_replace(ret, std::regex("[^<>:]*::"), "");
  // replace template arguments
  ret.clear();
  std::regex_replace(std::back_inserter(ret), tmp.begin(), tmp.end(),
                     std::regex("<.*>"), "");
  return ret;
}

int ch::internal::char2int(char x, int base) {
  switch (base) {
  case 2:
    if (x >= '0' && x <= '1')
      return (x - '0');
    break;
  case 8:
    if (x >= '0' && x <= '7')
      return (x - '0');
    break;
  case 16:
    if (x >= '0' && x <= '9')
      return (x - '0');
    if (x >= 'A' && x <= 'F')
      return (x - 'A') + 10;
    if (x >= 'a' && x <= 'f')
      return (x - 'a') + 10;
    break;
  }
  CH_ABORT("invalid value");
}

source_location ch::internal::caller_srcinfo(uint32_t level) {
  std::string cmd;
  {
    uint32_t l = 1 + level;
    std::vector<void*> callstack(1+l);
    uint32_t num_frames = backtrace(callstack.data(), callstack.size());
    auto symbols = backtrace_symbols(callstack.data(), num_frames);
    if (l < num_frames) {
      auto symbol = symbols[l];
      int p = 0;
      while (symbol[p] != '(' && symbol[p] != ' ' && symbol[p] != 0) {
        ++p;
      }
      cmd = stringf("addr2line %p -e %.*s", callstack[1+level], p, symbol);      
    }
    free(symbols);
  }
  if (!cmd.empty()) {
    std::stringstream ss;
    std::array<char, 128> out_buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) {
      throw std::runtime_error("popen() failed!");
    }
    while (fgets(out_buffer.data(), out_buffer.size(), pipe.get()) != nullptr) {
      ss << out_buffer.data();
    }
    auto lineinfo = split(ss.str(), ':');
    return source_location(lineinfo[0], stoi(lineinfo[1]));
  }
  return source_location();
}
