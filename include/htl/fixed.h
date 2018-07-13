#pragma once

#include <cash.h>
#include <math.h>

namespace ch {
namespace htl {

using namespace core;
using namespace extension;

// |1|<- N-F-1 bits ->|<--- F bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned F>
class ch_fixed;

template <unsigned I, unsigned F>
int FloatToFixed(float value) {
  static_assert(I >= 1 && (I + F) <= 32, "invalid size");
  auto xOne = (1 << F);
  int xvalue = static_cast<int>(floor(value * xOne + 0.5f));
  if constexpr (I == 1) {    
    if (xvalue == xOne) {
      xvalue = xOne - 1;
    }
    if (xvalue < 0) {
      xvalue += 2 * xOne;
    }
  }
  return xvalue;
}

template <unsigned N, unsigned F>
class ch_scfixed : public ch_scbit<N> {
public:  
  static_assert(N >= (F+1), "invalid size");
  using traits = scalar_traits<N, true, ch_scfixed, ch_fixed<N, F>>;
  using base = ch_scbit<N>;
  static constexpr unsigned I = N-F;

  explicit ch_scfixed(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scfixed(const U& other) : base(other) {}

  explicit ch_scfixed(float other) : base(FloatToFixed<I, F>(other)) {
    static_assert(N <= 32, "invalid size");
  }

  explicit ch_scfixed(const ch_scbit<N>& other) : base(other) {}

  ch_scfixed(const ch_scfixed& other) : base(other) {}

  ch_scfixed(ch_scfixed&& other) : base(std::move(other)) {}

  ch_scfixed& operator=(const ch_scfixed& other) {
    base::operator=(other);
    return *this;
  }

  ch_scfixed& operator=(ch_scfixed&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SCALAR_INTERFACE(ch_scfixed)

  friend auto operator<(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() < rhs.as_scint());
  }

  friend auto operator<=(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() <= rhs.as_scint());
  }

  friend auto operator>(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator>=(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() >= rhs.as_scint());
  }

  friend auto operator~(const ch_scfixed& self) {
    return (~self.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator&(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() & rhs.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator|(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() | rhs.as_scint()).template as<ch_scfixed>();
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator<<(const ch_scfixed& lhs, const U& rhs) {
    return (lhs.as_scint() << rhs).template as<ch_scfixed>();
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator>>(const ch_scfixed& lhs, const U& rhs) {
    return (lhs.as_scint() >> rhs).template as<ch_scfixed>();
  }

  friend auto operator-(const ch_scfixed& self) {
    return (-self.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator+(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() + rhs.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator-(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    return (lhs.as_scint() - rhs.as_scint()).template as<ch_scfixed>();
  }

  friend auto operator*(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    auto ret = ((lhs.as_scint().template pad<N+F>() * rhs.as_scint()) >> F).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  friend auto operator/(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    auto ret = ((lhs.as_scint().template pad<N+F>() << F) / rhs.as_scint()).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit operator U() const {
    return static_cast<U>(this->as_scint());
  }

  explicit operator float() const {
    static_assert(N <= 32, "invalid size");
    int32_t ivalue = static_cast<int32_t>(*this);
    auto value = float(ivalue) / (1 << F);
    return value;
  }
};

template <unsigned N, unsigned F>
class ch_fixed : public ch_bit<N> {
public:  
  static_assert(N >= (F+1), "invalid size");
  using traits = logic_traits<N, true, ch_fixed, ch_scfixed<N, F>>;
  using base = ch_bit<N>;
  static constexpr unsigned I = N-F;

  explicit ch_fixed(const logic_buffer& buffer = logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_fixed(const U& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(float other) : base(FloatToFixed<I, F>(other)) {
    static_assert(N <= 32, "invalid size");
  }

  explicit ch_fixed(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_fixed(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

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

  friend auto operator<(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() < rhs.as_int());
  }

  friend auto operator<=(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() <= rhs.as_int());
  }

  friend auto operator>(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator>=(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() >= rhs.as_int());
  }

  friend auto operator~(const ch_fixed& self) {
    return (~self.as_int()).template as<ch_fixed>();
  }

  friend auto operator&(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() & rhs.as_int()).template as<ch_fixed>();
  }

  friend auto operator|(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() | rhs.as_int()).template as<ch_fixed>();
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_bit<ch_width_v<U>>>)>
  friend auto operator<<(const ch_fixed& lhs, const U& rhs) {
    return (lhs.as_int() << rhs).template as<ch_fixed>();
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_bit<ch_width_v<U>>>)>
  friend auto operator>>(const ch_fixed& lhs, const U& rhs) {
    return (lhs.as_int() >> rhs).template as<ch_fixed>();
  }

  friend auto operator-(const ch_fixed& self) {
    return (-self.as_int()).template as<ch_fixed>();
  }

  friend auto operator+(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() + rhs.as_int()).template as<ch_fixed>();
  }

  friend auto operator-(const ch_fixed& lhs, const ch_fixed& rhs) {
    return (lhs.as_int() - rhs.as_int()).template as<ch_fixed>();
  }

  friend auto operator*(const ch_fixed& lhs, const ch_fixed& rhs) {
    auto ret = ch_shr<N>(ch_mul<N+F>(lhs.as_int(), rhs.as_int()), F);
    return ret.template as<ch_fixed>();
  }

  friend auto operator/(const ch_fixed& lhs, const ch_fixed& rhs) {
    auto ret = (ch_shl<N+F>(lhs.as_int(), F) / rhs.as_int()).template slice<N>();
    return ret.template as<ch_fixed>();
  }
};

}
}
