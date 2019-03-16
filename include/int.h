#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_int : public logic_op_relational<ch_int, N,
                        logic_op_bitwise<ch_int, N,
                          logic_op_shift<ch_int, N,
                            logic_op_arithmetic<ch_int, N,
                              logic_op_slice<ch_int, N, ch_bit<N>>>>>> {
public:
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = logic_op_relational<ch_int, N,
                 logic_op_bitwise<ch_int, N,
                   logic_op_shift<ch_int, N,
                     logic_op_arithmetic<ch_int, N,
                       logic_op_slice<ch_int, N, ch_bit<N>>>>>>;

  ch_int(const logic_buffer& buffer =
      logic_buffer(N, identifier_from_typeid(typeid(ch_int).name())))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int(const U& other)
    : base(logic_buffer(N, identifier_from_typeid(typeid(ch_int).name()))) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : base(logic_buffer(N, identifier_from_typeid(typeid(ch_int).name()))) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_int(const U& other)
    : base(logic_buffer(N, identifier_from_typeid(typeid(ch_int).name()))) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_int(const ch_int& other)
    : base(logic_buffer(N, identifier_from_typeid(typeid(ch_int).name()))) {
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

CH_LOGIC_FUNCTION_EQUALITY(ch_eq, ch_op::eq, ch_int)
CH_LOGIC_FUNCTION_EQUALITY(ch_ne, ch_op::ne, ch_int)

CH_LOGIC_FUNCTION_RELATIONAL(ch_lt, ch_op::lt, ch_int)
CH_LOGIC_FUNCTION_RELATIONAL(ch_le, ch_op::le, ch_int)
CH_LOGIC_FUNCTION_RELATIONAL(ch_gt, ch_op::gt, ch_int)
CH_LOGIC_FUNCTION_RELATIONAL(ch_ge, ch_op::ge, ch_int)

CH_LOGIC_FUNCTION_BITWISE1(ch_inv, ch_op::inv, ch_int)
CH_LOGIC_FUNCTION_BITWISE2(ch_and, ch_op::andb, ch_int)
CH_LOGIC_FUNCTION_BITWISE2(ch_or, ch_op::orb, ch_int)
CH_LOGIC_FUNCTION_BITWISE2(ch_xor, ch_op::xorb, ch_int)

CH_LOGIC_FUNCTION_SHIFT(ch_shl, ch_op::shl, ch_int)
CH_LOGIC_FUNCTION_SHIFT(ch_shr, ch_op::shr, ch_int)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_neg, ch_op::neg, ch_int)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_add, ch_op::add, ch_int)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_sub, ch_op::sub, ch_int)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_mul, ch_op::mul, ch_int)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_div, ch_op::div, ch_int)
CH_LOGIC_FUNCTION_ARITHMETIC3(ch_mod, ch_op::mod, ch_int)

}}
