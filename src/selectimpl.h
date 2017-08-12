#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class selectimpl : public lnodeimpl {
public:
  selectimpl(lnodeimpl* cond, lnodeimpl* true_, lnodeimpl* false_);
  
  lnodeimpl* get_cond() const {
    return srcs_[0].get_impl();
  }

  void set_cond(lnodeimpl* impl) {
    srcs_[0] = impl;
  }
  
  lnodeimpl* get_true() const {
    return srcs_[1].get_impl();
  }

  void set_true(lnodeimpl* impl) {
    srcs_[1] = impl;
  }
  
  lnodeimpl* get_false() const {
    return srcs_[2].get_impl();
  }

  void set_false(lnodeimpl* impl) {
    srcs_[2] = impl;
  }

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle ctime_;
};

}
}
