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
    return signed_;
  }

  bool should_resize_opds() const;

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  bool equals(const lnodeimpl& other) const override;

  void print(std::ostream& out) const override;
  
protected:

  aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
          lnodeimpl* lhs, const source_location& sloc);

  aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
          lnodeimpl* lhs, lnodeimpl* rhs, const source_location& sloc);

  ~aluimpl() {}

  void init(ch_op op,
            bool is_signed,
            lnodeimpl* lhs = nullptr,
            lnodeimpl* rhs = nullptr);

  ch_op op_;
  bool signed_;

  friend class context;
};

}
}
