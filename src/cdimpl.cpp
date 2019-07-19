#include "cd.h"
#include "cdimpl.h"
#include "ioimpl.h"
#include "litimpl.h"
#include "regimpl.h"
#include "memimpl.h"
#include "udfimpl.h"
#include "context.h"

using namespace ch::internal;

cdimpl::cdimpl(context* ctx,
               lnodeimpl* clk,
               bool pos_edge,
               const source_location& sloc)
  : ioimpl(ctx, type_cd, 1, "", sloc)
  , pos_edge_(pos_edge) {
  this->add_src(clk);
}

lnodeimpl* cdimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto clk = cloned_nodes.at(this->clk().id());
  return ctx->create_node<cdimpl>(clk, pos_edge_, sloc_);
}

bool cdimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto& _other = reinterpret_cast<const cdimpl&>(other);
    return (pos_edge_ == _other.pos_edge_);
  }
  return false;
}

void cdimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << "("
      << (pos_edge_ ? "pos_edge" : "negedge")
      << ", #" << this->src(0).id() << ")";
}

///////////////////////////////////////////////////////////////////////////////

cdimpl* ch::internal::get_snode_cd(lnodeimpl* node) {
  switch (node->type()) {
  default:
    assert(false);
  case type_reg:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<regimpl*>(node)->cd().impl());
  case type_msrport:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<memportimpl*>(node)->cd().impl());
  case type_mwport:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<memportimpl*>(node)->cd().impl());
  case type_udfs:
    return reinterpret_cast<cdimpl*>(
          reinterpret_cast<udfsimpl*>(node)->cd().impl());
  }
  return nullptr;
}

lnodeimpl* ch::internal::get_snode_enable(lnodeimpl* node) {
  switch (node->type()) {
  default:
    assert(false);
  case type_reg: {
    auto reg = reinterpret_cast<regimpl*>(node);
    return reg->has_enable() ? reg->enable().impl() : nullptr;
  }
  case type_msrport:
  case type_mwport: {
     auto mport = reinterpret_cast<memportimpl*>(node);
     return mport->has_enable() ? mport->enable().impl() : nullptr;
   }
  case type_udfs:
    return nullptr;
  }
  return nullptr;
}

lnodeimpl* ch::internal::get_snode_reset(lnodeimpl* node) {
  switch (node->type()) {
  default:
    assert(false);
  case type_reg: {
    auto reg = reinterpret_cast<regimpl*>(node);
    return reg->has_init_data() ? reg->reset().impl() : nullptr;
  }
  case type_udfs: {
    auto udfs = reinterpret_cast<udfsimpl*>(node);
    return udfs->reset().impl();
  }
  case type_msrport:
  case type_mwport:
    return nullptr;
  }
  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::getCurrentClockNode() {
  auto sloc = get_source_location();
  return ctx_curr()->current_clock(sloc);
}

lnodeimpl* ch::internal::getCurrentResetNode() {
  auto sloc = get_source_location();
  return ctx_curr()->current_reset(sloc);
}

void ch::internal::pushClockDomain(const lnode& clock,
                                   const lnode& reset,
                                   bool pos_edge) {
  auto sloc = get_source_location();
  clock.impl()->ctx()->push_cd(clock, reset, pos_edge, sloc);
}

void ch::internal::ch_popcd() {
  ctx_curr()->pop_cd();
}
