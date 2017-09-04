#include "litimpl.h"
#include "context.h"

using namespace cash::internal;

litimpl::litimpl(context* ctx, const bitvector& value) 
  : lnodeimpl(op_lit, ctx, value.get_size()) {
  value_ = value;
}

const bitvector& litimpl::eval(ch_tick) { 
  return value_; 
}

void litimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->get_name() << value_.get_size() 
      << "(" << value_ << ")";
}

void litimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}
