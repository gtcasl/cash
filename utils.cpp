#include <stdarg.h>
#include "common.h"
#include "utils.h"

using namespace std;
using namespace chdl_internal;

std::string chdl_internal::fstring(const char* format, ...) {
  std::string str;
  char* buf;
  va_list vargs;
  va_start(vargs, format);  
  vasprintf(&buf, format, vargs);
  va_end(vargs);
  str = buf;
  free(buf);
  return str;
}
