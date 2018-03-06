#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <unsigned N>
const auto ch_hot2bin = [](const ch_bit<N>& onehot) {
  auto cs = ch_case<ch_bit<log2ceil(N)>>(onehot, 1, 0);
  for (unsigned i = 1; i < N; ++i) {
    cs(1 << i, i);
  }
  return cs(0);
};

template <unsigned N>
const auto ch_bin2hot = [](const ch_bit<log2ceil(N)>& bin) {
  return ch_bit<N>(1) << bin;
};

}
}
