#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N>
class const_bit_slice {
public:
  static constexpr unsigned bitsize = N;
  using traits = logic_traits<const_bit_slice, const_bit_slice, ch_bit<N>, ch_scalar<N>>;

  const_bit_slice(const bit_buffer& buffer, size_t start = 0)
    : buffer_(bit_buffer(N, buffer, start)) {
    assert(N + start <= buffer.get_size());
  }

  const_bit_slice(const const_bit_slice& rhs)
    : buffer_(bit_accessor::clone(rhs))
  {}

  const_bit_slice(const_bit_slice&& rhs)
    : buffer_(std::move(rhs.buffer_))
  {}

  const auto operator[](size_t index) const {
    return const_bit_slice<1>(bit_buffer(1, buffer_, index));
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return const_bit_slice<M>(bit_buffer(M, buffer_, index));
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return const_bit_slice<M>(bit_buffer(M, buffer_, index * M));
  }

protected:

  const bit_buffer& get_buffer() const {
    return buffer_;
  }

  bit_buffer& get_buffer() {
    return buffer_;
  }

  bit_buffer buffer_;

  friend class bit_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class bit_slice : public const_bit_slice<N> {
public:
  using base = const_bit_slice<N>;
  using traits = logic_traits<bit_slice, const_bit_slice<N>, ch_bit<N>, ch_scalar<N>>;
  using base::buffer_;

  bit_slice(const bit_buffer& buffer, unsigned start = 0) : base(buffer, start) {}

  bit_slice(const bit_slice& rhs) : base(rhs) {}

  bit_slice(bit_slice&& rhs) : base(std::move(rhs)) {}

  bit_slice& operator=(const bit_slice& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  bit_slice& operator=(bit_slice&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

  template <typename T, CH_REQUIRES(is_bit_convertible<T, N>::value)>
  bit_slice& operator=(const T& rhs) {
    buffer_.set_data(get_lnode<T, N>(rhs));
    return *this;
  }

  auto operator[](size_t index) {
    return bit_slice<1>(bit_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return bit_slice<M>(bit_buffer(M, buffer_, start));
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
    return bit_slice<M>(bit_buffer(M, buffer_, start * M));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class bit_concat {
public:
  static constexpr unsigned bitsize = N;
  using traits = logic_traits<bit_concat, bit_concat, ch_bit<N>, ch_scalar<N>>;

  bit_concat(const std::vector<bit_buffer>& buffers) : buffers_(buffers) {}

  bit_concat(const bit_concat& rhs) : buffers_(rhs.buffers_) {}

  bit_concat(bit_concat&& rhs) : buffers_(std::move(rhs.buffers_)) {}

  bit_concat& operator=(const bit_concat& rhs) {
    buffers_ = rhs.buffers_;
  }

  bit_concat& operator=(bit_concat&& rhs) {
    buffers_ = std::move(rhs.buffers_);
  }

  template <typename T, CH_REQUIRES(is_bit_convertible<T, N>::value)>
  bit_concat& operator=(const T& rhs) {
    CH_TODO();
    return *this;
  }

protected:

  std::vector<bit_buffer> buffers_;
};

}}
