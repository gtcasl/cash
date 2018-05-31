#include "timeimpl.h"
#include "context.h"
#include "logic.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx)
  : ioimpl(ctx, type_time, 8 * sizeof(ch_tick))
  , tick_(0)
{}

void timeimpl::reset() {
  tick_ = 0;
}

void timeimpl::eval() {
  value_ = tick_++;
}

///////////////////////////////////////////////////////////////////////////////

ch_logic<64> ch::internal::ch_time() {
  return make_type<ch_logic<64>>(ctx_curr()->time());
}
