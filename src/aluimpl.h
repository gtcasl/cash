#pragma once

#include "lnodeimpl.h"
#include "arithm.h"

namespace cash {
namespace internal {

class aluimpl : public lnodeimpl {
public:
  aluimpl(ch_alu_op op, const lnode& lhs, const lnode& rhs);
  aluimpl(ch_alu_op op, const lnode& in);
  
  ch_alu_op get_alu_op() const {
    return alu_op_;
  }  

  const bitvector& eval(ch_tick t) override;
  
protected:
  ch_alu_op alu_op_;
  ch_tick tick_;
};

}
}
