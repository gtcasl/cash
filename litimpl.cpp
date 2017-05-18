#include "litimpl.h"
#include "context.h"

using namespace std;
using namespace cash::detail;

litimpl::litimpl(context* ctx, const bitvector& value) 
  : lnodeimpl(op_lit, ctx, value.get_size()) {
  value_ = value;
}

const bitvector& litimpl::eval(ch_cycle) { 
  return value_; 
}

void litimpl::print(ostream& out) const {
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size() 
      << "(" << value_ << ")";
}

void litimpl::print_vl(ostream& out) const {
  TODO("Not yet implemented!");
}
