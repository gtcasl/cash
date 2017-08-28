#include "aluimpl.h"
#include "context.h"

using namespace cash::detail;

#define CH_ALUOP_NAME(n) case alu_op_##n: return op_##n;

static ch_operator to_operator(ch_alu_op op) {
  switch (op) {
    CH_ALUOP_ENUM(CH_ALUOP_NAME)
  }
  CH_ABORT("invalid alu_op value");
}

#undef CH_ALUOP_NAME

///////////////////////////////////////////////////////////////////////////////

static void Invert(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  for (uint32_t i = 0, n = in.get_num_words(); i < n; ++i) {
    out.set_word(i, ~in.get_word(i));
  }
  out.clear_unused_bits();
}

static void And(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) & rhs.get_word(i));
  }
}

static void Or(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) | rhs.get_word(i));
  }
}

static void Xor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) ^ rhs.get_word(i));
  }
}

static void Nand(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, ~(lhs.get_word(i) & rhs.get_word(i)));
  }
  out.clear_unused_bits();
}

static void Nor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, ~(lhs.get_word(i) | rhs.get_word(i)));
  }
  out.clear_unused_bits();
}

static void Xnor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, ~(lhs.get_word(i) ^ rhs.get_word(i)));
  }
  out.clear_unused_bits();
}

static bool AndN(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result &= (in_w & 0x1);
  }
  return (result != 0);
}

static bool OrN(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result |= (in_w & 0x1);
  }
  return (result != 0);
}

static bool XorN(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result ^= (in_w & 0x1);
  }
  return (result != 0);
}

static void ShL(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.get_size() == in.get_size());
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.set_word(0, in.get_word(0) << dist);
  } else {
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    if (dist < in.get_size()) {
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      if (shift_bits) {
        uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
        uint32_t prev = 0;
        for (uint32_t i = 0, n = num_words - shift_words; i < n; ++i) {
          uint32_t curr = in.get_word(i);
          out.set_word(i + shift_words, (curr << shift_bits) | (prev >> shift_bits_r));
          prev = curr;
        }
      } else {
        for (uint32_t i = 0, n = num_words - shift_words; i < n; ++i) {
          out.set_word(i + shift_words, in.get_word(i));
        }
      }
    } else {
      shift_words = num_words;
    }
    std::fill_n(out.get_words(), shift_words, 0x0);
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

static void ShR(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.get_size() == in.get_size());
  uint32_t num_words   = in.get_num_words();
  if (num_words == 1) {
    out.set_word(0, in.get_word(0) >> dist);
  } else {
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    if (dist < in.get_size()) {
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      if (shift_bits) {
        uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
        uint32_t prev = 0;
        for (int32_t i = num_words - 1 - shift_words; i >= 0; --i) {
          uint32_t curr = in.get_word(i + shift_words);
          out.set_word(i, (curr >> shift_bits) | (prev << shift_bits_l));
          prev = curr;
        }
      } else {
        for (int32_t i = num_words - 1 - shift_words; i >= 0; --i) {
          out.set_word(i, in.get_word(i + shift_words));
        }
      }
    } else {
      shift_words = num_words;
    }
    std::fill_n(out.get_words() + (num_words - shift_words), shift_words, 0x0);
  }
}

static void RotL(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.get_size() == in.get_size());
  if (dist > in.get_size())
    dist %= in.get_size();
  if (0 == dist) {
    out = in;
    return;
  }
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.set_word(0, rotl(in.get_word(0), dist, in.get_size()));
  } else {
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    uint32_t shift_bits = dist & bitvector::WORD_MASK;
    if (shift_bits) {
      uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = in.get_word(num_words - 1);
      for (uint32_t i = 0, j = shift_words; i < num_words; ++i) {
        uint32_t curr = in.get_word(i);
        out.set_word(j, (curr << shift_bits) | (prev >> shift_bits_r));
        prev = curr;
        if (++j == num_words)
          j = 0;
      }
    } else {
      for (uint32_t i = 0, j = shift_words; i < num_words; ++i) {
        out.set_word(j, in.get_word(i));
        if (++j == num_words)
          j = 0;
      }
    }
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

static void RotR(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.get_size() == in.get_size());
  if (dist > in.get_size())
    dist %= in.get_size();
  if (0 == dist) {
    out = in;
    return;
  }
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.set_word(0, rotr(in.get_word(0), dist, in.get_size()));
  } else {
    int32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    int32_t shift_bits = dist & bitvector::WORD_MASK;
    if (shift_bits) {
      uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = in.get_word(0);
      for (int32_t i = num_words - 1, j = i - shift_words; i >= 0; --i) {
        uint32_t curr = in.get_word(i);
        out.set_word(j, (curr >> shift_bits) | (prev << shift_bits_l));
        prev = curr;
        if (0 == j--)
          j = num_words - 1;
      }
    } else {
      for (int32_t i = num_words - 1, j = i - shift_words; i >= 0; --i) {
        out.set_word(j, in.get_word(i));
        if (0 == j--)
          j = num_words - 1;
      }
    }
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

///////////////////////////////////////////////////////////////////////////////

static void Add(bitvector& dst, const bitvector& a, const bitvector& b, uint32_t cin = 0) {
  assert(dst.get_size() == a.get_size());
  assert(a.get_size() == b.get_size());

  uint32_t size = dst.get_size();
  uint32_t num_words = dst.get_num_words();

  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = a.get_word(i);
    uint32_t b_w = b.get_word(i);
    uint32_t c_w = a_w + b_w;

    uint32_t cout = 0;
    if (size < bitvector::WORD_SIZE)  {
      c_w += cin;
      c_w &= ~(1 << size); // remove overflow bit
    } else {
      if (c_w < a_w)
        cout = 1;
      c_w += cin;
      if (c_w < cin)
        cout = 1;
      size -= 32;
      cin = cout;
    }
    dst.set_word(i, c_w);
  }
}

///////////////////////////////////////////////////////////////////////////////

static void fAdd(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef + b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fSub(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef - b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fMult(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef * b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

static void fDiv(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 32);
  assert(a.get_size() == 32);
  assert(b.get_size() == 32);
  uint32_t a_value = a.get_word(0);
  uint32_t b_value = b.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef / b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  dst.set_word(0, result);
}

///////////////////////////////////////////////////////////////////////////////

static void Mux(bitvector& dst, const bitvector& in, const bitvector& sel) {
  uint32_t D = dst.get_size();
  uint32_t N = in.get_size();
  uint32_t S = sel.get_size();
  assert(D == N >> S);

  assert(sel.get_num_words() == 1);
  uint32_t offset = sel.get_word(0) * D;
  assert(offset + D <= N);

  bitvector::const_iterator iter_in(in.begin() + offset);
  bitvector::iterator iter_dst(dst.begin());
  for (uint32_t i = 0; i < D; ++i) {
    *iter_dst++ = *iter_in++;
  }
}

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op>
static void unaryop(bitvector& dst, const bitvector& a) {
  assert(dst.get_size() == a.get_size());
  
  switch (op) {
  case alu_op_inv:
    Invert(dst, a);
    break;
  default:
    CH_TODO();
  }
}

template <ch_alu_op op>
static void binaryop(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == a.get_size());
  assert(a.get_size() == b.get_size());
  
  switch (op) {
  case alu_op_and:
    And(dst, a, b);
    break;
  case alu_op_or:
    Or(dst, a, b);
    break;
  case alu_op_xor:
    Xor(dst, a, b);
    break;
  case alu_op_nand:
    Nand(dst, a, b);
    break;
  case alu_op_nor:
    Nor(dst, a, b);
    break;
  case alu_op_xnor:
    Xnor(dst, a, b);
    break;
  default:
    CH_TODO();
  }
}

template <ch_alu_op op>
static void shiftop(bitvector& dst, const bitvector& in, const bitvector& bits) {
  assert(dst.get_size() == in.get_size());
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range!");
  
  uint32_t wbits = bits.get_word(0);
  switch (op) {  
  case alu_op_shl:
    ShL(dst, in, wbits);
    break;
  case alu_op_shr:
    ShR(dst, in, wbits);
    break;
  case alu_op_rotl:
    RotL(dst, in, wbits);
    break;
  case alu_op_rotr:
    RotR(dst, in, wbits);
    break;
  default:
    CH_TODO();
  }
}

template <ch_alu_op op>
static void reduceop(bitvector& dst, const bitvector& in) {
  assert(dst.get_size() == 1);
  
  bool result;
  switch (op) {
  case alu_op_andr:
    result = AndN(in);
    break;
  case alu_op_orr:
    result = OrN(in);
    break;
  case alu_op_xorr:
    result = XorN(in);
    break;
  default:
    CH_TODO();
  } 
  dst[0] = result;
}

template <ch_alu_op op>
static void compareop(bitvector& dst, const bitvector& a, const bitvector& b) {
  assert(dst.get_size() == 1);
  assert(a.get_size() == b.get_size());
  
  bool result;
  switch (op) {
  case alu_op_eq:
    result = a == b;
    break;
  case alu_op_ne:
    result = !(a == b);
    break;
  case alu_op_lt:
    result = (a < b);
    break;
  case alu_op_gt:
    result = (b < a);
    break;
  case alu_op_le:
    result = !(b < a);
    break;
  case alu_op_ge:
    result = !(a < b);
    break;
  default:
    CH_TODO();
  }
  dst[0] = result;
}

static uint32_t get_output_size(ch_alu_op op, const lnode& a, const lnode& b) {
  switch (op) {
  case alu_op_and:
  case alu_op_or:
  case alu_op_xor:
  case alu_op_nand:
  case alu_op_nor:
  case alu_op_xnor:  
  case alu_op_add:
  case alu_op_sub:
  case alu_op_mult:
  case alu_op_div:
  case alu_op_mod:
    assert(a.get_size() == b.get_size());
    return a.get_size();

  case alu_op_shl:
  case alu_op_shr:
  case alu_op_rotl:
  case alu_op_rotr:
    return a.get_size();

  case alu_op_mux:
    return a.get_size() >> b.get_size();

  case alu_op_demux:
    return a.get_size() << b.get_size();

  case alu_op_eq:
  case alu_op_ne:
  case alu_op_lt:
  case alu_op_gt:
  case alu_op_le:
  case alu_op_ge:
    assert(a.get_size() == b.get_size());
    return 1;

  case alu_op_fadd:
  case alu_op_fsub:
  case alu_op_fmult:
  case alu_op_fdiv:
    assert(a.get_size() == b.get_size());
    return a.get_size();

  default:
    CH_ABORT("invalid alu operation");
  }
}

static uint32_t get_output_size(ch_alu_op op, const lnode& a) {
  switch (op) {
  case alu_op_inv:
  case alu_op_neg:
    return a.get_size();

  case alu_op_andr:
  case alu_op_orr:
  case alu_op_xorr:
    return 1;
  default:
    CH_ABORT("invalid alu operation");
  }
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(ch_alu_op op, const lnode& a, const lnode& b)
  : lnodeimpl(to_operator(op), a.get_ctx(), get_output_size(op, a, b))
  , alu_op_(op)
  , ctime_(~0ull) {
  srcs_.emplace_back(a);
  srcs_.emplace_back(b);
}

aluimpl::aluimpl(ch_alu_op op, const lnode& a)
  : lnodeimpl(to_operator(op), a.get_ctx(), get_output_size(op, a))
  , alu_op_(op)
  , ctime_(~0ull) {
  srcs_.emplace_back(a);
}

const bitvector& aluimpl::eval(ch_cycle t) {  
  if (ctime_ != t) {  
    ctime_ = t;
    
    switch (alu_op_) {
    case alu_op_inv:
      unaryop<alu_op_inv>(value_, srcs_[0].eval(t));  
      break;
    case alu_op_and:
      binaryop<alu_op_and>(value_, srcs_[0].eval(t), srcs_[1].eval(t));  
      break;
    case alu_op_or:
      binaryop<alu_op_or>(value_, srcs_[0].eval(t), srcs_[1].eval(t));        
      break;
    case alu_op_xor:
      binaryop<alu_op_xor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));        
      break;
    case alu_op_nand:
      binaryop<alu_op_nand>(value_, srcs_[0].eval(t), srcs_[1].eval(t));  
      break;
    case alu_op_nor:
      binaryop<alu_op_nor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));        
      break;
    case alu_op_xnor:
      binaryop<alu_op_xnor>(value_, srcs_[0].eval(t), srcs_[1].eval(t));        
      break;
    
    case alu_op_andr:
      reduceop<alu_op_andr>(value_, srcs_[0].eval(t));  
      break;
    case alu_op_orr:
      reduceop<alu_op_orr>(value_, srcs_[0].eval(t));        
      break;
    case alu_op_xorr:
      reduceop<alu_op_xorr>(value_, srcs_[0].eval(t));        
      break;
      
    case alu_op_shl:
      shiftop<alu_op_shl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_shr:
      shiftop<alu_op_shr>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_rotl:
      shiftop<alu_op_rotl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_rotr:
      shiftop<alu_op_rotr>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    case alu_op_add:
      Add(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_sub:{
        bitvector minus_b(value_.get_size());
        unaryop<alu_op_inv>(minus_b, srcs_[1].eval(t));
        Add(value_, srcs_[0].eval(t), minus_b, 1);
      } break;
    case alu_op_mult:
    case alu_op_div:
    case alu_op_mod:
      CH_TODO();
      break;
      
    case alu_op_eq:
      compareop<alu_op_eq>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_ne:
      compareop<alu_op_ne>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_lt:
      compareop<alu_op_lt>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_gt:
      compareop<alu_op_gt>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_le:
      compareop<alu_op_le>(value_, srcs_[0].eval(t), srcs_[1].eval(t));  
      break;
    case alu_op_ge:
      compareop<alu_op_ge>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;  
      
    case alu_op_mux:
      Mux(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_demux:
      CH_TODO();
      break;
      
    case alu_op_fadd:
      fAdd(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    case alu_op_fsub:
      fSub(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    case alu_op_fmult:
      fMult(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    case alu_op_fdiv:
      fDiv(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
      
    default:
      CH_TODO();
    }
  }
  return value_;
}

void aluimpl::print_vl(std::ostream& out) const {
  CH_UNUSED(out);
  CH_TODO();
} 

lnodeimpl* cash::detail::createAluNode(
    ch_alu_op op,
    const lnode& a,
    const lnode& b) {
  return new aluimpl(op, a, b);
}

lnodeimpl* cash::detail::createAluNode(ch_alu_op op, const lnode& a) {
  return new aluimpl(op, a);
}
