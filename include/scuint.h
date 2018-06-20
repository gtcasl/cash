#pragma once

#include "scint.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_scuint : public ch_scalar_integer<ch_scuint<N>> {
public:
  using traits = scalar_traits<N, false, ch_scuint, ch_uint<N>>;
  using base = ch_scalar_integer<ch_scuint>;

  ch_scuint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scuint(const U& rhs) : base(rhs) {}

  ch_scuint(const ch_scbit<N>& rhs) : base(rhs) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scuint(const ch_scuint<M>& rhs) : base(rhs.template pad<N>()) {}

  template <typename T>
  explicit ch_scuint(const ch_scalar_base<T>& rhs) : base(rhs) {}

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
};

}
}
