#pragma once

#include "scbit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_scint : public system_op_relational<ch_scint, N,
                          system_op_bitwise<ch_scint, N,
                            system_op_shift<ch_scint, N,
                              system_op_cast<ch_scint, N,
                                system_op_arithmetic<ch_scint, N,
                                  system_op_slice<ch_scint, N, ch_scbit<N>>>>>>> {
public:
  using traits = system_traits<N, true, ch_scint, ch_int<N>>;
  using base = system_op_relational<ch_scint, N,
                 system_op_bitwise<ch_scint, N,
                   system_op_shift<ch_scint, N,
                     system_op_cast<ch_scint, N,
                       system_op_arithmetic<ch_scint, N,
                         system_op_slice<ch_scint, N, ch_scbit<N>>>>>>>;
  using base::buffer_;

  ch_scint(const system_buffer_ptr& buffer = make_system_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint(const U& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scint(const U& other) : base(other) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scint(const ch_scint<M>& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
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

  CH_SYSTEM_INTERFACE(ch_scint)
};

}
}
