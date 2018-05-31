#pragma once

#include "lnodeimpl.h"
#include "cdimpl.h"
#include "arithm.h"

namespace ch {
namespace internal {

class aluimpl : public lnodeimpl {
public:

  ch_op op() const {
    return op_;
  }  

  bool equals(const lnodeimpl& rhs) const override;

  std::size_t hash() const override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  aluimpl(context* ctx, ch_op op, uint32_t size, const lnode& lhs);

  aluimpl(context* ctx, ch_op op, uint32_t size, const lnode& lhs, const lnode& rhs);

  ~aluimpl() {}

  ch_op op_;

  friend class context;
};

}
}
