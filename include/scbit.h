#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_scbit : public scalar_op_compare<ch_scbit, N,
                          scalar_op_logical<ch_scbit, N,
                            scalar_op_bitwise<ch_scbit, N,
                              scalar_op_shift<ch_scbit, N,
                                scalar_op_padding<ch_scbit, N,
                                  scalar_op_cast<ch_scbit, N>>>>>> {
public:
  using traits = scalar_traits<N, false, ch_scbit, ch_bit<N>>;
  using base = scalar_op_compare<ch_scbit, N,
                scalar_op_logical<ch_scbit, N,
                  scalar_op_bitwise<ch_scbit, N,
                    scalar_op_shift<ch_scbit, N,
                      scalar_op_padding<ch_scbit, N,
                        scalar_op_cast<ch_scbit, N>>>>>>;

  explicit ch_scbit(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scbit(const U& other)
    : buffer_(make_scalar_buffer(bitvector(N , other)))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<std::decay_t<U>>)>
  explicit ch_scbit(U&& other)
    : buffer_(make_scalar_buffer(bitvector(N , std::forward<U>(other))))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(ch_width_v<U> == N)>
  explicit ch_scbit(const U& other)
    : buffer_(scalar_accessor::copy_buffer(other))
  {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  explicit ch_scbit(const ch_scbit<M>& other)
    : buffer_(scalar_accessor::copy_buffer(other.template pad<N>()))
  {}

  ch_scbit(const ch_scbit& other)
    : base()
    , buffer_(scalar_accessor::copy_buffer(other))
  {}

  ch_scbit(ch_scbit&& other) : buffer_(std::move(other.buffer_)) {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(ch_width_v<U> == N)>
  ch_scbit& operator=(const U& other) {
    scalar_accessor::copy(*this, other);
    return *this;
  }

  ch_scbit& operator=(const ch_scbit& other) {
    scalar_accessor::copy(*this, other);
    return *this;
  }

  ch_scbit& operator=(ch_scbit&& other) {
    scalar_accessor::move(*this, std::move(other));
    return *this;
  }

  // subscript operators

  const auto operator[](size_t index) const {
    assert(index < N);
    return ch_scbit<1>(make_scalar_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    assert(index < N);
    return ch_scbit<1>(make_scalar_buffer(1, buffer_, index));
  }

  // slicing operators

  template <typename R>
  const auto slice(size_t start = 0) const {
    static_assert(is_scalar_type_v<R>, "invalid type");
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert((start + ch_width_v<R>) <= N);
    return R(make_scalar_buffer(ch_width_v<R>, buffer_, start));
  }

  template <typename R>
  const auto aslice(size_t start = 0) const {
    return this->slice<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return this->slice<ch_scbit<M>>(start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return this->slice<ch_scbit<M>>(start * M);
  }

  template <typename R>
  auto slice(size_t start = 0) {
    static_assert(is_scalar_type_v<R>, "invalid type");
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert((start + ch_width_v<R>) <= N);
    return R(make_scalar_buffer(ch_width_v<R>, buffer_, start));
  }

  template <typename R>
  auto aslice(size_t start = 0) {
    return this->slice<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return this->slice<ch_scbit<M>>(start);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
    return this->slice<ch_scbit<M>>(start * M);
  }

  // bits access

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset = 0,
            uint32_t length = N) const {
    buffer_->read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = N) {
    buffer_->write(dst_offset, in, in_cbsize, src_offset, length);
  }

  CH_SCALAR_INTERFACE(ch_scbit)

protected:

  const scalar_buffer_ptr& buffer() const {
    return buffer_;
  }

  scalar_buffer_ptr buffer_;

  friend class scalar_accessor;

  friend std::ostream& operator<<(std::ostream& out, const ch_scbit& in) {
    return out << scalar_accessor::data(in);
  }
};

}
}
