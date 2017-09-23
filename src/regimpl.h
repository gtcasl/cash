#pragma once

#include "lnodeimpl.h"
#include "tickable.h"
#include "cdomain.h"

namespace cash {
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
    return srcs_[next_id_];
  }

  const lnode& get_init() const {
    return srcs_[init_id_];
  }

  bool has_reset() const {
    return (reset_id_ != -1);
  }

  const lnode& get_reset() const {
    return srcs_[reset_id_];
  }

  bool has_enable() const {
    return (enable_id_ != -1);
  }

  const lnode& get_enable() const {
    return srcs_[enable_id_];
  }
  
  const bitvector& eval(ch_tick t) override;

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;
  
protected:

  void get_signals(cdomain* cd);

  cdomain*  cd_;
  bitvector q_next_;
  int next_id_;
  int init_id_;
  int reset_id_;
  int enable_id_;
};

}
}
