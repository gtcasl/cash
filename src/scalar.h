#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N>
class const_scalar_slice;

template <unsigned N>
class scalar_slice;

template <unsigned N>
class ch_scalar {
public:
  static constexpr unsigned bitcount = N;
  using value_type = ch_bit<N>;

  constexpr ch_scalar() : value_(N) {}
  constexpr ch_scalar(const ch_scalar& rhs) : value_(rhs.value_) {}
  constexpr ch_scalar(ch_scalar&& rhs) : value_(std::move(rhs.value_)) {}

  ch_scalar(const const_scalar_slice<N>& slice) {
    value_.copy(0, slice.scalar_.value_, slice.start_, N);
  }

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

  const auto operator[](size_t index) const {
    return const_scalar_slice<1>(*this, index);
  }

  const auto operator[](size_t index) {
    return scalar_slice<1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t start) const {
    return const_scalar_slice<M>(*this, start);
  }

  template <unsigned M>
  const auto slice(size_t start) {
    return scalar_slice<M>(*this, start);
  }

  template <unsigned M>
  const auto aslice(size_t start) const {
    return const_scalar_slice<M>(*this, start * M);
  }

  template <unsigned M>
  const auto aslice(size_t start) {
    return scalar_slice<M>(*this, start * M);
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

template <unsigned N>
class const_scalar_slice {
private:
  template <unsigned M>
  const_scalar_slice(const ch_scalar<M>& scalar, unsigned start)
    : value_(const_cast<bitvector&>(scalar.value_))
    , start_(start) {
    static_assert(N <= M, "invalid container size");
    assert(N + start <= M);
  }

  const_scalar_slice(const const_scalar_slice& rhs)
    : value_(rhs.value_)
    , start_(rhs.start_)
  {}

protected:

  const_scalar_slice& operator=(const const_scalar_slice& rhs) {
    value_ = rhs.value_;
    start_ = rhs.start_;
    return *this;
  }

  void copy(const bitvector& src, unsigned src_offset = 0) {
    value_.copy(start_, src, src_offset, N);
  }

  bitvector& value_;
  unsigned start_;

  template <unsigned M> friend class ch_scalar;
};

template <unsigned N>
class scalar_slice : public const_scalar_slice<N> {
private:
  using base = const_scalar_slice<N>;

  template <unsigned M>
  scalar_slice(const ch_scalar<M>& scalar, unsigned start)
    : base(scalar, start)
  {}

  scalar_slice(const scalar_slice& rhs) : base(rhs) {}

  scalar_slice& operator=(const scalar_slice& rhs) {
    this->copy(rhs.value_, rhs.start_);
    return *this;
  }

  scalar_slice& operator=(const ch_scalar<N>& rhs) {
    this->copy(rhs.value_);
    return *this;
  }

  template <typename U, CH_REQUIRES(std::is_integral<U>::value)>
  scalar_slice& operator=(U value) {
    this->copy(bitvector(value), 0);
    return *this;
  }

  scalar_slice& operator=(const std::initializer_list<uint32_t>& value) {
    this->copy(bitvector(value));
    return *this;
  }

  scalar_slice& operator=(const char* value) {
    this->copy(bitvector(value));
    return *this;
  }
};

}
}
