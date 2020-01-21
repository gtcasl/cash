#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  auto& clk() const {
    return this->src(0);
  }

  bool pos_edge() const {
    return pos_edge_;
  }

  lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) const override;

  bool equals(const lnodeimpl& other) const override;

  void print(std::ostream& out) const override;

protected:
  
  cdimpl(context* ctx,
         lnodeimpl* clk,
         bool pos_edge,
         const source_info& sloc);

  bool pos_edge_;

  friend class context;
};

///////////////////////////////////////////////////////////////////////////////

inline bool is_snode_type(lnodetype type) {
  return type == type_reg
      || type == type_mwport
      || type == type_msrport
      || type == type_udfs;
}

cdimpl* get_snode_cd(lnodeimpl* node);

lnodeimpl* get_snode_enable(lnodeimpl* node);

lnodeimpl* get_snode_reset(lnodeimpl* node);

}
}
