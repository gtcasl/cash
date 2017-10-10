#include "tickimpl.h"
#include "context.h"
#include "bit.h"

using namespace ch::internal;

tickimpl::tickimpl(context* ctx) 
  : ioimpl(ctx, type_tick, CHAR_BIT * sizeof(ch_tick))
  , tick_(~0ull) 
{}

const bitvector& tickimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = t;
  }
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

const ch_bit<64> ch::internal::ch_getTick() {
  return make_type<ch_bit<64>>(ctx_curr()->get_tick());
}
