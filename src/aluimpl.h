#pragma once

#include "lnodeimpl.h"
#include "cdomain.h"
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
  aluimpl(context* ctx, ch_alu_op op, unsigned size, unsigned num_operands);
  ~aluimpl() {}

   void eval(bitvector& inout, ch_tick t);

  ch_alu_op op_;
  ch_tick tick_;

  friend class context;
};

class delayed_aluimpl : public tickable, public aluimpl {
public:

  void tick(ch_tick t) override;
  void tick_next(ch_tick t) override;

  const bitvector& eval(ch_tick t) override;

protected:
  delayed_aluimpl(context* ctx,
                  ch_alu_op op,
                  unsigned size,
                  unsigned delay,
                  unsigned num_operands);
  ~delayed_aluimpl();

  std::vector<bitvector> queue_;
  bitvector next_;
  unsigned curr_pos_;
  cdomain* cd_;

  friend class context;
};

}
}
