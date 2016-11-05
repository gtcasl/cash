#pragma once

#include "ioimpl.h"

namespace chdl_internal {

class assertimpl : public ioimpl { // LCOV_EXCL_LINE
public:
  assertimpl(lnodeimpl* src, const std::string& msg);
  
  const bitvector& eval(ch_cycle t);
  
  void print_vl(std::ostream& out) const override {}  // LCOV_EXCL_LINE

private:
  std::string m_msg;
};

}
