#pragma once

#include "int.h"
#include "arithm.h"

namespace ch {
namespace internal {

class ch_float32 : public ch_int<32> {
public:  
  using traits = logic_traits<32, ch_float32, ch_scalar<32>>;
  using base = ch_int<32>;

  ch_float32(const logic_buffer& buffer = logic_buffer(32, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_float32(const ch_float32& rhs,
             const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const ch_logic<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(const ch_scalar<32>& rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(float rhs,
                      const source_location& sloc = CH_SRC_LOCATION)
    : base(bitcast<uint32_t, float>(rhs), sloc)
  {}

  ch_float32& operator=(const ch_float32& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  ch_float32& operator=(float rhs) {
    base::operator=(bitcast<uint32_t, float>(rhs));
    return *this;
  }

  auto operator+(const ch_float32& rhs) const {
    auto ret = createAluNode(alu_fadd, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator-(const ch_float32& rhs) const {
    auto ret = createAluNode(alu_fsub, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator*(const ch_float32& rhs) const {
    auto ret = createAluNode(alu_fmult, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

  auto operator/(const ch_float32& rhs) const {
    auto ret = createAluNode(alu_fdiv, get_lnode(*this), get_lnode(rhs));
    return make_type<ch_float32>(ret);
  }

protected:

  CH_FRIEND_OP_EQ((), const ch_float32&, float)
  CH_FRIEND_OP_NE((), const ch_float32&, float)
  CH_FRIEND_OP_LT((), const ch_float32&, float)
  CH_FRIEND_OP_LE((), const ch_float32&, float)
  CH_FRIEND_OP_GT((), const ch_float32&, float)
  CH_FRIEND_OP_GE((), const ch_float32&, float)

  CH_FRIEND_OP_ADD((), const ch_float32&, float)
  CH_FRIEND_OP_SUB((), const ch_float32&, float)
  CH_FRIEND_OP_MULT((), const ch_float32&, float)
  CH_FRIEND_OP_DIV((), const ch_float32&, float)
};

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(alu_fadd, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(alu_fsub, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fmult(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(alu_fmult, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_logic<1>& enable = ch_logic<1>(true)) {
  auto ret = createAluNode(alu_fdiv, Delay, get_lnode(enable), get_lnode(lhs), get_lnode(rhs));
  return make_type<ch_float32>(ret);
}

}
}
