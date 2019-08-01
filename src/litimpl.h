#pragma once

#include "lnodeimpl.h"

namespace ch {
namespace internal {

class litimpl : public lnodeimpl {
public:

  const sdata_type& value() const {
    return value_;
  }

  bool is_zero() const {
    return is_zero_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  void print(std::ostream& out) const override;

protected:

  litimpl(context* ctx, const sdata_type& value);

  sdata_type value_;
  bool is_zero_;

  friend class context;
};

inline bool is_literal_one(lnodeimpl* node) {
  return node 
      && (type_lit == node->type())
      && reinterpret_cast<litimpl*>(node)->value().is_ones();
}

inline bool is_literal_zero(lnodeimpl* node) {
  return node
      && (type_lit == node->type())
      && reinterpret_cast<litimpl*>(node)->value().is_zero();
}

}
}
