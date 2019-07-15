#pragma once

#include <cash.h>
#include <htl/fixed.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T>
__struct (ch_complex, (
  (T) re,
  (T) im
));

template <typename T>
auto operator==(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return (lhs.re == rhs.re) && (lhs.im == rhs.im);
}

template <typename T>
auto operator!=(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
auto operator-(const ch_complex<T>& self) {
  return ch_complex<T>(-self.im, -self.re);
}

template <typename T>
auto operator+(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return ch_complex<T>(lhs.im + rhs.im, lhs.re + rhs.re);
}

template <typename T>
auto operator-(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return ch_complex<T>(lhs.im - rhs.im, lhs.re - rhs.re);
}

template <typename T>
auto operator*(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  auto re = lhs.re * rhs.re - lhs.im * rhs.im;
  auto im = lhs.im * rhs.re + lhs.re * rhs.im;
  return ch_complex<T>(im, re);
}

template <unsigned N, unsigned F>
auto operator*(const ch_complex<ch_fixed<N, F>>& lhs, const ch_complex<ch_fixed<N, F>>& rhs) {
  static constexpr unsigned K = N + F;
  auto re = ch_shr<N>(ch_mul<K>(lhs.re.as_int(), rhs.re.as_int()) - ch_mul<K>(lhs.im.as_int(), rhs.im.as_int()), F);
  auto im = ch_shr<N>(ch_mul<K>(lhs.im.as_int(), rhs.re.as_int()) + ch_mul<K>(lhs.re.as_int(), rhs.im.as_int()), F);
  return ch_complex<ch_fixed<N, F>>(im, re);
}

template <typename T>
auto operator/(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  auto q_1 = rhs.re * rhs.re;
  auto q_2 = rhs.im * rhs.im;
  auto q  = q_1 + q_2;
  auto re_1 = lhs.re * rhs.re;
  auto re_2 = lhs.im * rhs.im;
  auto re = (re_1 + re_2) / q;
  auto im_1 = lhs.im * rhs.re;
  auto im_2 = lhs.re * rhs.im;
  auto im = (im_1 - im_2) / q;
  return ch_complex<T>(im, re);
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
