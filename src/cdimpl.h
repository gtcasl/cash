#pragma once

#include "ioimpl.h"
#include "tickable.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  const auto& regs() const {
    return regs_;
  }

  const auto& clk() const {
    return srcs_[0];
  }

  const auto& rst() const {
    return srcs_[1];
  }

  bool posedge() const {
    return posedge_;
  }

  void tick();

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

  void add_reg(tickable* reg);

  void remove_reg(tickable* reg);

protected:
  
  cdimpl(context* ctx, const lnode& clk, const lnode& rst, bool posedge);

  ~cdimpl();

  bool posedge_;
  bool prev_val_;
  std::vector<tickable*> regs_;

  friend class context;
};

}
}
