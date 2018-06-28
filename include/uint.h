#pragma once

#include "int.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_uint : public logic_op_compare<ch_uint, N,
                        logic_op_logical<ch_uint, N,
                          logic_op_bitwise<ch_uint, N,
                            logic_op_shift<ch_uint, N,
                              logic_op_padding<ch_uint, N,
                                logic_op_relational<ch_uint, N,
                                  logic_op_arithmetic<ch_uint, N, ch_bit<N>>>>>>>> {
public:
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = logic_op_compare<ch_uint, N,
                logic_op_logical<ch_uint, N,
                  logic_op_bitwise<ch_uint, N,
                    logic_op_shift<ch_uint, N,
                      logic_op_padding<ch_uint, N,
                        logic_op_relational<ch_uint, N,
                          logic_op_arithmetic<ch_uint, N, ch_bit<N>>>>>>>>;

  explicit ch_uint(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_uint(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_uint(const ch_scbit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_uint(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(ch_width_v<U> == N)>
  explicit ch_uint(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  explicit ch_uint(const ch_uint<M>& rhs, CH_SLOC) : base(rhs.template pad<N>(sloc), sloc) {}

  explicit ch_uint(const ch_bit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_uint(const ch_uint& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_uint(ch_uint&& rhs) : base(std::move(rhs)) {}

  ch_uint& operator=(const ch_uint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_uint& operator=(ch_uint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_uint)
};

}}
