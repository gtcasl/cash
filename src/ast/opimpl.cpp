#include "logic.h"
#include "opimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "cdimpl.h"
#include "context.h"

using namespace ch::internal;

opimpl::opimpl(context* ctx,
               ch_op op,
               uint32_t size,
               bool is_signed,
               lnodeimpl* in,
               const source_info& sloc)
  : lnodeimpl(ctx->node_id(), type_op, size, ctx, to_string(op), sloc) {
  this->init(op, is_signed, in);
}

opimpl::opimpl(context* ctx,
               ch_op op,
               uint32_t size,
               bool is_signed,
               lnodeimpl* lhs,
               lnodeimpl* rhs,
               const source_info& sloc)
  : lnodeimpl(ctx->node_id(), type_op, size, ctx, to_string(op), sloc) {
  this->init(op, is_signed, lhs, rhs);
}

void opimpl::init(ch_op op, bool is_signed, lnodeimpl* lhs, lnodeimpl* rhs) {
  op_ = op;
  if (lhs) {
    this->add_src(lhs);
  }
  if (rhs) {
    this->add_src(rhs);
  }
  // disable the sign if not applicable
  if (is_signed
   && !CH_OP_IS_SIGNED(op)
   && !this->should_resize_opds()) {
    is_signed = false;
  }
  signed_ = is_signed;
}

lnodeimpl* opimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto src0 = cloned_nodes.at(this->src(0).id());
  if (this->num_srcs() == 2) {
    auto src1 = cloned_nodes.at(this->src(1).id());
    return ctx->create_node<opimpl>(op_, this->size(), signed_, src0, src1, sloc_);
  } else {
    return ctx->create_node<opimpl>(op_, this->size(), signed_, src0, sloc_);
  }
}

bool opimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto& _other = reinterpret_cast<const opimpl&>(other);
    return (op_ == _other.op_) && (signed_ == _other.signed_);
  }
  return false;
}

void opimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << this->type() << this->size();
  auto n = this->num_srcs();
  out << "(" << op_ << (signed_ ? "_s" : "_u") << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  out << ")";
}

bool opimpl::should_resize_opds() const {
  auto op_resize = CH_OP_RESIZE(op_);
  switch (op_resize) {
  case op_flags::resize_src:
    // source operand sizes should match
    return (this->src(0).size() != this->src(1).size());
  case op_flags::resize_dst:
    // source operand and destination sizes should match
    return ((this->src(0).size() < this->size())
        || ((this->num_srcs() > 1) && this->src(1).size() < this->size()));
  default:
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createOpNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& in,
    const source_info& sloc) {
  is_signed &= CH_OP_IS_SIGNED(op);
  return ctx_curr()->create_node<opimpl>(op, size, is_signed, in.impl(), sloc);
}

lnodeimpl* ch::internal::createOpNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& lhs,
    const lnode& rhs,
    const source_info& sloc) {
  return ctx_curr()->create_node<opimpl>(op, size, is_signed, lhs.impl(), rhs.impl(), sloc);
}