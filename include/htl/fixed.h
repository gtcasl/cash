#pragma once

#include <cash.h>

namespace ch {
namespace htl {

using namespace core;

#define CH_INT_OPS(i, x) \
  CH_OP1_LT((), const ch_int&, x) \
  CH_OP1_LE((), const ch_int&, x) \
  CH_OP1_GT((), const ch_int&, x) \
  CH_OP1_GE((), const ch_int&, x) \
  CH_OP1_AND((), const ch_int&, x) \
  CH_OP1_OR((), const ch_int&, x) \
  CH_OP1_XOR((), const ch_int&, x) \
  CH_OP1_SLL((), const ch_int&, x) \
  CH_OP1_SRL((), const ch_int&, x) \
  CH_OP1_ADD((), const ch_int&, x) \
  CH_OP1_SUB((), const ch_int&, x) \
  CH_OP1_MULT((), const ch_int&, x) \
  CH_OP1_DIV((), const ch_int&, x) \
  CH_OP1_MOD((), const ch_int&, x)

#define CH_INT_OP_TYPES \
  ch_uint<N>, ch_int<N>, ch_scalar<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

template <unsigned N, unsigned F>
class ch_fixed : public ch_int<N> {
public:
  using traits = logic_traits<N, true, ch_fixed, ch_scint<N>>;
  using base = ch_int<N>;

  ch_fixed(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_fixed(const ch_fixed& rhs,
           const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_fixed(ch_fixed&& rhs) : base(std::move(rhs)) {}

  explicit ch_fixed(const ch_logic<N>& rhs,
                    const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_fixed(const ch_scalar<N>& rhs,
                    const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_fixed& operator=(const ch_fixed& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_fixed& operator=(ch_fixed&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  ch_fixed& operator=(float rhs) {
    base::operator=(bitcast<uint32_t, float>(rhs));
    return *this;
  }

  ch_fixed& operator=(float rhs) {
    base::operator=(rhs);
    return *this;
  }

  auto operator*(const ch_fixed& rhs) const {   
    return ch_fixed((*this * rhs) >> F);
  }

  auto operator/(const ch_fixed& rhs) const {
    return ch_fixed((*this << F) / rhs);
  }

private:

};

}
}
