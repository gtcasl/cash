#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class selectimpl : public lnodeimpl {
public:
  selectimpl(const lnode& test, const lnode& a, const lnode& b);
  virtual ~selectimpl() {}

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle m_ctime;
};

}
