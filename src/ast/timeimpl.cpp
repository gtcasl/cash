#include "debug.h"
#include "timeimpl.h"
#include "context.h"

using namespace ch::internal;

timeimpl::timeimpl(context* ctx, const source_info& srcinfo)
  : ioimpl(ctx, type_time, 8 * sizeof(ch_tick), "", srcinfo)
{}

lnodeimpl* timeimpl::clone(context* ctx, const clone_map&) const {
  return ctx->create_time(srcinfo_);
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::getCurrentTimeNode(const source_info& srcinfo) {
  return ctx_curr()->create_time(srcinfo);
}
