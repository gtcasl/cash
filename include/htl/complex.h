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
  return ch_complex<T>(lhs.im - rhs.im, lhs.re - rhs.re);
}

template <typename T>
auto operator*(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return ch_complex<T>(lhs.re * rhs.re - lhs.im * rhs.im,
                       lhs.re + rhs.im + lhs.im * rhs.re);
}

}
}
