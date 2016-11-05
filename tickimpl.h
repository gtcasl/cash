#pragma once

#include "lnodeimpl.h"

namespace chdl_internal {

class tickimpl : public lnodeimpl {
public:
  tickimpl(context* ctx);

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
private:
  ch_cycle m_ctime;
};

}
