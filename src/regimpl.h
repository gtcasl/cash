#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class regimpl : public tickable, public lnodeimpl {
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

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;
  
  const bitvector& eval(ch_tick t) override;

  void detach() override;
  
protected:

  regimpl(context* ctx, const lnode& next, const lnode& init);

  regimpl(context* ctx, const lnode& next);

  virtual ~regimpl();

  bitvector q_next_;

  friend class context;
};

}
}
