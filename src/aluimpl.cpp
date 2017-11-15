#include "aluimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_alu_op op) {
  static const char* sc_names[] = {
    CH_ALUOP_ENUM(CH_ALUOP_NAME)
  };
  return sc_names[CH_ALUOP_INDEX(op)];
}

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op>
static void unaryop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  
  switch (op) {
  case alu_inv:
    Inv(out, in);
    break;
  case alu_neg:
    Negate(out, in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void binaryop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  
  switch (op) {
  case alu_and:
    And(out, lhs, rhs);
    break;
  case alu_or:
    Or(out, lhs, rhs);
    break;
  case alu_xor:
    Xor(out, lhs, rhs);
    break;
  case alu_nand:
    Nand(out, lhs, rhs);
    break;
  case alu_nor:
    Nor(out, lhs, rhs);
    break;
  case alu_xnor:
    Xnor(out, lhs, rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void shiftop(bitvector& out, const bitvector& in, const bitvector& bits) {
  assert(out.get_size() == in.get_size());
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range!");
  
  uint32_t wbits = bits.get_word(0);
  switch (op) {  
  case alu_sll:
    Sll(out, in, wbits);
    break;
  case alu_srl:
    Srl(out, in, wbits);
    break;
  case alu_sra:
    CH_TODO();
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
}

template <ch_alu_op op>
static void rotateop(bitvector& dst, const bitvector& in, const bitvector& bits) {
  assert(dst.get_size() == in.get_size());
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range!");

  uint32_t wbits = bits.get_word(0);
  switch (op) {
  case alu_rotl:
    RotL(dst, in, wbits);
    break;
  case alu_rotr:
    RotR(dst, in, wbits);
    break;
  default:
    CH_TODO();
  }
}

template <ch_alu_op op>
static void reduceop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == 1);
  
  bool result;
  switch (op) {
  case alu_andr:
    result = AndR(in);
    break;
  case alu_orr:
    result = OrR(in);
    break;
  case alu_xorr:
    result = XorR(in);
    break;
  case alu_nandr:
    result = NandR(in);
    break;
  case alu_norr:
    result = NorR(in);
    break;
  case alu_xnorr:
    result = XnorR(in);
    break;
  default:
    CH_ABORT("invalid alu operation");
  } 
  out[0] = result;
}

template <ch_alu_op op>
static void compareop(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 1);
  assert(lhs.get_size() == rhs.get_size());
  
  bool result;
  switch (op) {
  case alu_eq:
    result = lhs == rhs;
    break;
  case alu_ne:
    result = !(lhs == rhs);
    break;
  case alu_lt:
    result = (lhs < rhs);
    break;
  case alu_gt:
    result = (rhs < lhs);
    break;
  case alu_le:
    result = !(rhs < lhs);
    break;
  case alu_ge:
    result = !(lhs < rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
  out[0] = result;
}

static uint32_t get_output_size(ch_alu_op op, const lnode& lhs, const lnode& rhs) {
  switch (op) {
  case alu_and:
  case alu_or:
  case alu_xor:
  case alu_nand:
  case alu_nor:
  case alu_xnor:
  case alu_add:
  case alu_sub:
  case alu_mult:
  case alu_div:
  case alu_mod:
    assert(lhs.get_size() == rhs.get_size());
    return lhs.get_size();

  case alu_sll:
  case alu_srl:
  case alu_sra:
    return lhs.get_size();

  case alu_rotl:
  case alu_rotr:
    return lhs.get_size();

  case alu_eq:
  case alu_ne:
  case alu_lt:
  case alu_gt:
  case alu_le:
  case alu_ge:
    assert(lhs.get_size() == rhs.get_size());
    return 1;

  case alu_mux:
    return lhs.get_size() >> rhs.get_size();

  case alu_fadd:
  case alu_fsub:
  case alu_fmult:
  case alu_fdiv:
    assert(lhs.get_size() == rhs.get_size());
    return lhs.get_size();

  default:
    CH_ABORT("invalid alu operation");
  }
}

static uint32_t get_output_size(ch_alu_op op, const lnode& in) {
  switch (op) {
  case alu_inv:
  case alu_neg:
    return in.get_size();

  case alu_andr:
  case alu_orr:
  case alu_xorr:
  case alu_nandr:
  case alu_norr:
  case alu_xnorr:
    return 1;
  default:
    CH_ABORT("invalid alu operation");
  }
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(context* ctx, ch_alu_op op, unsigned size, unsigned num_operands)
  : lnodeimpl(ctx, type_alu, size)
  , op_(op)
  , tick_(~0ull) {
  srcs_.resize(num_operands);
}

void aluimpl::eval(bitvector& inout, ch_tick t) {
  switch (op_) {
  case alu_inv:
    unaryop<alu_inv>(inout, srcs_[0].eval(t));
    break;
  case alu_and:
    binaryop<alu_and>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_or:
    binaryop<alu_or>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_xor:
    binaryop<alu_xor>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_nand:
    binaryop<alu_nand>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_nor:
    binaryop<alu_nor>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_xnor:
    binaryop<alu_xnor>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_andr:
    reduceop<alu_andr>(inout, srcs_[0].eval(t));
    break;
  case alu_orr:
    reduceop<alu_orr>(inout, srcs_[0].eval(t));
    break;
  case alu_xorr:
    reduceop<alu_xorr>(inout, srcs_[0].eval(t));
    break;
  case alu_nandr:
    reduceop<alu_nandr>(inout, srcs_[0].eval(t));
    break;
  case alu_norr:
    reduceop<alu_norr>(inout, srcs_[0].eval(t));
    break;
  case alu_xnorr:
    reduceop<alu_xnorr>(inout, srcs_[0].eval(t));
    break;

  case alu_sll:
    shiftop<alu_sll>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_srl:
    shiftop<alu_srl>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_sra:
    shiftop<alu_sra>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_rotl:
    rotateop<alu_rotl>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_rotr:
    rotateop<alu_rotr>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_add:
    Add(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_sub:
    Sub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_neg:
    unaryop<alu_neg>(inout, srcs_[0].eval(t));
    break;
  case alu_mult:
  case alu_div:
  case alu_mod:
    CH_TODO();
    break;

  case alu_eq:
    compareop<alu_eq>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_ne:
    compareop<alu_ne>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_lt:
    compareop<alu_lt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_gt:
    compareop<alu_gt>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_le:
    compareop<alu_le>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_ge:
    compareop<alu_ge>(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_mux:
    Mux(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  case alu_fadd:
    fAdd(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fsub:
    fSub(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fmult:
    fMult(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;
  case alu_fdiv:
    fDiv(inout, srcs_[0].eval(t), srcs_[1].eval(t));
    break;

  default:
    CH_ABORT("invalid alu operation");
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
                                 ch_alu_op op,
                                 unsigned size,
                                 unsigned delay,
                                 unsigned num_operands)
  : aluimpl(ctx, op, size, num_operands + 1)
  , queue_(delay, bitvector(size))
  , next_(size)
  , curr_pos_(0) {
  auto clk = ctx->get_clk();
  cd_ = ctx->create_cdomain({clock_event(clk, EDGE_POS)});
  cd_->add_use(this);
  this->set_src(num_operands, clk);
}

delayed_aluimpl::~delayed_aluimpl() {
  cd_->remove_use(this);
}

void delayed_aluimpl::tick(ch_tick t) {
  CH_UNUSED(t);
  queue_[curr_pos_] = next_;
  curr_pos_ = (curr_pos_ + 1) % queue_.size();
  value_ = queue_[curr_pos_];
}

void delayed_aluimpl::tick_next(ch_tick t) {
  this->aluimpl::eval(next_, t);
}

const bitvector& delayed_aluimpl::eval(ch_tick t) {
  CH_UNUSED(t);
  return value_;
}

///////////////////////////////////////////////////////////////////////////////

lnodeimpl* ch::internal::createAluNode(
    ch_alu_op op,
    const lnode& lhs,
    const lnode& rhs,
    unsigned delay) {
  aluimpl* impl;
  auto size = get_output_size(op, lhs, rhs);
  if (delay != 0) {
    impl = lhs.get_ctx()->createNode<delayed_aluimpl>(op, size, delay, 2);
  } else {
    impl = lhs.get_ctx()->createNode<aluimpl>(op, size, 2);
  }
  impl->set_src(0, lhs);
  impl->set_src(1, rhs);
  return impl;
}

lnodeimpl* ch::internal::createAluNode(
    ch_alu_op op,
    const lnode& in,
    unsigned delay) {
  aluimpl* impl;
  auto size = get_output_size(op, in);
  if (delay != 0) {
    impl = in.get_ctx()->createNode<delayed_aluimpl>(op, size, delay, 1);
  } else {
    impl = in.get_ctx()->createNode<aluimpl>(op, size, 1);
  }
  impl->set_src(0, in);
  return impl;
}
