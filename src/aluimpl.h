#pragma once

#include "lnodeimpl.h"
#include "arithm.h"

namespace ch {
namespace internal {

class aluimpl : public lnodeimpl {
public:
  ch_alu_op get_op() const {
    return op_;
  }  

  const bitvector& eval(ch_tick t) override;

  void print(std::ostream& out, uint32_t level) const override;
  
protected:    
  aluimpl(context* ctx, ch_alu_op op, const lnode& lhs, const lnode& rhs);
  aluimpl(context* ctx, ch_alu_op op, const lnode& in);
  ~aluimpl() {}

  ch_alu_op op_;
  ch_tick tick_;

  friend class context;
};

}
}
