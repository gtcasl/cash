#pragma once

#include "int.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_uint : public logic_op_relational<ch_uint, N,
                        logic_op_bitwise<ch_uint, N,
                          logic_op_shift<ch_uint, N,
                            logic_op_padding<ch_uint, N,
                              logic_op_arithmetic<ch_uint, N, ch_bit<N>>>>>> {
public:
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = logic_op_relational<ch_uint, N,
                 logic_op_bitwise<ch_uint, N,
                   logic_op_shift<ch_uint, N,
                     logic_op_padding<ch_uint, N,
                       logic_op_arithmetic<ch_uint, N, ch_bit<N>>>>>>;

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

CH_LOGIC_FUNCTION_EQUALITY(ch_eq, op_eq, ch_uint)
CH_LOGIC_FUNCTION_EQUALITY(ch_ne, op_ne, ch_uint)

CH_LOGIC_FUNCTION_RELATIONAL(ch_lt, op_lt, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_le, op_le, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_gt, op_gt, ch_uint)
CH_LOGIC_FUNCTION_RELATIONAL(ch_ge, op_ge, ch_uint)

CH_LOGIC_FUNCTION_BINARY1(ch_inv, op_inv, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_and, op_and, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_or, op_or, ch_uint)
CH_LOGIC_FUNCTION_BINARY2(ch_xor, op_xor, ch_uint)

CH_LOGIC_FUNCTION_SHIFT(ch_shl, op_shl, ch_uint)
CH_LOGIC_FUNCTION_SHIFT(ch_shr, op_shr, ch_uint)

CH_LOGIC_FUNCTION_ARITHMETIC1(ch_neg, op_neg, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_add, op_add, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_sub, op_sub, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_mul, op_mul, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_div, op_div, ch_uint)
CH_LOGIC_FUNCTION_ARITHMETIC2(ch_mod, op_mod, ch_uint)

}}
