#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <unsigned N>
auto ch_hot2bin(const ch_bit<N>& value, CH_SLOC) {
  static_assert(N >= 2, "invalid size");
  auto cs = ch_case<ch_bit<log2ceil(N)>>(value, 1, 0, sloc);
  for (unsigned i = 1; i < N-1; ++i) {
    cs(1 << i, i);
  }
  return cs(N-1);
}

template <unsigned N>
auto ch_bin2hot(const ch_bit<N>& value, CH_SLOC) {
  static_assert(N >= 1, "invalid size");
  return ch_shl(ch_bit<(1 << N)>(1), value, sloc);
}

}
}
