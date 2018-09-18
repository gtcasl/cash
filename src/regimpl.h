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

  bool has_initdata() const {
    return (initdata_idx_ != -1);
  }

  const lnode& initdata() const {
    return srcs_[initdata_idx_];
  }

  std::size_t hash() const override;

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
          const lnode& initdata,
          const source_location& sloc);

  unsigned length_;
  int enable_idx_;  
  int reset_idx_;
  int initdata_idx_;

  friend class context;
};

}
}
