#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_int : public ch_bit<N> {
public:  
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = ch_bit<N>;

  ch_int(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_int>()))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int(const U& other)
    : base(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : base(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : base(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_int(const ch_int& other)
    : base(logic_buffer(N, idname<ch_int>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_int(ch_int&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  ch_int& operator=(const ch_int& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  ch_int& operator=(ch_int&& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_int)
  CH_LOGIC_OP_RELATIONAL(ch_int)
  CH_LOGIC_OP_ARITHMETIC(ch_int)
  CH_LOGIC_OP_BITWISE(ch_int)
  CH_LOGIC_OP_SHIFT(ch_int)
  CH_LOGIC_OP_SLICE(ch_int)
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

CH_LOGIC_FUNCTION_EQUALITY(ch_int, ch_eq, ch_op::eq)
CH_LOGIC_FUNCTION_EQUALITY(ch_int, ch_ne, ch_op::ne)

CH_LOGIC_FUNCTION_RELATIONAL(ch_int, ch_lt, ch_op::lt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_int, ch_le, ch_op::le)
CH_LOGIC_FUNCTION_RELATIONAL(ch_int, ch_gt, ch_op::gt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_int, ch_ge, ch_op::ge)

CH_LOGIC_FUNCTION_BITWISE1(ch_int, ch_inv, ch_op::inv)
CH_LOGIC_FUNCTION_BITWISE2(ch_int, ch_and, ch_op::andb)
CH_LOGIC_FUNCTION_BITWISE2(ch_int, ch_or, ch_op::orb)
CH_LOGIC_FUNCTION_BITWISE2(ch_int, ch_xor, ch_op::xorb)

CH_LOGIC_FUNCTION_SHIFT(ch_int, ch_shl, ch_op::shl)
CH_LOGIC_FUNCTION_SHIFT(ch_int, ch_shr, ch_op::shr)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_int, ch_neg, ch_op::neg)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_int, ch_add, ch_op::add)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_int, ch_sub, ch_op::sub)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_int, ch_mul, ch_op::mul)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_int, ch_div, ch_op::div)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_int, ch_mod, ch_op::mod)

}}
