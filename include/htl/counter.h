#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <std::size_t N>
struct ch_counter {

  ch_uint<log2up(N)> value;
  ch_uint<log2up(N)> next;

  ch_counter(const ch_bool& incr = true) {
    if constexpr (N == 1) {
      this->value = 0;
      this->next = 0;
    } else {
      ch_reg<ch_uint<log2ceil(N)>> count(0);
      if constexpr (ispow2(N)) {
        count->next = ch_sel(incr, count + 1, count);
      } else {
        auto next = ch_sel(count >= (N-1), count - (N-1), count + 1);
        count->next = ch_sel(incr, next, count);
      }
      this->value = count;
      this->next  = count->next;
    }
  }

  template <typename S>
  ch_counter(const ch_bool& incr, const S& step) {
    if constexpr (N == 1) {
      this->value = 0;
      this->next = 0;
    } else {
      ch_reg<ch_uint<log2ceil(N)>> count(0);
      if constexpr (ispow2(N)) {
        count->next = ch_sel(incr, count + step, count);
      } else {
        auto next = ch_sel(count >= (N-step), count - (N-step), count + step);
        count->next = ch_sel(incr, next, count);
      }
      this->value = count;
      this->next  = count->next;
    }
  }

  template <typename S, typename I>
  ch_counter(const ch_bool& incr, const S& step, const I& init) {
    if constexpr (N == 1) {
      this->value = 0;
      this->next = 0;
    } else {
      static_assert(std::is_constructible_v<ch_uint<log2ceil(N)>, I>, "invalid type");
      ch_reg<ch_uint<log2ceil(N)>> count(init);
      if constexpr (ispow2(N)) {
        count->next = ch_sel(incr, count + step, count);
      } else {
        auto next = ch_sel(count >= (N-step), count - (N-step), count + step);
        count->next = ch_sel(incr, next, count);
      }
      this->value = count;
      this->next  = count->next;
    }
  }
};

}
}
