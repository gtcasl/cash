#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:
  litimpl(context* ctx, uint32_t size);
  litimpl(context* ctx, const bitvector& value);

  const bitvector& eval(ch_tick t) override;
  void print(std::ostream& out, uint32_t level) const override;
};

}
}
