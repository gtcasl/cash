#pragma once

#include "int.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_uint : public logic_op_relational<ch_uint, N,
                        logic_op_bitwise<ch_uint, N,
                          logic_op_shift<ch_uint, N,
                            logic_op_arithmetic<ch_uint, N,
                              logic_op_slice<ch_uint, N, ch_bit<N>>>>>> {
public:
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = logic_op_relational<ch_uint, N,
                 logic_op_bitwise<ch_uint, N,
                   logic_op_shift<ch_uint, N,
                     logic_op_arithmetic<ch_uint, N,
                       logic_op_slice<ch_uint, N, ch_bit<N>>>>>>;

  explicit ch_uint(const logic_buffer& buffer = logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_uint(const U& other, CH_SLOC) : base(other, sloc) {}

  ch_uint(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_uint(const U& other, CH_SLOC) : base(other, sloc) {}

  explicit ch_uint(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  explicit ch_uint(const U& other, CH_SLOC) : base(other, sloc) {}

  ch_uint(const ch_uint& other, CH_SLOC) : base(other, sloc) {}

  ch_uint(ch_uint&& other) : base(std::move(other)) {}

  ch_uint& operator=(const ch_uint& other) {
    base::operator=(other);
    return *this;
  }

  ch_uint& operator=(ch_uint&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_uint)
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_uint<N>& obj, CH_SLOC) {
  return ch_uint<M+N>(obj, sloc);
}

CH_LOGIC_FUNCTION_EQUALITY(ch_eq, ch_op::eq, ch_uint)
CH_LOGIC_FUNCTION_EQUALITY(ch_ne, ch_op::ne, ch_uint)

CH_LOGIC_FUNCTION_RELATIONAL(ch_lt, ch_op::lt, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_le, ch_op::le, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_gt, ch_op::gt, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_ge, ch_op::ge, ch_uint)

CH_LOGIC_FUNCTION_BINARY1(ch_inv, ch_op::inv, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_and, ch_op::andb, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_or, ch_op::orb, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_xor, ch_op::xorb, ch_uint)

CH_LOGIC_FUNCTION_SHIFT(ch_shl, ch_op::shl, ch_uint)
CH_LOGIC_FUNCTION_SHIFT(ch_shr, ch_op::shr, ch_uint)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_neg, ch_op::neg, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_add, ch_op::add, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_sub, ch_op::sub, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_mult, ch_op::mult, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_div, ch_op::div, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_mod, ch_op::mod, ch_uint)

}}
