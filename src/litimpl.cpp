#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

litimpl::litimpl(context* ctx, const sdata_type& value)
  : lnodeimpl(ctx, type_lit, value.size(), source_location())
  , value_(value)
{}

lnodeimpl* litimpl::clone(context* ctx, const clone_map&) {
  return ctx->create_literal(value_);
}

void litimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << size_
      << "(" << value_ << ")";
}
