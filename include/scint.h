#pragma once

#include "scbit.h"

namespace ch {
namespace internal {

template <unsigned N = 32>
class ch_scint : public ch_scbit<N> {
public:
  using traits = system_traits<N, true, ch_scint, ch_int<N>>;
  using base = ch_scbit<N>;
  using base::buffer_;

  ch_scint(const system_buffer_ptr& buffer = make_system_buffer(N, idname<ch_scint>()))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint(const U& other) : base(other) {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_scint(U&& other) : base(std::forward<U>(other)) {}

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_scint(const U& other) : base(other) {}

  ch_scint(const ch_scint& other) : base(other) {}

  ch_scint(ch_scint&& other) : base(std::move(other)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scint& operator=(const U& other) {
    base::operator=(other);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_scint& operator=(const U& other) {
    base::operator=(other);
    return *this;
  }

  ch_scint& operator=(const ch_scint& other) {
    base::operator=(other);
    return *this;
  }

  ch_scint& operator=(ch_scint&& other) {
    base::operator=(std::move(other));
    return *this;
  }

  CH_SYSTEM_INTERFACE(ch_scint)
  CH_SYSTEM_OP_RELATIONAL(ch_scint)
  CH_SYSTEM_OP_BITWISE(ch_scint)
  CH_SYSTEM_OP_SHIFT(ch_scint)
  CH_SYSTEM_OP_ARITHMETIC(ch_scint)
  CH_SYSTEM_OP_SLICE(ch_scint)
  CH_SYSTEM_OP_CAST(ch_scint)
};

}
}
