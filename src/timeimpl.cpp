#include "timeimpl.h"
#include "context.h"
#include "bit.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx, const source_location& sloc)
  : ioimpl(ctx, type_time, 8 * sizeof(ch_tick), sloc)
{}

///////////////////////////////////////////////////////////////////////////////

ch_bit<64> ch::internal::ch_now(const source_location& sloc) {
  return make_type<ch_bit<64>>(ctx_curr()->create_time(sloc), sloc);
}
