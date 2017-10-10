#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class selectimpl : public lnodeimpl {
public:
 const lnode& get_pred() const {
    return srcs_[0];
  }

  void set_pred(const lnode& node) {
    srcs_[0] = node;
  }

  const lnode& get_true() const {
    return srcs_[1];
  }

  void set_true(const lnode& node) {
    srcs_[1] = node;
  }

  const lnode& get_false() const {
    return srcs_[2];
  }

  void set_false(const lnode& node) {
    srcs_[2] = node;
  }

  const bitvector& eval(ch_tick t) override;

protected:
  selectimpl(context* ctx,
             const lnode& pred,
             const lnode& _true,
             const lnode& _false);
  ~selectimpl() {}

  ch_tick tick_;

  friend class context;
};

}
}
