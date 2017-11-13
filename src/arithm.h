#pragma once

#include "lnode.h"

#define ALTFP_SP_ADD_SUB 14
#define ALTFP_SP_MULT    11
#define ALTFP_SP_DIV     13

#define CH_ALUOP_ARY(x)   (x & (0x7 <<  8))
#define CH_ALUOP_CLASS(x) (x & (0x7 << 11))
#define CH_ALUOP_DTYPE(x) (x & (0x7 << 14))

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

namespace ch {
namespace internal {

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

enum ch_alu_op {
  CH_ALUOP_ENUM(CH_ALUOP_TYPE)
};

const char* to_string(ch_alu_op op);

lnodeimpl* createAluNode(ch_alu_op op, const lnode& in, unsigned delay = 0);

lnodeimpl* createAluNode(ch_alu_op op, const lnode& lhs, const lnode& rhs, unsigned delay = 0);

}
}

///////////////////////////////////////////////////////////////////////////////

#define CH_FRIEND_OPERATORS(func, header, lhs_t, rhs_t, body) \
  header \
  inline friend const auto func(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<lhs_t>>(_rhs); \
    return body; \
  } \
  header \
  inline friend const auto func(rhs_t _lhs, lhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<lhs_t>>(_lhs); \
    return body; \
  }

#define CH_GLOBAL_OPERATORS(func, header, lhs_t, rhs_t, body) \
  header \
  inline const auto func(lhs_t lhs, rhs_t _rhs) { \
    auto rhs = static_cast<std::decay_t<lhs_t>>(_rhs); \
    return body; \
  } \
  header \
  inline const auto func(rhs_t _lhs, lhs_t rhs) { \
    auto lhs = static_cast<std::decay_t<lhs_t>>(_lhs); \
    return body; \
  }

#define CH_FRIEND_OP_EQ(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator==, header, lhs_t, rhs_t, (lhs == rhs))

#define CH_GLOBAL_OP_EQ(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_eq, header, lhs_t, rhs_t, ch_eq(lhs, rhs))

#define CH_FRIEND_OP_NE(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator!=, header, lhs_t, rhs_t, (lhs != rhs))

#define CH_GLOBAL_OP_NE(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_ne, header, lhs_t, rhs_t, ch_ne(lhs, rhs))

#define CH_FRIEND_OP_LT(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator<, header, lhs_t, rhs_t, (lhs < rhs))

#define CH_GLOBAL_OP_LT(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_lt, header, lhs_t, rhs_t, ch_lt(lhs, rhs))

#define CH_FRIEND_OP_LE(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator<=, header, lhs_t, rhs_t, (lhs <= rhs))

#define CH_GLOBAL_OP_LE(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_le, header, lhs_t, rhs_t, ch_le(lhs, rhs))

#define CH_FRIEND_OP_GT(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator>, header, lhs_t, rhs_t, (lhs > rhs))

#define CH_GLOBAL_OP_GT(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_gt, header, lhs_t, rhs_t, ch_gt(lhs, rhs))

#define CH_FRIEND_OP_GE(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator>=, header, lhs_t, rhs_t, (lhs >= rhs))

#define CH_GLOBAL_OP_GE(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_ge, header, lhs_t, rhs_t, ch_ge(lhs, rhs))


#define CH_FRIEND_OP_AND(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator&&, header, lhs_t, rhs_t, (lhs && rhs)) \
  CH_FRIEND_OPERATORS(operator&, header, lhs_t, rhs_t, (lhs & rhs))

#define CH_GLOBAL_OP_AND(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_and, header, lhs_t, rhs_t, ch_and(lhs, rhs))

#define CH_FRIEND_OP_OR(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator||, header, lhs_t, rhs_t, (lhs || rhs)) \
  CH_FRIEND_OPERATORS(operator|, header, lhs_t, rhs_t, (lhs | rhs))

#define CH_GLOBAL_OP_OR(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_or, header, lhs_t, rhs_t, ch_or(lhs, rhs))

#define CH_FRIEND_OP_XOR(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator^, header, lhs_t, rhs_t, (lhs ^ rhs))

#define CH_GLOBAL_OP_XOR(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_xor, header, lhs_t, rhs_t, ch_xor(lhs, rhs))


#define CH_GLOBAL_OP_NAND(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_nand, header, lhs_t, rhs_t, ch_nand(lhs, rhs))

#define CH_GLOBAL_OP_NOR(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_nor, header, lhs_t, rhs_t, ch_nor(lhs, rhs))

#define CH_GLOBAL_OP_XNOR(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_xnor, header, lhs_t, rhs_t, ch_xnor(lhs, rhs))


#define CH_FRIEND_OP_ADD(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator+, header, lhs_t, rhs_t, (lhs + rhs))

#define CH_GLOBAL_OP_ADD(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_add, header, lhs_t, rhs_t, ch_add(lhs, rhs))

#define CH_FRIEND_OP_SUB(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator-, header, lhs_t, rhs_t, (lhs - rhs))

#define CH_GLOBAL_OP_SUB(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_sub, header, lhs_t, rhs_t, ch_sub(lhs, rhs))

#define CH_FRIEND_OP_MULT(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator*, header, lhs_t, rhs_t, (lhs * rhs))

#define CH_GLOBAL_OP_MULT(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_mult, header, lhs_t, rhs_t, ch_mult(lhs, rhs))

#define CH_FRIEND_OP_DIV(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator/, header, lhs_t, rhs_t, (lhs / rhs))

#define CH_GLOBAL_OP_DIV(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_div, header, lhs_t, rhs_t, ch_div(lhs, rhs))

#define CH_FRIEND_OP_MOD(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator%, header, lhs_t, rhs_t, (lhs % rhs))

#define CH_GLOBAL_OP_MOD(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_mod, header, lhs_t, rhs_t, ch_mod(lhs, rhs))


#define CH_FRIEND_OP_SLL(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator<<, header, lhs_t, rhs_t, (lhs << rhs))

#define CH_GLOBAL_OP_SLL(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_sll, header, lhs_t, rhs_t, ch_sll(lhs, rhs))

#define CH_FRIEND_OP_SRL(header, lhs_t, rhs_t) \
  CH_FRIEND_OPERATORS(operator>>, header, lhs_t, rhs_t, (lhs >> rhs))

#define CH_GLOBAL_OP_SRL(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_srl, header, lhs_t, rhs_t, ch_srl(lhs, rhs))

#define CH_GLOBAL_OP_SRA(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_sra, header, lhs_t, rhs_t, ch_sra(lhs, rhs))

#define CH_GLOBAL_OP_ROTL(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_rotl, header, lhs_t, rhs_t, ch_rotl(lhs, rhs))

#define CH_GLOBAL_OP_ROTR(header, lhs_t, rhs_t) \
  CH_GLOBAL_OPERATORS(ch_rotr, header, lhs_t, rhs_t, ch_rotr(lhs, rhs))
