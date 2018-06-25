#pragma once

#include "bit.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_int : public logic_op_compare<ch_int<N>,
                        logic_op_logical<ch_int<N>,
                          logic_op_bitwise<ch_int<N>,
                            logic_op_shift<ch_int<N>,
                              logic_op_relational<ch_int<N>,
                                logic_op_arithmetic<ch_int<N>, ch_bit<N>>>>>>> {
public:
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = logic_op_compare<ch_int<N>,
                logic_op_logical<ch_int<N>,
                  logic_op_bitwise<ch_int<N>,
                    logic_op_shift<ch_int<N>,
                      logic_op_relational<ch_int<N>,
                        logic_op_arithmetic<ch_int<N>, ch_bit<N>>>>>>>;

  explicit ch_int(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_int(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_int(const ch_scbit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_int(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_int(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_int(const ch_int<M>& rhs, CH_SLOC) : base(rhs.template pad<N>(sloc), sloc) {}

  explicit ch_int(const ch_bit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_int(const ch_int& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_int(ch_int&& rhs) : base(std::move(rhs)) {}

  ch_int& operator=(const ch_int& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_int& operator=(ch_int&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  // padding operators

  template <typename R>
  R pad(CH_SLOC) const {
    static_assert(is_logic_type_v<R>, "invalid type");
    static_assert(width_v<R> >= N, "invalid size");
    if constexpr (width_v<R> > N) {
      return make_logic_op<op_zext, R>(*this, sloc);
    } else
    if constexpr (std::is_same_v<R, ch_int>) {
      return *this;
    } else {
      return R(*this, sloc);
    }
  }

  template <unsigned M>
  auto pad(CH_SLOC) const {
    return this->pad<ch_int<M>>(sloc);
  }

  CH_LOGIC_INTERFACE(ch_int)
};

}}
