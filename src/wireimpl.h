#pragma once

#include "lnodeimpl.h"

namespace cash {
namespace detail {

class wireimpl : public lnodeimpl {
public:
  wireimpl(lnodeimpl* src);

  const lnode& get_src() const {
    return srcs_[0];
  }

  lnode& get_src() {
    return srcs_[0];
  }

  const bitvector& eval(ch_cycle t) override;
  void print_vl(std::ostream& out) const override;

private:
  ch_cycle ctime_;
};

}
}
