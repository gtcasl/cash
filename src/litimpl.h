#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:

  const bitvector& value() const {
    return value_;
  }

  void print(std::ostream& out) const override;

protected:

  litimpl(context* ctx, const bitvector& value);

  bitvector value_;

  friend class context;
};

}
}
