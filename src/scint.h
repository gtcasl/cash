#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

#define CH_SCALAR_INT_FRIEND_OP1(i, x) \
  CH_FRIEND_OP1((), <, const ch_scint&, x) \
  CH_FRIEND_OP1((), <=, const ch_scint&, x) \
  CH_FRIEND_OP1((), >, const ch_scint&, x) \
  CH_FRIEND_OP1((), >=, const ch_scint&, x)

#define CH_SCALAR_INT_OP1_TYPES \
  int8_t, int16_t, int32_t, int64_t

#define CH_SCALAR_INT_FRIEND_OP2(i, x) \
  CH_FRIEND_OP1((), &, const ch_scint&, x) \
  CH_FRIEND_OP1((), |, const ch_scint&, x) \
  CH_FRIEND_OP1((), ^, const ch_scint&, x) \
  CH_FRIEND_OP1((), +, const ch_scint&, x) \
  CH_FRIEND_OP1((), -, const ch_scint&, x) \
  CH_FRIEND_OP1((), *, const ch_scint&, x) \
  CH_FRIEND_OP1((), /, const ch_scint&, x) \
  CH_FRIEND_OP1((), %, const ch_scint&, x)

#define CH_SCALAR_INT_OP2_TYPES \
  const ch_scalar<N>&, \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_INT_FRIEND_OP3(i, x) \
  CH_FRIEND_OP3((), <<, const ch_scint&, x, const ch_scalar<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3((), >>, const ch_scint&, x, const ch_scalar<CH_WIDTH_OF(x)>&)

#define CH_SCALAR_INT_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_INT_GLOBAL_OP4(i, x) \
  CH_GLOBAL_OP4((template <unsigned M>), <<, const ch_scint<CH_WIDTH_OF(x)>&, x, const ch_scalar<M>&) \
  CH_GLOBAL_OP4((template <unsigned M>), >>, const ch_scint<CH_WIDTH_OF(x)>&, x, const ch_scalar<M>&)

#define CH_SCALAR_INT_OP4_TYPES \
  int8_t, int16_t, int32_t, int64_t

#define CH_SCALAR_INT_FRIEND_OP5(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <=, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >=, const ch_scint&, x)

#define CH_SCALAR_INT_OP5_TYPES \
  const ch_scint<M>&

#define CH_SCALAR_INT_FRIEND_OP6(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), +, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), -, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), *, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), /, const ch_scint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), %, const ch_scint&, x)

#define CH_SCALAR_INT_OP6_TYPES \
  const ch_scint<M>&, const ch_scalar<M>&

template <unsigned N>
class ch_scint : public ch_scalar<N> {
public:
  using traits = scalar_traits<N, true, ch_scint, ch_int<N>>;
  using base = ch_scalar<N>;
  using base::buffer_;

  ch_scint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  ch_scint(const ch_scint& rhs)
    : base(rhs)
  {}

  ch_scint(ch_scint&& rhs)
    : base(std::move(rhs))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(width_v<U> <= N)>
  explicit ch_scint(const U& rhs) :
    base(rhs)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible_v<U>)>
  explicit ch_scint(const U& rhs)
    : base(rhs)
  {}

  ch_scint& operator=(const ch_scint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scint& operator=(ch_scint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(width_v<U> <= N)>
  ch_scint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_scint& operator=(U rhs) {
    base::operator=(rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_scint& rhs) const {
    return (buffer_->data() < rhs.buffer_->data());
  }

  auto operator>=(const ch_scint& rhs) const {
    return !(buffer_->data() < rhs.buffer_->data());
  }

  auto operator>(const ch_scint& rhs) const {
    return (rhs.buffer_->data() < buffer_->data());
  }

  auto operator<=(const ch_scint& rhs) const {
    return !(rhs.buffer_->data() < rhs.buffer_->data());
  }

  // bitwise operators

  auto operator~() const {
    return ScalarOp<ch_scint>(*this, Inv);
  }

  auto operator&(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, And);
  }

  auto operator|(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Or);
  }

  auto operator^(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Xor);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Sll);
  }

  template <unsigned M>
  auto operator>>(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Sra);
  }

  // arithmetic operators

  auto operator-() const {
    return ScalarOp<ch_scint>(*this, Neg);
  }

  auto operator+(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Add);
  }

  auto operator-(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Sub);
  }

  auto operator*(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Mult);
  }

  auto operator/(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Div);
  }

  auto operator%(const ch_scint& rhs) const {
    return ScalarOp<ch_scint>(*this, rhs, Mod);
  }

  CH_SCALAR_INTERFACE(ch_scint)

  template <typename U,
            CH_REQUIRE_0(is_bitvector_castable_v<U>),
            CH_REQUIRE_0(CH_WIDTH_OF(U) >= N)>
  explicit operator U() const {
    if constexpr(std::is_signed_v<U> && (CH_WIDTH_OF(U) > N)) {
      return U(signext(static_cast<uint32_t>(buffer_->data()), N));
    } else {
      return static_cast<U>(buffer_->data());
    }
  }

protected:

  // friend operators

  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OP1, CH_SEP_SPACE, CH_SCALAR_INT_OP1_TYPES)
  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OP2, CH_SEP_SPACE, CH_SCALAR_INT_OP2_TYPES)
  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OP3, CH_SEP_SPACE, CH_SCALAR_INT_OP3_TYPES)
  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OP5, CH_SEP_SPACE, CH_SCALAR_INT_OP5_TYPES)
  CH_FOR_EACH(CH_SCALAR_INT_FRIEND_OP6, CH_SEP_SPACE, CH_SCALAR_INT_OP6_TYPES)
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_scint<N>& obj) {
  static_assert(M >= N, "invalid pad size");
  if constexpr(M > N) {
    return ScalarOp<ch_scint<M>>(obj, SExt);
  } else {
    return obj;
  }
}

// global operators

CH_FOR_EACH(CH_SCALAR_INT_GLOBAL_OP4, CH_SEP_SPACE, CH_SCALAR_INT_OP4_TYPES)

}
}
