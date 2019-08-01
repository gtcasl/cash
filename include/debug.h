#pragma once

#include "uint.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentTimeNode();

void createAssertNode(const lnode& cond, const std::string& msg);

void createPrintNode(const std::string& format, const std::vector<lnode>& args);

void registerTap(const lnode& node, const std::string& name);

lnodeimpl* getTap(const std::string& name, unsigned instance);

///////////////////////////////////////////////////////////////////////////////

// time function

inline auto ch_now() {
  CH_API_ENTRY(1);
  return make_logic_type<ch_uint<64>>(getCurrentTimeNode());
}

// print function

template <typename... Args>
void ch_print(const std::string& format, const Args&... args) {
  CH_API_ENTRY(1);
  static_assert((is_logic_type_v<Args> && ...), "invalid argument type");
  createPrintNode(format, {get_lnode(args)...});
}

template <typename... Args>
void ch_println(const std::string& format, const Args&... args) {
  CH_API_ENTRY(1);
  ch_print(format + '\n', args...);
}

// assert function

inline void ch_assert(const ch_bool& cond, const std::string& msg) {
  CH_API_ENTRY(1);
  createAssertNode(get_lnode(cond), msg);
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<T>, "invalid type");
  registerTap(get_lnode(value), name);
}

template <typename T>
T ch_tap(const std::string& name, unsigned instance = 0) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<T>, "invalid type");
  auto ret = make_logic_type<T>(getTap(name, instance));
  auto size = logic_accessor::size(ret);
  if (size != ch_width_v<T>)
    throw std::invalid_argument("invalid tap type cast");
  return ret;
}

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(x, #x)
#else
  #define CH_TAP(x)
#endif

#ifndef NDEBUG
  #define CH_ASSERT(x) \
    ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
