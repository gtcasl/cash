#pragma once

#include "bit.h"
#include "arithm.h"
#include "reg.h"

namespace ch {
namespace internal {

class ch_float32;
class const_float32;

class const_float32 : public const_bit<32> {
public:
  using base = const_bit<32>;
  using traits = logic_traits<32, const_float32, const_float32, ch_float32, ch_scalar<32>>;

  const_float32(const bit_buffer& buffer = bit_buffer(32, CH_SOURCE_LOCATION))
    : base(buffer)
  {}

  const_float32(const const_float32& rhs,
                const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  const_float32(const_float32&& rhs) : base(std::move(rhs)) {}

  explicit const_float32(const const_bit<32>& rhs,
                         const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit const_float32(const ch_scalar<32>& rhs,
                         const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit const_float32(float rhs,
                         const source_location& sloc = CH_SOURCE_LOCATION)
    : base(bitcast<uint32_t, float>(rhs), sloc)
  {}
};

class ch_float32 : public const_float32 {
public:  
  using base = const_float32;
  using traits = logic_traits<32, ch_float32, const_float32, ch_float32, ch_scalar<32>>;

  ch_float32(const bit_buffer& buffer = bit_buffer(32, CH_SOURCE_LOCATION))
    : base(buffer)
  {}

  ch_float32(const ch_float32& rhs,
             const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32(const const_float32& rhs,
             const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const const_bit<32>& rhs,
                      const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(const ch_scalar<32>& rhs,
                      const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  explicit ch_float32(float rhs,
                      const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_float32& operator=(const ch_float32& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_float32& operator=(float rhs) {
    buffer_->write(bitvector(32, bitcast<uint32_t, float>(rhs)));
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

  CH_FRIEND_OP_EQ(, const ch_float32&, float)
  CH_FRIEND_OP_NE(, const ch_float32&, float)
  CH_FRIEND_OP_LT(, const ch_float32&, float)
  CH_FRIEND_OP_LE(, const ch_float32&, float)
  CH_FRIEND_OP_GT(, const ch_float32&, float)
  CH_FRIEND_OP_GE(, const ch_float32&, float)

  CH_FRIEND_OP_ADD(, const ch_float32&, float)
  CH_FRIEND_OP_SUB(, const ch_float32&, float)
  CH_FRIEND_OP_MULT(, const ch_float32&, float)
  CH_FRIEND_OP_DIV(, const ch_float32&, float)
};

template <unsigned Delay>
auto ch_fadd(const ch_float32& lhs, const ch_float32& rhs, const ch_bit<1>& enable = ch_bit<1>(true)) {
  auto ret = createAluNode(alu_fadd, get_lnode(lhs), get_lnode(rhs), Delay, get_lnode(enable));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fsub(const ch_float32& lhs, const ch_float32& rhs, const ch_bit<1>& enable = ch_bit<1>(true)) {
  auto ret = createAluNode(alu_fsub, get_lnode(lhs), get_lnode(rhs), Delay, get_lnode(enable));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fmult(const ch_float32& lhs, const ch_float32& rhs, const ch_bit<1>& enable = ch_bit<1>(true)) {
  auto ret = createAluNode(alu_fmult, get_lnode(lhs), get_lnode(rhs), Delay, get_lnode(enable));
  return make_type<ch_float32>(ret);
}

template <unsigned Delay>
auto ch_fdiv(const ch_float32& lhs, const ch_float32& rhs, const ch_bit<1>& enable = ch_bit<1>(true)) {
  auto ret = createAluNode(alu_fdiv, get_lnode(lhs), get_lnode(rhs), Delay, get_lnode(enable));
  return make_type<ch_float32>(ret);
}

}
}
