#include "aluimpl.h"
#include "proxyimpl.h"
#include "litimpl.h"
#include "logic.h"
#include "context.h"

using namespace ch::internal;

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 lnodeimpl* in, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 lnodeimpl* lhs, lnodeimpl* rhs, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

lnodeimpl* aluimpl::clone(context* ctx, const clone_map& cloned_nodes) {
  auto src0 = cloned_nodes.at(srcs_[0].id());
  if (srcs_.size() == 2) {
    auto src1 = cloned_nodes.at(srcs_[1].id());
    return ctx->create_node<aluimpl>(op_, size_, is_signed_, src0, src1, sloc_);
  } else {
    return ctx->create_node<aluimpl>(op_, size_, is_signed_, src0, sloc_);
  }
}

bool aluimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const aluimpl&>(other);
    return (this->op() == _other.op());
  }
  return false;
}

uint64_t aluimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();    
  ret.fields.op = (int)this->op();
  auto n = this->srcs().size();
  if (n > 0) {
    ret.fields.arg0 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg1 = this->src(1).id();
    }
  }
  return ret.value;
}

void aluimpl::print(std::ostream& out) const {
  out << "#" << id_ << " <- " << to_string(this->type()) << size_;
  uint32_t n = srcs_.size();
  out << "(" << to_string(op_) << (is_signed_ ? "_s" : "_u") << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << srcs_[i].id();
  }
  out << ")";
}

bool aluimpl::should_resize_opds() const {
  auto op_resize = CH_OP_RESIZE(op_);
  switch (op_resize) {
  case op_flags::resize_src:
    // source operand sizes should match
    return (srcs_[0].size() != srcs_[1].size());
  case op_flags::resize_dst:
    // source operand and destination sizes should match
    return ((srcs_[0].size() < size_)
        || ((srcs_.size() > 1) && srcs_[1].size() < size_));
  default:
    return false;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& in,
    const source_location& sloc) {
  return in.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, in.impl(), sloc);
}

lnodeimpl* ch::internal::createAluNode(
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
