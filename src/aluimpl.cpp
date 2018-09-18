#include "aluimpl.h"
#include "proxyimpl.h"
#include "logic.h"
#include "context.h"

using namespace ch::internal;

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 const lnode& in, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, bool is_signed,
                 const lnode& lhs, const lnode& rhs, const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, sloc)
  , op_(op)
  , is_signed_(is_signed) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

bool aluimpl::equals(const lnodeimpl& other) const {
  if (lnodeimpl::equals(other)) {
    auto _other = reinterpret_cast<const aluimpl&>(other);
    return (this->op() == _other.op());
  }
  return false;
}

std::size_t aluimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();  
  auto n = this->srcs().size();  
  ret.fields.arg0 = (int)this->op();
  if (n > 0) {
    ret.fields.srcs = n;
    ret.fields.arg1 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg2 = this->src(1).id();
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

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& in,
    const source_location& sloc) {
  return in.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, in, sloc);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    bool is_signed,
    const lnode& lhs,
    const lnode& rhs,
    const source_location& sloc) {
  return lhs.impl()->ctx()->create_node<aluimpl>(op, size, is_signed, lhs, rhs, sloc);
}
