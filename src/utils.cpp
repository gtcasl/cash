#include "utils.h"
#include "common.h"
#include <stdarg.h>
#include <cxxabi.h>

#define BACKWARD_HAS_BFD 1
#include "backward.h"

using namespace ch::internal;

std::string ch::internal::fstring(const char *format, ...) {
  static const int STACK_BUFFER_SIZE = 256;

  std::string result;
  char stack_buffer[STACK_BUFFER_SIZE];
  char *buffer = stack_buffer;
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

void ch::internal::dbprint(int level, const char *format, ...) {
  if (level > platform::self().get_dbg_level())
    return;
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}

void ch::internal::dump_stack_trace(FILE *out, unsigned int max_frames) {
  using namespace backward;
  StackTrace st;
  st.load_here(max_frames);
  Printer p; 
  p.print(st, out);
}

std::string ch::internal::identifier_from_typeid(const char* name) {
  int status;
  char* demangled = abi::__cxa_demangle(name, 0, 0, &status);
  CH_CHECK(0 == status, "abi::__cxa_demangle() failed");
  std::string ret(demangled);
  // remove namespace prefix and template posfix
  auto pos = ret.find_last_of(':') + 1;
  auto len = ret.find_first_of('<') - pos;
  ret = ret.substr(pos, len);
  free(demangled);
  return ret;
}

std::string unique_name::get(const char* name) {
  std::string unique_name(name);
  unsigned instances = dups_[name]++;
  if (instances != 0) {
    unique_name = fstring("%s_%d", name, instances-1);
    // resolve collisions
    while (dups_.count(unique_name) != 0) {
      instances = dups_[name]++;
      unique_name = fstring("%s_%d", name, instances-1);
    }
  }
  return unique_name;
}
