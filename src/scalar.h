#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

template <typename T>
class bytes_accessor {
public:
  static void read_bytes(const T& obj, uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) {
    obj.read_bytes(dst_offset, out, out_cbsize, src_offset, length);
  }
  static void write_bytes(T& obj, uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
    obj.write_bytes(dst_offset, in, in_cbsize, src_offset, length);
  }
};

template <unsigned N>
class const_scalar_slice;

template <unsigned N>
class scalar_slice;

template <unsigned N> class ch_bit;

template<typename T, typename Enable = void>
struct is_sim_type : std::false_type {};

template<typename T>
struct is_sim_type<T, typename std::enable_if_t<std::is_same<std::decay_t<T>, typename std::decay_t<T>::sim_type>::value>> : std::true_type {};

template <unsigned N>
class ch_scalar {
public:
  static constexpr unsigned bitcount = N;  
  using sim_type = ch_scalar;
  using value_type = ch_bit<N>;

  constexpr ch_scalar(unsigned size = N) : value_(size) {}
  constexpr ch_scalar(const ch_scalar& rhs) : value_(rhs.value_) {}
  constexpr ch_scalar(ch_scalar&& rhs) : value_(std::move(rhs.value_)) {}

  ch_scalar(const const_scalar_slice<N>& slice) {
    value_.copy(0, slice.scalar_.value_, slice.start_, N);
  }

  template <typename U, CH_REQUIRES(is_sim_type<U>::value)>
  explicit ch_scalar(const U& rhs) {
    bytes_accessor<U>::read_bytes(rhs, 0, value_.get_words(), value_.get_cbsize(), 0, N);
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
  const auto slice(size_t start = 0) const {
    return const_scalar_slice<M>(*this, start);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) {
    return scalar_slice<M>(*this, start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_scalar_slice<M>(*this, start * M);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) {
    return scalar_slice<M>(*this, start * M);
  }

protected:

  bitvector value_;

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const {
    value_.read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
    value_.write(dst_offset, in, in_cbsize, src_offset, length);
  }

  template <typename T> friend class bytes_accessor;

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

  template <unsigned M> friend class ch_bitbase;
  template <unsigned M> friend class const_bit;
  template <unsigned M> friend class const_scalar_slice;
};

template <unsigned N>
class const_scalar_slice {
public:
  static constexpr unsigned bitcount = N;
  using value_type = ch_bit<N>;

  template <unsigned M>
  const_scalar_slice(const ch_scalar<M>& scalar, unsigned start = 0)
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
public:
  using base = const_scalar_slice<N>;
  using value_type = ch_bit<N>;

  template <unsigned M>
  scalar_slice(const ch_scalar<M>& scalar, unsigned start = 0)
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
