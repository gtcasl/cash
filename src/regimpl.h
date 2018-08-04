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
    return pipe_.size() + 1;
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

  bool has_init() const {
    return (init_idx_ != -1);
  }

  const lnode& init() const {
    return srcs_[init_idx_];
  }

  const lnode& reset() const {
    return srcs_[reset_idx_];
  }

  std::size_t hash() const override;

  void eval() override;
  
protected:

  regimpl(context* ctx,
          unsigned length,
          const lnode& next,
          const lnode& enable,
          const source_location& sloc);

  regimpl(context* ctx,
          unsigned length,
          const lnode& next,
          const lnode& enable,
          const lnode& init,
          const source_location& sloc);

  int enable_idx_;
  int init_idx_;
  int reset_idx_;
  std::vector<bitvector> pipe_;

  friend class context;
};

}
}
