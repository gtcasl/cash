#pragma once

#include "scbit.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_scint : public scalar_op_compare<ch_scint<N>,
                          scalar_op_logical<ch_scint<N>,
                            scalar_op_bitwise<ch_scint<N>,
                              scalar_op_shift<ch_scint<N>,
                                scalar_cast_op<ch_scint<N>,
                                  scalar_op_relational<ch_scint<N>,
                                    scalar_op_arithmetic<ch_scint<N>, ch_scbit<N>>>>>>>> {
public:
  using traits = scalar_traits<N, true, ch_scint, ch_int<N>>;
  using base = scalar_op_compare<ch_scint<N>,
                scalar_op_logical<ch_scint<N>,
                  scalar_op_bitwise<ch_scint<N>,
                    scalar_op_shift<ch_scint<N>,
                      scalar_cast_op<ch_scint<N>,
                        scalar_op_relational<ch_scint<N>,
                          scalar_op_arithmetic<ch_scint<N>, ch_scbit<N>>>>>>>>;
  using base::buffer_;

  explicit ch_scint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint(const U& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scint(const U& rhs) : base(rhs) {}

  explicit ch_scint(const ch_scbit<N>& rhs) : base(rhs) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scint(const ch_scint<M>& rhs) : base(rhs.template pad<N>()) {}

  ch_scint(const ch_scint& rhs) : base(rhs) {}

  ch_scint(ch_scint&& rhs) : base(std::move(rhs)) {}

  ch_scint& operator=(const ch_scint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scint& operator=(ch_scint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  // padding operators

  template <typename R>
  R pad() const {
    static_assert(is_scalar_type_v<R>, "invalid type");
    static_assert(width_v<R> >= N, "invalid size");
    if constexpr (width_v<R> > N) {
      return make_scalar_op<R>(*this, SExt);
    } else
    if constexpr (std::is_same_v<R, ch_scint>) {
      return *this;
    } else {
      return R(*this);
    }
  }

  template <unsigned M>
  auto pad() const {
    return this->pad<ch_scint<M>>();
  }

  CH_SCALAR_INTERFACE(ch_scint)
};

}
}
