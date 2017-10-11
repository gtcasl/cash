#pragma once

#include "bit.h"

enum alu_flags {
  alu_unary   = 1 << 8,
  alu_binary  = 2 << 8,
  alu_tenary  = 3 << 8,
  alu_nary    = 4 << 8,

  alu_bitwise = 1 << 11,
  alu_compare = 2 << 11,  
  alu_arithm  = 3 << 11,
  alu_shift   = 4 << 11,
  alu_rotate  = 5 << 11,
  alu_reduce  = 6 << 11,
  alu_misc    = 7 << 11,

  alu_integer = 1 << 14,
  alu_fixed   = 2 << 14,
  alu_float   = 3 << 14,
  alu_double  = 4 << 14,
};

#define CH_ALUOP_ARY(x)   (x & (0x7 <<  8))
#define CH_ALUOP_CLASS(x) (x & (0x7 << 11))
#define CH_ALUOP_DATA(x)  (x & (0x7 << 14))

#define CH_ALUOP_TYPE(n, v) alu_##n = v,
#define CH_ALUOP_NAME(n, v) #n,
#define CH_ALUOP_INDEX(op) (op & 0xff)
#define CH_ALUOP_ENUM(m) \
  m(inv,    0 | alu_unary  | alu_bitwise | alu_integer) \
  m(and,    1 | alu_binary | alu_bitwise | alu_integer) \
  m(or,     2 | alu_binary | alu_bitwise | alu_integer) \
  m(xor,    3 | alu_binary | alu_bitwise | alu_integer) \
  m(nand,   4 | alu_binary | alu_bitwise | alu_integer) \
  m(nor,    5 | alu_binary | alu_bitwise | alu_integer) \
  m(xnor,   6 | alu_binary | alu_bitwise | alu_integer) \
  m(andr,   7 | alu_unary  | alu_reduce  | alu_integer) \
  m(orr,    8 | alu_unary  | alu_reduce  | alu_integer) \
  m(xorr,   9 | alu_unary  | alu_reduce  | alu_integer) \
  m(nandr, 10 | alu_unary  | alu_reduce  | alu_integer) \
  m(norr,  11 | alu_unary  | alu_reduce  | alu_integer) \
  m(xnorr, 12 | alu_unary  | alu_reduce  | alu_integer) \
  m(sll,   13 | alu_binary | alu_shift   | alu_integer) \
  m(srl,   14 | alu_binary | alu_shift   | alu_integer) \
  m(sra,   15 | alu_binary | alu_shift   | alu_integer) \
  m(add,   16 | alu_binary | alu_arithm  | alu_integer) \
  m(sub,   17 | alu_binary | alu_arithm  | alu_integer) \
  m(neg,   18 | alu_unary  | alu_arithm  | alu_integer) \
  m(mult,  19 | alu_binary | alu_arithm  | alu_integer) \
  m(div,   20 | alu_binary | alu_arithm  | alu_integer) \
  m(mod,   21 | alu_binary | alu_arithm  | alu_integer) \
  m(eq,    22 | alu_binary | alu_compare | alu_integer) \
  m(ne,    23 | alu_binary | alu_compare | alu_integer) \
  m(lt,    24 | alu_binary | alu_compare | alu_integer) \
  m(gt,    25 | alu_binary | alu_compare | alu_integer) \
  m(le,    26 | alu_binary | alu_compare | alu_integer) \
  m(ge,    27 | alu_binary | alu_compare | alu_integer) \
  m(rotl,  28 | alu_binary | alu_rotate  | alu_integer) \
  m(rotr,  29 | alu_binary | alu_rotate  | alu_integer) \
  m(mux,   30 | alu_binary | alu_misc    | alu_integer) \
  m(fadd,  31 | alu_binary | alu_arithm  | alu_float) \
  m(fsub,  32 | alu_binary | alu_arithm  | alu_float) \
  m(fmult, 33 | alu_binary | alu_arithm  | alu_float) \
  m(fdiv,  34 | alu_binary | alu_arithm  | alu_float)

#define CH_BINOP_GEN(func, op) \
  template <typename A, typename B, \
            CH_REQUIRES(!are_all_ch_scalar<A, B>::value), \
            CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0), \
            CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value), \
            CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)> \
  const auto op(const A& a, const B& b) { \
    return func(a, b); \
  }

#define CH_UNARYOP_GEN(func, op) \
  template <unsigned N> \
  const auto op(const ch_bitbase<N>& in) { \
    return func(in); \
  }

#define CH_COMPAREOP_GEN(func, op) \
  template <typename A, typename B, \
            CH_REQUIRES(!are_all_ch_scalar<A, B>::value), \
            CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0), \
            CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value), \
            CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)> \
  const auto op(const A& a, const B& b) { \
    return func(a, b); \
  }

#define CH_SHIFTOP_GEN(func, op) \
  template <typename A, typename B, \
            CH_REQUIRES(!are_all_ch_scalar<A, B>::value), \
            CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0), \
            CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value), \
            CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)> \
  const auto op(const A& a, const B& b) { \
    return func(a, b); \
  }

namespace ch {
namespace internal {

enum ch_alu_op {
  CH_ALUOP_ENUM(CH_ALUOP_TYPE)
};

const char* to_string(ch_alu_op op);

lnodeimpl* createAluNode(ch_alu_op op, const lnode& lhs, const lnode& rhs);
lnodeimpl* createAluNode(ch_alu_op op, const lnode& in);

// compare operators

CH_COMPAREOP_GEN(ch_eq, operator==)
CH_COMPAREOP_GEN(ch_ne, operator!=)
CH_COMPAREOP_GEN(ch_lt, operator<)
CH_COMPAREOP_GEN(ch_gt, operator>)
CH_COMPAREOP_GEN(ch_le, operator<=)
CH_COMPAREOP_GEN(ch_ge, operator>=)

// logic operators

CH_BINOP_GEN(ch_and, operator&)
CH_BINOP_GEN(ch_or, operator|)
CH_BINOP_GEN(ch_xor, operator^)
CH_UNARYOP_GEN(ch_inv, operator~)

// arithmetic operators

CH_UNARYOP_GEN(ch_neg, operator-)
CH_BINOP_GEN(ch_add, operator+)
CH_BINOP_GEN(ch_sub, operator-)
CH_BINOP_GEN(ch_mult, operator*)
CH_BINOP_GEN(ch_div, operator/)
CH_BINOP_GEN(ch_mod, operator%)

// shift operators

CH_SHIFTOP_GEN(ch_sll, operator<<)
CH_SHIFTOP_GEN(ch_srl, operator>>)

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpBinary(const A& a, const B& b) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N, unsigned M, typename A, typename B>
const auto OpShift(const A& a, const B& b) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, M>(b)));
}

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpCompare(const A& a, const B& b) {
  return make_type<ch_bit<1>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N>
const auto OpUnary(const ch_bitbase<N>& a) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode(a)));
}

template <ch_alu_op op, unsigned N>
const auto OpReduce(const ch_bitbase<N>& a) {
  return make_type<ch_bit<1>>(createAluNode(op, get_lnode(a)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_inv(const ch_bitbase<N>& a) {
  return OpUnary<alu_inv>(a);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_nand(const A& a, const B& b) {
  return OpBinary<alu_nand, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_nor(const A& a, const B& b) {
  return OpBinary<alu_nor, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_and(const A& a, const B& b) {
  return OpBinary<alu_and, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_or(const A& a, const B& b) {
  return OpBinary<alu_or, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_xor(const A& a, const B& b) {
  return OpBinary<alu_xor, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_xnor(const A& a, const B& b) {
  return OpBinary<alu_xnor, deduce_type_t<A, B>::bitcount>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_andr(const ch_bitbase<N>& a) {
  return OpReduce<alu_andr>(a);
}

template <unsigned N>
const auto ch_orr(const ch_bitbase<N>& a) {
  return OpReduce<alu_orr>(a);
}

template <unsigned N>
const auto ch_xorr(const ch_bitbase<N>& a) {
  return OpReduce<alu_xorr>(a);
}

template <unsigned N>
const auto ch_nandr(const ch_bitbase<N>& a) {
  return OpReduce<alu_nandr>(a);
}

template <unsigned N>
const auto ch_norr(const ch_bitbase<N>& a) {
  return OpReduce<alu_norr>(a);
}

template <unsigned N>
const auto ch_xnorr(const ch_bitbase<N>& a) {
  return OpReduce<alu_xnorr>(a);
}

///////////////////////////////////////////////////////////////////////////////

inline const auto operator! (const ch_bitbase<1>& a) {
  return ch_inv(a);         
}

inline const auto operator&& (const ch_bitbase<1>& a, const ch_bitbase<1>& b) {
  return ch_and(a, b);      
}

inline const auto operator|| (const ch_bitbase<1>& a, const ch_bitbase<1>& b) {
  return ch_or(a, b);      
}

///////////////////////////////////////////////////////////////////////////////

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_eq(const A& a, const B& b) {
  return OpCompare<alu_eq, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_ne(const A& a, const B& b) {
  return OpCompare<alu_ne, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_lt(const A& a, const B& b) {
  return OpCompare<alu_lt, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_gt(const A& a, const B& b) {
  return OpCompare<alu_gt, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_ge(const A& a, const B& b) {
  return OpCompare<alu_ge, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_le(const A& a, const B& b) {
  return OpCompare<alu_le, deduce_type_t<A, B>::bitcount>(a, b);
}  

///////////////////////////////////////////////////////////////////////////////

template <typename A, typename B,
          CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)>
const auto ch_sll(const A& a, const B& b) {
  return OpShift<alu_sll, deduce_first_type_t<A, B>::bitcount, deduce_first_type_t<B, A>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)>
const auto ch_srl(const A& a, const B& b) {
  return OpShift<alu_srl, deduce_first_type_t<A, B>::bitcount, deduce_first_type_t<B, A>::bitcount>(a, b);
}  

template <typename A, typename B,
          CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)>
const auto ch_sra(const A& a, const B& b) {
  return OpShift<alu_sra, deduce_first_type_t<A, B>::bitcount, deduce_first_type_t<B, A>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)>
const auto ch_rotl(const A& a, const B& b) {
  return OpShift<alu_rotl, deduce_first_type_t<A, B>::bitcount, deduce_first_type_t<B, A>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_first_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_first_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_first_type_t<B, A>::bitcount>::value)>
const auto ch_rotr(const A& a, const B& b) {
  return OpShift<alu_rotr, deduce_first_type_t<A, B>::bitcount, deduce_first_type_t<B, A>::bitcount>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_neg(const ch_bitbase<N>& a) {
  return OpUnary<alu_neg>(a);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_add(const A& a, const B& b) {
  return OpBinary<alu_add, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_sub(const A& a, const B& b) {
  return OpBinary<alu_sub, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_mult(const A& a, const B& b) {
  return OpBinary<alu_mult, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_div(const A& a, const B& b) {
  return OpBinary<alu_div, deduce_type_t<A, B>::bitcount>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type_t<A, B>::bitcount != 0),
          CH_REQUIRES(is_bit_convertible<A, deduce_type_t<A, B>::bitcount>::value),
          CH_REQUIRES(is_bit_convertible<B, deduce_type_t<A, B>::bitcount>::value)>
const auto ch_mod(const A& a, const B& b) {
  return OpBinary<alu_mod, deduce_type_t<A, B>::bitcount>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned I, unsigned S>
const auto ch_mux(const ch_bitbase<I>& in, const ch_bitbase<S>& sel) {
  return make_type<ch_bit<(I >> S)>>(
        createAluNode(alu_mux, get_lnode(in), get_lnode(sel)));
}

}
}

#undef CH_BINOP_GEN0
#undef CH_BINOP_GEN1
#undef CH_BINOP_GEN2

#undef CH_UNARYOP_GEN

#undef CH_COMPAREOP_GEN0
#undef CH_COMPAREOP_GEN1

#undef CH_SHIFTOP_GEN0
#undef CH_SHIFTOP_GEN1
#undef CH_SHIFTOP_GEN2
