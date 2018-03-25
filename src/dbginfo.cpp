#include <sstream>
#include <string>
#include <vector>
#include <cxxabi.h>
#include <execinfo.h>
#include <stdio.h>

#include <boost/algorithm/string.hpp>

namespace ch {
namespace internal {

std::string addr2line(std::string const &program, void *addr) {
  std::stringstream ss;
  ss << "addr2line -e " << program << " " << addr;

  auto fp = popen(ss.str().c_str(), "r");
  ss.str("");
  if (fp) {
    char buff[256];
    while (fgets(buff, sizeof(buff), fp) != nullptr) {
      ss << buff;
    }
    fclose(fp);
  }

  if (ss.str() == "") {
    ss << program << " [" << addr << "]";
  }

  return boost::algorithm::trim_copy(ss.str());
}

std::vector<std::string> generate_stack_trace() {
  const int MAX_TRACE_LEVEL = 16;

  void *trace[MAX_TRACE_LEVEL];
  int trace_size = backtrace(trace, MAX_TRACE_LEVEL);

  char** messages = backtrace_symbols(trace, trace_size);
  std::vector<std::string> stacktrace;
  for (int i = 0; i < trace_size; i++) {
    // message[i] will be of the form:
    // executable_name(mangled-function-name+0xnnnn) [0xmmmm]
    // we extract the executable name and then try to call addr2line (which may or may not succeed)
    // then we try to demangle the function name
    std::vector<std::string> split_vector;
    boost::algorithm::split(split_vector, messages[i], boost::is_any_of("(+)"));

    int status;
    char* demangled_name = abi::__cxa_demangle(split_vector[1].c_str(), 0, 0, &status);
    if (demangled_name == nullptr) {
      demangled_name = messages[i];
    }

    std::stringstream ss;
    ss << demangled_name << " at " << addr2line(split_vector[0], trace[i]);
    stacktrace.push_back(ss.str());
  }
  free(messages);

  return stacktrace;
}

}
}
