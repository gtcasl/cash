#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace ch {
namespace internal {

class regimpl : public tickable, public lnodeimpl {
public:

  cdomain* get_cd() const {
    return cd_;
  }

  const lnode& get_reset() const {
    return srcs_[0];
  }

  const lnode& get_init() const {
    return srcs_[1];
  }

  const lnode& get_next() const {
    return srcs_[2];
  }

  void tick(ch_tick t) override;

  void tick_next(ch_tick) override;
  
  const bitvector& eval(ch_tick t) override;

  
protected:

  regimpl(context* ctx,
          cdomain* cd,
          const lnode& next,
          const lnode& init,
          const lnode& reset);

  virtual ~regimpl();

  void get_signals(cdomain* cd);

  cdomain* cd_;
  bitvector q_next_;
  ch_tick tick_;

  friend class context;
};

}
}
