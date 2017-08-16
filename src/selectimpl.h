#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class selectimpl : public lnodeimpl {
public:
  selectimpl(const lnode& cond, const lnode& true_, const lnode& false_);
  
 const lnode& get_cond() const {
    return srcs_[0];
  }

  void set_cond(const lnode& node) {
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

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle ctime_;
};

}
}
