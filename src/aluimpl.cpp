#include "aluimpl.h"
#include "context.h"

using namespace ch::internal;

const char* ch::internal::to_string(ch_alu_op op) {
  static const char* sc_names[] = {
    CH_ALUOP_ENUM(CH_ALUOP_NAME)
  };
  return sc_names[CH_ALUOP_INDEX(op)];
}

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
  case alu_inv:
    Inverse(out, in);
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
    SLL(out, in, wbits);
    break;
  case alu_srl:
    SRL(out, in, wbits);
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
