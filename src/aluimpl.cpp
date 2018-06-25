#include "aluimpl.h"
#include "proxyimpl.h"
#include "logic.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_op op) {
  static const char* sc_names[] = {
    CH_OP_ENUM(CH_OP_NAME)
  };
  return sc_names[CH_OP_INDEX(op)];
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, const lnode& in,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, 0, "", sloc)
  , op_(op) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_op op, uint32_t size, const lnode& lhs, const lnode& rhs,
                 const source_location& sloc)
  : lnodeimpl(ctx, type_alu, size, 0, "", sloc)
  , op_(op) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

bool aluimpl::equals(const lnodeimpl& rhs) const {
  if (lnodeimpl::equals(rhs)) {
    auto _rhs = reinterpret_cast<const aluimpl&>(rhs);
    return (this->op() == _rhs.op());
  }
  return false;
}

std::size_t aluimpl::hash() const {
  hash_t ret;
  ret.fields.type = this->type();
  ret.fields.size = this->size();  
  auto n = this->srcs().size();  
  ret.fields.arg0 = this->op();
  if (n > 0) {
    ret.fields.srcs = n;
    ret.fields.arg1 = this->src(0).id();
    if (n > 1) {
      ret.fields.arg2 = this->src(1).id();
    }
  }
  return ret.value;
}

void aluimpl::eval() {
  const bitvector& src0 = (srcs_.size() > 0) ? srcs_[0].data() : value_;
  const bitvector& src1 = (srcs_.size() > 1) ? srcs_[1].data() : src0;

  switch (op_) {
  case op_eq:
    value_.word(0) = (src0 == src1);
    break;
  case op_ne:
    value_.word(0) = (src0 != src1);
    break;
  case op_lt:
    value_.word(0) = (src0 < src1);
    break;
  case op_gt:
    value_.word(0) = (src0 > src1);
    break;
  case op_le:
    value_.word(0) = (src0 <= src1);
    break;
  case op_ge:
    value_.word(0) = (src0 >= src1);
    break;

  case op_inv:
    Inv(value_, src0);
    break;
  case op_and:
    And(value_, src0, src1);
    break;
  case op_or:
    Or(value_, src0, src1);
    break;
  case op_xor:
    Xor(value_, src0, src1);
    break;

  case op_andr:
    value_.word(0) = AndR(src0);
    break;
  case op_orr:
    value_.word(0) = OrR(src0);
    break;
  case op_xorr:
    value_.word(0) = XorR(src0);
    break;

  case op_sll:
    Sll(value_, src0, src1);
    break;
  case op_srl:
    Srl(value_, src0, src1);
    break;
  case op_sra:
    Sra(value_, src0, src1);
    break;

  case op_add:
    Add(value_, src0, src1);
    break;
  case op_sub:
    Sub(value_, src0, src1);
    break;
  case op_neg:
    Neg(value_, src0);
    break;
  case op_mult:
    Mult(value_, src0, src1);
    break;
  case op_div:
    Div(value_, src0, src1);
    break;
  case op_mod:
    Mod(value_, src0, src1);
    break;

  case op_zext:
    ZExt(value_, src0);
    break;
  case op_sext:
    SExt(value_, src0);
    break;

  default:
    CH_ABORT("invalid opcode");
  }
}

void aluimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << to_string(this->type()) << value_.size();
  uint32_t n = srcs_.size();
  out << "(" << to_string(op_) << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << srcs_[i].id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    const lnode& in,
    const source_location& sloc) {
  return in.impl()->ctx()->create_node<aluimpl>(op, size, in, sloc);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    uint32_t size,
    const lnode& lhs,
    const lnode& rhs,
    const source_location& sloc) {
  return lhs.impl()->ctx()->create_node<aluimpl>(op, size, lhs, rhs, sloc);
}

lnodeimpl* ch::internal::createRotateNode(
    const lnode& next,
    uint32_t dist,
    bool right,
    const source_location& sloc) {
  auto N = next.size();
  auto mod = dist % N;
  auto ret = next.impl()->ctx()->create_node<proxyimpl>(N, 0, "", sloc);
  if (right) {
    ret->add_source(0, next, mod, N - mod);
    ret->add_source(N - mod, next, 0, mod);
  } else {
    ret->add_source(0, next, N - mod, mod);
    ret->add_source(mod, next, 0, N - mod);
  }
  return ret;
}
