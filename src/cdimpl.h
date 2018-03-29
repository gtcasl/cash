#pragma once

#include "ioimpl.h"
#include "tickable.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  const auto& get_clock() const {
    return srcs_[0];
  }

  const auto& get_reset() const {
    return srcs_[1];
  }

  bool posedge() const {
    return posedge_;
  }

  void tick(ch_tick t);

  void tick_next(ch_tick t);

  const bitvector& eval(ch_tick) override {
    return value_;
  }

  void print(std::ostream& out, uint32_t level) const override;

  void add_reg(tickable* reg);

  void remove_reg(tickable* reg);

protected:
  
  cdimpl(context* ctx, const lnode& clock, const lnode& reset, bool posedge);

  ~cdimpl();

  bool posedge_;
  bool prev_val_;
  std::vector<tickable*> regs_;

  friend class context;
};

}
}
