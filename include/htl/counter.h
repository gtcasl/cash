#pragma once

#include <cash.h>

namespace ch {
namespace htl {

template <unsigned End, unsigned Start = 0x0>
auto ch_counter(const ch_bool& inc) {
  ch_reg<ch_uint<log2ceil(End+1)>> count(Start);
  if constexpr(ispow2(End+1)) {
    count->next = ch_sel(inc, count + 0x1, count);
  } else {
    auto value = ch_sel(count == End, 0x0, count + 0x1);
    count->next = ch_sel(inc, value, count);
  }
  return std::tuple(count, count->next);
}

}
}
