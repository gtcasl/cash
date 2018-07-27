#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace ch::core;

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
  auto im = lhs.im - rhs.im;
  auto re = lhs.re - rhs.re;
  ch_tap(lhs.im, "fx_lhs_im");
  ch_tap(lhs.re, "fx_lhs_re");
  ch_tap(rhs.im, "fx_rhs_im");
  ch_tap(rhs.re, "fx_rhs_re");
  ch_tap(im, "fx_sub_re");
  ch_tap(re, "fx_sub_im");
  return ch_complex<T>(im, re);
}

template <typename T>
auto operator*(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  auto re = lhs.re * rhs.re - lhs.im * rhs.im;
  auto im = lhs.im * rhs.re + lhs.re * rhs.im;
  return ch_complex<T>(im, re);
}

template <typename T>
auto operator/(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  auto q  = rhs.re * rhs.re + rhs.im * rhs.im;
  auto re = (lhs.re * rhs.re + lhs.im * rhs.im) / q;
  auto im = (lhs.im * rhs.re - lhs.re * rhs.im) / q;
  return ch_complex<T>(im, re);
}

}
}
