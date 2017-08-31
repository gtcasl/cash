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

#define CH_BINOP_GEN0(func, type) \
  template <unsigned N> \
  const auto func(const ch_bitbase<N>& a, type b) { \
    return func(a, ch_bit<N>(b));\
  } \
  template <unsigned N> \
  const auto func(type a, const ch_bitbase<N>& b) { \
    return func(ch_bit<N>(a), b); \
  }

#define CH_BINOP_GEN1(func) \
  template <unsigned N, unsigned M> \
  const auto func(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { \
    return func(ch_zext<CH_MAX(N,M)>(a), ch_zext<CH_MAX(N,M)>(b)); \
  } \
  CH_BINOP_GEN0(func, char) \
  CH_BINOP_GEN0(func, int8_t) \
  CH_BINOP_GEN0(func, uint8_t) \
  CH_BINOP_GEN0(func, int16_t) \
  CH_BINOP_GEN0(func, uint16_t) \
  CH_BINOP_GEN0(func, int32_t) \
  CH_BINOP_GEN0(func, uint32_t) \
  CH_BINOP_GEN0(func, int64_t) \
  CH_BINOP_GEN0(func, uint64_t)

#define CH_BINOP_GEN2(func, op) \
  CH_BINOP_GEN1(func) \
  template <unsigned N, unsigned M> \
  const auto op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { \
    return func(a, b); \
  } \
  CH_BINOP_GEN0(op, char) \
  CH_BINOP_GEN0(op, int8_t) \
  CH_BINOP_GEN0(op, uint8_t) \
  CH_BINOP_GEN0(op, int16_t) \
  CH_BINOP_GEN0(op, uint16_t) \
  CH_BINOP_GEN0(op, int32_t) \
  CH_BINOP_GEN0(op, uint32_t) \
  CH_BINOP_GEN0(op, int64_t) \
  CH_BINOP_GEN0(op, uint64_t)

#define CH_UNARYOP_GEN(func, op) \
  template <unsigned N> \
  const auto op(const ch_bitbase<N>& in) { \
    return func(in); \
  }

#define CH_COMPAREOP_GEN0(func, op, type) \
  template <unsigned N> \
  const auto func(const ch_bitbase<N>& a, type b) { \
    return func(a, ch_bit<N>(b)); \
  } \
  template <unsigned N> \
  const auto func(type a, const ch_bitbase<N>& b) { \
    return func(ch_bit<N>(a), b); \
  } \
  template <unsigned N> \
  const auto op(const ch_bitbase<N>& a, type b) { \
    return func(a, ch_bit<N>(b)); \
  } \
  template <unsigned N> \
  const auto op(type a, const ch_bitbase<N>& b) { \
    return func(ch_bit<N>(a), b); \
  }

#define CH_COMPAREOP_GEN1(func, op) \
  template <unsigned N> \
  const auto op(const ch_bitbase<N>& a, const ch_bitbase<N>& b) { \
    return func(a, b); \
  } \
  CH_COMPAREOP_GEN0(func, op, char) \
  CH_COMPAREOP_GEN0(func, op, int8_t) \
  CH_COMPAREOP_GEN0(func, op, uint8_t) \
  CH_COMPAREOP_GEN0(func, op, int16_t) \
  CH_COMPAREOP_GEN0(func, op, uint16_t) \
  CH_COMPAREOP_GEN0(func, op, int32_t) \
  CH_COMPAREOP_GEN0(func, op, uint32_t) \
  CH_COMPAREOP_GEN0(func, op, int64_t) \
  CH_COMPAREOP_GEN0(func, op, uint64_t)

#define CH_SHIFTOP_GEN0(func, type) \
  template <unsigned N> \
  const auto func(const ch_bitbase<N>& a, type b) { \
    return func(a, ch_bit<N>(b)); \
  }

#define CH_SHIFTOP_GEN1(func) \
  CH_SHIFTOP_GEN0(func, char) \
  CH_SHIFTOP_GEN0(func, int8_t) \
  CH_SHIFTOP_GEN0(func, uint8_t) \
  CH_SHIFTOP_GEN0(func, int16_t) \
  CH_SHIFTOP_GEN0(func, uint16_t) \
  CH_SHIFTOP_GEN0(func, int32_t) \
  CH_SHIFTOP_GEN0(func, uint32_t) \
  CH_SHIFTOP_GEN0(func, int64_t) \
  CH_SHIFTOP_GEN0(func, uint64_t)

#define CH_SHIFTOP_GEN2(func, op) \
  CH_SHIFTOP_GEN1(func) \
  template <unsigned N, unsigned M> \
  const auto op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { \
    return func(a, b); \
  } \
  CH_SHIFTOP_GEN0(op, char) \
  CH_SHIFTOP_GEN0(op, int8_t) \
  CH_SHIFTOP_GEN0(op, uint8_t) \
  CH_SHIFTOP_GEN0(op, int16_t) \
  CH_SHIFTOP_GEN0(op, uint16_t) \
  CH_SHIFTOP_GEN0(op, int32_t) \
  CH_SHIFTOP_GEN0(op, uint32_t) \
  CH_SHIFTOP_GEN0(op, int64_t) \
  CH_SHIFTOP_GEN0(op, uint64_t)

namespace cash {
namespace internal {

enum ch_alu_op {
  CH_ALUOP_ENUM(CH_ALUOP_TYPE)
};

lnodeimpl* createAluNode(ch_alu_op op, const lnode& a, const lnode& b);
lnodeimpl* createAluNode(ch_alu_op op, const lnode& a);

// compare operators

CH_COMPAREOP_GEN1(ch_eq, operator==)
CH_COMPAREOP_GEN1(ch_ne, operator!=)
CH_COMPAREOP_GEN1(ch_lt, operator<)
CH_COMPAREOP_GEN1(ch_gt, operator>)
CH_COMPAREOP_GEN1(ch_le, operator<=)
CH_COMPAREOP_GEN1(ch_ge, operator>=)

// logic operators

CH_BINOP_GEN2(ch_and, operator&)
CH_BINOP_GEN2(ch_or, operator|)
CH_BINOP_GEN2(ch_xor, operator^)
CH_UNARYOP_GEN(ch_inv, operator~)
CH_BINOP_GEN1(ch_nand)
CH_BINOP_GEN1(ch_nor)
CH_BINOP_GEN1(ch_xnor)

// arithmetic operators

CH_UNARYOP_GEN(ch_neg, operator-)
CH_BINOP_GEN2(ch_add, operator+)
CH_BINOP_GEN2(ch_sub, operator-)
CH_BINOP_GEN2(ch_mult, operator*)
CH_BINOP_GEN2(ch_div, operator/)
CH_BINOP_GEN2(ch_mod, operator%)

// shift operators

CH_SHIFTOP_GEN2(ch_sll, operator<<)
CH_SHIFTOP_GEN2(ch_slr, operator>>)
CH_SHIFTOP_GEN1(ch_rotl)
CH_SHIFTOP_GEN1(ch_rotr)

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op, unsigned N, unsigned M>
const auto OpBinary(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return make_bit<N>(createAluNode(op, get_node(a), get_node(b)));
}

template <ch_alu_op op, unsigned N>
const auto OpCompare(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return make_bit<1>(createAluNode(op, get_node(a), get_node(b)));
}

template <ch_alu_op op, unsigned N>
const auto OpUnary(const ch_bitbase<N>& a) {
  return make_bit<N>(createAluNode(op, get_node(a)));
}

template <ch_alu_op op, unsigned N>
const auto OpReduce(const ch_bitbase<N>& a) {
  return make_bit<1>(createAluNode(op, get_node(a)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_inv(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_inv>(a);
}

template <unsigned N>
const auto ch_nand(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_nand>(a, b);
}

template <unsigned N>
const auto ch_nor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_nor>(a, b);
}

template <unsigned N>
const auto ch_and(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_and>(a, b);
}

template <unsigned N>
const auto ch_or(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_or>(a, b);
}

template <unsigned N>
const auto ch_xor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_xor>(a, b);
}

template <unsigned N>
const auto ch_xnor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_xnor>(a, b);
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

template <unsigned N> 
const auto ch_eq(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_eq>(a, b);
}

template <unsigned N> 
const auto ch_ne(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_ne>(a, b);
}

template <unsigned N>
const auto ch_lt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_lt>(a, b);
}

template <unsigned N>
const auto ch_gt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_gt>(a, b);
}

template <unsigned N>
const auto ch_ge(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_ge>(a, b);
}

template <unsigned N>
const auto ch_le(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_le>(a, b);
}  

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned M>
const auto ch_sll(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_shl>(a, b);
}

template <unsigned N, unsigned M>
const auto ch_slr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_shr>(a, b);
}  

template <unsigned N, unsigned M>
const auto ch_rotl(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_rotl>(a, b);
}

template <unsigned N, unsigned M>
const auto ch_rotr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_rotr>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
const auto ch_add(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_add>(a, b);
}

template <unsigned N>
const auto ch_sub(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_sub>(a, b);
}

template <unsigned N>
const auto ch_neg(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_neg>(a);
}

template <unsigned N>
const auto ch_mult(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_mult>(a, b);
}

template <unsigned N>
const auto ch_div(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_div>(a, b);
}

template <unsigned N>
const auto ch_mod(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_mod>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned S>
const auto ch_mux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  return make_bit<(N >> S)>(createAluNode(alu_op_mux, get_node(in), get_node(sel)));
}

template <unsigned N, unsigned S> 
const auto ch_demux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  return make_bit<(N << S)>(createAluNode(alu_op_mux, get_node(in), get_node(sel)));
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
