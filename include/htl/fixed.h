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
class ch_sfixed : public ch_snumber_base<ch_sfixed<N, F>> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = system_traits<N, true, ch_sfixed, ch_fixed<N, Frac>>;
  using base = ch_snumber_base<ch_sfixed<N, F>>;

  ch_sfixed(const system_buffer_ptr& buffer
            = make_system_buffer(N, ch::internal::idname<ch_sfixed>()))
    : buffer_(buffer)
  {}

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_sfixed(const U& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    base::operator=(other);
  }

  explicit ch_sfixed(float other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    this->operator=(other);
  }

  explicit ch_sfixed(double other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_sfixed(const ch_sbit_base<U>& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_sfixed(const ch_sbit<M>& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_sfixed(const ch_suint<M>& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_sfixed(const ch_sint<M>& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    base::operator=(other);
  }

  explicit ch_sfixed(const ch_sfixed& other)
    : ch_sfixed(make_system_buffer(N, ch::internal::idname<ch_sfixed>())) {
    this->operator=(other);
  }

  ch_sfixed(ch_sfixed&& other) : buffer_(std::move(other.buffer_)) {}

  ch_sfixed& operator=(const ch_sfixed& other) {
    this->as_bit().operator=(other.as_bit());
    return *this;
  }

  ch_sfixed& operator=(ch_sfixed&& other) {
    this->as_bit().operator=(std::move(other.as_bit()));
    return *this;
  }

  ch_sfixed& operator=(float other) {
    static_assert(N <= 32, "invalid size");
    base::operator=(ToFixed<int32_t>(other, Intg, Frac));
    return *this;
  }

  ch_sfixed& operator=(double other) {
    static_assert(N <= 64, "invalid size");
    base::operator=(ToFixed<int64_t>(other, Intg, Frac));
    return *this;
  }

  explicit operator float() const {
    static_assert(N <= 32, "invalid size");
    auto ivalue = static_cast<int32_t>(*this);
    auto value = float(ivalue) / (1 << Frac);
    return value;
  }

  explicit operator double() const {
    static_assert(N <= 64, "invalid size");
    auto ivalue = static_cast<int64_t>(*this);
    auto value = double(ivalue) / (1 << Frac);
    return value;
  }

protected:

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfixed>, "invalid type");
    auto ret = ch_shr<N>(ch_mul<N+Frac>(this->as_int(), other.as_int()), Frac);
    return ret.template as<ch_sfixed>();
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    static_assert(std::is_same_v<R, ch_sfixed>, "invalid type");
    auto ret = ch_slice<N>(ch_shl<N+Frac>(this->as_int(), Frac) / other.as_int());
    return ret.template as<ch_sfixed>();
  }

  const system_buffer_ptr& __buffer() const {
    return buffer_;
  }

  system_buffer_ptr buffer_;

  friend class ch::internal::system_accessor;
  template <unsigned M, unsigned E> friend class ch_sfixed;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned F>
class ch_fixed : public ch_number_base<ch_fixed<N, F>> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = logic_traits<N, true, ch_fixed, ch_sfixed<N, Frac>>;
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

  explicit ch_fixed(float other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    this->operator=(other);
  }

  explicit ch_fixed(double other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_fixed(const ch_sbit_base<U>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_sbit<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_sint<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_suint<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_fixed(const ch_bit_base<U>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_bit<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_uint<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_fixed(const ch_int<M>& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    base::operator=(other);
  }

  ch_fixed(const ch_fixed& other)
    : ch_fixed(logic_buffer(N, ch::internal::idname<ch_fixed>())) {
    __source_location(1);
    this->operator=(other);
  }

  ch_fixed(ch_fixed&& other) : buffer_(std::move(other.buffer_)) {}

  ch_fixed& operator=(float other) {
    __source_location(1);
    base::operator=(ToFixed<int>(other, Intg, Frac));
    return *this;
  }

  ch_fixed& operator=(double other) {
    __source_location(1);
    base::operator=(ToFixed<int>(other, Intg, Frac));
    return *this;
  }

  ch_fixed& operator=(const ch_fixed& other) {
    __source_location(1);
    this->as_bit().operator=(other.as_bit());
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    __source_location(1);
    this->as_bit().operator=(std::move(other.as_bit()));
    return *this;
  }

protected:

  template <typename R, typename U>
  auto do_mul(const U& other) const {
    static_assert(std::is_same_v<R, ch_fixed>, "invalid type");
    auto ret = ch_shr<N>(ch_mul<N+Frac>(this->as_int(), other.as_int()), Frac);
    return ret.template as<ch_fixed>();
  }

  template <typename R, typename U>
  auto do_div(const U& other) const {
    static_assert(std::is_same_v<R, ch_fixed>, "invalid type");
    auto ret = ch_slice<N>(ch_shl<N+Frac>(this->as_int(), Frac) / other.as_int());
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
