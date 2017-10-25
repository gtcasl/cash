#pragma once

#include "bit.h"
#include "arithm.h"

namespace ch {
namespace internal {

class ch_float32;
class const_float32;

class const_float32 : public const_bit<32> {
public:
  using traits = logic_traits<32, const_float32, const_float32, ch_float32, ch_scalar<32>>;
  using base = const_bit<32>;

  const_float32() {}

  const_float32(const const_float32& rhs) : base(rhs) {}

  const_float32(const_float32&& rhs) : base(std::move(rhs)) {}

  explicit const_float32(const bit_buffer& buffer) : base(buffer) {}

  explicit const_float32(const const_bit<32>& rhs) : base(rhs) {}

  explicit const_float32(const ch_scalar<32>& rhs) : base(rhs) {}

  explicit const_float32(float rhs) : base(bitcast<uint32_t, float>(rhs)) {}
};

class ch_float32 : public const_float32 {
public:  
  using traits = logic_traits<32, ch_float32, const_float32, ch_float32, ch_scalar<32>>;
  using base = const_float32;

  ch_float32() {}

  ch_float32(const ch_float32& rhs) : base(rhs) {}

  ch_float32(const const_float32& rhs) : base(rhs) {}

  ch_float32(ch_float32&& rhs) : base(std::move(rhs)) {}

  explicit ch_float32(const bit_buffer& buffer) : base(buffer) {}

  explicit ch_float32(const const_bit<32>& rhs) : base(rhs) {}

  explicit ch_float32(const ch_scalar<32>& rhs) : base(rhs) {}

  explicit ch_float32(float rhs) : base(rhs) {}

  ch_float32& operator=(const ch_float32& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_float32& operator=(ch_float32&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_float32& operator=(float rhs) {
    buffer_->set_data(bitvector(32, bitcast<uint32_t, float>(rhs)));
    return *this;
  }

  const auto operator+(const ch_float32& rhs) const {
    return make_type<ch_float32>(createAluNode(alu_fadd, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator-(const ch_float32& rhs) const {
    return make_type<ch_float32>(createAluNode(alu_fsub, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator*(const ch_float32& rhs) const {
    return make_type<ch_float32>(createAluNode(alu_fmult, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator/(const ch_float32& rhs) const {
    return make_type<ch_float32>(createAluNode(alu_fdiv, get_lnode(*this), get_lnode(rhs)));
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

}
}
