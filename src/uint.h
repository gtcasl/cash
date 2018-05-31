#pragma once

#include "logic.h"

namespace ch {
namespace internal {

#define CH_LOGIC_UINT_FRIEND_OP1(i, x) \
  CH_FRIEND_OP1((), <, const ch_uint&, x) \
  CH_FRIEND_OP1((), <=, const ch_uint&, x) \
  CH_FRIEND_OP1((), >, const ch_uint&, x) \
  CH_FRIEND_OP1((), >=, const ch_uint&, x)

#define CH_LOGIC_UINT_GLOBAL_FUNC1(i, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_lt, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_le, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_gt, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_ge, const ch_uint<N>&, x)

#define CH_LOGIC_UINT_OP1_TYPES \
  const ch_scalar<N>&, uint8_t, uint16_t, uint32_t, uint64_t

#define CH_LOGIC_UINT_FRIEND_OP2(i, x) \
  CH_FRIEND_OP1((), &, const ch_uint&, x) \
  CH_FRIEND_OP1((), |, const ch_uint&, x) \
  CH_FRIEND_OP1((), ^, const ch_uint&, x) \
  CH_FRIEND_OP1((), +, const ch_uint&, x) \
  CH_FRIEND_OP1((), -, const ch_uint&, x) \
  CH_FRIEND_OP1((), *, const ch_uint&, x) \
  CH_FRIEND_OP1((), /, const ch_uint&, x) \
  CH_FRIEND_OP1((), %, const ch_uint&, x)

#define CH_LOGIC_UINT_GLOBAL_FUNC2(i, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_and, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_or, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_xor, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_add, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_sub, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_mult, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_div, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_mod, const ch_uint<N>&, x)

#define CH_LOGIC_UINT_OP2_TYPES \
  const ch_logic<N>&, const ch_scalar<N>&, \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_UINT_FRIEND_OP3(i, x) \
  CH_FRIEND_OP3((), <<, const ch_uint&, x, const ch_logic<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3((), >>, const ch_uint&, x, const ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_UINT_GLOBAL_FUNC3(i, x) \
  CH_GLOBAL_FUNC3((template <unsigned N>), ch_sll, const ch_uint<N>&, x, const ch_logic<CH_WIDTH_OF(x)>&) \
  CH_GLOBAL_FUNC3((template <unsigned N>), ch_srl, const ch_uint<N>&, x, const ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_UINT_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_UINT_GLOBAL_OP4(i, x) \
  CH_GLOBAL_OP4((template <unsigned N>), <<, const ch_uint<CH_WIDTH_OF(x)>&, x, const ch_logic<N>&) \
  CH_GLOBAL_OP4((template <unsigned N>), >>, const ch_uint<CH_WIDTH_OF(x)>&, x, const ch_logic<N>&)

#define CH_LOGIC_UINT_GLOBAL_FUNC4(i, x) \
  CH_GLOBAL_FUNC4((template <unsigned M>), ch_sll, const ch_uint<CH_WIDTH_OF(x)>&, x, const ch_logic<M>&) \
  CH_GLOBAL_FUNC4((template <unsigned M>), ch_srl, const ch_uint<CH_WIDTH_OF(x)>&, x, const ch_logic<M>&)

#define CH_LOGIC_UINT_OP4_TYPES \
  uint8_t, uint16_t, uint32_t, uint64_t

#define CH_LOGIC_UINT_FRIEND_OP5(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <=, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >=, const ch_uint&, x)

#define CH_LOGIC_UINT_GLOBAL_FUNC5(i, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_lt, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_le, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_gt, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_ge, const ch_uint<N>&, x)

#define CH_LOGIC_UINT_OP5_TYPES \
  const ch_uint<M>&, const ch_logic<M>&, const ch_scalar<M>&

#define CH_LOGIC_UINT_FRIEND_OP6(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), +, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), -, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), *, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), /, const ch_uint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), %, const ch_uint&, x)

#define CH_LOGIC_UINT_GLOBAL_FUNC6(i, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_and, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_or, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xor, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_add, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_sub, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_mult, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_div, const ch_uint<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_mod, const ch_uint<N>&, x)

#define CH_LOGIC_UINT_OP6_TYPES \
  const ch_uint<M>&, const ch_logic<M>&, const ch_scalar<M>&

#define CH_LOGIC_UINT_FRIEND_OP7(i, x) \
  CH_FRIEND_OP3((template <unsigned M>), <<, const ch_uint&, x, const ch_logic<M>&) \
  CH_FRIEND_OP3((template <unsigned M>), >>, const ch_uint&, x, const ch_logic<M>&)

#define CH_LOGIC_UINT_GLOBAL_FUNC7(i, x) \
  CH_GLOBAL_FUNC3((template <unsigned N, unsigned M>), ch_sll, const ch_uint<N>&, x, const ch_logic<M>&) \
  CH_GLOBAL_FUNC3((template <unsigned N, unsigned M>), ch_srl, const ch_uint<N>&, x, const ch_logic<M>&)

#define CH_LOGIC_UINT_OP7_TYPES \
  const ch_scalar<M>&

#define CH_LOGIC_UINT_GLOBAL_OP8(i, x) \
  CH_GLOBAL_OP4((template <unsigned N, unsigned M>), <<, const ch_uint<N>&, x, const ch_logic<M>&) \
  CH_GLOBAL_OP4((template <unsigned N, unsigned M>), >>, const ch_uint<N>&, x, const ch_logic<M>&)

#define CH_LOGIC_UINT_GLOBAL_FUNC8(i, x) \
  CH_GLOBAL_FUNC4((template <unsigned N, unsigned M>), ch_sll, const ch_uint<N>&, x, const ch_logic<M>&) \
  CH_GLOBAL_FUNC4((template <unsigned N, unsigned M>), ch_srl, const ch_uint<N>&, x, const ch_logic<M>&)

#define CH_LOGIC_UINT_OP8_TYPES \
  const ch_scuint<N>&

template <unsigned N>
class ch_uint : public ch_logic<N> {
public:
  using traits = logic_traits<N, false, ch_uint, ch_scuint<N>>;
  using base = ch_logic<N>;

  ch_uint(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_uint(const ch_uint& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_uint(ch_uint&& rhs) : base(std::move(rhs)) {}

  ch_uint(const ch_scalar<N>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_uint(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
  explicit ch_uint(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible_v<U>)>
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

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  ch_uint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
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
    return LogicOp<op_lt, ch_logic<1>>(*this, rhs);
  }

  auto operator<=(const ch_uint& rhs) const {
    return LogicOp<op_le, ch_logic<1>>(*this, rhs);
  }

  auto operator>(const ch_uint& rhs) const {
    return LogicOp<op_gt, ch_logic<1>>(*this, rhs);
  }

  auto operator>=(const ch_uint& rhs) const {
    return LogicOp<op_ge, ch_logic<1>>(*this, rhs);
  }

  // bitwise operators

  auto operator~() const {
    return LogicOp<op_inv, ch_uint>(*this);
  }

  auto operator&(const ch_uint& rhs) const {
    return LogicOp<op_and, ch_uint>(*this, rhs);
  }

  auto operator|(const ch_uint& rhs) const {
    return LogicOp<op_or, ch_uint>(*this, rhs);
  }

  auto operator^(const ch_uint& rhs) const {
    return LogicOp<op_xor, ch_uint>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_logic<M>& rhs) const {
    return LogicOp<op_sll, ch_uint>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_logic<M>& rhs) const {
    return LogicOp<op_sra, ch_uint>(*this, rhs);
  }

  // arithmetic operators

  auto operator-() const {
    return LogicOp<op_neg, ch_uint>(*this);
  }

  auto operator+(const ch_uint& rhs) const {
    return LogicOp<op_add, ch_uint>(*this, rhs);
  }

  auto operator-(const ch_uint& rhs) const {
    return LogicOp<op_sub, ch_uint>(*this, rhs);
  }

  auto operator*(const ch_uint& rhs) const {
    return LogicOp<op_mult, ch_uint>(*this, rhs);
  }

  auto operator/(const ch_uint& rhs) const {
    return LogicOp<op_div, ch_uint>(*this, rhs);
  }

  auto operator%(const ch_uint& rhs) const {
    return LogicOp<op_mod, ch_uint>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_uint)

protected:

  // friend operators

  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP1, CH_SEP_SPACE, CH_LOGIC_UINT_OP1_TYPES)
  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP2, CH_SEP_SPACE, CH_LOGIC_UINT_OP2_TYPES)
  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP3, CH_SEP_SPACE, CH_LOGIC_UINT_OP3_TYPES)
  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP5, CH_SEP_SPACE, CH_LOGIC_UINT_OP5_TYPES)
  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP6, CH_SEP_SPACE, CH_LOGIC_UINT_OP6_TYPES)
  CH_FOR_EACH(CH_LOGIC_UINT_FRIEND_OP7, CH_SEP_SPACE, CH_LOGIC_UINT_OP7_TYPES)
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
inline auto ch_sll(const ch_uint<N>& lhs, const ch_logic<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_uint<N>& lhs, const ch_logic<M>& rhs) {
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

template <unsigned M, unsigned N>
auto ch_pad(const ch_uint<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_pad<ch_uint<M>>(obj, sloc);
}

// global operators

CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_OP4, CH_SEP_SPACE, CH_LOGIC_UINT_OP4_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_OP8, CH_SEP_SPACE, CH_LOGIC_UINT_OP8_TYPES)

// global functions

CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC1, CH_SEP_SPACE, CH_LOGIC_UINT_OP1_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC2, CH_SEP_SPACE, CH_LOGIC_UINT_OP2_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC3, CH_SEP_SPACE, CH_LOGIC_UINT_OP3_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC4, CH_SEP_SPACE, CH_LOGIC_UINT_OP4_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC5, CH_SEP_SPACE, CH_LOGIC_UINT_OP5_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC6, CH_SEP_SPACE, CH_LOGIC_UINT_OP6_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC7, CH_SEP_SPACE, CH_LOGIC_UINT_OP7_TYPES)
CH_FOR_EACH(CH_LOGIC_UINT_GLOBAL_FUNC8, CH_SEP_SPACE, CH_LOGIC_UINT_OP8_TYPES)

}}
