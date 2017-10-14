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
  using value_type = ch_real;
  using const_type = const_real;

  const_real() {}

  const_real(const const_real& rhs) : base(rhs) {}

  const_real(const_real&& rhs) : base(rhs) {}

  const_real(const ch_bitbase<32>& rhs) : base(rhs) {}

  explicit const_real(float rhs) : base(bitcast<uint32_t, float>(rhs)) {}
};

class ch_real : public const_real {
public:
  using base = const_real;
  using value_type = ch_real;
  using const_type = const_real;

  ch_real() {}

  ch_real(const ch_real& rhs) : base(rhs) {}

  ch_real(const const_real& rhs) : base(rhs) {}

  ch_real(ch_real&& rhs) : base(rhs) {}

  ch_real(const ch_bitbase<32>& rhs) : base(rhs) {}

  explicit ch_real(float rhs) : base(rhs) {}

  ch_real& operator=(const ch_real& rhs) {
    base::assign(rhs);
    return *this;
  }

  ch_real& operator=(ch_real&& rhs) {
    node_.move(rhs.node_, bitsize);
    return *this;
  }

  ch_real& operator=(const ch_bitbase<32>& rhs) {
    base::assign(rhs);
    return *this;
  }

  ch_real& operator=(float rhs) {
    base::assign(ch_real(rhs));
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
