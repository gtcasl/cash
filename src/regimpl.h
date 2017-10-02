#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace ch {
namespace internal {

class regimpl : public tickable, public lnodeimpl {
public:
  regimpl(cdomain* cd,
          const lnode& next,
          const lnode& init,
          const lnode& reset);

  regimpl(cdomain* cd,
          const lnode& next,
          const lnode& init,
          const lnode& reset,
          const lnode& enable);

  virtual ~regimpl();

  cdomain* get_cd() const {
    return cd_;
  }

  const lnode& get_next() const {
    return srcs_[next_idx_];
  }

  const lnode& get_init() const {
    return srcs_[init_idx_];
  }

  bool has_reset() const {
    return (reset_idx_ != -1);
  }

  const lnode& get_reset() const {
    return srcs_[reset_idx_];
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& get_enable() const {
    return srcs_[enable_idx_];
  }
  
  const bitvector& eval(ch_tick t) override;

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;
  
protected:

  void get_signals(cdomain* cd);

  cdomain*  cd_;
  bitvector q_next_;
  int next_idx_;
  int init_idx_;
  int reset_idx_;
  int enable_idx_;
};

}
}
