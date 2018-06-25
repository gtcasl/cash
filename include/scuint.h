#pragma once

#include "scint.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_scuint : public scalar_op_compare<ch_scuint<N>,
                          scalar_op_logical<ch_scuint<N>,
                            scalar_op_bitwise<ch_scuint<N>,
                              scalar_op_shift<ch_scuint<N>,
                                scalar_cast_op<ch_scuint<N>,
                                  scalar_op_relational<ch_scuint<N>,
                                    scalar_op_arithmetic<ch_scuint<N>, ch_scbit<N>>>>>>>> {
public:
  using traits = scalar_traits<N, false, ch_scuint, ch_uint<N>>;
  using base = scalar_op_compare<ch_scuint<N>,
                scalar_op_logical<ch_scuint<N>,
                  scalar_op_bitwise<ch_scuint<N>,
                    scalar_op_shift<ch_scuint<N>,
                      scalar_cast_op<ch_scuint<N>,
                        scalar_op_relational<ch_scuint<N>,
                          scalar_op_arithmetic<ch_scuint<N>, ch_scbit<N>>>>>>>>;

  explicit ch_scuint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scuint(const U& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scuint(const U& rhs) : base(rhs) {}

  explicit ch_scuint(const ch_scbit<N>& rhs) : base(rhs) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scuint(const ch_scuint<M>& rhs) : base(rhs.template pad<N>()) {}

  ch_scuint(const ch_scuint& rhs) : base(rhs) {}

  ch_scuint(ch_scuint&& rhs) : base(std::move(rhs)) {}

  ch_scuint& operator=(const ch_scuint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scuint& operator=(ch_scuint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  // padding operators

  template <typename R>
  R pad() const {
    static_assert(is_scalar_type_v<R>, "invalid type");
    static_assert(width_v<R> >= N, "invalid size");
    if constexpr (width_v<R> > N) {
      return make_scalar_op<R>(*this, ZExt);
    } else
    if constexpr (std::is_same_v<R, ch_scuint>) {
      return *this;
    } else {
      return R(*this);
    }
  }

  template <unsigned M>
  auto pad() const {
    return this->pad<ch_scuint<M>>();
  }

  CH_SCALAR_INTERFACE(ch_scuint)
};

}
}
