#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <std::size_t N>
class ch_counter {
public:

  template <typename S, typename I>
  ch_counter(const ch_bool& incr,
             const S& step,
             const I& init,
             const ch_bool& reset) {
    incr_  = incr;
    step_  = step;
    init_  = init;
    reset_ = reset;
    if constexpr (N == 1) {
      value_ = 0;
      next_ = 0;
    } else {
      static_assert(std::is_constructible_v<ch_uint<log2ceil(N)>, I>, "invalid type");
      ch_pushcd(ch_clock(), ch_reset() || reset_);
      ch_reg<ch_uint<log2ceil(N)>> count(init_);
      ch_popcd();
      if constexpr (ispow2(N)) {
        count->next = ch_sel(incr_, count + step_, count);
      } else {
        auto next = ch_sel(count >= (N-step_), count - (N-step_), count + step_);
        count->next = ch_sel(incr_, next, count);
      }
      value_ = count;
      next_  = count->next;
    }
  }

  template <typename S>
  ch_counter(const ch_bool& incr, const S& step) : ch_counter(incr, step, 0, false) {}

  ch_counter(const ch_bool& incr = true) : ch_counter(incr, 1) {}

  auto& value() const {
    return value_;
  }

  auto& next() const {
    return next_;
  }

  auto& init() const {
    return init_;
  }

  void init(const ch_uint<log2up(N)>& init) {
    init_ = init;
  }

  auto& step() const {
    return step_;
  }

  void step(const ch_uint<log2up(N)>& step) {
    step_ = step;
  }

  auto& incr() const {
    return incr_;
  }

  void incr(const ch_bool& incr) {
    incr_ = incr;
  }

  auto& reset() const {
    return reset_;
  }

  void reset(const ch_bool& reset) {
    reset_ = reset;
  }

protected:

  ch_uint<log2up(N)> value_;
  ch_uint<log2up(N)> next_;
  ch_uint<log2up(N)> init_;
  ch_uint<log2up(N)> step_;
  ch_bool incr_;
  ch_bool reset_;
};

}
}
