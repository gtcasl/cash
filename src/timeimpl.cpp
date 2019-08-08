#include "debug.h"
#include "timeimpl.h"
#include "context.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx, const source_location& sloc)
  : ioimpl(ctx, type_time, 8 * sizeof(ch_tick), "", sloc)
{}

lnodeimpl* timeimpl::clone(context* ctx, const clone_map&) const {
  return ctx->create_time(sloc_);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::getCurrentTimeNode() {
  auto sloc = get_source_location();
  return ctx_curr()->create_time(sloc);
}
