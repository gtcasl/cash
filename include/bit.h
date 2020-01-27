#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_sbit : public ch_sbitbase<ch_sbit<N>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = system_traits<N, false, ch_sbit, ch_bit<N>>;
  using base = ch_sbitbase<ch_sbit<N>>;
  using base::operator=;

  ch_sbit(const system_buffer& buffer
          = make_system_buffer(N, idname<ch_sbit>()))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_sbit(const U& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_bitvector_extended_type_v<U>)>
  explicit ch_sbit(U&& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(make_system_buffer(sdata_type(N , std::forward<U>(other))));
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_sbit(const ch_sbitbase<U>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_sbit(const ch_sbool& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_sint<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_suint<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_sbit<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  ch_sbit(const ch_sbit& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  ch_sbit(ch_sbit&& other) : buffer_(std::move(other.buffer_)) {}

  ch_sbit& operator=(const ch_sbit& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_sbit& operator=(ch_sbit&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const system_buffer& __buffer() const {
    return buffer_;
  }

  system_buffer buffer_;

  friend class system_accessor;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public ch_bitbase<ch_bit<N>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, false, ch_bit, ch_sbit<N>>;
  using base = ch_bitbase<ch_bit<N>>;
  using base::operator=;

  ch_bit(const logic_buffer& buffer 
    = make_logic_buffer(N, idname<ch_bit>(), CH_CUR_SRC_INFO))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_bit(const U& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_bit(const ch_sbitbase<U>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_bit(const ch_sbool& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_sbit<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_sint<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_suint<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_bit(const ch_bitbase<U>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(reinterpret_cast<const U&>(other));
  }

  ch_bit(const ch_bool& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_uint<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_int<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_bit<M>& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  ch_bit(const ch_bit& other, CH_SRC_INFO)
    : ch_bit(make_logic_buffer(N, idname<ch_bit>(), srcinfo)) {
    this->operator=(other);
  }

  ch_bit(ch_bit&& other) : buffer_(std::move(other.buffer_)) {}  

  ch_bit& operator=(const ch_bit& other) {
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_bit& operator=(ch_bit&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
};

}
}
