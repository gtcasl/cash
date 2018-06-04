#pragma once

#include "lnodeimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class regimpl : public lnodeimpl {
public:

  const lnode& cd() const {
    return srcs_[0];
  }

  const lnode& next() const {
    return srcs_[1];
  }

  lnode& next() {
    return srcs_[1];
  }

  bool has_init() const {
    return (3 == srcs_.size());
  }

  const lnode& init() const {
    return srcs_[2];
  }

  std::size_t hash() const override;

  void eval() override;
  
protected:

  regimpl(context* ctx, const lnode& next, const lnode& init);

  regimpl(context* ctx, const lnode& next);

  virtual ~regimpl();

  friend class context;
};

}
}
