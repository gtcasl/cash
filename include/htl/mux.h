#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;
using namespace extension;

template <typename ArgN, typename ArgM, typename... Args>
auto ch_hmux(const ch_bit<(2+sizeof...(Args))>& sel,
             const ArgN& argN,
             const ArgM& argM,
             const Args&... args) {
  static_assert((is_object_type_v<ArgN>), "invalid type");
  static_assert((is_object_type_v<ArgM>), "invalid type");
  static_assert((is_object_type_v<Args> && ...), "invalid type");
  auto cs = ch_case(sel, (1 << sizeof...(Args)), argM);
  int i = 0;
  for_each_reverse([&](auto arg){ cs(1 << i++, arg); }, args...);
  return cs(argN);
}

template <typename T, unsigned N>
auto ch_hmux(const ch_bit<N>& sel, const ch_vec<T, N>& args) {
  static_assert(is_object_type_v<T>, "invalid type");
  static_assert(N >= 2, "invalid size");
  auto cs = ch_case(sel, 0x1, args[0]);
  for (unsigned i = 1; i < N-1; ++i) {
    cs(1 << i, args[i]);
  }
  return cs(args[N-1]);
}

}
}
