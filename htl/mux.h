#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename S, typename Arg0, typename... Args,
          __requires(ch_is_bit_convertible<S, (1+sizeof...(Args))>::value)>
auto ch_hmux(const S& sel,
             const Arg0& arg0,
             const Args&... args) {
  auto cs = ch_case(sel, (1 << sizeof...(Args)), arg0);
  int i = 0;
  for_each_reverse([&](auto arg){ cs(1 << i++, arg); }, args...);
  return cs(0x0);
};

template <typename S, typename T, unsigned N,
          __requires(ch_is_bit_convertible<S, N>::value)>
auto ch_hmux(const S& sel, const ch_const_vec<T, N>& args) {
  auto cs = ch_case(sel, 0x1, args[0]);
  for (int i = 1; i < N; ++i) {
    cs(1 << i, args[i]);
  }
  return cs(0x0);
};

}
}
