#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:

  const sdata_type& value() const {
    return value_;
  }

  bool is_zero() const {
    return is_zero_;
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  void print(std::ostream& out) const override;

protected:

  litimpl(context* ctx, const sdata_type& value);

  sdata_type value_;
  bool is_zero_;

  friend class context;
};

}
}
