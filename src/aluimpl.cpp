#include "aluimpl.h"
#include "proxyimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_op op) {
  static const char* sc_names[] = {
    CH_OP_ENUM(CH_OP_NAME)
  };
  return sc_names[CH_OP_INDEX(op)];
}

///////////////////////////////////////////////////////////////////////////////

template <ch_op op>
static void unaryop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  
  switch (op) {
  case op_inv:
    Inv(out, in);
    break;
  case op_neg:
    Neg(out, in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_op op>
static void binaryop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  
  switch (op) {
  case op_and:
    And(out, lhs, rhs);
    break;
  case op_or:
    Or(out, lhs, rhs);
    break;
  case op_xor:
    Xor(out, lhs, rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_op op>
static void shiftop(bitvector& out, const bitvector& in, const bitvector& bits) {
  assert(out.get_size() == in.get_size());  
  switch (op) {  
  case op_sll:
    Sll(out, in, bits);
    break;
  case op_srl:
    Srl(out, in, bits);
    break;
  case op_sra:
    Sra(out, in, bits);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_op op>
static void reduceop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == 1);
  
  bool result;
  switch (op) {
  case op_andr:
    result = AndR(in);
    break;
  case op_orr:
    result = OrR(in);
    break;
  case op_xorr:
    result = XorR(in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  } 
  out[0] = result;
}

template <ch_op op>
static void compareop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 1);
  assert(lhs.get_size() == rhs.get_size());
  
  bool result;
  switch (op) {
  case op_eq:
    result = lhs == rhs;
    break;
  case op_ne:
    result = !(lhs == rhs);
    break;
  case op_lt:
    result = (lhs < rhs);
    break;
  case op_gt:
    result = (rhs < lhs);
    break;
  case op_le:
    result = !(rhs < lhs);
    break;
  case op_ge:
    result = !(lhs < rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
  out[0] = result;
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(context* ctx, ch_op op, unsigned size, const lnode& in)
  : lnodeimpl(ctx, type_alu, size)
  , op_(op)
  , tick_(~0ull) {
  name_ = to_string(op);
  srcs_.push_back(in);
}

aluimpl::aluimpl(context* ctx, ch_op op, unsigned size, const lnode& lhs, const lnode& rhs)
  : lnodeimpl(ctx, type_alu, size)
  , op_(op)
  , tick_(~0ull) {
  name_ = to_string(op);
  srcs_.push_back(lhs);
  srcs_.push_back(rhs);
}

void aluimpl::eval(bitvector& inout, ch_tick t) {
  switch (op_) {  
  case op_eq:
    compareop<op_eq>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_ne:
    compareop<op_ne>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_lt:
    compareop<op_lt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_gt:
    compareop<op_gt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_le:
    compareop<op_le>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_ge:
    compareop<op_ge>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case op_inv:
    unaryop<op_inv>(inout, srcs_[0].eval(t));
    break;
  case op_and:
    binaryop<op_and>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_or:
    binaryop<op_or>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_xor:
    binaryop<op_xor>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case op_andr:
    reduceop<op_andr>(inout, srcs_[0].eval(t));
    break;
  case op_orr:
    reduceop<op_orr>(inout, srcs_[0].eval(t));
    break;
  case op_xorr:
    reduceop<op_xorr>(inout, srcs_[0].eval(t));
    break;

  case op_sll:
    shiftop<op_sll>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_srl:
    shiftop<op_srl>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_sra:
    shiftop<op_sra>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case op_add:
    Add(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_sub:
    Sub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_neg:
    unaryop<op_neg>(inout, srcs_[0].eval(t));
    break;
  case op_mult:
    Mult(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_div:
    Div(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_mod:
    Mod(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case op_zext:
    ZExt(inout, srcs_[0].eval(t));
    break;
  case op_sext:
    SExt(inout, srcs_[0].eval(t));
    break;

  case op_fadd:
    fAdd(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_fsub:
    fSub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_fmult:
    fMult(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case op_fdiv:
    fDiv(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  default:
    CH_ABORT("invalid opcode");
  }
}

const bitvector& aluimpl::eval(ch_tick t) {  
  if (tick_ != t) {  
    tick_ = t;
    this->eval(value_, t);
  }
  return value_;
}

void aluimpl::print(std::ostream& out, uint32_t level) const {
  out << "#" << id_ << " <- " << to_string(this->get_type()) << value_.get_size();
  uint32_t n = srcs_.size();
  out << "(" << to_string(op_) << ", ";
  for (uint32_t i = 0; i < n; ++i) {
    if (i > 0)
      out << ", ";
    out << "#" << srcs_[i].get_id();
  }
  out << ")";
  if (level == 2) {
    out << " = " << value_;
  }
}

///////////////////////////////////////////////////////////////////////////////

delayed_aluimpl::delayed_aluimpl(context* ctx,
                                 ch_op op,
                                 unsigned size,
                                 unsigned delay,
                                 const lnode& enable,
                                 const lnode& in)
  : aluimpl(ctx, op, size, in)
  , cd_idx_(-1)
  , enable_idx_(-1) {

  p_value_.resize(delay, bitvector(this->get_size()));
  p_next_.resize(delay, bitvector(this->get_size()));

  auto cd = ctx->current_cd();
  cd->add_reg(this);
  cd_idx_ = srcs_.size();
  srcs_.push_back(cd);

  if (!enable.is_empty()) {
    assert(1 == enable.get_size());
    enable_idx_ = srcs_.size();
    srcs_.push_back(enable);
  }  
}

delayed_aluimpl::delayed_aluimpl(context* ctx,
                                 ch_op op,
                                 unsigned size,
                                 unsigned delay,
                                 const lnode& enable,
                                 const lnode& lhs,
                                 const lnode& rhs)
  : aluimpl(ctx, op, size, lhs, rhs)
  , cd_idx_(-1)
  , enable_idx_(-1) {

  p_value_.resize(delay, bitvector(this->get_size()));
  p_next_.resize(delay, bitvector(this->get_size()));

  auto cd = ctx->current_cd();
  cd->add_reg(this);
  cd_idx_ = srcs_.size();
  srcs_.push_back(cd);

  if (!enable.is_empty()) {
    assert(1 == enable.get_size());
    enable_idx_ = srcs_.size();
    srcs_.push_back(enable);
  }
}

delayed_aluimpl::~delayed_aluimpl() {
  this->detach();
}

void delayed_aluimpl::detach() {
  if (!srcs_[2].is_empty()) {
    reinterpret_cast<cdimpl*>(srcs_[2].get_impl())->remove_reg(this);
    srcs_[2].clear();
  }
}

void delayed_aluimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  for (int i = p_value_.size()-1; i >= 0; --i) {
    p_value_[i] = p_next_[i];
  }
}

void delayed_aluimpl::tick_next(ch_tick t) {
  if (-1 == enable_idx_ || srcs_[enable_idx_].eval(t)[0]) {
    for (int i = p_value_.size()-1; i >= 0; --i) {
      if (0 == i) {
        this->aluimpl::eval(p_next_[0], t);
      } else {
        p_next_[i] = p_value_[i-1];
      }
    }
  } else {
    for (int i = p_value_.size()-1; i >= 0; --i) {
      p_next_[i] = p_value_[i];
    }
  }
}

const bitvector& delayed_aluimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return p_value_[p_value_.size()-1];
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    unsigned size,
    const lnode& in) {
  auto ctx = in.get_ctx();
  return ctx->create_alu(op, size, in);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    unsigned size,
    const lnode& lhs,
    const lnode& rhs) {
  auto ctx = lhs.get_ctx();
  return ctx->create_alu(op, size, lhs, rhs);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    unsigned size,
    unsigned delay,
    const lnode& enable,
    const lnode& in) {
  auto ctx = in.get_ctx();
  return ctx->create_node<delayed_aluimpl>(op, size, delay, enable, in);
}

lnodeimpl* ch::internal::createAluNode(
    ch_op op,
    unsigned size,
    unsigned delay,
    const lnode& enable,
    const lnode& lhs,
    const lnode& rhs) {
  auto ctx = lhs.get_ctx();
  return ctx->create_node<delayed_aluimpl>(op, size, delay, enable, lhs, rhs);
}

lnodeimpl* ch::internal::createRotateNode(
    const lnode& next,
    unsigned dist,
    bool right) {
  auto ctx = next.get_ctx();
  auto N = next.get_size();
  auto mod = dist % N;
  auto ret = ctx->create_node<proxyimpl>(N);
  if (right) {
    ret->add_source(0, next, mod, N - mod);
    ret->add_source(N - mod, next, 0, mod);
  } else {
    ret->add_source(0, next, N - mod, mod);
    ret->add_source(mod, next, 0, N - mod);
  }
  return ret;
}
