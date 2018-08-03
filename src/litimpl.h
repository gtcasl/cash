#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:

  litimpl(context* ctx, const bitvector& value);

  friend class context;
};

}
}
