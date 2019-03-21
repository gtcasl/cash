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
         const source_location& sloc);

  bool pos_edge_;

  friend class context;
};

}
}
