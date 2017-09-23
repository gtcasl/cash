#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace internal {

class litimpl : public lnodeimpl {
public:
  litimpl(context* ctx, const bitvector& value);

  const bitvector& eval(ch_tick t) override;
  void print(std::ostream& out, uint32_t level) const override;
};

}
}
