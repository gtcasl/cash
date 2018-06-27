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
    return (srcs_.size() > 2);
  }

  const lnode& init() const {
    return srcs_[2];
  }

  const lnode& reset() const {
    return srcs_[3];
  }

  std::size_t hash() const override;

  void eval() override;
  
protected:

  regimpl(context* ctx, const lnode& next, const source_location& sloc);

  regimpl(context* ctx,
          const lnode& next,
          const lnode& init,
          const source_location& sloc);

  virtual ~regimpl();

  int init_idx_;

  friend class context;
};

}
}
