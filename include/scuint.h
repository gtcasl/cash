#pragma once

#include "scbit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_scuint : public system_op_relational<ch_scuint, N,
                           system_op_bitwise<ch_scuint, N,
                             system_op_shift<ch_scuint, N,
                               system_op_cast<ch_scuint, N,
                                 system_op_arithmetic<ch_scuint, N,
                                   system_op_slice<ch_scuint, N, ch_scbit<N>>>>>>> {
public:
  using traits = system_traits<N, false, ch_scuint, ch_uint<N>>;
  using base = system_op_relational<ch_scuint, N,
                 system_op_bitwise<ch_scuint, N,
                   system_op_shift<ch_scuint, N,
                     system_op_cast<ch_scuint, N,
                       system_op_arithmetic<ch_scuint, N,
                         system_op_slice<ch_scuint, N, ch_scbit<N>>>>>>>;

  ch_scuint(const system_buffer_ptr& buffer = make_system_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scuint(const U& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scuint(U&& other) : base(std::forward<U>(other)) {}

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_scuint(const U& other) : base(other) {}

  ch_scuint(const ch_scuint& other) : base(other) {}

  ch_scuint(ch_scuint&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scuint& operator=(const U& other) {
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_scuint& operator=(const U& other) {
    base::operator=(other);
    return *this;
  }

  ch_scuint& operator=(const ch_scuint& other) {
    base::operator=(other);
    return *this;
  }

  ch_scuint& operator=(ch_scuint&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SYSTEM_INTERFACE(ch_scuint)
};

}
}
