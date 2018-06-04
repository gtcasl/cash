#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  const auto& clk() const {
    return srcs_[0];
  }

  const auto& rst() const {
    return srcs_[1];
  }

  bool posedge() const {
    return posedge_;
  }

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  cdimpl(context* ctx, const lnode& clk, const lnode& rst, bool posedge);

  ~cdimpl();

  bool posedge_;
  bool prev_val_;

  friend class context;
};

}
}
