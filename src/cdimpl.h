#pragma once

#include "ioimpl.h"

namespace ch {
namespace internal {

class cdimpl : public ioimpl {
public:

  auto& clk() const {
    return srcs_[0];
  }

  bool pos_edge() const {
    return pos_edge_;
  }

  virtual lnodeimpl* clone(context* ctx, const clone_map& cloned_nodes) override;

  void print(std::ostream& out) const override;

protected:
  
  cdimpl(context* ctx,
         const lnode& clk,
         bool pos_edge,
         const source_location& sloc);

  bool pos_edge_;

  friend class context;
};

}
}
