#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;
using namespace extension;

template <typename ArgN, typename ArgM, typename... Args>
auto ch_mux(const ch_bit<(log2ceil(2+sizeof...(Args)))>& sel,
            const ArgN& argN,
            const ArgM& argM,
            const Args&... args) {
  static_assert((is_data_type_v<ArgN>), "invalid type");
  static_assert((is_data_type_v<ArgM>), "invalid type");
  static_assert((is_data_type_v<Args> && ...), "invalid type");
  auto cs = ch_case(sel, sizeof...(Args), argM);
  int i = 0;
  for_each_reverse([&](auto arg){ cs(i++, arg); }, args...);
  return cs(argN);
}

template <unsigned N, typename T, std::size_t M>
auto ch_mux(const ch_bit<N>& sel, const ch_vec<T, M>& args) {
  static_assert(is_data_type_v<T>, "invalid type");
  static_assert(N == log2ceil(M), "invalid size");
  static_assert(M >= 2, "invalid size");
  auto cs = ch_case(sel, 0, args[0]);
  for (unsigned i = 1; i < M-1; ++i) {
    cs(i, args[i]);
  }
  return cs(args[M-1]);
}

template <unsigned N, unsigned M>
auto ch_mux(const ch_bit<N>& sel, const ch_bit<M>& args) {
  static constexpr unsigned Q = 1 << N;
  static constexpr unsigned K = M / Q;
  static_assert(Q*K == M, "invalid size");
  static_assert(M >= 2, "invalid size");
  auto cs = ch_case(sel, 0,  ch_aslice<K>(args, 0));
  for (unsigned i = 1; i < Q-1; ++i) {
    cs(i, ch_aslice<K>(args, i));
  }
  return cs(ch_aslice<K>(args, Q-1));
}

///////////////////////////////////////////////////////////////////////////////

template <typename ArgN, typename... Args>
auto ch_hmux(const ch_bit<(1+sizeof...(Args))>& sel,
             const ArgN& argN,
             const Args&... args) {
  static_assert((is_data_type_v<ArgN>), "invalid type");
  static_assert(sizeof...(Args) >= 1, "invalid size");
  auto cs = ch_case(sel, (ch_sbit<1+sizeof...(Args)>(1) << sizeof...(Args)), argN);
  int i = 0;
  for_each_reverse([&](auto arg){ cs(ch_sbit<1+sizeof...(Args)>(1) << i++, arg); }, args...);
  return cs(0);
}

template <unsigned N, typename T, std::size_t M>
auto ch_hmux(const ch_bit<N>& sel, const ch_vec<T, M>& args) {
  static_assert(is_data_type_v<T>, "invalid type");
  static_assert(N == M, "invalid size");
  static_assert(N >= 2, "invalid size");
  auto cs = ch_case(sel, 0x1, args[0]);
  for (unsigned i = 1; i < N; ++i) {
    cs(ch_sbit<N>(1) << i, args[i]);
  }
  T def;
  def.as_int() = 0;
  return cs(def);
}

template <unsigned N, unsigned M>
auto ch_hmux(const ch_bit<N>& sel, const ch_bit<M>& args) {
  static constexpr unsigned K = M / N;
  static_assert(N*K == M, "invalid size");
  static_assert(N >= 2, "invalid size");
  auto cs = ch_case(sel, 0x1, ch_aslice<K>(args, 0));
  for (unsigned i = 1; i < N; ++i) {
    cs(ch_sbit<N>(1) << i, ch_aslice<K>(args, i));
  }
  return cs(0);
}

}
}
