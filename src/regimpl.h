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

  auto length() const {
    return length_;
  }

  bool is_pipe() const {
    return length_ > 1;
  }

  const lnode& next() const {
    return srcs_[1];
  }

  lnode& next() {
    return srcs_[1];
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& enable() const {
    return srcs_[enable_idx_];
  }

  const lnode& reset() const {
    return srcs_[reset_idx_];
  }

  bool has_init_data() const {
    return (initdata_idx_ != -1);
  }

  const lnode& init_data() const {
    return srcs_[initdata_idx_];
  }

  bool equals(const lnodeimpl& other) const override;

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  uint64_t hash() const override;

protected:

  regimpl(context* ctx,
          unsigned length,
          lnodeimpl* next,
          lnodeimpl* enable,
          lnodeimpl* init_data,
          lnodeimpl* cd,
          lnodeimpl* reset,
          const source_location& sloc);

  unsigned length_;
  int enable_idx_;  
  int reset_idx_;
  int initdata_idx_;

  friend class context;
};

}
}
