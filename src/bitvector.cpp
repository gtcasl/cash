#include "bitvector.h"

using namespace ch::internal;

bitvector::bitvector(const bitvector& other)
  : bitvector() {
  this->resize(other.size_);
  std::copy(other.words_, other.words_ + other.num_words(), words_);
}

bitvector::bitvector(bitvector&& other) {
  words_ = other.words_;
  size_ = other.size_;
  other.words_ = nullptr;
  other.size_ = 0;
}

bitvector::bitvector(uint32_t size)
  : bitvector() {
  this->resize(size, 0, true);
}

bitvector::bitvector(uint32_t size, int64_t value)
  : bitvector() {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, uint64_t value)
  : bitvector() {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, const std::string& value)
  : bitvector() {
  this->resize(size);
  this->operator =(value);
}

bitvector::~bitvector() {
  this->clear();
}

void bitvector::clear() {
  if (words_) {
    delete [] words_;
    words_ = nullptr;
  }
  size_ = 0;
}

void bitvector::resize(uint32_t size,
                       uint32_t value,
                       bool initialize,
                       bool preserve) {
  auto old_num_words = (size_ + WORD_MASK) >> WORD_LOGSIZE;
  auto new_num_words = (size + WORD_MASK) >> WORD_LOGSIZE;
  if (new_num_words != old_num_words) {
    auto words = new word_t[new_num_words];
    if (words_) {      
      if (preserve) {
        std::copy(words_, words_ + std::min(new_num_words, old_num_words), words);
      }
      delete [] words_;
    }
    if (initialize && new_num_words > old_num_words) {
      std::fill(words + old_num_words, words + new_num_words, value);
    }
    words_ = words;    
  }   
  size_ = size;
  if (initialize) {
    this->clear_unused_bits();
  }
}

void bitvector::clear_unused_bits() {
  auto extra_bits = size_ & WORD_MASK;
  if (extra_bits) {
    auto num_words = this->num_words();
    words_[num_words-1] &= ~(~word_t(0) << extra_bits);
  }
}

bitvector& bitvector::operator=(const bitvector& other) {
  if (0 == size_) {
    this->resize(other.size_);
  }
  assert(size_ == other.size_);
  std::copy(other.words_, other.words_ + other.num_words(), words_);
  return *this;
}

bitvector& bitvector::operator=(bitvector&& other) {
  delete[] words_;
  size_ = other.size_;
  words_ = other.words_;
  other.size_ = 0;
  other.words_ = nullptr;
  return *this;
}

bitvector& bitvector::operator=(int64_t value) {
  assert(size_);
  // check for extra bits
  CH_CHECK(ceilpow2(value) <= size_, "value out of range");
  // write the value
  words_[0] = value;
  this->clear_unused_bits();
  return *this;
}

bitvector& bitvector::operator=(uint64_t value) {
  assert(size_);
  // check for extra bits
  CH_CHECK(ceilpow2(value) <= size_, "value out of range");
  // write the value
  words_[0] = value;
  return *this;
}

bitvector& bitvector::operator=(const std::string& value) {
  assert(size_);

  int base = 0;
  int start = 0;
  size_t len = value.length();

  switch (value[len-1]) {
  case 'b':
    base = 2;
    break;
  case 'o':
    base = 8;
    break;
  case 'h':
    base = 16;
    if (len > 1 && (value[1] == 'x' || value[1] == 'X')) {
      start = 2;
    }
    break;
  default:
    CH_ABORT("invalid binary format, missing encoding base type.");
  }
  
  uint32_t log_base = log2ceil(base);
  len -= 2; // remove type info
  
  // calculate binary size
  uint32_t size = 0;  
  for (uint32_t i = start; i < len; ++i) {
    char chr = value[i];
    if (chr == '\'') 
      continue; // skip separator character
    if (0 == size) {
       // calculate exact bit coverage for the first non zero character
       auto v = char2int(chr, base);
       if (v) {
         size += ilog2(v) + 1;
       }
    } else {
      size += log_base;
    }
  }
  CH_CHECK(size_ >= size, "value out of range");
  
  // clear extra words
  auto num_words = this->num_words();
  auto src_num_words = (size + WORD_MASK) >> WORD_LOGSIZE;
  if (src_num_words < num_words) {
    std::fill_n(words_ + src_num_words, num_words - src_num_words, 0x0);
  }
  
  // write the value
  word_t w(0);
  word_t* dst = words_;
  for (uint32_t i = 0, j = 0, n = len - start; i < n; ++i) {
    char chr = value[len - i - 1];
    if (chr == '\'')
      continue; // skip separator character
    word_t v = char2int(chr, base);
    w |= v << j;
    j += log_base;
    if (j >= WORD_SIZE) {
      *dst++ = w;
      j -= WORD_SIZE;
      w = v >> (log_base - j);      
    }
  }

  if (w) {
    *dst = w;
  }
  
  return *this;
}

bitvector::const_reference bitvector::at(uint32_t index) const {
  assert(index < size_);
  auto widx = index >> WORD_LOGSIZE;
  auto wbit = index & WORD_MASK;
  auto mask = word_t(1) << wbit;
  return (words_[widx] & mask) != 0;
}

bitvector::reference bitvector::at(uint32_t index) {
  assert(index < size_);
  auto widx = index >> WORD_LOGSIZE;
  auto wbit = index & WORD_MASK;
  auto mask = word_t(1) << wbit;
  return reference(words_[widx], mask);
}

bool bitvector::operator==(const bitvector& other) const {
  if (size_ != other.size_)
    return false;
  for (uint32_t i = 0, n = other.num_words(); i < n; ++i) {
    if (words_[i] != other.words_[i])
      return false;
  }
  return true;
}

void bitvector::copy(uint32_t dst_offset,
                     const bitvector& src,
                     uint32_t src_offset,
                     uint32_t length) {
  assert(size_ > 0);
  assert(src.size_ > 0);
  assert(src_offset + length <= src.size_);
  assert(dst_offset + length <= size_);
  if (length == size_ && src.size_ == size_) {
    assert(0 == dst_offset && 0 == src_offset);
    *this = src;
  } else {  
    const_iterator iter_src(src.begin() + src_offset);
    iterator iter_dst(this->begin() + dst_offset);
    while (length--) {
      *iter_dst++ = *iter_src++;
    }
  }
}

int bitvector::find_first() const {
  for (uint32_t i = 0, n = this->num_words(); i < n; ++i) {
    auto w = words_[i];
    if (w) {
      int z = ctz(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

int bitvector::find_last() const {
  for (int32_t i = this->num_words() - 1; i >= 0; --i) {
    auto w = words_[i];
    if (w) {
      int z = clz(w);
      return (WORD_MASK - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

bool bitvector::empty() const {
  for (uint32_t i = 0, n = this->num_words(); i < n; ++i) {
    if (words_[i])
      return false;
  }
  return true;
}

void bitvector::read(
    uint32_t src_offset,
    void* dst,
    uint32_t dst_cbsize,
    uint32_t dst_offset,
    uint32_t length) const {
  CH_CHECK(src_offset + length <= size_, "out of bound access");
  CH_CHECK(dst_offset + length <= dst_cbsize * 8, "out of bound access");

  uint32_t b_dst_offset = dst_offset / 8;
  auto b_dst = reinterpret_cast<uint8_t*>(dst) + b_dst_offset;
  uint32_t dst_rem = dst_offset & 0x7;
  uint32_t src_rem = src_offset & 0x7;
  uint32_t end_rem = (dst_offset + length) & 0x7;

  if (0 == src_rem
   && 0 == dst_rem) {
    // byte-aligned offsets
    uint32_t b_length = CH_CEILDIV(length, 8);
    uint32_t b_src_offset = src_offset / 8;
    auto b_src = reinterpret_cast<uint8_t*>(words_) + b_src_offset;
    if (0 == end_rem) {
      std::copy_n(b_src, b_length, b_dst);
    } else {
      // copy all bytes except the last one
      uint32_t end = b_length - 1;
      std::copy_n(b_src, end, b_dst);
      // only update set bits from source in the last byte
      uint32_t sel_mask = (~0UL << end_rem);
      b_dst[end] = CH_BLEND(sel_mask, b_src[end], b_dst[end]);
    }
  } else {
    uint8_t tmp = 0;
    auto iter = this->begin() + src_offset;
    if (dst_rem) {
      tmp = *b_dst & ~(~0UL << dst_rem);
    }
    for (uint32_t i = dst_offset, end = dst_offset + length; i < end; ++i) {
      uint32_t shift = i & 0x7;
      tmp |= (*iter++) << shift;
      if (shift == 0x7) {
        *b_dst++ = tmp;
        tmp = 0;
      }
    }
    if (end_rem) {
      uint32_t sel_mask = (~0UL << end_rem);
      *b_dst = CH_BLEND(sel_mask, tmp, *b_dst);
    }
  }
}

void bitvector::write(
    uint32_t dst_offset,
    const void* src,
    uint32_t src_cbsize,
    uint32_t src_offset,
    uint32_t length) {
  CH_CHECK(dst_offset + length <= size_, "out of bound access");
  CH_CHECK(src_offset + length <= src_cbsize * 8, "out of bound access");

  uint32_t b_src_offset = src_offset / 8;
  auto b_src = reinterpret_cast<const uint8_t*>(src) + b_src_offset;
  uint32_t dst_rem = dst_offset & 0x7;
  uint32_t src_rem = src_offset & 0x7;

  if (0 == dst_rem
   && 0 == src_rem) {
    // byte-aligned offsets
    uint32_t b_length = CH_CEILDIV(length, 8);
    uint32_t b_dst_offset = dst_offset / 8;
    auto b_dst = reinterpret_cast<uint8_t*>(words_) + b_dst_offset;
    uint32_t end_rem = (src_offset + length) & 0x7;
    if (0 == end_rem) {
      std::copy_n(b_src, b_length, b_dst);
    } else {
      // copy all bytes except the last one
      uint32_t end = b_length - 1;
      std::copy_n(b_src, end, b_dst);
      // only update set bits from source in the last byte
      uint32_t sel_mask = (~0UL << end_rem);
      b_dst[end] = CH_BLEND(sel_mask, b_src[end], b_dst[end]);
    }
  } else {
    auto iter = this->begin() + dst_offset;
    uint32_t tmp = 0;
    for (uint32_t i = src_offset, end = src_offset + length; i < end; ++i) {
      uint32_t shift = i & 0x7;
      if (i == src_offset || 0 == shift) {
        tmp = *b_src++;
      }
      *iter++ = (tmp >> shift) & 0x1;            
    }
  }
}

void bitvector::deadbeef() {
  for (uint32_t i = 0, n = this->num_words(); i < n; ++i) {
    words_[i] = bitcast<word_t>(0xdeadbeefdeadbeef);
  }
  this->clear_unused_bits();
}

std::ostream& ch::internal::operator<<(std::ostream& out, const bitvector& in) {
  out << "0x";
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);

  bitvector::word_t word(0);
  bool skip_zeros = true;  
  auto size = in.size();

  for (auto it = in.begin() + (size - 1); size;) {
    word = (word << 0x1) | *it--;
    if (0 == (--size & 0x3)) {
      if (0 == size || (word != 0 ) || !skip_zeros) {
        out << word;
        skip_zeros = false;
      }
      word = 0;
    }
  }
  if (0 != (size & 0x3)) {
    out << word;
  }
  out.flags(oldflags);
  return out;
}

///////////////////////////////////////////////////////////////////////////////

bool ch::internal::bv_ltu(const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() == rhs.size());
  for (int32_t i = rhs.num_words() - 1; i >= 0; --i) {
    if (lhs.word(i) < rhs.word(i))
      return true;
    if (lhs.word(i) > rhs.word(i))
      return false;
  }
  return false;
}

bool ch::internal::bv_lts(const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() == rhs.size());
  auto msb_idx = lhs.size() - 1;
  bool lhs_is_neg = lhs[msb_idx];
  bool rhs_is_neg = rhs[msb_idx];

  // lhs is negative and rhs is non-negative
  if (lhs_is_neg && !rhs_is_neg) {
    return true;
  }

  // lhs is non-negative and rhs is negative
  if (!lhs_is_neg && rhs_is_neg) {
    return false;
  }

  // both negative or both non-negative
  // compare most significant words without the signed bit
  auto num_words = lhs.num_words();
  auto msb_mask = (bitvector::word_t(1) << (msb_idx % bitvector::WORD_SIZE)) - 1;
  auto lhs_msw = lhs.word(num_words - 1) & msb_mask;
  auto rhs_msw = rhs.word(num_words - 1) & msb_mask;
  if (lhs_msw < rhs_msw)
    return true;
  if (lhs_msw > rhs_msw)
    return false;

  // compare remaining words
  for (int32_t i = num_words - 2; i >= 0; --i) {
    if (lhs.word(i) < rhs.word(i))
      return true;
    if (lhs.word(i) > rhs.word(i))
      return false;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_inv(bitvector& out, const bitvector& in) {
  assert(out.size() == in.size());
  for (uint32_t i = 0, n = in.num_words(); i < n; ++i) {
    out.word(i) = ~in.word(i);
  }
  out.clear_unused_bits();
}

void ch::internal::bv_and(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.size() == lhs.size());
  assert(lhs.size() == rhs.size());
  for (int32_t i = 0, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) & rhs.word(i);
  }
}

void ch::internal::bv_or(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.size() == lhs.size());
  assert(lhs.size() == rhs.size());
  for (int32_t i = 0, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) | rhs.word(i);
  }
}

void ch::internal::bv_xor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.size() == lhs.size());
  assert(lhs.size() == rhs.size());
  for (int32_t i = 0, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) ^ rhs.word(i);
  }
}

///////////////////////////////////////////////////////////////////////////////

bool ch::internal::bv_andr(const bitvector& in) {
  auto in_w = in.word(0);
  auto result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.word(j++);
    }
    in_w >>= 1;
    result &= (in_w & 0x1);
  }
  return (result != 0);
}

bool ch::internal::bv_orr(const bitvector& in) {
  auto in_w = in.word(0);
  auto result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.word(j++);
    }
    in_w >>= 1;
    result |= (in_w & 0x1);
  }
  return (result != 0);
}

bool ch::internal::bv_xorr(const bitvector& in) {
  auto in_w = in.word(0);
  auto result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = in.size(); i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = in.word(j++);
    }
    in_w >>= 1;
    result ^= (in_w & 0x1);
  }
  return (result != 0);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_sll(bitvector& out, const bitvector& in, const bitvector& bits) {
  CH_CHECK(bits.find_last() <= bitvector::WORD_MASK, "shift amount out of range");
  auto dist = bitcast<uint32_t>(bits.word(0));
  auto out_num_words = out.num_words();
  if (1 == out_num_words) {
    out.word(0) = in.word(0) << dist;
  } else {
    auto in_num_words = in.num_words();
    auto shift_words = dist >> bitvector::WORD_LOGSIZE;
    if (dist < out.size()) {
      auto shift_bits = dist & bitvector::WORD_MASK;
      auto shift_bits_r = bitvector::WORD_SIZE - shift_bits;
      bitvector::word_t prev(0);
      for (uint32_t i = 0, n = out_num_words - shift_words; i < n; ++i) {
        auto curr = (i < in_num_words) ? in.word(i) : bitvector::word_t(0);
        auto pad = prev >> shift_bits_r;
        out.word(i + shift_words) = (curr << shift_bits) | pad;
        prev = curr;
      }
    } else {
      shift_words = out_num_words;
    }
    std::fill_n(out.words(), shift_words, 0x0);
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

void ch::internal::bv_srl(bitvector& out, const bitvector& in, const bitvector& bits) {  
  CH_CHECK(bits.find_last() <= bitvector::WORD_MASK, "shift amount out of range");
  auto dist = bitcast<uint32_t>(bits.word(0));
  auto shift_words = dist >> bitvector::WORD_LOGSIZE;
  auto out_num_words = out.num_words();
  auto in_num_words = in.num_words();
  if (1 == in_num_words) {
    out.word(0) = in.word(0) >> dist;
  } else {
    if (dist < in.size()) {
      auto shift_bits = dist & bitvector::WORD_MASK;
      auto shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      bitvector::word_t prev(0);
      for (int32_t i = in_num_words - 1 - shift_words; i >= 0; --i) {
        auto curr = in.word(i + shift_words);
        auto pad = prev << shift_bits_l;
        if (uint32_t(i) < out_num_words) {
          out.word(i) = (curr >> shift_bits) | pad;
        }
        prev = curr;
      }
    } else {
      shift_words = in_num_words;
    }
  }  
  auto rem_words = in_num_words - shift_words;
  if (rem_words < out_num_words) {
    std::fill_n(out.words() + rem_words, out_num_words - rem_words, 0x0);
  }
}

void ch::internal::bv_sra(bitvector& out, const bitvector& in, const bitvector& bits) {
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range");
  auto size = in.size();
  auto dist = bitcast<uint32_t>(bits.word(0));
  auto shift_words = dist >> bitvector::WORD_LOGSIZE;
  auto fill_value = in[size - 1] ? bitvector::WORD_MAX : bitvector::word_t(0);
  auto out_num_words = out.num_words();
  auto in_num_words = in.num_words();
  if (1 == in_num_words) {
    bitvector::sword_t value = sign_ext(in.word(0), size);
    out.word(0) = value >> dist;
  } else {
    if (dist < size) {
      auto shift_bits = dist & bitvector::WORD_MASK;
      auto shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      auto prev = fill_value;
      for (int32_t i = in_num_words - 1 - shift_words; i >= 0; --i) {
        auto curr = in.word(i + shift_words);
        auto pad = prev << shift_bits_l;
        if (uint32_t(i) < out_num_words) {
          out.word(i) = (curr >> shift_bits) | pad;
        }
        prev = curr;
      }
    } else {
      shift_words = in_num_words;
    }    
  }
  auto rem_words = in_num_words - shift_words;
  if (rem_words < out_num_words) {
    std::fill_n(out.words() + rem_words, out_num_words - rem_words, fill_value);
  }
  if (fill_value) {
    out.clear_unused_bits();
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_add(bitvector& out, const bitvector& lhs, const bitvector& rhs, uint32_t cin) {
  assert(lhs.size() == out.size());
  assert(rhs.size() == out.size());

  auto size = out.size();
  auto num_words = out.num_words();

  for (uint32_t i = 0; i < num_words; ++i) {
    auto a_w = lhs.word(i);
    auto b_w = rhs.word(i);
    auto c_w = a_w + b_w;

    uint32_t cout = 0;
    if (size < bitvector::WORD_SIZE)  {
      c_w += cin;
      c_w &= ~(bitvector::word_t(1) << size); // remove overflow bit
    } else {
      if (c_w < a_w)
        cout = 1;
      c_w += cin;
      if (c_w < cin)
        cout = 1;
      size -= bitvector::WORD_SIZE;
      cin = cout;
    }
    out.word(i) = c_w;
  }
}

void ch::internal::bv_sub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  bitvector minus_b(out.size());
  bv_inv(minus_b, rhs);
  bv_add(out, lhs, minus_b, 1);
}

void ch::internal::bv_neg(bitvector& out, const bitvector& in) {
  bitvector zero(out.size(), 0x0);
  bv_sub(out, zero, in);
}

void ch::internal::bv_mul(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() == out.size());
  assert(rhs.size() == out.size());
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    auto a_w = lhs.word(0);
    auto b_w = rhs.word(0);
    out.word(0) = a_w * b_w;
    out.clear_unused_bits();
  } else {
    CH_TODO();
  }
}

void ch::internal::bv_divu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() == out.size());
  assert(rhs.size() == out.size());
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    auto a_w = lhs.word(0);
    auto b_w = rhs.word(0);
    out.word(0) = b_w ? (a_w / b_w) : bitvector::WORD_MAX;
  } else {
    CH_TODO();
  }
}

void ch::internal::bv_divs(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  uint32_t size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    bitvector::sword_t a_w = sign_ext(lhs.word(0), size);
    bitvector::sword_t b_w = sign_ext(rhs.word(0), size);
    out.word(0) = b_w ? uint32_t(a_w / b_w) : bitvector::WORD_MAX;
    out.clear_unused_bits();
  } else {
    CH_TODO();
  }
}

void ch::internal::bv_modu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  auto size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    auto a_w = lhs.word(0);
    auto b_w = rhs.word(0);
    out.word(0) = a_w % b_w;
  } else {
    bitvector d(size);
    bitvector m(size);
    bv_divu(d, lhs, rhs);
    bv_mul(m, d, rhs);
    bv_sub(out, lhs, m);
  }
}

void ch::internal::bv_mods(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  auto size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    bitvector::sword_t a_w = sign_ext(lhs.word(0), size);
    bitvector::sword_t b_w = sign_ext(rhs.word(0), size);
    out.word(0) = a_w % b_w;
    out.clear_unused_bits();
  } else {
    bitvector d(size);
    bitvector m(size);
    bv_divs(d, lhs, rhs);
    bv_mul(m, d, rhs);
    bv_sub(out, lhs, m);
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_zext(bitvector& out, const bitvector& in) {
  assert(out.size() >= in.size());
  std::copy(in.words(), in.words() + in.num_words(), out.words());
  std::fill(out.words() + in.num_words(),
            out.words() + out.num_words(),
            0);
}

void ch::internal::bv_sext(bitvector& out, const bitvector& in) {
  assert(out.size() >= in.size());
  auto msb_idx = in.size() - 1;
  if (in[msb_idx]) {
    auto msb_blk_idx = msb_idx >> bitvector::WORD_LOGSIZE;
    auto msb_blk_rem = msb_idx & bitvector::WORD_MASK;
    auto msb_blk = in.word(msb_blk_idx);
    std::copy(in.words(), in.words() + in.num_words(), out.words());
    out.word(msb_blk_idx) = msb_blk | (bitvector::WORD_MAX << msb_blk_rem);
    std::fill(out.words() + in.num_words(),
              out.words() + out.num_words(),
              bitvector::WORD_MAX);
    out.clear_unused_bits();
  } else {
    bv_zext(out, in);
  }
}
