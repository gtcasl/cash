#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:

  const sdata_type& value() const {
    return value_;
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  void print(std::ostream& out) const override;

protected:

  litimpl(context* ctx, const sdata_type& value);

  sdata_type value_;

  friend class context;
};

}
}
