#pragma once

#include "bit.h"
#include "arithm.h"

namespace ch {
namespace internal {

class ch_real;
class const_real;

class const_real : public const_bit<32> {
public:
  using traits = logic_traits<32, const_real, const_real, ch_real, ch_scalar<32>>;
  using base = const_bit<32>;

  const_real() {}

  const_real(const const_real& rhs) : base(rhs) {}

  const_real(const_real&& rhs) : base(std::move(rhs)) {}

  explicit const_real(const const_bit<32>& rhs) : base(rhs) {}

  explicit const_real(const ch_scalar<32>& rhs) : base(rhs) {}

  explicit const_real(const bit_buffer& buffer) : base(buffer) {}

  explicit const_real(float rhs) : base(bitcast<uint32_t, float>(rhs)) {}
};

class ch_real : public const_real {
public:  
  using traits = logic_traits<32, ch_real, const_real, ch_real, ch_scalar<32>>;
  using base = const_real;

  ch_real() {}

  ch_real(const ch_real& rhs) : base(rhs) {}

  ch_real(const const_real& rhs) : base(rhs) {}

  ch_real(ch_real&& rhs) : base(std::move(rhs)) {}

  explicit ch_real(const const_bit<32>& rhs) : base(rhs) {}

  explicit ch_real(const ch_scalar<32>& rhs) : base(rhs) {}

  explicit ch_real(const bit_buffer& buffer) : base(buffer) {}

  explicit ch_real(float rhs) : base(rhs) {}

  ch_real& operator=(const ch_real& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_real& operator=(ch_real&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_real& operator=(float rhs) {
    buffer_->set_data(bitvector(32, bitcast<uint32_t, float>(rhs)));
    return *this;
  }

  const auto operator+(const ch_real& rhs) const {
    return make_type<ch_real>(createAluNode(alu_fadd, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator-(const ch_real& rhs) const {
    return make_type<ch_real>(createAluNode(alu_fsub, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator*(const ch_real& rhs) const {
    return make_type<ch_real>(createAluNode(alu_fmult, get_lnode(*this), get_lnode(rhs)));
  }

  const auto operator/(const ch_real& rhs) const {
    return make_type<ch_real>(createAluNode(alu_fdiv, get_lnode(*this), get_lnode(rhs)));
  }

protected:

  CH_FRIEND_OP_EQ(, const ch_real&, float)
  CH_FRIEND_OP_NE(, const ch_real&, float)
  CH_FRIEND_OP_LT(, const ch_real&, float)
  CH_FRIEND_OP_LE(, const ch_real&, float)
  CH_FRIEND_OP_GT(, const ch_real&, float)
  CH_FRIEND_OP_GE(, const ch_real&, float)

  CH_FRIEND_OP_ADD(, const ch_real&, float)
  CH_FRIEND_OP_SUB(, const ch_real&, float)
  CH_FRIEND_OP_MULT(, const ch_real&, float)
  CH_FRIEND_OP_DIV(, const ch_real&, float)
};

}
}
