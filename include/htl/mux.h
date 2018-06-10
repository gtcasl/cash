#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename S, typename Arg0, typename... Args,
          __require0(ch_is_logic_convertible_v<S, (1+sizeof...(Args))>)>
auto ch_hmux(const S& sel,
             const Arg0& arg0,
             const Args&... args) {
  auto cs = ch_case(sel, (1 << sizeof...(Args)), arg0);
  int i = 0;
  for_each_reverse([&](auto arg){ cs(1 << i++, arg); }, args...);
  return cs(0x0);
}

template <typename S, typename T, unsigned N,
          __require0(ch_is_logic_convertible_v<S, N>)>
auto ch_hmux(const S& sel, const ch_vec<T, N>& args) {
  auto cs = ch_case(sel, 0x1, args[0]);
  for (unsigned i = 1; i < N; ++i) {
    cs(1 << i, args[i]);
  }
  return cs(0x0);
}

}
}
