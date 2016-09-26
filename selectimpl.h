#pragma once

#include "nodeimpl.h"

namespace chdl_internal {

class selectimpl : public nodeimpl {
public:
  selectimpl(const ch_node& test, const ch_node& a, const ch_node& b);
  virtual ~selectimpl() {}

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle m_ctime;
};

}
