#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;
using namespace extension;

// |1|<- N-F-1 bits ->|<--- F bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned F>
class ch_fixed : public ch_bit<N> {
public:
  using traits = logic_traits<N, true, ch_fixed, ch_scint<N>>;
  using base = ch_bit<N>;
  static constexpr unsigned I = N-F;

  explicit ch_fixed(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_fixed(const U& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_fixed(const U& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(const ch_bit<I>& otherI, const ch_bit<F>& otherF, CH_SLOC)
    : base(((otherI.template pad<N>() << F) | otherF).template slice<N>(), sloc)
  {}

  ch_fixed(const ch_fixed& other, CH_SLOC) : base(other, sloc) {}

  ch_fixed(ch_fixed&& other) : base(std::move(other)) {}

  ch_fixed& operator=(const ch_fixed& other) {
    base::operator=(other);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_fixed)

  friend auto operator==(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() == rhs.as_int());
  }

  friend auto operator!=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() != rhs.as_int());
  }

  friend auto operator<(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() < rhs.as_int());
  }

  friend auto operator<=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() <= rhs.as_int());
  }

  friend auto operator>(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator>=(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator+(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() + rhs.as_int());
  }

  friend auto operator-(ch_fixed lhs, const ch_fixed& rhs) {
    return (lhs.as_int() - rhs.as_int());
  }

  friend auto operator*(ch_fixed lhs, const ch_fixed& rhs) {
    return ((lhs.as_int().template pad<N + F>() * rhs.as_int()) >> F).template slice<N>();
  }

  friend auto operator/(ch_fixed lhs, const ch_fixed& rhs) {
    return ((lhs.as_int().template pad<N + F>() << F) / rhs.as_int()).template slice<N>();
  }
};

}
}
