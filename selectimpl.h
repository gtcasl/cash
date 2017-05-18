#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class selectimpl : public lnodeimpl {
public:
  selectimpl(lnodeimpl* cond, lnodeimpl* true_, lnodeimpl* false_);
  
  const lnode& get_cond() const {
    return srcs_[0];
  }
  
  const lnode& get_true() const {
    return srcs_[1];
  }
  
  const lnode& get_false() const {
    return srcs_[2];
  }

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle ctime_;
};

}
}
