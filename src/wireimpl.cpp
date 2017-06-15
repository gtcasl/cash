#include "wireimpl.h"

using namespace std;
using namespace cash::detail;

wireimpl::wireimpl(lnodeimpl* src)
  : lnodeimpl(op_wire, src->get_ctx(), src->get_size()) {
  srcs_.emplace_back(src);
}
