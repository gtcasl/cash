#pragma once

#include "bit.h"

#define CH_ALUOP_TYPE(t) alu_op_##t,
#define CH_ALUOP_ENUM(m) \
  m(inv) \
  m(and) \
  m(or) \
  m(xor) \
  m(nand) \
  m(nor) \
  m(xnor) \
  m(andr) \
  m(orr) \
  m(xorr) \
  m(shl) \
  m(shr) \
  m(rotl) \
  m(rotr) \
  m(add) \
  m(sub) \
  m(neg) \
  m(mult) \
  m(div) \
  m(mod) \
  m(eq) \
  m(ne) \
  m(lt) \
  m(gt) \
  m(le) \
  m(ge) \
  m(mux) \
  m(demux) \
  m(fadd) \
  m(fsub) \
  m(fmult) \
  m(fdiv)

#define CH_BINOP_GEN(func, op) \
  template <typename A, typename B, \
            CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
            CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
            CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
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
            CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
            CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
            CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
  const auto op(const A& a, const B& b) { \
    return func(a, b); \
  }

#define CH_SHIFTOP_GEN(func, op) \
  template <typename A, typename B, \
            CH_REQUIRES(first_bitcount<A, B>::value != 0), \
            CH_REQUIRES(is_weak_convertible<A, ch_bit<first_bitcount<A, B>::value>>::value), \
            CH_REQUIRES(is_weak_convertible<B, ch_bit<first_bitcount<B, A>::value>>::value)> \
  const auto op(const A& a, const B& b) { \
    return func(a, b); \
  }

namespace cash {
namespace internal {

enum ch_alu_op {
  CH_ALUOP_ENUM(CH_ALUOP_TYPE)
};

lnodeimpl* createAluNode(ch_alu_op op, const lnode& a, const lnode& b);
lnodeimpl* createAluNode(ch_alu_op op, const lnode& a);

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
CH_SHIFTOP_GEN(ch_slr, operator>>)

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpBinary(const A& a, const B& b) {
  return make_bit<N>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N, unsigned M, typename A, typename B>
const auto OpShift(const A& a, const B& b) {
  return make_bit<N>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, M>(b)));
}

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpCompare(const A& a, const B& b) {
  return make_bit<1>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N>
const auto OpUnary(const ch_bitbase<N>& a) {
  return make_bit<N>(createAluNode(op, get_lnode(a)));
}

template <ch_alu_op op, unsigned N>
const auto OpReduce(const ch_bitbase<N>& a) {
  return make_bit<1>(createAluNode(op, get_lnode(a)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_inv(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_inv>(a);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_nand(const A& a, const B& b) {
  return OpBinary<alu_op_nand, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_nor(const A& a, const B& b) {
  return OpBinary<alu_op_nor, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_and(const A& a, const B& b) {
  return OpBinary<alu_op_and, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_or(const A& a, const B& b) {
  return OpBinary<alu_op_or, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_xor(const A& a, const B& b) {
  return OpBinary<alu_op_xor, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_xnor(const A& a, const B& b) {
  return OpBinary<alu_op_xnor, deduce_bitcount<A, B>::value>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
const auto ch_andr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_andr>(a);
}

template <unsigned N> 
const auto ch_orr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_orr>(a);
}

template <unsigned N> 
const auto ch_xorr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_xorr>(a);
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
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_eq(const A& a, const B& b) {
  return OpCompare<alu_op_eq, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_ne(const A& a, const B& b) {
  return OpCompare<alu_op_ne, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_lt(const A& a, const B& b) {
  return OpCompare<alu_op_lt, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_gt(const A& a, const B& b) {
  return OpCompare<alu_op_gt, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_ge(const A& a, const B& b) {
  return OpCompare<alu_op_ge, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)>
const auto ch_le(const A& a, const B& b) {
  return OpCompare<alu_op_le, deduce_bitcount<A, B>::value>(a, b);
}  

///////////////////////////////////////////////////////////////////////////////

template <typename A, typename B,
          CH_REQUIRES(first_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<first_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<first_bitcount<B, A>::value>>::value)>
const auto ch_sll(const A& a, const B& b) {
  return OpShift<alu_op_shl, first_bitcount<A, B>::value, first_bitcount<B, A>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(first_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<first_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<first_bitcount<B, A>::value>>::value)>
const auto ch_slr(const A& a, const B& b) {
  return OpShift<alu_op_shr, first_bitcount<A, B>::value, first_bitcount<B, A>::value>(a, b);
}  

template <typename A, typename B,
          CH_REQUIRES(first_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<first_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<first_bitcount<B, A>::value>>::value)>
const auto ch_rotl(const A& a, const B& b) {
  return OpShift<alu_op_rotl, first_bitcount<A, B>::value, first_bitcount<B, A>::value>(a, b);
}

template <typename A, typename B,
          CH_REQUIRES(first_bitcount<A, B>::value != 0),
          CH_REQUIRES(is_weak_convertible<A, ch_bit<first_bitcount<A, B>::value>>::value),
          CH_REQUIRES(is_weak_convertible<B, ch_bit<first_bitcount<B, A>::value>>::value)>
const auto ch_rotr(const A& a, const B& b) {
  return OpShift<alu_op_rotr, first_bitcount<A, B>::value, first_bitcount<B, A>::value>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_neg(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_neg>(a);
}

template <typename A, typename B, \
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
const auto ch_add(const A& a, const B& b) {
  return OpBinary<alu_op_add, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B, \
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
const auto ch_sub(const A& a, const B& b) {
  return OpBinary<alu_op_sub, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B, \
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
const auto ch_mult(const A& a, const B& b) {
  return OpBinary<alu_op_mult, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B, \
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
const auto ch_div(const A& a, const B& b) {
  return OpBinary<alu_op_div, deduce_bitcount<A, B>::value>(a, b);
}

template <typename A, typename B, \
          CH_REQUIRES(deduce_bitcount<A, B>::value != 0), \
          CH_REQUIRES(is_weak_convertible<A, ch_bit<deduce_bitcount<A, B>::value>>::value), \
          CH_REQUIRES(is_weak_convertible<B, ch_bit<deduce_bitcount<A, B>::value>>::value)> \
const auto ch_mod(const A& a, const B& b) {
  return OpBinary<alu_op_mod, deduce_bitcount<A, B>::value>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <typename I, typename S,
          CH_REQUIRES(is_weak_convertible<I, ch_bit<I::bitcount>>::value),
          CH_REQUIRES(is_weak_convertible<S, ch_bit<S::bitcount>>::value)>
const auto ch_mux(const I& in, const S& sel) {
  return make_bit<(I::bitcount >> S::bitcount)>(
        createAluNode(alu_op_mux, get_lnode(in), get_lnode(sel)));
}

template <typename I, typename S,
          CH_REQUIRES(is_weak_convertible<I, ch_bit<I::bitcount>>::value),
          CH_REQUIRES(is_weak_convertible<S, ch_bit<S::bitcount>>::value)>
const auto ch_demux(const I& in, const S& sel) {
  return make_bit<(I::bitcount << S::bitcount)>(
        createAluNode(alu_op_mux, get_lnode(in), get_lnode(sel)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
const auto ch_log2(const ch_bitbase<N>& a) {
  CH_TODO();
}

template <unsigned N> 
const auto ch_lsb(const ch_bitbase<N>& a) {
  CH_TODO();
}

template <unsigned N> 
const auto ch_enc(const ch_bitbase<N>& a) {
  CH_TODO();
}

template <unsigned N> 
const auto ch_dec(const ch_bitbase<N>& a) {
  CH_TODO();
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
