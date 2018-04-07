#pragma once

#include "logic.h"

namespace ch {
namespace internal {

#define CH_UINT_FRIEND_OPS(i, x) \
  CH_FRIEND_OP_LT((), const ch_uint&, x) \
  CH_FRIEND_OP_LE((), const ch_uint&, x) \
  CH_FRIEND_OP_GT((), const ch_uint&, x) \
  CH_FRIEND_OP_GE((), const ch_uint&, x) \
  CH_FRIEND_OP_ADD((), const ch_uint&, x) \
  CH_FRIEND_OP_SUB((), const ch_uint&, x) \
  CH_FRIEND_OP_MULT((), const ch_uint&, x) \
  CH_FRIEND_OP_DIV((), const ch_uint&, x) \
  CH_FRIEND_OP_MOD((), const ch_uint&, x)

#define CH_UINT_OP_TYPES \
  ch_scalar<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

template <unsigned N>
class ch_uint : public ch_logic<N> {
public:
  using traits = logic_traits<N, ch_uint, ch_scalar<N>>;
  using base = ch_logic<N>;
  using base::buffer_;

  ch_uint(const logic_buffer& buffer = logic_buffer(N, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_uint(const ch_uint& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_uint(ch_uint&& rhs) : base(std::move(rhs)) {}

  ch_uint(const ch_scalar<N>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <unsigned M, CH_REQUIRE_0(M < N)>
  explicit ch_uint(const ch_scalar<M>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_uint(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> == N)>
  explicit ch_uint(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit ch_uint(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_uint& operator=(const ch_uint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_uint& operator=(ch_uint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <unsigned M, CH_REQUIRE_0(M < N)>
  ch_uint& operator=(const ch_scalar<M>& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(N == width_v<U>)>
  ch_uint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(N == width_v<U>)>
  ch_uint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_uint& operator=(U rhs) {
    base::operator=(rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_uint& rhs) const {
    return OpBinary<alu_lt, ch_logic<1>>(*this, rhs);
  }

  auto operator<=(const ch_uint& rhs) const {
    return OpBinary<alu_le, ch_logic<1>>(*this, rhs);
  }

  auto operator>(const ch_uint& rhs) const {
    return OpBinary<alu_gt, ch_logic<1>>(*this, rhs);
  }

  auto operator>=(const ch_uint& rhs) const {
    return OpBinary<alu_ge, ch_logic<1>>(*this, rhs);
  }

  // bitwise operators

  auto operator~() const {
    return OpUnary<alu_inv, ch_uint>(*this);
  }

  auto operator&(const ch_logic<N>& rhs) const {
    return OpBinary<alu_and, ch_uint>(*this, rhs);
  }

  auto operator|(const ch_logic<N>& rhs) const {
    return OpBinary<alu_or, ch_uint>(*this, rhs);
  }

  auto operator^(const ch_logic<N>& rhs) const {
    return OpBinary<alu_xor, ch_uint>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_logic<M>& rhs) const {
    return OpBinary<alu_sll, ch_uint>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_logic<M>& rhs) const {
    return OpBinary<alu_sra, ch_uint>(*this, rhs);
  }

  // arithmetic operators

  auto operator-() const {
    return OpUnary<alu_neg, ch_uint>(*this);
  }

  auto operator+(const ch_uint& rhs) const {
    return OpBinary<alu_add, ch_uint>(*this, rhs);
  }

  auto operator-(const ch_uint& rhs) const {
    return OpBinary<alu_sub, ch_uint>(*this, rhs);
  }

  auto operator*(const ch_uint& rhs) const {
    return OpBinary<alu_mult, ch_uint>(*this, rhs);
  }

  auto operator/(const ch_uint& rhs) const {
    return OpBinary<alu_div, ch_uint>(*this, rhs);
  }

  auto operator%(const ch_uint& rhs) const {
    return OpBinary<alu_mod, ch_uint>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_uint)

protected:

  CH_FOR_EACH(CH_UINT_FRIEND_OPS, CH_SEP_SPACE, CH_UINT_OP_TYPES)

  template <unsigned M>
  inline friend ch_uint operator>>(const ch_uint& lhs, const ch_scalar<M>& rhs) {
    return lhs >> ch_uint<M>(rhs);
  }
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <unsigned N>
inline auto ch_lt(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs < rhs);
}

template <unsigned N>
inline auto ch_le(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs <= rhs);
}

template <unsigned N>
inline auto ch_gt(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs > rhs);
}

template <unsigned N>
inline auto ch_ge(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs >= rhs);
}

// bitwise operators

template <unsigned N>
auto ch_inv(const ch_uint<N>& in) {
  return ~in;
}

template <unsigned N>
inline auto ch_and(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs & rhs);
}

template <unsigned N>
inline auto ch_or(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs | rhs);
}

template <unsigned N>
inline auto ch_xor(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs ^ rhs);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const ch_uint<N>& lhs, const ch_uint<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_uint<N>& lhs, const ch_uint<M>& rhs) {
  return (lhs >> rhs);
}

// arithmetic operators

template <unsigned N>
auto ch_neg(const ch_uint<N>& in) {
  return -in;
}

template <unsigned N>
inline auto ch_add(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs + rhs);
}

template <unsigned N>
inline auto ch_sub(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs - rhs);
}

template <unsigned N>
inline auto ch_mult(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs * rhs);
}

template <unsigned N>
inline auto ch_div(const ch_uint<N>& lhs, const ch_uint<N>& rhs) {
  return (lhs / rhs);
}

// padding

template <typename R, unsigned N>
auto ch_pad(const ch_uint<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> >= N, "invalid extend size");
  if constexpr(width_v<R> > N) {
    auto padding = ch_logic<(width_v<R> - N)>(0x0, sloc);
    return ch_cat(padding, obj, sloc).template as<R>();
  } else {
    return R(obj, sloc);
  }
}

template <unsigned N, unsigned M>
auto ch_pad(const ch_uint<M>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_pad<ch_uint<N>>(obj, sloc);
}

// global operators

CH_GLOBAL_OP_AND_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_OR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_XOR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_ADD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_SUB_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_MULT_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_DIV_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_MOD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_uint<M>&)

#define CH_UINT_GLOBAL_OPS(i, x) \
  CH_GLOBAL_OP_EQ((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_NE((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_LT((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_LE((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_GT((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_GE((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_AND((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_OR((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_XOR((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_NAND((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_NOR((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_XNOR((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_ADD((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_SUB((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_MULT((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_DIV((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_MOD((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_SLL((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_SRL((template <unsigned N>), const ch_uint<N>&, x) \
  CH_GLOBAL_OP_SRA((template <unsigned N>), const ch_uint<N>&, x)

CH_FOR_EACH(CH_UINT_GLOBAL_OPS, CH_SEP_SPACE, CH_UINT_OP_TYPES)

}}
