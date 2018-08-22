#pragma once

#include <cash.h>

namespace ch {
namespace htl {

template <auto N>
auto ch_counter(const ch_bool& incr = 1, const ch_uint<log2ceil(N)>& init = 0) {
  static_assert(std::is_integral_v<decltype(N)> && (N >= 2), "invalid size");
  ch_reg<ch_uint<log2ceil(N)>> count(init);
  if constexpr(ispow2(N)) {
    count->next = ch_sel(incr, count + 0x1, count);
  } else {
    auto next = ch_sel(count == (N-1), 0x0, count + 0x1);
    count->next = ch_sel(incr, next, count);
  }
  return std::tuple<ch_uint<log2ceil(N)>, ch_uint<log2ceil(N)>>(count, count->next);
}

}
}
