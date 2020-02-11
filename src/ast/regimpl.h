#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class regimpl : public lnodeimpl {
public:

  const lnode& cd() const {
    return this->src(0);
  }

  auto length() const {
    return length_;
  }

  bool is_pipe() const {
    return length_ > 1;
  }

  const lnode& next() const {
    return this->src(1);
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& enable() const {
    return this->src(enable_idx_);
  }

  bool has_reset() const {
    return (reset_idx_ != -1);
  }

  const lnode& reset() const {
    return this->src(reset_idx_);
  }

  bool has_init_data() const {
    return (initdata_idx_ != -1);
  }

  const lnode& init_data() const {
    return this->src(initdata_idx_);
  }

  void set_next(lnodeimpl* node);

  void set_enable(lnodeimpl* node);

  lnodeimpl* remove_enable();

  bool equals(const lnodeimpl& other) const override;

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void print(std::ostream& out) const override;

protected:

  regimpl(context* ctx,
          uint32_t size,
          uint32_t length,
          lnodeimpl* cd,
          lnodeimpl* reset,
          lnodeimpl* enable,
          lnodeimpl* next,
          lnodeimpl* init_data,
          const std::string& name, 
          const source_location& sloc);

  uint32_t length_;
  int reset_idx_;
  int initdata_idx_;
  int enable_idx_;

  friend class context;
};

}
}
