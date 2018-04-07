#pragma once

#include "lnodeimpl.h"
#include "cdimpl.h"
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

  aluimpl(context* ctx, ch_alu_op op, const lnode& lhs);

  aluimpl(context* ctx, ch_alu_op op, const lnode& lhs, const lnode& rhs);

  ~aluimpl() {}

   void eval(bitvector& inout, ch_tick t);

  ch_alu_op op_;
  ch_tick tick_;

  friend class context;
};

class delayed_aluimpl : public tickable, public aluimpl {
public:

  const lnode& get_cd() const {
    return srcs_[cd_idx_];
  }

  bool has_enable() const {
    return (enable_idx_ != -1);
  }

  const lnode& get_enable() const {
    return srcs_[enable_idx_];
  }

  void tick(ch_tick t) override;

  void tick_next(ch_tick t) override;

  const bitvector& eval(ch_tick t) override;

  void detach() override;

protected:

  delayed_aluimpl(context* ctx,
                  ch_alu_op op,
                  unsigned delay,
                  const lnode& enable,
                  const lnode& lhs);

  delayed_aluimpl(context* ctx,
                  ch_alu_op op,
                  unsigned delay,
                  const lnode& enable,
                  const lnode& lhs,
                  const lnode& rhs);

  ~delayed_aluimpl();

  std::vector<bitvector> p_value_;
  std::vector<bitvector> p_next_;
  int cd_idx_;
  int enable_idx_;
  friend class context;
};

bool alu_symmetric(ch_alu_op op);

}
}
