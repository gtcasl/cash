#include "aluimpl.h"
#include "context.h"

using namespace cash::internal;

static void Inverse(bitvector& out, const bitvector& in) {
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

static bool AndR(const bitvector& in) {
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

static bool OrR(const bitvector& in) {
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

static bool XorR(const bitvector& in) {
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

static bool NandR(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result = ~(result & (in_w & 0x1));
  }
  return (result != 0);
}

static bool NorR(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result = ~(result | (in_w & 0x1));
  }
  return (result != 0);
}

static bool XnorR(const bitvector& in) {
  uint32_t in_w = in.get_word(0);
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.get_size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.get_word(j++);
    }
    in_w >>= 1;
    result = ~(result ^ (in_w & 0x1));
  }
  return (result != 0);
}

static void SLL(bitvector& out, const bitvector& in, uint32_t dist) {
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

static void SRL(bitvector& out, const bitvector& in, uint32_t dist) {
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

static void Add(bitvector& out, const bitvector& lhs, const bitvector& rhs, uint32_t cin = 0) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());

  uint32_t size = out.get_size();
  uint32_t num_words = out.get_num_words();

  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = lhs.get_word(i);
    uint32_t b_w = rhs.get_word(i);
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
    out.set_word(i, c_w);
  }
}

static void Sub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  bitvector minus_b(out.get_size());
  Inverse(minus_b, rhs);
  Add(out, lhs, minus_b, 1);
}

static void Negate(bitvector& out, const bitvector& in) {
  bitvector zero(out.get_size(), 0x0);
  Sub(out, zero, in);
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

static void fAdd(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef + b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  out.set_word(0, result);
}

static void fSub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef - b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  out.set_word(0, result);
}

static void fMult(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef * b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  out.set_word(0, result);
}

static void fDiv(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = *(const float*)&a_value;
  float b_valuef = *(const float*)&b_value;
  float resultf = a_valuef / b_valuef;
  uint32_t result = *(const uint32_t*)&resultf;
  out.set_word(0, result);
}

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op>
static void unaryop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  
  switch (op) {
  case alu_op_inv:
    Inverse(out, in);
    break;
  case alu_op_neg:
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
  case alu_op_and:
    And(out, lhs, rhs);
    break;
  case alu_op_or:
    Or(out, lhs, rhs);
    break;
  case alu_op_xor:
    Xor(out, lhs, rhs);
    break;
  case alu_op_nand:
    Nand(out, lhs, rhs);
    break;
  case alu_op_nor:
    Nor(out, lhs, rhs);
    break;
  case alu_op_xnor:
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
  case alu_op_sll:
    SLL(out, in, wbits);
    break;
  case alu_op_srl:
    SRL(out, in, wbits);
    break;
  case alu_op_sra:
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
static void reduceop(bitvector& out, const bitvector& in) {
  assert(out.get_size() == 1);
  
  bool result;
  switch (op) {
  case alu_op_andr:
    result = AndR(in);
    break;
  case alu_op_orr:
    result = OrR(in);
    break;
  case alu_op_xorr:
    result = XorR(in);
    break;
  case alu_op_nandr:
    result = NandR(in);
    break;
  case alu_op_norr:
    result = NorR(in);
    break;
  case alu_op_xnorr:
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
  case alu_op_eq:
    result = lhs == rhs;
    break;
  case alu_op_ne:
    result = !(lhs == rhs);
    break;
  case alu_op_lt:
    result = (lhs < rhs);
    break;
  case alu_op_gt:
    result = (rhs < lhs);
    break;
  case alu_op_le:
    result = !(rhs < lhs);
    break;
  case alu_op_ge:
    result = !(lhs < rhs);
    break;
  default:
    CH_ABORT("invalid alu operation");
  }
  out[0] = result;
}

static uint32_t get_output_size(ch_alu_op op, const lnode& lhs, const lnode& rhs) {
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
    assert(lhs.get_size() == rhs.get_size());
    return lhs.get_size();

  case alu_op_sll:
  case alu_op_srl:
  case alu_op_sra:
    return lhs.get_size();

  case alu_op_rotl:
  case alu_op_rotr:
    return lhs.get_size();

  case alu_op_eq:
  case alu_op_ne:
  case alu_op_lt:
  case alu_op_gt:
  case alu_op_le:
  case alu_op_ge:
    assert(lhs.get_size() == rhs.get_size());
    return 1;

  case alu_op_mux:
    return lhs.get_size() >> rhs.get_size();

  case alu_op_fadd:
  case alu_op_fsub:
  case alu_op_fmult:
  case alu_op_fdiv:
    assert(lhs.get_size() == rhs.get_size());
    return lhs.get_size();

  default:
    CH_ABORT("invalid alu operation");
  }
}

static uint32_t get_output_size(ch_alu_op op, const lnode& in) {
  switch (op) {
  case alu_op_inv:
  case alu_op_neg:
    return in.get_size();

  case alu_op_andr:
  case alu_op_orr:
  case alu_op_xorr:
  case alu_op_nandr:
  case alu_op_norr:
  case alu_op_xnorr:
    return 1;
  default:
    CH_ABORT("invalid alu operation");
  }
}

///////////////////////////////////////////////////////////////////////////////

aluimpl::aluimpl(ch_alu_op op, const lnode& lhs, const lnode& rhs)
  : lnodeimpl(op_alu, lhs.get_ctx(), get_output_size(op, lhs, rhs))
  , alu_op_(op)
  , tick_(~0ull) {
  srcs_.emplace_back(lhs);
  srcs_.emplace_back(rhs);
}

aluimpl::aluimpl(ch_alu_op op, const lnode& in)
  : lnodeimpl(op_alu, in.get_ctx(), get_output_size(op, in))
  , alu_op_(op)
  , tick_(~0ull) {
  srcs_.emplace_back(in);
}

const bitvector& aluimpl::eval(ch_tick t) {  
  if (tick_ != t) {  
    tick_ = t;
    
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
    case alu_op_nandr:
      reduceop<alu_op_nandr>(value_, srcs_[0].eval(t));
      break;
    case alu_op_norr:
      reduceop<alu_op_norr>(value_, srcs_[0].eval(t));
      break;
    case alu_op_xnorr:
      reduceop<alu_op_xnorr>(value_, srcs_[0].eval(t));
      break;
      
    case alu_op_sll:
      shiftop<alu_op_sll>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_srl:
      shiftop<alu_op_srl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_sra:
      shiftop<alu_op_sra>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;

    case alu_op_rotl:
      rotateop<alu_op_rotl>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_rotr:
      rotateop<alu_op_rotr>(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;

    case alu_op_add:
      Add(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_sub:
      Sub(value_, srcs_[0].eval(t), srcs_[1].eval(t));
      break;
    case alu_op_neg:
      unaryop<alu_op_neg>(value_, srcs_[0].eval(t));
      break;
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
      CH_ABORT("invalid alu operation");
    }
  }
  return value_;
}

lnodeimpl* cash::internal::createAluNode(
    ch_alu_op op,
    const lnode& lhs,
    const lnode& rhs) {
  return new aluimpl(op, lhs, rhs);
}

lnodeimpl* cash::internal::createAluNode(ch_alu_op op, const lnode& in) {
  return new aluimpl(op, in);
}
