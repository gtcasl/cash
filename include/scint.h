#pragma once

#include "scbit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_scint : public scalar_op_equality<ch_scint, N,
                          scalar_op_logical<ch_scint, N,
                            scalar_op_bitwise<ch_scint, N,
                              scalar_op_shift<ch_scint, N,
                                scalar_op_padding<ch_scint, N,
                                  scalar_op_cast<ch_scint, N,
                                    scalar_op_relational<ch_scint, N,
                                      scalar_op_arithmetic<ch_scint, N, ch_scbit<N>>>>>>>>> {
public:
  using traits = scalar_traits<N, true, ch_scint, ch_int<N>>;
  using base = scalar_op_equality<ch_scint, N,
                scalar_op_logical<ch_scint, N,
                  scalar_op_bitwise<ch_scint, N,
                    scalar_op_shift<ch_scint, N,
                      scalar_op_padding<ch_scint, N,
                        scalar_op_cast<ch_scint, N,
                          scalar_op_relational<ch_scint, N,
                            scalar_op_arithmetic<ch_scint, N, ch_scbit<N>>>>>>>>>;
  using base::buffer_;

  explicit ch_scint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint(const U& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scint(const U& other) : base(other) {}

  explicit ch_scint(const ch_scbit<N>& other) : base(other) {}

  ch_scint(const ch_scint& other) : base(other) {}

  ch_scint(ch_scint&& other) : base(std::move(other)) {}

  ch_scint& operator=(const ch_scint& other) {
    base::operator=(other);
    return *this;
  }

  ch_scint& operator=(ch_scint&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SCALAR_INTERFACE(ch_scint)
};

}
}
