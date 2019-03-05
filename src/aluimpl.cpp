#include "aluimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "logic.h"
#include "context.h"

using namespace ch::internal;

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 lnodeimpl* in, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc) {
  this->init(op, is_signed, in);
}

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 lnodeimpl* lhs, lnodeimpl* rhs, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc) {
  this->init(op, is_signed, lhs, rhs);
}

void aluimpl::init(ch_op op, bool is_signed, lnodeimpl* lhs, lnodeimpl* rhs) {
  op_ = op;
  name_ = to_string(op);
  if (lhs) {
    this->add_src(lhs);
  }
  if (rhs) {
    this->add_src(rhs);
  }
  // disable the sign if not applicable
  if (is_signed
   && (0 == (CH_OP_PROP(op) & op_flags::is_signed))
   && !this->should_resize_opds()) {
    is_signed = false;
  }
  signed_ = is_signed;
}

lnodeimpl* aluimpl::clone(context* ctx, const clone_map& cloned_nodes) const {
  auto src0 = cloned_nodes.at(this->src(0).id());
  if (this->srcs().size() == 2) {
    auto src1 = cloned_nodes.at(this->src(1).id());
    return ctx->create_node<aluimpl>(op_, this->size(), signed_, src0, src1, sloc_);
  } else {
    return ctx->create_node<aluimpl>(op_, this->size(), signed_, src0, sloc_);
  }
}

bool aluimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const aluimpl&>(other);
    return (op_ == _other.op_) && (signed_ == _other.signed_);
  }
  return false;
}

void aluimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << to_string(this->type()) << this->size();
  auto n = this->srcs().size();
  out << "(" << to_string(op_) << (signed_ ? "_s" : "_u") << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << this->src(i).id();
  }
  out << ")";
}

bool aluimpl::should_resize_opds() const {
  auto op_resize = CH_OP_RESIZE(op_);
  switch (op_resize) {
  case op_flags::resize_src:
    // source operand sizes should match
    return (this->src(0).size() != this->src(1).size());
  case op_flags::resize_dst:
    // source operand and destination sizes should match
    return ((this->src(0).size() < this->size())
        || ((this->srcs().size() > 1) && this->src(1).size() < this->size()));
  default:
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnode ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& in,
    const source_location& sloc) {
  return in.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, in.impl(), sloc);
}

lnode ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& lhs,
    const lnode& rhs,
    const source_location& sloc) {
  if (op == ch_op::ne || op == ch_op::eq) {
    if (type_lit == lhs.impl()->type() && reinterpret_cast<litimpl*>(lhs.impl())->is_zero()) {
      op = (op == ch_op::eq) ? ch_op::notl : ch_op::orr;
      return rhs.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, rhs.impl(), sloc);
    } else
    if (type_lit == lhs.impl()->type() && reinterpret_cast<litimpl*>(rhs.impl())->is_zero()) {
      op = (op == ch_op::eq) ? ch_op::notl : ch_op::orr;
      return lhs.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, lhs.impl(), sloc);
    }
  }
  return lhs.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, lhs.impl(), rhs.impl(), sloc);
}
