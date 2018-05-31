#pragma once

#include "lnode.h"

#define CH_OP_ARY(x)   (x & (0x3 << 5))
#define CH_OP_CLASS(x) (x & (0x7 << 7))

#define CH_OP_TYPE(n, v) op_##n = v,
#define CH_OP_NAME(n, v) #n,
#define CH_OP_INDEX(op)  (op & 0x1f)
#define CH_OP_ENUM(m) \
  m(eq,     0 | op_binary | op_compare | op_symmetric) \
  m(ne,     1 | op_binary | op_compare | op_symmetric) \
  m(lt,     2 | op_binary | op_compare) \
  m(gt,     3 | op_binary | op_compare) \
  m(le,     4 | op_binary | op_compare) \
  m(ge,     5 | op_binary | op_compare) \
  m(inv,    6 | op_unary  | op_bitwise) \
  m(and,    7 | op_binary | op_bitwise | op_symmetric) \
  m(or,     8 | op_binary | op_bitwise | op_symmetric) \
  m(xor,    9 | op_binary | op_bitwise | op_symmetric) \
  m(andr,  10 | op_unary  | op_reduce) \
  m(orr,   11 | op_unary  | op_reduce) \
  m(xorr,  12 | op_unary  | op_reduce) \
  m(sll,   13 | op_binary | op_shift) \
  m(srl,   14 | op_binary | op_shift) \
  m(sra,   15 | op_binary | op_shift) \
  m(add,   16 | op_binary | op_arithm | op_symmetric) \
  m(sub,   17 | op_binary | op_arithm) \
  m(neg,   18 | op_unary  | op_arithm) \
  m(mult,  19 | op_binary | op_arithm | op_symmetric) \
  m(div,   20 | op_binary | op_arithm) \
  m(mod,   21 | op_binary | op_arithm) \
  m(zext,  22 | op_unary  | op_misc) \
  m(sext,  23 | op_unary  | op_misc)

namespace ch {
namespace internal {

enum op_flags {
  op_unary   = 0 << 5,
  op_binary  = 1 << 5,
  op_tenary  = 2 << 5,
  op_nary    = 3 << 5,

  op_bitwise = 0 << 7,
  op_compare = 1 << 7,
  op_arithm  = 2 << 7,
  op_shift   = 3 << 7,
  op_reduce  = 4 << 7,
  op_misc    = 5 << 7,

  op_symmetric = 1 << 10,
};

enum ch_op {
  CH_OP_ENUM(CH_OP_TYPE)
};

template <typename... Ts>
struct width_impl;

template <typename T>
struct width_impl<T> {
  static constexpr uint32_t value = T::traits::bitwidth;
};

template <typename T0, typename... Ts>
struct width_impl<T0, Ts...> {
  static constexpr uint32_t value = T0::traits::bitwidth + width_impl<Ts...>::value;
};

template <typename... Ts>
inline constexpr uint32_t width_v = width_impl<std::decay_t<Ts>...>::value;

template <typename T0, typename... Ts>
inline constexpr bool signed_v = std::decay_t<T0>::traits::is_signed;

const char* to_string(ch_op op);

lnodeimpl* createAluNode(ch_op op, uint32_t size, const lnode& in);

lnodeimpl* createAluNode(ch_op op, uint32_t size, const lnode& lhs, const lnode& rhs);

lnodeimpl* createRotateNode(const lnode& next, uint32_t dist, bool right);

}
}

///////////////////////////////////////////////////////////////////////////////

#define CH_FRIEND_OP1(header, op, lhs_t, rhs_t) \
  CH_REM header \
  inline friend auto operator op(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<lhs_t>>(_rhs); \
    return lhs op rhs; \
  } \
  CH_REM header \
  inline friend auto operator op(rhs_t _lhs, lhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<lhs_t>>(_lhs); \
    return lhs op rhs; \
  }

#define CH_FRIEND_OP2(header, op, lhs_t, rhs_t) \
  CH_REM header \
  inline friend auto operator op(lhs_t _lhs, rhs_t _rhs) { \
    constexpr auto W = std::max(width_v<lhs_t>, width_v<rhs_t>); \
    auto lhs = ch_pad<W>(_lhs); \
    auto rhs = ch_pad<W>(_rhs); \
    return lhs op rhs; \
  } \
  CH_REM header \
  inline friend auto operator op(rhs_t _lhs, lhs_t _rhs) { \
    constexpr auto W = std::max(width_v<lhs_t>, width_v<rhs_t>); \
    auto lhs = ch_pad<W>(_lhs); \
    auto rhs = ch_pad<W>(_rhs); \
    return lhs op rhs; \
  }

#define CH_FRIEND_OP3(header, op, lhs_t, rhs_t, cvt_t) \
  CH_REM header \
  inline friend auto operator op(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<cvt_t>>(_rhs); \
    return lhs op rhs; \
  }

#define CH_FRIEND_OP4(header, op, cvt_t, lhs_t, rhs_t) \
  CH_REM header \
  inline friend auto operator op(lhs_t _lhs, rhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<cvt_t>>(_lhs); \
    return lhs op rhs; \
  }

#define CH_GLOBAL_OP4(header, op, cvt_t, lhs_t, rhs_t) \
  CH_REM header \
  inline auto operator op(lhs_t _lhs, rhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<cvt_t>>(_lhs); \
    return lhs op rhs; \
  }

#define CH_GLOBAL_FUNC1(header, func, lhs_t, rhs_t) \
  CH_REM header \
  inline auto func(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<lhs_t>>(_rhs); \
    return func(lhs, rhs); \
  } \
  CH_REM header \
  inline auto func(rhs_t _lhs, lhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<lhs_t>>(_lhs); \
    return func(lhs, rhs); \
  }

#define CH_GLOBAL_FUNC2(header, func, lhs_t, rhs_t) \
  CH_REM header \
  inline auto func(lhs_t _lhs, rhs_t _rhs) { \
    constexpr auto W = std::max(width_v<lhs_t>, width_v<rhs_t>); \
    auto lhs = ch_pad<W>(_lhs); \
    auto rhs = ch_pad<W>(_rhs); \
    return func(lhs, rhs); \
  } \
  CH_REM header \
  inline auto func(rhs_t _lhs, lhs_t _rhs) { \
    constexpr auto W = std::max(width_v<lhs_t>, width_v<rhs_t>); \
    auto lhs = ch_pad<W>(_lhs); \
    auto rhs = ch_pad<W>(_rhs); \
    return func(lhs, rhs); \
  }

#define CH_GLOBAL_FUNC3(header, func, lhs_t, rhs_t, cvt_t) \
  CH_REM header \
  inline auto func(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<cvt_t>>(_rhs); \
    return func(lhs, rhs); \
  }

#define CH_GLOBAL_FUNC4(header, func, cvt_t, lhs_t, rhs_t) \
  CH_REM header \
  inline auto func(lhs_t _lhs, rhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<cvt_t>>(_lhs); \
    return func(lhs, rhs); \
  }
