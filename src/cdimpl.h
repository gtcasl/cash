#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  const auto& clk() const {
    return srcs_[0];
  }

  bool posedge() const {
    return posedge_;
  }

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;

protected:
  
  cdimpl(context* ctx,
         const lnode& clk,
         bool posedge,
         const source_location& sloc);

  ~cdimpl();

  bool posedge_;
  bool prev_val_;

  friend class context;
};

}
}
