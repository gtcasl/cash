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
bool operator==(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return lhs.read == rhs.re && lhs.im == rhs.im;
}

template <typename T>
bool operator!=(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
ch_complex<T> operator+(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return ch_complex<T>(lhs.im + rhs.im, lhs.re + rhs.re);
}

template <typename T>
ch_complex<T> operator-(const ch_complex<T>& lhs, const ch_complex<T>& rhs) {
  return ch_complex<T>(lhs.im - rhs.im, lhs.re - rhs.re);
}

}
}
