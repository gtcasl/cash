#pragma once

#include "../core.h"
#include "complex.h"
#include <math.h>

namespace ch {
namespace htl {

using namespace logic;
using namespace extension;

// |1|<- N-F-1 bits ->|<--- F bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

namespace detail {
template <typename T>
inline T to_fixed(double value, unsigned I, unsigned F) {
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
}

template <unsigned N, unsigned F>
class ch_fixed;

template <unsigned N, unsigned F>
class ch_sfixed : public ch_snumbase<ch_sfixed<N, F>> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = system_traits<N, true, ch_sfixed, ch_fixed<N, F>>;
  using base = ch_snumbase<ch_sfixed<N, F>>;
  using base::operator=;

  explicit  ch_sfixed(const system_buffer& buffer = make_system_buffer(N))
    : buffer_(buffer)
  {}

  explicit ch_sfixed(float other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  explicit ch_sfixed(double other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_sfixed(const ch_sbitbase<U>& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  template <typename U,
            CH_REQUIRES(std::is_integral_v<U>)>
  ch_sfixed(const U& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_sfixed(const ch_sbit<M>& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_sfixed(const ch_suint<M>& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_sfixed(const ch_sint<M>& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  ch_sfixed(const ch_sfixed& other)
    : ch_sfixed(make_system_buffer(N)) {
    this->operator=(other);
  }

  ch_sfixed(ch_sfixed&& other) : buffer_(std::move(other.buffer_)) {}

  ch_sfixed& operator=(const ch_sfixed& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_sfixed& operator=(ch_sfixed&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

  ch_sfixed& operator=(float other) {
    static_assert(N <= 32, "invalid size");
    base::operator=(detail::to_fixed<int32_t>(other, Intg, Frac));
    return *this;
  }

  ch_sfixed& operator=(double other) {
    static_assert(N <= 64, "invalid size");
    base::operator=(detail::to_fixed<int64_t>(other, Intg, Frac));
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

  const system_buffer& __buffer() const {
    return buffer_;
  }

  system_buffer buffer_;

  friend class ch::extension::system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned F>
class ch_fixed : public ch_numbase<ch_fixed<N, F>> {
public:  
  static constexpr unsigned Intg = N-F;
  static constexpr unsigned Frac = F;
  static_assert(N >= (Frac+1), "invalid size");
  using traits = logic_traits<N, true, ch_fixed, ch_sfixed<N, F>>;
  using base = ch_numbase<ch_fixed<N, F>>;
  using base::operator=;

  explicit ch_fixed(const logic_buffer& buffer
     = make_logic_buffer(N, CH_CUR_SRC_INFO))
    : buffer_(buffer)
  {}

  explicit ch_fixed(float other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  explicit ch_fixed(double other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_fixed(const ch_sbitbase<U>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  template <typename U,
            CH_REQUIRES(ch_width_v<U> <= N)>
  explicit ch_fixed(const ch_bitbase<U>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  template <typename U,
            CH_REQUIRES(std::is_integral_v<U>)>
  ch_fixed(const U& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_sbit<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_sint<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_suint<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_bit<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_uint<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRES(M <= N)>
  ch_fixed(const ch_int<M>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  ch_fixed(const ch_sfixed<N, F>& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  ch_fixed(const ch_fixed& other, CH_SRC_INFO)
    : ch_fixed(make_logic_buffer(N, srcinfo)) {
    this->operator=(other);
  }

  ch_fixed(ch_fixed&& other) : buffer_(std::move(other.buffer_)) {}

  ch_fixed& operator=(float other) {
    base::operator=(detail::to_fixed<int32_t>(other, Intg, Frac));
    return *this;
  }

  ch_fixed& operator=(double other) {
    base::operator=(detail::to_fixed<int64_t>(other, Intg, Frac));
    return *this;
  }

  ch_fixed& operator=(const ch_fixed& other) {
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  template <typename R, typename U>
  auto do_mul(const U& other, CH_SRC_INFO) const {
    static_assert(std::is_same_v<R, ch_fixed>, "invalid type");
    auto ret = ch_shr<N>(ch_mul<N+Frac>(this->as_int(), other.as_int(), srcinfo), Frac, srcinfo);
    return ret.template as<ch_fixed>();
  }

  template <typename R, typename U>
  auto do_div(const U& other, CH_SRC_INFO) const {
    static_assert(std::is_same_v<R, ch_fixed>, "invalid type");
    auto ret = ch_div<N>(ch_shl<N+Frac>(this->as_int(), Frac, srcinfo), other.as_int(), srcinfo);
    return ret.template as<ch_fixed>();
  }

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class ch::extension::logic_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned F>
auto operator*(const ch_complex<ch_fixed<N, F>>& lhs, const ch_complex<ch_fixed<N, F>>& rhs) {
  static constexpr unsigned K = N + F;
  auto re = ch_shr<N>(ch_mul<K>(lhs.re.as_int(), rhs.re.as_int()) - ch_mul<K>(lhs.im.as_int(), rhs.im.as_int()), F);
  auto im = ch_shr<N>(ch_mul<K>(lhs.im.as_int(), rhs.re.as_int()) + ch_mul<K>(lhs.re.as_int(), rhs.im.as_int()), F);
  return ch_complex<ch_fixed<N, F>>(im, re);
}

template <unsigned N, unsigned F>
auto operator/(const ch_complex<ch_fixed<N, F>>& lhs, const ch_complex<ch_fixed<N, F>>& rhs) {
  static constexpr unsigned K = N + F;  
  auto re = ch_shr<N>(ch_mul<K>(lhs.re.as_int(), rhs.re.as_int()) + ch_mul<K>(lhs.im.as_int(), rhs.im.as_int()), F);
  auto im = ch_shr<N>(ch_mul<K>(lhs.im.as_int(), rhs.re.as_int()) - ch_mul<K>(lhs.re.as_int(), rhs.im.as_int()), F);
  auto q  = ch_shr<N>(ch_mul<K>(rhs.re.as_int(), rhs.re.as_int()) + ch_mul<K>(rhs.im.as_int(), rhs.im.as_int()), F);
  return ch_complex<ch_fixed<N, F>>(ch_slice<N>(ch_shl<N+F>(im, F) / q), ch_slice<N>(ch_shl<N+F>(re, F) / q));
}

}
}
