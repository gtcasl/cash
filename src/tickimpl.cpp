#include "tickimpl.h"
#include "context.h"
#include "bit.h"

using namespace cash::internal;

tickimpl::tickimpl(context* ctx) 
  : ioimpl(op_tick, ctx, CHAR_BIT * sizeof(ch_tick))
  , tick_(~0ull) 
{}

const bitvector& tickimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = t;
  }
  return value_;
}

void tickimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
}

///////////////////////////////////////////////////////////////////////////////

const ch_bit<64> cash::internal::ch_getTick() {
  return make_bit<64>(ctx_curr()->get_tick());
}
