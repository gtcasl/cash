#pragma once

#include "bool.h"
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
#ifndef NDEBUG
  CH_API_ENTRY(1);
  static_assert((is_logic_type_v<Args> && ...), "invalid argument type");
  if (format.empty())
    return;
  ch_cout.flush();
  createPrintNode(format, {get_lnode(args)...});
#else
  CH_UNUSED(format);
#endif

}

template <typename... Args>
void ch_println(const std::string& format, const Args&... args) {
  CH_API_ENTRY(1);
  ch_print(format + '\n', args...);
}

// assert function

inline void ch_assert(const ch_bool& cond, const std::string& msg) {
#ifndef NDEBUG
  CH_API_ENTRY(1);
  createAssertNode(get_lnode(cond), msg);
#else
  CH_UNUSED(cond, msg);
#endif
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name) {
#ifndef NDEBUG
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<T>, "invalid type");
  registerTap(get_lnode(value), name);
#else
  CH_UNUSED(value, name);
#endif
}

}
}

#define CH_TAP(x) ch_tap(x, #x)

#define CH_assert(x) ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))