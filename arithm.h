#pragma once

#include "bitv.h"

#define CHDL_BINOP_GEN(op, func) \
  template <unsigned N, unsigned M> ch_bitv<CHDL_MAX(N,M)> func(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(ch_zext<CHDL_MAX(N,M)>(a), ch_zext<CHDL_MAX(N,M)>(b)); } \
  template <unsigned N> ch_bitv<N> func(uint32_t a, const ch_bitbase<N>& b) { return func(ch_bitv<N>(a), b); } \
  template <unsigned N> ch_bitv<N> func(const ch_bitbase<N>& a, uint32_t b) { return func(a, ch_bitv<N>(b)); } \
  template <unsigned N, unsigned M> ch_bitv<CHDL_MAX(N,M)> op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(a, b); } \
  template <unsigned N> ch_bitv<N> op(uint32_t a, const ch_bitbase<N>& b) { return func(ch_bitv<N>(a), b); } \
  template <unsigned N> ch_bitv<N> op(const ch_bitbase<N>& a, uint32_t b) { return func(a, ch_bitv<N>(b)); }

#define CHDL_UNARYOP_GEN(op, func) \
  template <unsigned N> ch_bitv<N> op(const ch_bitbase<N>& in) { return func(in); }
  
#define CHDL_COMPAREOP_GEN(op, func) \
  template <unsigned N> ch_logic func(uint32_t a, const ch_bitbase<N>& b) { return func(ch_bitv<N>(a), b); } \
  template <unsigned N> ch_logic func(const ch_bitbase<N>& a, uint32_t b) { return func(a, ch_bitv<N>(b)); } \
  template <unsigned N> ch_logic op(const ch_bitbase<N>& a, const ch_bitbase<N>& b) { return func(a, b); } \
  template <unsigned N> ch_logic op(uint32_t a, const ch_bitbase<N>& b) { return func(a, b); } \
  template <unsigned N> ch_logic op(const ch_bitbase<N>& a, uint32_t b) { return func(a, b); }

#define CHDL_SHIFTOP_GEN(op, func) \
  template <unsigned N> ch_bitv<N> func(const ch_bitbase<N>& a, uint32_t b) { return func(a, ch_bitv<N>(b)); } \
  template <unsigned N, unsigned M> ch_bitv<N> op(const ch_bitbase<N>& a, const ch_bitbase<M>& b) { return func(a, b); } \
  template <unsigned N> ch_bitv<N> op(const ch_bitbase<N>& a, uint32_t b) { return func(a, ch_bitv<N>(b)); }

#define CHDL_REDUCEOP_GEN(op, func) \
  template <unsigned N> ch_logic op(const ch_bitv<N>& in) { return func(in); }

namespace chdl_internal {

enum ch_operator {
  op_inv,
  op_and,
  op_or,
  op_xor,
  op_nand,
  op_nor,
  op_xnor,
  op_andr,
  op_orr,
  op_xorr,
  op_sll,
  op_slr,
  op_rotl,
  op_rotr,
  op_add,
  op_sub,
  op_neg,
  op_mult,
  op_div,
  op_mod,
  op_eq,
  op_ne,
  op_lt,
  op_gt,
  op_le,
  op_ge,
};

ch_node createAluNode(ch_operator op, uint32_t size, const ch_node& a, const ch_node& b);
ch_node createAluNode(ch_operator op, uint32_t size, const ch_node& a);

// compare operators

CHDL_COMPAREOP_GEN(operator==, ch_eq)
CHDL_COMPAREOP_GEN(operator!=, ch_ne)
CHDL_COMPAREOP_GEN(operator<,  ch_lt)
CHDL_COMPAREOP_GEN(operator>,  ch_gt)
CHDL_COMPAREOP_GEN(operator<=, ch_le)
CHDL_COMPAREOP_GEN(operator>=, ch_ge)

// ch_logic operators

CHDL_BINOP_GEN(operator&, ch_and)
CHDL_BINOP_GEN(operator|, ch_or)
CHDL_BINOP_GEN(operator^, ch_xor)
CHDL_UNARYOP_GEN(operator~, ch_inv)

// arithmetic operators

CHDL_UNARYOP_GEN(operator-, ch_neg)
CHDL_BINOP_GEN(operator+, ch_add)
CHDL_BINOP_GEN(operator-, ch_sub)
CHDL_BINOP_GEN(operator*, ch_mult)
CHDL_BINOP_GEN(operator/, ch_div)
CHDL_BINOP_GEN(operator%, ch_mod)

// shift operators

CHDL_SHIFTOP_GEN(operator<<, ch_sll)
CHDL_SHIFTOP_GEN(operator>>, ch_slr)

///////////////////////////////////////////////////////////////////////////////

template <ch_operator op, unsigned N, unsigned M>
ch_bitv<N> OpBinary(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return ch_bitv<N>(createAluNode(op, N, ch_bitv<N>(a), ch_bitv<M>(b)));
}

template <ch_operator op, unsigned N>
ch_logic OpCompare(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return ch_logic(createAluNode(op, 1, ch_bitv<N>(a), ch_bitv<N>(b)));
}

template <ch_operator op, unsigned N>
ch_bitv<N> OpUnary(const ch_bitbase<N>& a) {
  return ch_bitv<N>(createAluNode(op, N, ch_bitv<N>(a)));
}

template <ch_operator op, unsigned N>
ch_bitv<N> OpReduce(const ch_bitbase<N>& a) {
  return ch_bitv<N>(createAluNode(op, 1, ch_bitv<N>(a)));
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
ch_bitv<N> ch_inv(const ch_bitbase<N>& a) {
  return OpUnary<op_inv>(a);
}

template <unsigned N>
ch_bitv<N> ch_nand(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_nand>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_nor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_nor>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_and(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_and>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_or(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_or>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_xor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_xor>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_xnor(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_xnor>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
ch_logic ch_andr(const ch_bitbase<N>& a) {
  return OpReduce<op_andr>(a);
}

template <unsigned N> 
ch_logic ch_orr(const ch_bitbase<N>& a) {
  return OpReduce<op_orr>(a);
}

template <unsigned N> 
ch_logic ch_xorr(const ch_bitbase<N>& a) {
  return OpReduce<op_xorr>(a);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> 
ch_logic ch_eq(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_eq>(a, b);
}

template <unsigned N> 
ch_logic ch_ne(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_ne>(a, b);
}

template <unsigned N>
ch_logic ch_lt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_lt>(a, b);
}

template <unsigned N>
ch_logic ch_gt(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_gt>(a, b);
}

template <unsigned N>
ch_logic ch_ge(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_ge>(a, b);
}

template <unsigned N>
ch_logic ch_le(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpCompare<op_le>(a, b);
}  

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned M>
ch_bitv<N> ch_sll(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<op_sll>(a, b);
}

template <unsigned N, unsigned M>
ch_bitv<N> ch_slr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<op_slr>(a, b);
}  

template <unsigned N, unsigned M>
ch_bitv<N> ch_rotl(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<op_rotl>(a, b);
}

template <unsigned N, unsigned M>
ch_bitv<N> ch_rotr(const ch_bitbase<N>& a, const ch_bitbase<M>& b) {
  return OpBinary<op_rotr>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
ch_bitv<N> ch_add(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_add>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_sub(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_sub>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_neg(const ch_bitbase<N>& a) {
  return OpUnary<op_neg>(a);
}

template <unsigned N>
ch_bitv<N> ch_mult(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_mult>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_div(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_div>(a, b);
}

template <unsigned N>
ch_bitv<N> ch_mod(const ch_bitbase<N>& a, const ch_bitbase<N>& b) {
  return OpBinary<op_mod>(a, b);
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, unsigned S>
ch_bitv<(N >> S)> ch_mux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  TODO();
}

template <unsigned N, unsigned S> 
ch_bitv<(N << S)> ch_demux(const ch_bitbase<N>& in, const ch_bitbase<S>& sel) {
  TODO();
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
ch_bitv<CLOG2(N)> ch_penc(ch_logic& valid, const ch_bitbase<N>& a, bool reverse = false) {
  TODO();
}

template <unsigned N> 
ch_bitv<CLOG2(N)> ch_log2(const ch_bitbase<N>& a) {
  TODO();
}

template <unsigned N> 
ch_bitv<CLOG2(N)> ch_lsb(const ch_bitbase<N>& a) {
  TODO();
}

template <unsigned N> 
ch_bitv<CLOG2(N)> ch_enc(const ch_bitbase<N>& a) {
  TODO();
}

///////////////////////////////////////////////////////////////////////////////

inline ch_bitv<1> operator! (const ch_bitbase<1>& a) {
  return ch_inv(a);         
}

inline ch_bitv<1> operator&& (const ch_bitbase<1>& a, const ch_bitbase<1>& b) {
  return ch_and(a, b);      
}

inline ch_bitv<1> operator|| (const ch_bitbase<1>& a, const ch_bitbase<1>& b) {
  return ch_or(a, b);      
}

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
void ch_print(const ch_bitbase<N>& a) {
  TODO();
}

}

#undef CHDL_BINOP_GEN
#undef CHDL_UNARYOP_GEN  
#undef CHDL_COMPAREOP_GEN
#undef CHDL_SHIFTOP_GEN
#undef CHDL_REDUCEOP_GEN
#undef CHDL_CONCAT_GEN
