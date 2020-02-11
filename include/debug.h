#pragma once

#include "bool.h"
#include "uint.h"

namespace ch {
namespace internal {

lnodeimpl* getCurrentTimeNode(const source_location& sloc);

void createAssertNode(const lnode& cond, 
                      const std::string& message,
                      const source_location& sloc);

void createPrintNode(const std::string& format, 
                     const std::vector<lnode>& args, 
                     const source_location& sloc);

void registerTap(const lnode& node, 
                 const std::string& name, 
                 const source_location& sloc);

lnodeimpl* getTap(const std::string& name, unsigned instance);

///////////////////////////////////////////////////////////////////////////////

// time function

inline auto ch_now(CH_SLOC) {
  return make_logic_type<ch_uint<64>>(getCurrentTimeNode(sloc));
}

// print function

namespace detail {
struct token_ {};

inline
void createPrintNode_(const std::string& format, 
                      const source_location& sloc,
                      std::vector<lnode>& nodes,
                      token_) {
  createPrintNode(format, nodes, sloc);
}

template <class Arg0, class... Args>
void createPrintNode_(const std::string& format, 
                      const source_location& sloc,
                      std::vector<lnode>& nodes,
                      token_, 
                      Arg0&& arg0,
                      Args&&... args) {
  auto len = snprintf(nullptr, 0, format.c_str(), std::forward<Arg0>(arg0), std::forward<Args>(args)...);
  std::string tmp(len + 1, '\0');
  snprintf(tmp.data(), len + 1, format.c_str(), std::forward<Arg0>(arg0), std::forward<Args>(args)...);
  createPrintNode(tmp, nodes, sloc);
}

template <class Arg0, class... Args>
void createPrintNode_(const std::string& format, 
                      const source_location& sloc,
                      std::vector<lnode>& nodes,
                      Arg0&& arg0, 
                      Args&&... args) {
  if constexpr (is_data_type_v<Arg0>) {
    nodes.push_back(get_lnode<Arg0>(std::forward<Arg0>(arg0)));
    createPrintNode_(format, sloc, nodes, std::forward<Args>(args)...);
  } else {
    createPrintNode_(format, sloc, nodes, std::forward<Args>(args)..., std::forward<Arg0>(arg0));    
  }
}

template <class... Args>
void createPrintNode(const std::string& format, 
                     const source_location& sloc,
                     Args&&... args) {  
  if (format.empty())
    return;
  ch_cout.flush();  
  std::vector<lnode> nodes;
  createPrintNode_(format, sloc, nodes, std::forward<Args>(args)..., token_{});
}

}

template <typename... Args>
void ch_print(const sloc_arg<std::string>& format, Args&&... args) {
#ifndef NDEBUG  
  detail::createPrintNode(format.data, format.sloc, std::forward<Args>(args)...);
#else
  CH_UNUSED(format, args...);
#endif
}

/*template <typename... Args>
void ch_print(const sloc_arg<const char*>& format, Args&&... args) {
#ifndef NDEBUG  
  detail::createPrintNode(format.data, format.sloc, std::forward<Args>(args)...);
#else
  CH_UNUSED(format, args...);
#endif
}*/

template <typename... Args>
void ch_println(const sloc_arg<std::string>& format, Args&&... args) {
#ifndef NDEBUG
  detail::createPrintNode(format.data + "\n", format.sloc, std::forward<Args>(args)...);
#else
  CH_UNUSED(format, args...);
#endif
}

/*template <typename... Args>
void ch_println(const sloc_arg<const char*>& format, Args&&... args) {
#ifndef NDEBUG
  detail::createPrintNode(std::string(format.data) + "\n", format.sloc, std::forward<Args>(args)...);
#else
  CH_UNUSED(format, args...);
#endif
}*/

// assert function

inline void ch_assert(const ch_bool& cond, const std::string& message, CH_SLOC) {
#ifndef NDEBUG
  createAssertNode(get_lnode(cond), message, sloc);
#else
  CH_UNUSED(cond, message, srcinfo);
#endif
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name, CH_SLOC) {
#ifndef NDEBUG
  static_assert(is_logic_type_v<T>, "invalid type");
  registerTap(get_lnode(value), name, sloc);
#else
  CH_UNUSED(value, name, srcinfo);
#endif
}

}
}

#define CH_TAP(x) ch_tap(x, #x)

#define CH_assert(x) ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))