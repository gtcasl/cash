#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

litimpl::litimpl(context* ctx, uint32_t size, const std::initializer_list<uint32_t>& value) 
  : nodeimpl(ctx, size) {
  uint32_t W = size / value.size();
  if (W * value.size() != size)
      CHDL_ABORT("initializer list size mismatch");
  uint32_t i = value.size() - 1;
  for (uint32_t word : value) {
    for (uint32_t j = 0; j < W; ++j) {
      m_value.set_bit(i * W + j, word & 0x1);
      word >>= 1;
    }
    assert(word == 0);
    --i;
  }
}

bool litimpl::ready() const {
  return true;
}

bool litimpl::valid() const {
  return true;
}

const bitvector& litimpl::eval(ch_cycle) { 
  return m_value; 
}

void litimpl::print(ostream& out) const {
  //out << "  lit" << m_value << ' ' << m_id << endl;
}

void litimpl::print_vl(ostream& out) const {
  //out << "  assign __x" << m_id << " = " << (m_value ? "1'b1" : "1'b0") << ';' << endl;
}
