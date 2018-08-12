#include <stdarg.h>
#include <cxxabi.h>
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

void ch::internal::dbprint(int level, const char* format, ...) {
  if (level > platform::self().dbg_level())
    return;
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
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

std::string unique_names::get(const std::string& name) {
  std::string unique_name(name);
  uint32_t instances = names_[name]++;
  if (instances != 0) {
    unique_name = stringf("%s_%d", name.c_str(), instances-1);
    // resolve collisions
    while (names_.count(unique_name) != 0) {
      instances = names_[name]++;
      unique_name = stringf("%s_%d", name.c_str(), instances-1);
    }
  }
  return unique_name;
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
  CH_ABORT("invalid scalar value");
}
