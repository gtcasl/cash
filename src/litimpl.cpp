#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

litimpl::litimpl(context* ctx, const bitvector& value) 
  : lnodeimpl(ctx, type_lit, value.size()) {
  value_ = value;
}

void litimpl::eval() {
  //--
}

void litimpl::print(std::ostream& out, uint32_t level) const {
  CH_UNUSED(level);
  out << "#" << id_ << " <- " << this->type() << value_.size()
      << "(" << value_ << ")";
}
