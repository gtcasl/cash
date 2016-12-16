#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace chdl_internal;

litimpl::litimpl(context* ctx, const bitvector& value) 
  : lnodeimpl(op_lit, ctx, value.get_size()) {
  m_value = value;
}

const bitvector& litimpl::eval(ch_cycle) { 
  return m_value; 
}

void litimpl::print(ostream& out) const {
  out << "#" << m_id << " <- " << this->get_name() << m_value.get_size() 
      << "(" << m_value << ")";
}

// LCOV_EXCL_START
void litimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
// LCOV_EXCL_END
