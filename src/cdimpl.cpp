#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx,
               lnodeimpl* clk,
               bool pos_edge,
               const source_location& sloc)
  : ioimpl(ctx, type_cd, 1, sloc, "")
  , pos_edge_(pos_edge) {
  this->add_src(clk);
}

lnodeimpl* cdimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto clk = cloned_nodes.at(this->clk().id());
  return ctx->create_cd(clk, pos_edge_, sloc_);
}

bool cdimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const cdimpl&>(other);
    return (pos_edge_ == _other.pos_edge_);
  }
  return false;
}

void cdimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << "("
      << (pos_edge_ ? "pos_edge" : "negedge")
      << ", #" << this->src(0).id() << ")";
}
