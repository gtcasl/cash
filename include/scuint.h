#pragma once

#include "scint.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_scuint : public scalar_op_compare<ch_scuint, N,
                          scalar_op_logical<ch_scuint, N,
                            scalar_op_bitwise<ch_scuint, N,
                              scalar_op_shift<ch_scuint, N,
                                scalar_op_padding<ch_scuint, N,
                                  scalar_op_cast<ch_scuint, N,
                                    scalar_op_relational<ch_scuint, N,
                                      scalar_op_arithmetic<ch_scuint, N, ch_scbit<N>>>>>>>>> {
public:
  using traits = scalar_traits<N, false, ch_scuint, ch_uint<N>>;
  using base = scalar_op_compare<ch_scuint, N,
                scalar_op_logical<ch_scuint, N,
                  scalar_op_bitwise<ch_scuint, N,
                    scalar_op_shift<ch_scuint, N,
                      scalar_op_padding<ch_scuint, N,
                        scalar_op_cast<ch_scuint, N,
                          scalar_op_relational<ch_scuint, N,
                            scalar_op_arithmetic<ch_scuint, N, ch_scbit<N>>>>>>>>>;

  explicit ch_scuint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scuint(const U& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scuint(const U& other) : base(other) {}

  explicit ch_scuint(const ch_scbit<N>& other) : base(other) {}

  ch_scuint(const ch_scuint& other) : base(other) {}

  ch_scuint(ch_scuint&& other) : base(std::move(other)) {}

  ch_scuint& operator=(const ch_scuint& other) {
    base::operator=(other);
    return *this;
  }

  ch_scuint& operator=(ch_scuint&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SCALAR_INTERFACE(ch_scuint)
};

}
}
