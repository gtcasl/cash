#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx,
               const lnode& clk,
               bool pos_edge,
               const source_location& sloc)
  : ioimpl(ctx, type_cd, 1, sloc)
  , pos_edge_(pos_edge) {
  srcs_.emplace_back(clk);
}

void cdimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << "("
      << (pos_edge_ ? "pos_edge" : "negedge")
      << ", #" << srcs_[0].id() << ")";
}
