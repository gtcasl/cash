#include "timeimpl.h"
#include "context.h"
#include "uint.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx, const source_location& sloc)
  : ioimpl(ctx, type_time, 8 * sizeof(ch_tick), sloc, "time")
{}

lnodeimpl* timeimpl::clone(context* ctx, const clone_map&) const {
  return ctx->create_time(sloc_);
}

///////////////////////////////////////////////////////////////////////////////

ch_uint<64> ch::internal::ch_now(const source_location& sloc) {
  return make_type<ch_uint<64>>(ctx_curr()->create_time(sloc), sloc);
}
