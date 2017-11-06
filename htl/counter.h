#pragma once

#include <cash.h>

namespace ch {
namespace htl {

template <unsigned MaxValue, unsigned InitValue = 0x0>
const auto ch_counter(const ch_bool& inc) {
  ch_seq<ch_bit<log2ceil(MaxValue+1)>> count(InitValue);
  if constexpr(ispow2(MaxValue+1)) {
    count.next = ch_select(inc, count + 0x1, count);
  } else {
    auto value = ch_select(count == MaxValue, 0x0, count + 0x1);
    count.next = ch_select(inc, value, count);
  }
  return count;
}

}
}
