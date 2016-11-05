#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

litimpl::litimpl(context* ctx, const bitvector& value) 
  : lnodeimpl("lit", ctx, value.get_size()) {
  m_value = value;
}

const bitvector& litimpl::eval(ch_cycle) { 
  return m_value; 
}

void litimpl::print(ostream& out) const {
  out << "#" << m_id << " <- " << m_name << m_value.get_size() << "(";
  for (uint32_t w = m_value.get_num_words(); w--;) {
    out << hex << m_value.get_word(w);
    if (w)
      out << "-";
  }
  out << ")" << endl;
}

// LCOV_EXCL_START
void litimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END
