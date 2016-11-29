#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class selectimpl : public lnodeimpl {
public:
  selectimpl(lnodeimpl* cond, lnodeimpl* true_, lnodeimpl* false_);
  
  const lnode& get_cond() const {
    return m_srcs[0];
  }
  
  const lnode& get_true() const {
    return m_srcs[1];
  }
  
  const lnode& get_false() const {
    return m_srcs[2];
  }

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle m_ctime;
};

}
