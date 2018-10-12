#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <std::size_t N>
struct ch_counter {

  ch_uint<log2ceil(N)> value;
  ch_uint<log2ceil(N)> next;

  ch_counter(const ch_bool& incr = true, const ch_uint<log2ceil(N)>& init = 0) {
    static_assert(N >= 2, "invalid size");
    ch_reg<ch_uint<log2ceil(N)>> count(init);
    if constexpr (ispow2(N)) {
      count->next = ch_sel(incr, count + 0x1, count);
    } else {
      auto next = ch_sel(count == (N-1), 0x0, count + 0x1);
      count->next = ch_sel(incr, next, count);
    }
    this->value = count;
    this->next  = count->next;
  }
};

}
}
