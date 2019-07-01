#include <stdarg.h>
#include <cxxabi.h>
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

std::string ch::internal::demanged_typeid(const std::string& name) {
  int status;
  char* demangled = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
  CH_CHECK(0 == status, "abi::__cxa_demangle() failed");
  std::string sd(demangled);
  ::free(demangled);
  return sd;
}

std::string ch::internal::identifier_from_string(const std::string& name) {
  auto ret(name);
  auto not_identifier = [&](auto x){ return !isalnum(x) && (x != '_'); };
  std::replace_if(ret.begin(), ret.end(), not_identifier, '_');
  return ret;
}

std::string ch::internal::identifier_from_typeid(const std::string& name,
                                                 bool no_args) {
  // get demanged type name
  auto dt = demanged_typeid(name);

  // extract name
  auto name_e = dt.find_first_of('<', 0);
  auto name_s = dt.find_last_of(':', name_e);
  if (name_s != std::string::npos) {
    ++name_s;
  } else {
    name_s = 0;
  }
  auto ret = dt.substr(name_s, name_e - name_s);

  // process template arguments
  if (!no_args
   && name_e != std::string::npos) {
    std::stringstream ss;
    ss << "_";
    auto pos = name_e + 1;
    for (;;) {
      auto start = pos;
      pos = dt.find_first_of(" ,:<>", pos);
      if (pos == std::string::npos)
        break;
      auto token = dt[pos];
      if (token != ':') {
        ss << dt.substr(start, pos - start);
        if (token == ' ' || token == '<') {
          ss << "_";
        }
      }
      ++pos;
    }
    ret += ss.str();
  }

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
