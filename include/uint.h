#pragma once

#include "int.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_uint : public ch_logic_integer<ch_uint<N>> {
public:
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = ch_logic_integer<ch_uint>;

  ch_uint(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_uint(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U>
  ch_uint(const ch_scalar_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_uint(const ch_uint<M>& rhs, CH_SLOC) : base(rhs.template pad<N>(), sloc) {}

  template <typename U>
  explicit ch_uint(const ch_logic_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_uint(const ch_uint& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_uint(ch_uint&& rhs) : base(std::move(rhs)) {}

  ch_uint& operator=(const ch_uint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_uint& operator=(ch_uint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }
};

}}
