#pragma once

#include "bit.h"
#include "arithm.h"

namespace ch {
namespace internal {

class ch_real;
class const_real;

class const_real : public const_bit<32> {
public:
  using base = const_bit<32>;
  using traits = logic_traits<const_real, const_real, ch_real, ch_scalar<32>>;

  const_real() {}

  const_real(const const_real& rhs) : base(rhs) {}

  const_real(const_real&& rhs) : base(rhs) {}

  explicit const_real(const bit_buffer& buffer) : base(buffer) {}

  explicit const_real(float rhs) : base(bitcast<uint32_t, float>(rhs)) {}
};

class ch_real : public const_real {
public:
  using base = const_real;
  using traits = logic_traits<ch_real, const_real, ch_real, ch_scalar<32>>;

  ch_real() {}

  ch_real(const ch_real& rhs) : base(rhs) {}

  ch_real(const const_real& rhs) : base(rhs) {}

  ch_real(ch_real&& rhs) : base(rhs) {}

  explicit ch_real(const bit_buffer& buffer) : base(buffer) {}

  explicit ch_real(float rhs) : base(rhs) {}

  ch_real& operator=(const ch_real& rhs) {
    buffer_.copy(rhs.buffer_);
    return *this;
  }

  ch_real& operator=(ch_real&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

  ch_real& operator=(float rhs) {
    buffer_.set_data(bitvector(32, bitcast<uint32_t, float>(rhs)));
    return *this;
  }
};

inline const auto operator+(const const_real& lhs, const const_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fadd, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator-(const const_real& lhs, const const_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fsub, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator*(const const_real& lhs, const const_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fmult, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator/(const const_real& lhs, const const_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fdiv, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator+(const ch_real& lhs, const ch_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fadd, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator-(const ch_real& lhs, const ch_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fsub, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator*(const ch_real& lhs, const ch_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fmult, get_lnode(lhs), get_lnode(rhs)));
}

inline const auto operator/(const ch_real& lhs, const ch_real& rhs) {
  return make_type<ch_real>(createAluNode(alu_fdiv, get_lnode(lhs), get_lnode(rhs)));
}

}
}
