#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

#define CH_SCALAR_UINT_FRIEND_OP1(i, x) \
  CH_FRIEND_OP1((), <, const ch_scuint&, x) \
  CH_FRIEND_OP1((), <=, const ch_scuint&, x) \
  CH_FRIEND_OP1((), >, const ch_scuint&, x) \
  CH_FRIEND_OP1((), >=, const ch_scuint&, x)

#define CH_SCALAR_UINT_OP1_TYPES \
  const ch_scalar<N>&, uint8_t, uint16_t, uint32_t, uint64_t

#define CH_SCALAR_UINT_FRIEND_OP2(i, x) \
  CH_FRIEND_OP1((), &, const ch_scuint&, x) \
  CH_FRIEND_OP1((), |, const ch_scuint&, x) \
  CH_FRIEND_OP1((), ^, const ch_scuint&, x) \
  CH_FRIEND_OP1((), +, const ch_scuint&, x) \
  CH_FRIEND_OP1((), -, const ch_scuint&, x) \
  CH_FRIEND_OP1((), *, const ch_scuint&, x) \
  CH_FRIEND_OP1((), /, const ch_scuint&, x) \
  CH_FRIEND_OP1((), %, const ch_scuint&, x)

#define CH_SCALAR_UINT_OP2_TYPES \
  const ch_scalar<N>&, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_UINT_FRIEND_OP3(i, x) \
  CH_FRIEND_OP3((), <<, const ch_scuint&, x, const ch_scalar<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3((), >>, const ch_scuint&, x, const ch_scalar<CH_WIDTH_OF(x)>&)

#define CH_SCALAR_UINT_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_UINT_GLOBAL_OP4(i, x) \
  CH_GLOBAL_OP4((template <unsigned M>), <<, const ch_scuint<CH_WIDTH_OF(x)>&, x, const ch_scalar<M>&) \
  CH_GLOBAL_OP4((template <unsigned M>), >>, const ch_scuint<CH_WIDTH_OF(x)>&, x, const ch_scalar<M>&)

#define CH_SCALAR_UINT_OP4_TYPES \
  uint8_t, uint16_t, uint32_t, uint64_t

#define CH_SCALAR_UINT_FRIEND_OP5(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), <=, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), >=, const ch_scuint&, x)

#define CH_SCALAR_UINT_OP5_TYPES \
  const ch_scuint<M>&, const ch_scalar<M>&

#define CH_SCALAR_UINT_FRIEND_OP6(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), +, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), -, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), *, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), /, const ch_scuint&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), %, const ch_scuint&, x)

#define CH_SCALAR_UINT_OP6_TYPES \
  const ch_scuint<M>&, const ch_scalar<M>&

template <unsigned N>
class ch_scuint : public ch_scalar<N>  {
public:
  using traits = scalar_traits<N, false, ch_scuint, ch_uint<N>>;
  using base = ch_scalar<N>;
  using base::buffer_;

  ch_scuint(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  ch_scuint(const ch_scuint& rhs)
    : base(rhs)
  {}

  ch_scuint(ch_scuint&& rhs)
    : base(std::move(rhs))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(width_v<U> <= N)>
  explicit ch_scuint(const U& rhs) :
    base(rhs)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible_v<U>)>
  explicit ch_scuint(const U& rhs)
    : base(rhs)
  {}

  ch_scuint& operator=(const ch_scuint& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scuint& operator=(ch_scuint&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type_v<U>),
            CH_REQUIRE_0(width_v<U> <= N)>
  ch_scuint& operator=(const U& rhs) {
    base::operator=(rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_scuint& operator=(U rhs) {
    base::operator=(rhs);
    return *this;
  }

  // compare operators

  auto operator<(const ch_scuint& rhs) const {
    return (buffer_->data() < rhs.buffer_->data());
  }

  auto operator>=(const ch_scuint& rhs) const {
    return !(buffer_->data() < rhs.buffer_->data());
  }

  auto operator>(const ch_scuint& rhs) const {
    return (rhs.buffer_->data() < buffer_->data());
  }

  auto operator<=(const ch_scuint& rhs) const {
    return !(rhs.buffer_->data() < rhs.buffer_->data());
  }

  // bitwise operators

  auto operator~() const {
    return ScalarOp<ch_scuint>(*this, Inv);
  }

  auto operator&(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, And);;
  }

  auto operator|(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Or);
  }

  auto operator^(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Xor);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Sll);
  }

  template <unsigned M>
  auto operator>>(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Srl);
  }

  // arithmetic operators

  auto operator-() const {
    return ScalarOp<ch_scuint>(*this, Neg);
  }

  auto operator+(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Add);
  }

  auto operator-(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Sub);
  }

  auto operator*(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Mult);
  }

  auto operator/(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Div);
  }

  auto operator%(const ch_scuint& rhs) const {
    return ScalarOp<ch_scuint>(*this, rhs, Mod);
  }

  CH_SCALAR_INTERFACE(ch_scuint)

protected:

  // friend operators

  CH_FOR_EACH(CH_SCALAR_UINT_FRIEND_OP1, CH_SEP_SPACE, CH_SCALAR_UINT_OP1_TYPES)
  CH_FOR_EACH(CH_SCALAR_UINT_FRIEND_OP2, CH_SEP_SPACE, CH_SCALAR_UINT_OP2_TYPES)
  CH_FOR_EACH(CH_SCALAR_UINT_FRIEND_OP3, CH_SEP_SPACE, CH_SCALAR_UINT_OP3_TYPES)
  CH_FOR_EACH(CH_SCALAR_UINT_FRIEND_OP5, CH_SEP_SPACE, CH_SCALAR_UINT_OP5_TYPES)
  CH_FOR_EACH(CH_SCALAR_UINT_FRIEND_OP6, CH_SEP_SPACE, CH_SCALAR_UINT_OP6_TYPES)
};

template <unsigned M, unsigned N>
auto ch_pad(const ch_scuint<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  CH_UNUSED(sloc);
  static_assert(M >= N, "invalid pad size");
  if constexpr(M > N) {
    return ScalarOp<ch_scuint<M>>(obj, ZExt);
  } else {
    return obj;
  }
}

// global operators

CH_FOR_EACH(CH_SCALAR_UINT_GLOBAL_OP4, CH_SEP_SPACE, CH_SCALAR_UINT_OP4_TYPES)

}
}
