#pragma once

#include "lnodeimpl.h"
#include "arithm.h"

namespace cash_internal {

class aluimpl : public lnodeimpl {
public:
  aluimpl(ch_alu_operator alu_op, uint32_t size, lnodeimpl* a, lnodeimpl* b);
  aluimpl(ch_alu_operator alu_op, uint32_t size, lnodeimpl* a);
  
  ch_alu_operator get_alu_op() const {
    return alu_op_;
  }  

  const bitvector& eval(ch_cycle t) override;  
  void print_vl(std::ostream& out) const override;
  
protected:
  ch_alu_operator alu_op_;
  ch_cycle ctime_;
};

}
