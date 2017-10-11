#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N>
class ch_scalar {
public:
  static constexpr unsigned bitcount = N;
  using value_type = ch_bit<N>;

  constexpr ch_scalar(unsigned size = N) : value_(size) {}
  constexpr ch_scalar(const ch_scalar& rhs) : value_(rhs.value_) {}
  constexpr ch_scalar(ch_scalar&& rhs) : value_(std::move(rhs.value_)) {}

  template <typename U, CH_REQUIRES(std::is_integral<U>::value)>
  explicit ch_scalar(U value) : value_(N, value) {}

  explicit ch_scalar(const std::initializer_list<uint32_t>& value)
    : value_(N, value)
  {}

  explicit ch_scalar(const char* value) : value_(N, value) {}

  ch_scalar& operator=(const ch_scalar& rhs) {
    value_ = rhs.value_;
    return *this;
  }

  ch_scalar& operator=(ch_scalar&& rhs) {
    value_ = std::move(rhs.value_);
    return *this;
  }

  template <typename U, CH_REQUIRES(std::is_integral<U>::value)>
  ch_scalar& operator=(U value) {
    value_ = value;
    return *this;
  }

  ch_scalar& operator=(const std::initializer_list<uint32_t>& value) {
    value_ = value;
    return *this;
  }

  ch_scalar& operator=(const char* value) {
    value_ = value;
    return *this;
  }

private:

  bitvector value_;

  friend std::ostream& operator<<(std::ostream& out, const ch_scalar& rhs) {
    return out << rhs.value_;
  }

  friend bool operator!=(const ch_scalar& lhs, const ch_scalar& rhs) {
    return !(lhs.value_ == rhs.value_);
  }

  friend bool operator>=(const ch_scalar& lhs, const ch_scalar& rhs) {
    return !(lhs.value_ < rhs.value_);
  }

  friend bool operator>(const ch_scalar& lhs, const ch_scalar& rhs) {
    return (rhs.value_ < lhs.value_);
  }

  friend bool operator<=(const ch_scalar& lhs, const ch_scalar& rhs) {
    return !(rhs.value_ < lhs.value_);
  }

  friend bool operator!(const ch_scalar& rhs) {
    ch_scalar ret;
    Inverse(ret, rhs.value_);
    return ret;
  }

  friend const auto operator~(const ch_scalar& rhs) {
    ch_scalar ret;
    Inverse(ret.value_, rhs.value_);
    return ret;
  }

  friend const auto operator&(const ch_scalar& lhs, const ch_scalar& rhs) {
    ch_scalar ret;
    And(ret, lhs.value_, rhs.value_);
    return ret;
  }

  friend const auto operator|(const ch_scalar& lhs, const ch_scalar& rhs) {
    ch_scalar ret;
    Or(ret.value_, lhs.value_, rhs.value_);
    return ret;
  }

  friend const auto operator^(const ch_scalar& lhs, const ch_scalar& rhs) {
    ch_scalar ret;
    Xor(ret.value_, lhs.value_, rhs.value_);
    return ret;
  }

  friend const auto operator<<(const ch_scalar& lhs, uint32_t rhs) {
    ch_scalar ret;
    SLL(ret, lhs.value_, rhs);
    return ret;
  }

  friend const auto operator>>(const ch_scalar& lhs, uint32_t rhs) {
    ch_scalar ret;
    SLL(ret, lhs.value_, rhs);
    return ret;
  }

  friend const auto operator+(const ch_scalar& lhs, const ch_scalar& rhs) {
    ch_scalar ret;
    Add(ret, lhs.value_, rhs.value_);
    return ret;
  }

  friend const auto operator-(const ch_scalar& lhs, const ch_scalar& rhs) {
    ch_scalar ret;
    Sub(ret, lhs.value_, rhs.value_);
    return ret;
  }

  friend const auto operator-(const ch_scalar& rhs) {
    ch_scalar ret;
    Negate(ret, rhs.value_);
    return ret;
  }

  template <unsigned M> friend class bitbase;
  template <unsigned M> friend class const_bit;
};

}
}
