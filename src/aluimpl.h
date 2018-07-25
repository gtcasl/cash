#pragma once

#include "lnodeimpl.h"
#include "cdimpl.h"

namespace ch {
namespace internal {

class aluimpl : public lnodeimpl {
public:

  ch_op op() const {
    return op_;
  }  

  bool is_signed() const {
    return is_signed_;
  }

  bool equals(const lnodeimpl& other) const override;

  std::size_t hash() const override;

  void initialize() override;

  void eval() override;

  void print(std::ostream& out, uint32_t level) const override;
  
protected:

  aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
          const lnode& lhs, const source_location& sloc);

  aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
          const lnode& lhs, const lnode& rhs, const source_location& sloc);

  ~aluimpl() {}

  void update_shadow_buffers();

  const bitvector& src_arg(unsigned index);

  ch_op op_;
  bool is_signed_;
  bool need_resizing_;
  const bitvector* src0_;
  const bitvector* src1_;
  bitvector t_src0_;
  bitvector t_src1_;

  friend class context;
};

}
}
