#include "aluimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

template <ch_operator op>
static void unaryop(bitvector& dst, const bitvector& a) {
  uint32_t num_words = ((dst.get_size() + 31) >> 5);
  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t d_w;
    switch (op) {
    case op_inv:
      d_w = ~a_w;
      break;
    default:
      TODO();
    }
    dst.set_word(i, d_w);
  }
}

template <ch_operator op>
static void binaryop(bitvector& dst, const bitvector& a, const bitvector& b) {
  uint32_t num_words = ((dst.get_size() + 31) >> 5);
  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t b_w = b.get_word(i);
    uint32_t d_w;    
    switch (op) {
    case op_and:
      d_w = a_w & b_w;
      break;
    case op_or:
      d_w = a_w | b_w;
      break;
    case op_xor:
      d_w = a_w ^ b_w;
      break;
    case op_nand:
      d_w = ~(a_w & b_w);
      break;
    case op_nor:
      d_w = ~(a_w | b_w);
      break;
    case op_xnor:
      d_w = ~(a_w ^ b_w);
      break;
    default:
      TODO();
    }
    dst.set_word(i, d_w);
  }
}

template <ch_operator op>
static void reduceop(bitvector& dst, const bitvector& in) {
  uint32_t size = in.get_size();
  uint32_t result;
  for (uint32_t i = 0, j = 0, in_w; i < size; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }    
    uint32_t bit = in_w & 0x1;
    in_w >>= 1;
    
    if (i == 0) {
      result = bit; // initialize
      continue;
    }
    switch (op) {
    case op_andr:
      result &= bit;
      break;
    case op_orr:
      result |= bit;
      break;
    case op_xorr:
      result ^= bit;
      break;
    default:
      TODO();
    }    
  }
  dst.set_word(0, result);
}

template <ch_operator op>
static void compareop(bitvector& dst, const bitvector& a, const bitvector& b) {
  uint32_t num_words = ((dst.get_size() + 31) >> 5);
  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t b_w = b.get_word(i);        
    bool cmp;
    switch (op) {
    case op_eq:
      cmp = a_w == b_w;
      break;
    case op_lt:
      cmp = a_w < b_w;
      break;
    case op_le:
      cmp = a_w <= b_w;
      break;
    default:
      TODO();
    }
    if (!cmp) {
      dst.set_word(0, 0);
      return;
    }
  }
  dst.set_word(0, 1);
}

static void add(bitvector& dst, const bitvector& a, const bitvector& b) {
  uint32_t size = dst.get_size();
  uint32_t num_words = ((size + 31) >> 5);
  
  uint32_t cin  = 0;
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

aluimpl::aluimpl(ch_operator op, const ch_node& a, const ch_node& b) 
  : nodeimpl(a.get_ctx(), a.get_size())
  , m_op(op)
  , m_ctime(~0ull) {
  m_srcs.push_back(a);
  m_srcs.push_back(b);
}

aluimpl::aluimpl(ch_operator op, const ch_node& a) 
  : nodeimpl(a.get_ctx(), a.get_size())
  , m_op(op)
  , m_ctime(~0ull) {
  m_srcs.push_back(a);
}

aluimpl::~aluimpl() {
  //--
}

const bitvector& aluimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {  
    m_ctime = t;
    
    switch (m_op) {
    case op_inv:
      unaryop<op_inv>(m_value, m_srcs[0].eval(t));  
      break;
    case op_and:
      binaryop<op_and>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));  
      break;
    case op_or:
      binaryop<op_or>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case op_xor:
      binaryop<op_xor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case op_nand:
      binaryop<op_nand>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));  
      break;
    case op_nor:
      binaryop<op_nor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case op_xnor:
      binaryop<op_xnor>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    
    case op_andr:
      reduceop<op_andr>(m_value, m_srcs[0].eval(t));  
      break;
    case op_orr:
      reduceop<op_orr>(m_value, m_srcs[0].eval(t));        
      break;
    case op_xorr:
      reduceop<op_xorr>(m_value, m_srcs[0].eval(t));        
      break;
      
    case op_sll:
    case op_slr:
    case op_rotl:
    case op_rotr:
      TODO();
      break;  
      
    case op_add:
      add(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));        
      break;
    case op_sub:
    case op_mult:
    case op_div:
    case op_mod:
      TODO();
      break;
      
    case op_eq:
      compareop<op_eq>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case op_ne:
      compareop<op_eq>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      m_value.set_bit(0, !m_value.get_bit(0));
      break;
    case op_lt:
      compareop<op_lt>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case op_gt:
      compareop<op_le>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      m_value.set_bit(0, !m_value.get_bit(0));
      break;
    case op_le:
      compareop<op_le>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      break;
    case op_ge:
      compareop<op_lt>(m_value, m_srcs[0].eval(t), m_srcs[1].eval(t));
      m_value.set_bit(0, !m_value.get_bit(0));
      break;  
      
    default:
      TODO();
    }
  }
  return m_value;
}

void aluimpl::print(std::ostream& out) const {
  TODO();
}

void aluimpl::print_vl(std::ostream& out) const {
  TODO();
}

ch_node chdl_internal::createAluNode(uint32_t size, ch_operator op, const ch_node& a, const ch_node& b) {
  return ch_node(new aluimpl(op, a, b)); 
}

ch_node chdl_internal::createAluNode(uint32_t size, ch_operator op, const ch_node& a) {
  return ch_node(new aluimpl(op, a));
}
