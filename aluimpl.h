#pragma once

#include "lnodeimpl.h"
#include "arithm.h"

namespace chdl_internal {

class aluimpl : public lnodeimpl {
public:
  aluimpl(ch_operator op, uint32_t size, lnodeimpl* a, lnodeimpl* b);
  aluimpl(ch_operator op, uint32_t size, lnodeimpl* a);
  ~aluimpl();
  
  ch_operator get_op() const {
    return m_op;
  }  

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
protected:
  ch_operator m_op;
  ch_cycle m_ctime;
};

}
