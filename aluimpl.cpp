#include "aluimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

static void adder(bitvector& dst, const bitvector& a, const bitvector& b) {
  uint32_t cin   = 0;
  uint32_t size  = dst.get_size();
  uint32_t words = ((size + 31) >> 5);
  
  for (uint32_t i = 0; i < words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t b_w = b.get_word(i);
    uint32_t c_w = a_w + b_w;
  
    uint32_t cout = 0;
    if (size < 32)  {
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

aluimpl::~aluimpl() {
  //--
}

bool aluimpl::ready() const {
  return true;
}

bool aluimpl::valid() const {
  return true;
}

const bitvector& aluimpl::eval(ch_cycle t) {  
  if (m_ctime != t) {  
    m_ctime = t;
    
    const bitvector& a_bits = m_srcs[0].eval(t);
    const bitvector& b_bits = m_srcs[1].eval(t);
    
    switch (m_op) {
    case op_add:
      adder(m_value, a_bits, b_bits);  
      break;
    case op_sub:
      //--
      break;
    case op_mult:
      //--
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
 switch (op) {
 case op_add:
 case op_sub:
 case op_mult:
   return ch_node(new aluimpl(op, a, b));
 }
}

ch_node chdl_internal::createAluNode(uint32_t size, ch_operator op, const ch_node& in) {
  TODO()
}
