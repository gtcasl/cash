#pragma once

#include "uint.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_int : public ch_number_base<ch_int<N>> {
public:  
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  template <unsigned M> using size_cast = ch_int<M>;
  using base = ch_number_base<ch_int<N>>;
  using base::operator=;

  ch_int(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_int>()))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_int(const U& other)
    : ch_int(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_scbit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : ch_int(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_bit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : ch_int(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_int(const ch_int& other)
    : ch_int(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_int(ch_int&& other) : buffer_(std::move(other.buffer_)) {}

  ch_int& operator=(const ch_int& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_int& operator=(ch_int&& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
  template <unsigned M> friend class ch_int;
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_int<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_int<M+N>(obj);
}

template <unsigned N>
auto ch_abs(const ch_int<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_sel(obj[N-1], -obj, obj);
}

}}
