#include "timeimpl.h"
#include "context.h"
#include "logic.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx)
  : ioimpl(ctx, type_tick, 8 * sizeof(ch_tick))
  , tick_(~0ull) 
{}

const bitvector& timeimpl::eval(ch_tick t) {
  if (tick_ != t) {
    tick_ = t;
    value_ = t;
  }
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

ch_logic<64> ch::internal::ch_time() {
  return make_type<ch_logic<64>>(ctx_curr()->time());
}
