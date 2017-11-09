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

aluimpl::aluimpl(context* ctx, ch_alu_op op, const lnode& lhs, const lnode& rhs)
  : lnodeimpl(ctx, type_alu, get_output_size(op, lhs, rhs))
  , op_(op)
  , tick_(~0ull) {
  srcs_.emplace_back(lhs);
  srcs_.emplace_back(rhs);
}

aluimpl::aluimpl(context* ctx, ch_alu_op op, const lnode& in)
  : lnodeimpl(ctx, type_alu, get_output_size(op, in))
  , op_(op)
  , tick_(~0ull) {
  srcs_.emplace_back(in);
}

const bitvector& aluimpl::eval(ch_tick t) {  
  if (tick_ != t) {  
    tick_ = t;
    
    switch (op_) {
    case alu_inv:
      unaryop<alu_inv>(value_, srcs_[0].eval(t));
      break;
    case alu_and:
      binaryop<alu_and>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_or:
      binaryop<alu_or>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_xor:
      binaryop<alu_xor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_nand:
      binaryop<alu_nand>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_nor:
      binaryop<alu_nor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_xnor:
      binaryop<alu_xnor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    
    case alu_andr:
      reduceop<alu_andr>(value_, srcs_[0].eval(t));
      break;
    case alu_orr:
      reduceop<alu_orr>(value_, srcs_[0].eval(t));
      break;
    case alu_xorr:
      reduceop<alu_xorr>(value_, srcs_[0].eval(t));
      break;
    case alu_nandr:
      reduceop<alu_nandr>(value_, srcs_[0].eval(t));
      break;
    case alu_norr:
      reduceop<alu_norr>(value_, srcs_[0].eval(t));
      break;
    case alu_xnorr:
      reduceop<alu_xnorr>(value_, srcs_[0].eval(t));
      break;
      
    case alu_sll:
      shiftop<alu_sll>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_srl:
      shiftop<alu_srl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_sra:
      shiftop<alu_sra>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;

    case alu_rotl:
      rotateop<alu_rotl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_rotr:
      rotateop<alu_rotr>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;

    case alu_add:
      Add(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_sub:
      Sub(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_neg:
      unaryop<alu_neg>(value_, srcs_[0].eval(t));
      break;
    case alu_mult:
    case alu_div:
    case alu_mod:
      CH_TODO();
      break;
      
    case alu_eq:
      compareop<alu_eq>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_ne:
      compareop<alu_ne>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_lt:
      compareop<alu_lt>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_gt:
      compareop<alu_gt>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_le:
      compareop<alu_le>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_ge:
      compareop<alu_ge>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;

    case alu_mux:
      Mux(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    case alu_fadd:
      fAdd(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;      
    case alu_fsub:
      fSub(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;      
    case alu_fmult:
      fMult(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;      
    case alu_fdiv:
      fDiv(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    default:
      CH_ABORT("invalid alu operation");
    }
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

lnodeimpl* ch::internal::createAluNode(
    ch_alu_op op,
    const lnode& lhs,
    const lnode& rhs) {
  return lhs.get_ctx()->createNode<aluimpl>(op, lhs, rhs);
}

lnodeimpl* ch::internal::createAluNode(ch_alu_op op, const lnode& in) {
  return in.get_ctx()->createNode<aluimpl>(op, in);
}
