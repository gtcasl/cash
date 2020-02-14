#pragma once

#include "../core.h"

namespace ch {
namespace htl {

template <unsigned N>
auto ch_pri_enc(const ch_bit<N>& input) {
  static_assert(N >= 2, "invalid size");
  auto sel = ch_sel<ch_bit<log2ceil(N)>>(input[N-1], N-1);
  for (int i = N-2; i > 0; --i) {
    sel(input[i], i);
  }
  return sel(0);
}

}
}
