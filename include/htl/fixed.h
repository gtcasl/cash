#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;

// |1|<- N-Q-1 bits ->|<--- Q bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned Q>
class ch_fixed : public ch_bit<N> {
public:
  using traits = logic_traits<N, true, ch_fixed, ch_scint<N>>;
  using base = ch_bit<N>;

  explicit ch_fixed(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  ch_fixed(const ch_fixed& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(ch_fixed&& other) : base(std::move(other)) {}

  explicit ch_fixed(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed& operator=(const ch_fixed& other) {
    base::operator=(other);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  // compare operators

  auto operator<(const ch_fixed& other) const {
    return ch_int<32>(*this) < ch_int<32>(other);
  }

  auto operator<=(const ch_fixed& other) const {
    return ch_int<32>(*this) <= ch_int<32>(other);
  }

  auto operator>(const ch_fixed& other) const {
    return ch_int<32>(*this) > ch_int<32>(other);
  }

  auto operator>=(const ch_fixed& other) const {
    return ch_int<32>(*this) >= ch_int<32>(other);
  }

  CH_LOGIC_INTERFACE(ch_fixed)
};

}
}
