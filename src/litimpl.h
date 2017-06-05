#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class litimpl : public lnodeimpl {
public:
  litimpl(context* ctx, const bitvector& value);

  const bitvector& eval(ch_cycle t) override;
  void print(std::ostream& out, uint32_t level) const override;
  void print_vl(std::ostream& out) const override;
};

}
}
