#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_int : public logic_op_compare<ch_int, N,
                        logic_op_logical<ch_int, N,
                          logic_op_bitwise<ch_int, N,
                            logic_op_shift<ch_int, N,
                              logic_op_padding<ch_int, N,
                                logic_op_relational<ch_int, N,
                                  logic_op_arithmetic<ch_int, N, ch_bit<N>>>>>>>> {
public:
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = logic_op_compare<ch_int, N,
                logic_op_logical<ch_int, N,
                  logic_op_bitwise<ch_int, N,
                    logic_op_shift<ch_int, N,
                      logic_op_padding<ch_int, N,
                        logic_op_relational<ch_int, N,
                          logic_op_arithmetic<ch_int, N, ch_bit<N>>>>>>>>;

  explicit ch_int(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int(const U& other, CH_SLOC) : base(other, sloc) {}

  ch_int(const ch_scbit<N>& other, CH_SLOC) : base(other, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_int(const U& other, CH_SLOC) : base(other, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  explicit ch_int(const ch_int<M>& other, CH_SLOC) : base(other.template pad<N>(sloc), sloc) {}

  explicit ch_int(const ch_bit<N>& other, CH_SLOC) : base(other, sloc) {}

  ch_int(const ch_int& other, CH_SLOC) : base(other, sloc) {}

  ch_int(ch_int&& other) : base(std::move(other)) {}

  ch_int& operator=(const ch_int& other) {
    base::operator=(other);
    return *this;
  }

  ch_int& operator=(ch_int&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_LOGIC_INTERFACE(ch_int)
};

}}
