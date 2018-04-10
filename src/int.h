#pragma once

#include "logic.h"

namespace ch {
namespace internal {

#define CH_INT_FRIEND_OPS(i, x) \
  CH_FRIEND_OP_LT((), const ch_int&, x) \
  CH_FRIEND_OP_LE((), const ch_int&, x) \
  CH_FRIEND_OP_GT((), const ch_int&, x) \
  CH_FRIEND_OP_GE((), const ch_int&, x) \
  CH_FRIEND_OP_AND((), const ch_int&, x) \
  CH_FRIEND_OP_OR((), const ch_int&, x) \
  CH_FRIEND_OP_XOR((), const ch_int&, x) \
  CH_FRIEND_OP_SLL((), const ch_int&, x) \
  CH_FRIEND_OP_SRL((), const ch_int&, x) \
  CH_FRIEND_OP_ADD((), const ch_int&, x) \
  CH_FRIEND_OP_SUB((), const ch_int&, x) \
  CH_FRIEND_OP_MULT((), const ch_int&, x) \
  CH_FRIEND_OP_DIV((), const ch_int&, x) \
  CH_FRIEND_OP_MOD((), const ch_int&, x)

#define CH_INT_OP_TYPES \
  ch_uint<N>, ch_scalar<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

template <unsigned N>
class ch_int : public ch_logic<N> {
public:
  using traits = logic_traits<N, ch_int, ch_sint<N>>;
  using base = ch_logic<N>;

  ch_int(const logic_buffer& buffer = logic_buffer(N, CH_SRC_LOCATION))
    : base(buffer)
  {}

  ch_int(const ch_int& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  ch_int(ch_int&& rhs) : base(std::move(rhs)) {}

  ch_int(const ch_scalar<N>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <unsigned M, CH_REQUIRE_0(M < N)>
  explicit ch_int(const ch_scalar<M>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_int(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> == N)>
  explicit ch_int(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
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

  template <unsigned M, CH_REQUIRE_0(M < N)>
  ch_int& operator=(const ch_scalar<M>& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(N == width_v<U>)>
  ch_int& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(N == width_v<U>)>
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
    return OpBinary<alu_lt, ch_logic<1>>(*this, rhs);
  }

  auto operator<=(const ch_int& rhs) const {
    return OpBinary<alu_le, ch_logic<1>>(*this, rhs);
  }

  auto operator>(const ch_int& rhs) const {
    return OpBinary<alu_gt, ch_logic<1>>(*this, rhs);
  }

  auto operator>=(const ch_int& rhs) const {
    return OpBinary<alu_ge, ch_logic<1>>(*this, rhs);
  }

  // bitwise operators

  auto operator~() const {
    return OpUnary<alu_inv, ch_int>(*this);
  }

  auto operator&(const ch_logic<N>& rhs) const {
    return OpBinary<alu_and, ch_int>(*this, rhs);
  }

  auto operator|(const ch_logic<N>& rhs) const {
    return OpBinary<alu_or, ch_int>(*this, rhs);
  }

  auto operator^(const ch_logic<N>& rhs) const {
    return OpBinary<alu_xor, ch_int>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_logic<M>& rhs) const {
    return OpBinary<alu_sll, ch_int>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_logic<M>& rhs) const {
    return OpBinary<alu_sra, ch_int>(*this, rhs);
  }

  // arithmetic operators

  auto operator-() const {
    return OpUnary<alu_neg, ch_int>(*this);
  }

  auto operator+(const ch_int& rhs) const {
    return OpBinary<alu_add, ch_int>(*this, rhs);
  }

  auto operator-(const ch_int& rhs) const {
    return OpBinary<alu_sub, ch_int>(*this, rhs);
  }

  auto operator*(const ch_int& rhs) const {
    return OpBinary<alu_mult, ch_int>(*this, rhs);
  }

  auto operator/(const ch_int& rhs) const {
    return OpBinary<alu_div, ch_int>(*this, rhs);
  }

  auto operator%(const ch_int& rhs) const {
    return OpBinary<alu_mod, ch_int>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_int)

protected:

  CH_FOR_EACH(CH_INT_FRIEND_OPS, CH_SEP_SPACE, CH_INT_OP_TYPES)

  template <unsigned M>
  inline friend ch_int operator>>(const ch_int& lhs, const ch_scalar<M>& rhs) {
    return lhs >> ch_int<M>(rhs);
  }
};

// compare operators

template <unsigned N>
inline auto ch_lt(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs < rhs);
}

template <unsigned N>
inline auto ch_le(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs <= rhs);
}

template <unsigned N>
inline auto ch_gt(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs > rhs);
}

template <unsigned N>
inline auto ch_ge(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs >= rhs);
}

// bitwise operators

template <unsigned N>
auto ch_inv(const ch_int<N>& in) {
  return ~in;
}

template <unsigned N>
inline auto ch_and(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs & rhs);
}

template <unsigned N>
inline auto ch_or(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs | rhs);
}

template <unsigned N>
inline auto ch_xor(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs ^ rhs);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const ch_int<N>& lhs, const ch_int<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_int<N>& lhs, const ch_int<M>& rhs) {
  return (lhs >> rhs);
}

// arithmetic operators

template <unsigned N>
auto ch_neg(const ch_int<N>& in) {
  return -in;
}

template <unsigned N>
inline auto ch_add(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs + rhs);
}

template <unsigned N>
inline auto ch_sub(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs - rhs);
}

template <unsigned N>
inline auto ch_mult(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs * rhs);
}

template <unsigned N>
inline auto ch_div(const ch_int<N>& lhs, const ch_int<N>& rhs) {
  return (lhs / rhs);
}

// padding

template <typename R, unsigned N>
auto ch_pad(const ch_int<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> >= N, "invalid extend size");
  if constexpr(1 == N) {
    return ch_pad<N>(obj, sloc);
  } else
  if constexpr(width_v<R> > N) {
    auto padding = -ch_pad<ch_int<width_v<R> - N>>(obj[N - 1], sloc);
    return ch_cat(padding, obj, sloc). template as<R>();
  } else {
    return R(obj, sloc);
  }
}

template <unsigned N, unsigned M>
auto ch_pad(const ch_int<M>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_pad<ch_int<N>>(obj, sloc);
}

// global operators

CH_GLOBAL_OP_AND_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_AND_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_AND_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_OR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_OR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_OR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_XOR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_XOR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_XOR_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_ADD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_ADD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_ADD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_SUB_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_SUB_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_SUB_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_MULT_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_MULT_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_MULT_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_DIV_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_DIV_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_DIV_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

CH_GLOBAL_OP_MOD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_int<M>&)
CH_GLOBAL_OP_MOD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_int<N>&, const ch_uint<M>&)
CH_GLOBAL_OP_MOD_RSZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const ch_uint<N>&, const ch_int<M>&)

#define CH_INT_GLOBAL_OPS(i, x) \
  CH_GLOBAL_OP_EQ((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_NE((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_LT((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_LE((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_GT((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_GE((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_AND((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_OR((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_XOR((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_NAND((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_NOR((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_XNOR((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_ADD((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_SUB((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_MULT((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_DIV((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_MOD((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_SLL((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_SRL((template <unsigned N>), const ch_int<N>&, x) \
  CH_GLOBAL_OP_SRA((template <unsigned N>), const ch_int<N>&, x)

CH_FOR_EACH(CH_INT_GLOBAL_OPS, CH_SEP_SPACE, CH_INT_OP_TYPES)

///////////////////////////////////////////////////////////////////////////////

#define CH_SCALAR_INT_FRIEND_OPS(i, x) \
  CH_FRIEND_OP_LT((), const ch_sint&, x) \
  CH_FRIEND_OP_LE((), const ch_sint&, x) \
  CH_FRIEND_OP_GT((), const ch_sint&, x) \
  CH_FRIEND_OP_GE((), const ch_sint&, x) \
  CH_FRIEND_OP_AND((), const ch_sint&, x) \
  CH_FRIEND_OP_OR((), const ch_sint&, x) \
  CH_FRIEND_OP_XOR((), const ch_sint&, x) \
  CH_FRIEND_OP_ADD((), const ch_sint&, x) \
  CH_FRIEND_OP_SUB((), const ch_sint&, x) \
  CH_FRIEND_OP_MULT((), const ch_sint&, x) \
  CH_FRIEND_OP_DIV((), const ch_sint&, x) \
  CH_FRIEND_OP_MOD((), const ch_sint&, x) \
  CH_FRIEND_OP_SLL((), const ch_sint&, x) \
  CH_FRIEND_OP_SRL((), const ch_sint&, x)

#define CH_SCALAR_INT_OP_TYPES \
  ch_suint<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

template <unsigned N>
class ch_sint : public ch_scalar<N> {
public:
  using traits = scalar_traits<N, ch_sint, ch_int<N>>;
  using base = ch_scalar<N>;
  using base::buffer_;

  ch_sint(const scalar_buffer& buffer = scalar_buffer(N))
    : base(buffer)
  {}

  ch_sint(const ch_sint& rhs)
    : base(rhs)
  {}

  ch_sint(ch_sint&& rhs)
    : base(std::move(rhs))
  {}

  template <unsigned M, CH_REQUIRE_0(M < N)>
  explicit ch_sint(const ch_scalar<M>& rhs)
    : base(rhs)
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(N == width_v<U>)>
  explicit ch_sint(const U& rhs) :
    base(rhs)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit ch_sint(const U& rhs)
    : base(rhs)
  {}

  ch_sint& operator=(const ch_sint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_sint& operator=(ch_sint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <unsigned M, CH_REQUIRE_0(M < N)>
  ch_sint& operator=(const ch_scalar<M>& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(N == width_v<U>)>
  ch_sint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_sint& operator=(U rhs) {
    base::operator=(rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_sint& rhs) const {
    return (buffer_->get_data() < rhs.buffer_->get_data());
  }

  auto operator>=(const ch_sint& rhs) const {
    return !(buffer_->get_data() < rhs.buffer_->get_data());
  }

  auto operator>(const ch_sint& rhs) const {
    return (rhs.buffer_->get_data() < buffer_->get_data());
  }

  auto operator<=(const ch_sint& rhs) const {
    return !(rhs.buffer_->get_data() < rhs.buffer_->get_data());
  }

  // bitwise operators

  auto operator~() const {
    bitvector ret(N);
    Inv(ret, buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator&(const ch_sint& rhs) const {
    bitvector ret(N);
    And(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator|(const ch_sint& rhs) const {
    bitvector ret(N);
    Or(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator^(const ch_sint& rhs) const {
    bitvector ret(N);
    Xor(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }
  // shift operators

  auto operator<<(const ch_sint& rhs) const {
    bitvector ret(N);
    auto shift = rhs.buffer_->get_data();
    CH_CHECK(shift.find_last() <= 31, "shift amount out of range");
    Sll(ret, buffer_->get_data(), shift.get_word(0));
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator>>(const ch_sint& rhs) const {
    bitvector ret(N);
    auto shift = rhs.buffer_->get_data();
    CH_CHECK(shift.find_last() <= 31, "shift amount out of range");
    Sra(ret, buffer_->get_data(), shift.get_word(0));
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  // arithmetic operators

  auto operator-() const {
    bitvector ret(N);
    Negate(ret, buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator+(const ch_sint& rhs) const {
    bitvector ret(N);
    Add(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator-(const ch_sint& rhs) const {
    bitvector ret(N);
    Sub(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator*(const ch_sint& rhs) const {
    bitvector ret(N);
    Mult(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator/(const ch_sint& rhs) const {
    bitvector ret(N);
    Div(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  auto operator%(const ch_sint& rhs) const {
    bitvector ret(N);
    Mod(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_sint<N>(scalar_buffer(std::move(ret)));
  }

  CH_SCALAR_INTERFACE(ch_sint)

protected:

  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OPS, CH_SEP_SPACE, CH_SCALAR_INT_OP_TYPES)
};

}}
