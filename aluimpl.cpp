#include "aluimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

#define CHDL_ALUOP_NAME(n) case alu_op_##n: return op_##n;

static ch_operator to_operator(ch_alu_operator op) {
  switch (op) {
    CHDL_ALUOP_ENUM(CHDL_ALUOP_NAME)
  }
}

template <ch_alu_operator op>
static void unaryop(bitvector& dst, const bitvector& a) {
  assert(dst.get_size() == a.get_size());
  
  switch (op) {
  case alu_op_inv:
    Invert(dst, a);
    break;
  default:
    TODO("Not yet implemented!");
  }
}

template <ch_alu_operator op>
static void binaryop(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == a.get_size());
  assert(a.get_size() == b.get_size());
  
  switch (op) {
  case alu_op_and:
    And(dst, a, b);
    break;
  case alu_op_or:
    Or(dst, a, b);
    break;
  case alu_op_xor:
    Xor(dst, a, b);
    break;
  case alu_op_nand:
    Nand(dst, a, b);
    break;
  case alu_op_nor:
    Nor(dst, a, b);
    break;
  case alu_op_xnor:
    Xnor(dst, a, b);
    break;
  default:
    TODO("Not yet implemented!");
  }
}

template <ch_alu_operator op>
static void shiftop(bitvector& dst, const bitvector& in, const bitvector& bits) {  
  assert(dst.get_size() == in.get_size());
  CHDL_CHECK(bits.find_last() <= 31, "shift amount out of range!");
  
  uint32_t wbits = bits.get_word(0);
  switch (op) {  
  case alu_op_shl:
    ShiftLeft(dst, in, wbits);
    break;
  case alu_op_shr:
    ShiftRight(dst, in, wbits);
    break;
  case alu_op_rotl:
    RotateLeft(dst, in, wbits);
    break;
  case alu_op_rotr:
    RotateRight(dst, in, wbits);
    break;
  default:
    TODO("Not yet implemented!");
  }
}

template <ch_alu_operator op>
static void reduceop(bitvector& dst, const bitvector& in) {
  assert(dst.get_size() == 1);
  
  bool result;
  switch (op) {
  case alu_op_andr:
    result = in.andr();
    break;
  case alu_op_orr:
    result = in.orr();
    break;
  case alu_op_xorr:
    result = in.xorr();
    break;
  default:
    TODO("Not yet implemented!");
  } 
  dst[0] = result;
}

template <ch_alu_operator op>
static void compareop(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 1);
  assert(a.get_size() == b.get_size());
  
  bool result;
  switch (op) {
  case alu_op_eq:
    result = a == b;
    break;
  case alu_op_ne:
    result = a != b;
    break;
  case alu_op_lt:
    result = a < b;
    break;
  case alu_op_gt:
    result = a > b;
    break;
  case alu_op_le:
    result = a <= b;
    break;
  case alu_op_ge:
    result = a >= b;
    break;
  default:
    TODO("Not yet implemented!");
  }
  dst[0] = result;
}

static void add(bitvector& dst, const bitvector& a, const bitvector& b, uint32_t cin = 0) {
  assert(dst.get_size() == a.get_size());
  assert(a.get_size() == b.get_size());
  
  uint32_t size = dst.get_size();
  uint32_t num_words = ((size + 31) >> 5);
  
  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t b_w = b.get_word(i);
    uint32_t c_w = a_w + b_w;
  
    uint32_t cout = 0;
    if (size < bitvector::WORD_SIZE)  {
      c_w += cin;
      c_w &= ~(1 << size); // remove overflow bit
    } else {
      if (c_w < a_w)
        cout = 1;
      c_w += cin;
      if (c_w < cin)
        cout = 1;
      size -= 32;
      cin = cout;
    }    
    dst.set_word(i, c_w);
  }
}

///////////////////////////////////////////////////////////////////////////////

static void fadd(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);  
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef + b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fsub(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);  
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef - b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fmult(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);  
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef * b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fdiv(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);  
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef / b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

///////////////////////////////////////////////////////////////////////////////

static void mux(bitvector& dst, const bitvector& in, const bitvector& sel) {
  uint32_t D = dst.get_size();
  uint32_t N = in.get_size();
  uint32_t S = sel.get_size();
  assert(D == N >> S);
  
  assert(sel.get_num_words() == 1);
  uint32_t offset = sel.get_word(0) * D;
  assert(offset + D <= N);
  
  bitvector::const_iterator iter_in(in.begin() + offset);
  bitvector::iterator iter_dst(dst.begin());
  for (uint32_t i = 0; i < D; ++i) {
    *iter_dst++ = *iter_in++;
  }
}

static void demux(bitvector& dst, const bitvector& in, const bitvector& sel) {
  TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(ch_alu_operator alu_op, uint32_t size, lnodeimpl* a, lnodeimpl* b) 
  : lnodeimpl(to_operator(alu_op), a->get_ctx(), size)
  , m_alu_op(alu_op)
  , m_ctime(~0ull) {
  m_srcs.emplace_back(a);
  m_srcs.emplace_back(b);
}

aluimpl::aluimpl(ch_alu_operator alu_op, uint32_t size, lnodeimpl* a) 
  : lnodeimpl(to_operator(alu_op), a->get_ctx(), size)
  , m_alu_op(alu_op)
  , m_ctime(~0ull) {
  m_srcs.emplace_back(a);
}

const bitvector& aluimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {  
    m_ctime = t;
    
    switch (m_alu_op) {
    case alu_op_inv:
      unaryop<alu_op_inv>(m_value, m_srcs[0].eval(t));  
      break;
    case alu_op_and:
      binaryop<alu_op_and>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));  
      break;
    case alu_op_or:
      binaryop<alu_op_or>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case alu_op_xor:
      binaryop<alu_op_xor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case alu_op_nand:
      binaryop<alu_op_nand>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));  
      break;
    case alu_op_nor:
      binaryop<alu_op_nor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case alu_op_xnor:
      binaryop<alu_op_xnor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    
    case alu_op_andr:
      reduceop<alu_op_andr>(m_value, m_srcs[0].eval(t));  
      break;
    case alu_op_orr:
      reduceop<alu_op_orr>(m_value, m_srcs[0].eval(t));        
      break;
    case alu_op_xorr:
      reduceop<alu_op_xorr>(m_value, m_srcs[0].eval(t));        
      break;
      
    case alu_op_shl:
      shiftop<alu_op_shl>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_shr:
      shiftop<alu_op_shr>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_rotl:
      shiftop<alu_op_rotl>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_rotr:
      shiftop<alu_op_rotr>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    case alu_op_add:
      add(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case alu_op_sub:{
        bitvector minus_b(m_value.get_size());
        unaryop<alu_op_inv>(minus_b, m_srcs[1].eval(t));
        add(m_value, m_srcs[0].eval(t), minus_b, 1);        
      } break;
    case alu_op_mult:
    case alu_op_div:
    case alu_op_mod:
      TODO("Not yet implemented!");
      break;
      
    case alu_op_eq:
      compareop<alu_op_eq>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_ne:
      compareop<alu_op_ne>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_lt:
      compareop<alu_op_lt>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_gt:
      compareop<alu_op_gt>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_le:
      compareop<alu_op_le>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));  
      break;
    case alu_op_ge:
      compareop<alu_op_ge>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;  
      
    case alu_op_mux:
      mux(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case alu_op_demux:
      demux(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    case alu_op_fadd:
      fadd(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    case alu_op_fsub:
      fsub(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    case alu_op_fmult:
      fmult(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    case alu_op_fdiv:
      fdiv(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
      
    default:
      TODO("Not yet implemented!");
    }
  }
  return m_value;
}

// LCOV_EXCL_START
void aluimpl::print_vl(std::ostream& out) const {
  TODO("Not yet implemented!");
} 
//LCOV_EXCL_END

lnodeimpl* chdl_internal::createAluNode(ch_alu_operator op, uint32_t size, lnodeimpl* a, lnodeimpl* b) {
  return new aluimpl(op, size, a, b); 
}

lnodeimpl* chdl_internal::createAluNode(ch_alu_operator op, uint32_t size, lnodeimpl* a) {
  return new aluimpl(op, size, a);
}
