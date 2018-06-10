#pragma once

#include "logic.h"

namespace ch {
namespace internal {

#define CH_LOGIC_INT_OP1(i, x) \
  CH_FRIEND_OP1_IMPL((), <, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), <=, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), >, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), >=, const ch_int&, x)

#define CH_LOGIC_INT_FUNC1(i, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_lt, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_le, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_gt, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_ge, const ch_int<N>&, x)

#define CH_LOGIC_INT_OP1_TYPES \
  const ch_scint<N>&, int8_t, int16_t, int32_t, int64_t

#define CH_LOGIC_INT_OP2(i, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), <, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), <=, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), >, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), >=, const ch_int&, x)

#define CH_LOGIC_INT_FUNC2(i, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_lt, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_le, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_gt, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_ge, const ch_int<N>&, x)

#define CH_LOGIC_INT_OP2_TYPES \
  const ch_int<M>&, const ch_scint<M>&

#define CH_LOGIC_INT_OP3(i, x) \
  CH_FRIEND_OP1_IMPL((), &, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), |, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), ^, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), +, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), -, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), *, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), /, const ch_int&, x) \
  CH_FRIEND_OP1_IMPL((), %, const ch_int&, x)

#define CH_LOGIC_INT_FUNC3(i, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_and, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_or, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_xor, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_add, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_sub, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_mult, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_div, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_mod, const ch_int<N>&, x)

#define CH_LOGIC_INT_OP3_TYPES \
  const ch_uint<N>&, const ch_logic<N>&, const ch_scalar<N>&, \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_INT_OP4(i, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), +, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), -, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), *, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), /, const ch_int&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), %, const ch_int&, x)

#define CH_LOGIC_INT_FUNC4(i, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_and, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_or, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xor, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_add, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_sub, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_mult, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_div, const ch_int<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_mod, const ch_int<N>&, x)

#define CH_LOGIC_INT_OP4_TYPES \
  const ch_int<M>&, const ch_uint<M>&, const ch_logic<M>&, const ch_scalar<M>&

#define CH_LOGIC_INT_OP5(i, x) \
  CH_FRIEND_OP3_IMPL((), <<, const ch_int&, x, const ch_int<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3_IMPL((), >>, const ch_int&, x, const ch_int<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_INT_FUNC5(i, x) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N>), ch_sll, const ch_int<N>&, x, const ch_int<CH_WIDTH_OF(x)>&) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N>), ch_srl, const ch_int<N>&, x, const ch_int<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_INT_OP5_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_INT_OP6(i, x) \
  CH_FRIEND_OP3_IMPL((template <unsigned M>), <<, const ch_int&, x, const ch_int<M>&) \
  CH_FRIEND_OP3_IMPL((template <unsigned M>), >>, const ch_int&, x, const ch_int<M>&)

#define CH_LOGIC_INT_FUNC6(i, x) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N, unsigned M>), ch_sll, const ch_int<N>&, x, const ch_int<M>&) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N, unsigned M>), ch_srl, const ch_int<N>&, x, const ch_int<M>&)

#define CH_LOGIC_INT_OP6_TYPES \
  const ch_uint<M>&, const ch_logic<M>&, const ch_scalar<M>&

template <unsigned N>
class ch_int : public ch_logic<N> {
public:
  using traits = logic_traits<N, true, ch_int, ch_scint<N>>;
  using base = ch_logic<N>;

  ch_int(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_int(const ch_int& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_int(ch_int&& rhs) : base(std::move(rhs)) {}

  ch_int(const ch_scalar<N>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_int(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
  explicit ch_int(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible_v<U>)>
  explicit ch_int(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_int& operator=(const ch_int& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_int& operator=(ch_int&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  ch_int& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
  ch_int& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_int& operator=(U rhs) {
    base::operator=(rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_int& rhs) const {
    return make_logic_op<op_lt, ch_logic<1>>(*this, rhs);
  }

  auto operator<=(const ch_int& rhs) const {
    return make_logic_op<op_le, ch_logic<1>>(*this, rhs);
  }

  auto operator>(const ch_int& rhs) const {
    return make_logic_op<op_gt, ch_logic<1>>(*this, rhs);
  }

  auto operator>=(const ch_int& rhs) const {
    return make_logic_op<op_ge, ch_logic<1>>(*this, rhs);
  }

  // bitwise operators

  auto operator~() const {
    return make_logic_op<op_inv, ch_int>(*this);
  }

  auto operator&(const ch_int& rhs) const {
    return make_logic_op<op_and, ch_int>(*this, rhs);
  }

  auto operator|(const ch_int& rhs) const {
    return make_logic_op<op_or, ch_int>(*this, rhs);
  }

  auto operator^(const ch_int& rhs) const {
    return make_logic_op<op_xor, ch_int>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_int<M>& rhs) const {
    return make_logic_op<op_sll, ch_int>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_int<M>& rhs) const {
    return make_logic_op<op_sra, ch_int>(*this, rhs);
  }

  // arithmetic operators

  auto operator-() const {
    return make_logic_op<op_neg, ch_int>(*this);
  }

  auto operator+(const ch_int& rhs) const {
    return make_logic_op<op_add, ch_int>(*this, rhs);
  }

  auto operator-(const ch_int& rhs) const {
    return make_logic_op<op_sub, ch_int>(*this, rhs);
  }

  auto operator*(const ch_int& rhs) const {
    return make_logic_op<op_mult, ch_int>(*this, rhs);
  }

  auto operator/(const ch_int& rhs) const {
    return make_logic_op<op_div, ch_int>(*this, rhs);
  }

  auto operator%(const ch_int& rhs) const {
    return make_logic_op<op_mod, ch_int>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_int)

protected:

  // friend operators

  CH_FOR_EACH(CH_LOGIC_INT_OP1, CH_SEP_SPACE, CH_LOGIC_INT_OP1_TYPES)
  CH_FOR_EACH(CH_LOGIC_INT_OP2, CH_SEP_SPACE, CH_LOGIC_INT_OP2_TYPES)
  CH_FOR_EACH(CH_LOGIC_INT_OP3, CH_SEP_SPACE, CH_LOGIC_INT_OP3_TYPES)
  CH_FOR_EACH(CH_LOGIC_INT_OP4, CH_SEP_SPACE, CH_LOGIC_INT_OP4_TYPES)
  CH_FOR_EACH(CH_LOGIC_INT_OP5, CH_SEP_SPACE, CH_LOGIC_INT_OP5_TYPES)
  CH_FOR_EACH(CH_LOGIC_INT_OP6, CH_SEP_SPACE, CH_LOGIC_INT_OP6_TYPES)
};

// compare operators

template <unsigned N>
inline auto ch_lt(const ch_int<N>& lhs,
                  const ch_int<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_lt, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_le(const ch_int<N>& lhs,
                  const ch_int<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_le, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_gt(const ch_int<N>& lhs,
                  const ch_int<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_gt, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_ge(const ch_int<N>& lhs,
                  const ch_int<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_ge, ch_int<N>>(lhs, rhs, sloc);
}

// bitwise operators

template <unsigned N>
auto ch_inv(const ch_int<N>& in,
            const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_inv, ch_int<N>>(in, sloc);
}

template <unsigned N>
inline auto ch_and(const ch_int<N>& lhs,
                   const ch_int<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_and, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_or(const ch_int<N>& lhs,
                  const ch_int<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_or, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_xor(const ch_int<N>& lhs,
                   const ch_int<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_xor, ch_int<N>>(lhs, rhs, sloc);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const ch_int<N>& lhs,
                   const ch_int<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_sll, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_int<N>& lhs,
                   const ch_int<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_srl, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N, unsigned M>
inline auto ch_sra(const ch_int<N>& lhs,
                   const ch_int<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_sra, ch_int<N>>(lhs, rhs, sloc);
}

// arithmetic operators

template <unsigned N>
auto ch_neg(const ch_int<N>& in,
            const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_neg, ch_int<N>>(in, sloc);
}

template <unsigned N>
inline auto ch_add(const ch_int<N>& lhs,
                   const ch_int<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_add, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_sub(const ch_int<N>& lhs,
                   const ch_int<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_sub, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_mult(const ch_int<N>& lhs,
                    const ch_int<N>& rhs,
                    const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_mult, ch_int<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_div(const ch_int<N>& lhs,
                   const ch_int<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_div, ch_int<N>>(lhs, rhs, sloc);
}

// padding

template <typename R, unsigned N>
auto ch_pad(const ch_int<N>& obj,
            const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> >= N, "invalid pad size");
  if constexpr(width_v<R> > N) {
    return make_logic_op<op_sext, R>(obj, sloc);
  } else {
    return R(obj, sloc);
  }
}

template <unsigned M, unsigned N>
auto ch_pad(const ch_int<N>& obj,
            const source_location& sloc = CH_SRC_LOCATION) {
  return ch_pad<ch_int<M>>(obj, sloc);
}

// global functions

CH_FOR_EACH(CH_LOGIC_INT_FUNC1, CH_SEP_SPACE, CH_LOGIC_INT_OP1_TYPES)
CH_FOR_EACH(CH_LOGIC_INT_FUNC2, CH_SEP_SPACE, CH_LOGIC_INT_OP2_TYPES)
CH_FOR_EACH(CH_LOGIC_INT_FUNC3, CH_SEP_SPACE, CH_LOGIC_INT_OP3_TYPES)
CH_FOR_EACH(CH_LOGIC_INT_FUNC4, CH_SEP_SPACE, CH_LOGIC_INT_OP4_TYPES)
CH_FOR_EACH(CH_LOGIC_INT_FUNC5, CH_SEP_SPACE, CH_LOGIC_INT_OP5_TYPES)
CH_FOR_EACH(CH_LOGIC_INT_FUNC6, CH_SEP_SPACE, CH_LOGIC_INT_OP6_TYPES)

}}
