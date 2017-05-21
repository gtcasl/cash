#include "tickimpl.h"
#include "context.h"
#include "bit.h"

using namespace std;
using namespace cash::detail;

tickimpl::tickimpl(context* ctx) 
  : lnodeimpl(op_tick, ctx, CHAR_BIT * sizeof(ch_cycle))
  , ctime_(~0ull) 
{}

const bitvector& tickimpl::eval(ch_cycle t) {
  if (ctime_ != t) {
    ctime_ = t;
    value_ = t;
  }
  return value_;
}

void tickimpl::print_vl(std::ostream& out) const {
  CH_UNREFERENCED_PARAMETER(out);
  CH_TODO("Not yet implemented!");
}

///////////////////////////////////////////////////////////////////////////////

ch_bit<64> cash::detail::ch_tick() {
  return ch_bit<64>(new tickimpl(ctx_curr()));
}
