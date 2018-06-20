#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;

// |1|<- N-Q-1 bits ->|<--- Q bits -->|
// |S|IIIIIIIIIIIIIIII|FFFFFFFFFFFFFFF|

template <unsigned N, unsigned Q>
class ch_fixed : public ch_bit<N> {
public:
  using traits = logic_traits<N, true, ch_fixed, ch_scint<N>>;
  using base = ch_bit<N>;

  ch_fixed(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  ch_fixed(const ch_fixed& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_fixed(ch_fixed&& rhs) : base(std::move(rhs)) {}

  explicit ch_fixed(const ch_bit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  explicit ch_fixed(const ch_scbit<N>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_fixed& operator=(const ch_fixed& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  // compare operators

  auto operator<(const ch_fixed& rhs) const {
    return ch_int<32>(*this) < ch_int<32>(rhs);
  }

  auto operator<=(const ch_fixed& rhs) const {
    return ch_int<32>(*this) <= ch_int<32>(rhs);
  }

  auto operator>(const ch_fixed& rhs) const {
    return ch_int<32>(*this) > ch_int<32>(rhs);
  }

  auto operator>=(const ch_fixed& rhs) const {
    return ch_int<32>(*this) >= ch_int<32>(rhs);
  }

protected:

  CH_SCALAR_OP1_IMPL((), <, const ch_fixed&, float)
  CH_SCALAR_OP1_IMPL((), <=, const ch_fixed&, float)
  CH_SCALAR_OP1_IMPL((), >, const ch_fixed&, float)
  CH_SCALAR_OP1_IMPL((), >=, const ch_fixed&, float)
};

}
}
