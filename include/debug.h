#pragma once

#include "uint.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentTimeNode();

void createAssertNode(const lnode& cond, const std::string& msg);

void createPrintNode(const std::string& format, const std::vector<lnode>& args);

void registerTap(const lnode& node, const std::string& name);

///////////////////////////////////////////////////////////////////////////////

// time function

inline auto ch_now() {
  CH_SOURCE_LOCATION(1);
  return make_type<ch_uint<64>>(getCurrentTimeNode());
}

// print function

template <typename... Args>
void ch_print(const std::string& format, const Args&... args) {
  static_assert((is_logic_type_v<Args> && ...), "invalid argument type");
  CH_SOURCE_LOCATION(1);
  createPrintNode(format, {get_lnode(args)...});
}

template <typename... Args>
void ch_println(const std::string& format, const Args&... args) {
  CH_SOURCE_LOCATION(1);
  ch_print(format + '\n', args...);
}

// assert function

inline void ch_assert(const ch_bit<1>& cond, const std::string& msg) {
  CH_SOURCE_LOCATION(1);
  createAssertNode(get_lnode(cond), msg);
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  registerTap(get_lnode(value), name);
}

}
}
