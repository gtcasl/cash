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
  template <unsigned N> ch_bit<N> func(const ch_bitbase<N>& a, type b) { return func(a, ch_bit<N>(b)); } \
  template <unsigned N> ch_bit<N> func(type a, const ch_bitbase<N>& b) { return func(ch_bit<N>(a), b); }

#define CH_BINOP_GEN1(func) \
  template <unsigned N, unsigned M> ch_bit<CH_MAX(N,M)> func(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(ch_zext<CH_MAX(N,M)>(a), ch_zext<CH_MAX(N,M)>(b)); } \
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
  template <unsigned N, unsigned M> ch_bit<CH_MAX(N,M)> op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(a, b); } \
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
  template <unsigned N> ch_bit<N> op(const ch_bitbase<N>& in) { return func(in); }

#define CH_COMPAREOP_GEN0(func, op, type) \
  template <unsigned N> ch_logic func(const ch_bitbase<N>& a, type b) { return func(a, ch_bit<N>(b)); } \
  template <unsigned N> ch_logic func(type a, const ch_bitbase<N>& b) { return func(ch_bit<N>(a), b); } \
  template <unsigned N> ch_logic op(const ch_bitbase<N>& a, type b) { return func(a, ch_bit<N>(b)); } \
  template <unsigned N> ch_logic op(type a, const ch_bitbase<N>& b) { return func(ch_bit<N>(a), b); }

#define CH_COMPAREOP_GEN1(func, op) \
  template <unsigned N> ch_logic op(const ch_bitbase<N>& a, const ch_bitbase<N>& b) { return func(a, b); } \
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
  template <unsigned N> ch_bit<N> func(const ch_bitbase<N>& a, type b) { return func(a, ch_bit<N>(b)); }

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
  template <unsigned N, unsigned M> ch_bit<N> op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(a, b); } \
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
namespace detail {

enum ch_alu_op {
  CH_ALUOP_ENUM(CH_ALUOP_TYPE)
};

lnodeimpl* createAluNode(ch_alu_op op, uint32_t size, lnodeimpl* a, lnodeimpl* b);
lnodeimpl* createAluNode(ch_alu_op op, uint32_t size, lnodeimpl* a);

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
ch_bit<N> OpBinary(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return ch_bit<N>(createAluNode(op, N, get_node(a).get_impl(), get_node(b).get_impl()));
}

template <ch_alu_op op, unsigned N>
ch_logic OpCompare(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return ch_logic(createAluNode(op, 1, get_node(a).get_impl(), get_node(b).get_impl()));
}

template <ch_alu_op op, unsigned N>
ch_bit<N> OpUnary(const ch_bitbase<N>& a) {
  return ch_bit<N>(createAluNode(op, N, get_node(a).get_impl()));
}

template <ch_alu_op op, unsigned N>
ch_logic OpReduce(const ch_bitbase<N>& a) {
  return ch_logic(createAluNode(op, 1, get_node(a).get_impl()));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
ch_bit<N> ch_inv(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_inv>(a);
}

template <unsigned N>
ch_bit<N> ch_nand(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_nand>(a, b);
}

template <unsigned N>
ch_bit<N> ch_nor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_nor>(a, b);
}

template <unsigned N>
ch_bit<N> ch_and(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_and>(a, b);
}

template <unsigned N>
ch_bit<N> ch_or(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_or>(a, b);
}

template <unsigned N>
ch_bit<N> ch_xor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_xor>(a, b);
}

template <unsigned N>
ch_bit<N> ch_xnor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_xnor>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
ch_logic ch_andr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_andr>(a);
}

template <unsigned N> 
ch_logic ch_orr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_orr>(a);
}

template <unsigned N> 
ch_logic ch_xorr(const ch_bitbase<N>& a) {
  return OpReduce<alu_op_xorr>(a);
}

///////////////////////////////////////////////////////////////////////////////

inline ch_logic operator! (const ch_logicbase& a) {
  return ch_inv(a);         
}

inline ch_logic operator&& (const ch_logicbase& a, const ch_logicbase& b) {
  return ch_and(a, b);      
}

inline ch_logic operator|| (const ch_logicbase& a, const ch_logicbase& b) {
  return ch_or(a, b);      
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
ch_logic ch_eq(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_eq>(a, b);
}

template <unsigned N> 
ch_logic ch_ne(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_ne>(a, b);
}

template <unsigned N>
ch_logic ch_lt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_lt>(a, b);
}

template <unsigned N>
ch_logic ch_gt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_gt>(a, b);
}

template <unsigned N>
ch_logic ch_ge(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_ge>(a, b);
}

template <unsigned N>
ch_logic ch_le(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<alu_op_le>(a, b);
}  

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned M>
ch_bit<N> ch_sll(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_shl>(a, b);
}

template <unsigned N, unsigned M>
ch_bit<N> ch_slr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_shr>(a, b);
}  

template <unsigned N, unsigned M>
ch_bit<N> ch_rotl(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_rotl>(a, b);
}

template <unsigned N, unsigned M>
ch_bit<N> ch_rotr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<alu_op_rotr>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
ch_bit<N> ch_add(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_add>(a, b);
}

template <unsigned N>
ch_bit<N> ch_sub(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_sub>(a, b);
}

template <unsigned N>
ch_bit<N> ch_neg(const ch_bitbase<N>& a) {
  return OpUnary<alu_op_neg>(a);
}

template <unsigned N>
ch_bit<N> ch_mult(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_mult>(a, b);
}

template <unsigned N>
ch_bit<N> ch_div(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_div>(a, b);
}

template <unsigned N>
ch_bit<N> ch_mod(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<alu_op_mod>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned S>
ch_bit<(N >> S)> ch_mux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  return ch_bit<(N >> S)>(createAluNode(alu_op_mux, (N >> S), get_node(in).get_impl(), get_node(sel).get_impl()));
}

template <unsigned N, unsigned S> 
ch_bit<(N << S)> ch_demux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  return ch_bit<(N << S)>(createAluNode(alu_op_mux, (N << S), get_node(in).get_impl(), get_node(sel).get_impl()));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
ch_bit<ilog2ceil(N)> ch_log2(const ch_bitbase<N>& a) {
  TODO("Not yet implemented!");
}

template <unsigned N> 
ch_bit<ilog2ceil(N)> ch_lsb(const ch_bitbase<N>& a) {
  TODO("Not yet implemented!");
}

template <unsigned N> 
ch_bit<ilog2ceil(N)> ch_enc(const ch_bitbase<N>& a) {
  TODO("Not yet implemented!");
}

template <unsigned N> 
ch_bit<(1 << N)> ch_dec(const ch_bitbase<N>& a) {
  TODO("Not yet implemented!");
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
