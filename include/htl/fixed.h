#pragma once

#include <cash.h>
#include <math.h>

namespace ch {
namespace htl {

using namespace logic;
using namespace extension;

// |1|<- N-F-1 bits ->|<--- F bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned F>
class ch_fixed;

template <typename T>
inline T ToFixed(double value, unsigned I, unsigned F) {
  assert(I >= 1 && (I + F) <= 8 * sizeof(T));
  auto xOne = T(1) << F;
  auto step = 1.0 / xOne;
  auto uMax = double(T(1) << (I-1));
  auto min_value = -uMax;
  auto max_value = uMax - step;
  if (value > max_value) {
    value = max_value;
  }
  if (value < min_value) {
    value = min_value;
  }
  return static_cast<T>(floor(value * xOne + 0.5));
}

template <unsigned N, unsigned F>
class ch_scfixed : public ch_scint<N> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = system_traits<N, true, ch_scfixed, ch_fixed<N, Frac>>;
  using base = ch_scint<N>;

  ch_scfixed(const system_buffer_ptr& buffer = make_system_buffer(N, ch::internal::idname<ch_scfixed>()))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_scfixed(const U& other) : base(other) {}

  explicit ch_scfixed(double other) : base(ToFixed<int>(other, Intg, Frac)) {
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

  CH_SYSTEM_INTERFACE(ch_scfixed)

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
            CH_REQUIRE(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator<<(const ch_scfixed& lhs, const U& rhs) {
    return (lhs.as_scint() << rhs).template as<ch_scfixed>();
  }

  template <typename U,
            CH_REQUIRE(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
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
    auto ret = ((ch_scint<N+Frac>(lhs) * rhs.as_scint()) >> Frac).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  friend auto operator/(const ch_scfixed& lhs, const ch_scfixed& rhs) {
    auto ret = ((ch_scint<N+Frac>(lhs) << Frac) / rhs.as_scint()).template slice<N>();
    return ret.template as<ch_scfixed>();
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  explicit operator U() const {
    return static_cast<U>(this->as_scint());
  }

  explicit operator float() const {
    static_assert(N <= 32, "invalid size");
    int32_t ivalue = static_cast<int32_t>(*this);
    auto value = float(ivalue) / (1 << Frac);
    return value;
  }

  explicit operator double() const {
    static_assert(N <= 32, "invalid size");
    int32_t ivalue = static_cast<int32_t>(*this);
    auto value = double(ivalue) / (1 << Frac);
    return value;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned F>
class ch_fixed : public ch_number_base<ch_fixed<N, F>> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = logic_traits<N, true, ch_fixed, ch_scfixed<N, Frac>>;
  using base = ch_number_base<ch_fixed<N, F>>;

  ch_fixed(const logic_buffer& buffer =
      logic_buffer(N, ch::internal::idname<ch_fixed>()))
    : buffer_(buffer)
  {}

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_fixed(const U& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  explicit ch_fixed(double other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch::internal::is_scbit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_fixed(const U& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch::internal::is_bit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_fixed(const U& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  explicit ch_fixed(const ch_fixed& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    this->operator=(other);
  }

  ch_fixed(ch_fixed&& other) : buffer_(std::move(other.buffer_)) {}

  ch_fixed& operator=(double other) {
    __source_location(1);
    base::operator=(ToFixed<int>(other, Intg, Frac));
    return *this;
  }

  ch_fixed& operator=(const ch_fixed& other) {
    __source_location(1);
    base::operator=(other);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    __source_location(1);
    base::operator=(std::move(other));
    return *this;
  }

protected:

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    auto ret = ch_shr<N>(ch_mul<N+Frac>(this->as_int(), other), Frac);
    return ret.template as<ch_fixed>();
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    auto ret = (ch_shl<N+Frac>(this->as_int(), Frac) / other).template slice<N>();
    return ret.template as<ch_fixed>();
  }

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class ch::internal::logic_accessor;
  template <unsigned M, unsigned E> friend class ch_fixed;
};

}
}
