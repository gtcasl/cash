#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_uint : public ch_bit<N> {
public:  
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = ch_bit<N>;

  ch_uint(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_uint>()))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_uint(const U& other)
    : base(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_uint(const U& other)
    : base(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_uint(const U& other)
    : base(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_uint(const ch_uint& other)
    : base(logic_buffer(N, idname<ch_uint>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_uint(ch_uint&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_uint& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_uint& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_uint& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  ch_uint& operator=(const ch_uint& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
    return *this;
  }

  ch_uint& operator=(ch_uint&& other) {
    CH_SOURCE_LOCATION(1);
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_uint)
  CH_LOGIC_OP_RELATIONAL(ch_uint)
  CH_LOGIC_OP_BITWISE(ch_uint)
  CH_LOGIC_OP_SHIFT(ch_uint)
  CH_LOGIC_OP_ARITHMETIC(ch_uint)
  CH_LOGIC_OP_SLICE(ch_uint)
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_uint<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_uint<M+N>(obj);
}

CH_LOGIC_FUNCTION_EQUALITY(ch_uint, ch_eq, ch_op::eq)
CH_LOGIC_FUNCTION_EQUALITY(ch_uint, ch_ne, ch_op::ne)

CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_lt, ch_op::lt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_le, ch_op::le)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_gt, ch_op::gt)
CH_LOGIC_FUNCTION_RELATIONAL(ch_uint, ch_ge, ch_op::ge)

CH_LOGIC_FUNCTION_BITWISE1(ch_uint, ch_inv, ch_op::inv)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_and, ch_op::andb)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_or, ch_op::orb)
CH_LOGIC_FUNCTION_BITWISE2(ch_uint, ch_xor, ch_op::xorb)

CH_LOGIC_FUNCTION_SHIFT(ch_uint, ch_shl, ch_op::shl)
CH_LOGIC_FUNCTION_SHIFT(ch_uint, ch_shr, ch_op::shr)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_uint, ch_neg, ch_op::neg)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_uint, ch_add, ch_op::add)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_uint, ch_sub, ch_op::sub)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_mul, ch_op::mul)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_div, ch_op::div)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_uint, ch_mod, ch_op::mod)

}}
