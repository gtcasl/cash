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

bitvector::bitvector(uint32_t size, uint64_t value)
  : bitvector() {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, int64_t value)
  : bitvector() {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size,
                     const std::initializer_list<uint32_t>& value)
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
  uint32_t old_num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  uint32_t new_num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  if (new_num_words != old_num_words) {
    auto words = new uint32_t[new_num_words];
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
  uint32_t extra_bits = size_ & WORD_MASK;
  if (extra_bits) {
    uint32_t num_words = this->num_words();
    words_[num_words-1] &= ~(~0UL << extra_bits);
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
  words_[0] = value & 0xffffffff;
  uint32_t num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  if (num_words > 1) {
    words_[1] = value >> 32;
    // clear extra words
    std::fill_n(words_ + 2, num_words - 2, 0x0);
  }
  this->clear_unused_bits();
  return *this;
}

bitvector& bitvector::operator=(uint64_t value) {
  assert(size_);
  // check for extra bits
  CH_CHECK(ceilpow2(value) <= size_, "value out of range");
  // write the value
  words_[0] = value & 0xffffffff;
  uint32_t num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  if (num_words > 1) {
    words_[1] = value >> 32;
    // clear extra words
    std::fill_n(words_ + 2, num_words - 2, 0x0);
  }
  return *this;
}

bitvector& bitvector::operator=(const std::initializer_list<uint32_t>& value) {
  assert(size_);

  auto iterValue = value.begin();
  uint32_t num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  uint32_t src_num_words = value.size();

  // check for extra bits
  int no_overflow = true;
  for (uint32_t i = num_words; i < src_num_words; ++i) {
    no_overflow &= !*iterValue++;
  }
  CH_CHECK(no_overflow
        || (value.size() < num_words)
        || (0 == (size_ & WORD_MASK)
        || (0 == (*iterValue >> (size_ & WORD_MASK)))), "value out of range");

  // clear extra words
  auto dst = words_ + (num_words - 1);
  if (src_num_words < num_words) {
    uint32_t unused_words = num_words - src_num_words;
    std::fill_n(dst, unused_words, 0x0);
    dst -= unused_words;
  }

  // write the value
  for (auto iterEnd = value.end(); iterValue != iterEnd; ++iterValue) {
    *dst-- = *iterValue;
  }

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
  --len; // remove type character
  
  // calculate binary size
  uint32_t size = 0;  
  for (uint32_t i = start; i < len; ++i) {
    char chr = value[i];
    if (chr == '\'') 
      continue; // skip separator character
    if (0 == size) {
       // calculate exact bit coverage for the first non zero character
       uint32_t v = char2int(chr, base);
       if (v) {
         size += ilog2(v) + 1;
       }
    } else {
      size += log_base;
    }
  }
  CH_CHECK(size_ >= size, "value out of range");
  
  // clear extra words
  uint32_t num_words = this->num_words();
  uint32_t src_num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  if (src_num_words < num_words) {
    std::fill_n(words_ + src_num_words, num_words - src_num_words, 0x0);
  }
  
  // write the value
  uint32_t w = 0;  
  uint32_t* dst = words_;
  for (uint32_t i = 0, j = 0, n = len - start; i < n; ++i) {
    char chr = value[len - i - 1];
    if (chr == '\'')
      continue; // skip separator character
    uint32_t v = char2int(chr, base);
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

bitvector::const_reference bitvector::at(uint32_t idx) const {
  assert(idx < size_);
  uint32_t widx = idx >> WORD_SIZE_LOG;
  uint32_t wbit = idx & WORD_MASK;
  uint32_t mask = 1 << wbit;
  return (words_[widx] & mask) != 0;
}

bitvector::reference bitvector::at(uint32_t idx) {
  assert(idx < size_);
  uint32_t widx = idx >> WORD_SIZE_LOG;
  uint32_t wbit = idx & WORD_MASK;
  uint32_t mask = 1 << wbit;
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
    uint32_t w = words_[i];
    if (w) {
      int z = ctz(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

int bitvector::find_last() const {
  for (int32_t i = this->num_words() - 1; i >= 0; --i) {
    uint32_t w = words_[i];
    if (w) {
      int z = clz(w);
      return (WORD_MASK - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

bool bitvector::empty() const {
  for (int32_t i = 0, n = this->num_words(); i < n; ++i) {
    if (words_[i])
      return false;
  }
  return true;
}

void bitvector::read(
    uint32_t dst_offset,
    void* dst,
    uint32_t dst_cbsize,
    uint32_t src_offset,
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
    words_[i] = 0xdeadbeef;
  }
  this->clear_unused_bits();
}

std::ostream& ch::internal::operator<<(std::ostream& out, const bitvector& in) {
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);
  out << "0x";
  auto_separator sep("_");
  for (int32_t i = in.num_words() - 1; i >= 0; --i) {
    out << sep << in.word(i);
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
  int32_t num_words = lhs.num_words();
  uint32_t msb_mask = (1 << (msb_idx % bitvector::WORD_SIZE)) - 1;
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
  uint32_t in_w = in.word(0);
  uint32_t result = in_w & 0x1;
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
  uint32_t in_w = in.word(0);
  uint32_t result = in_w & 0x1;
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
  uint32_t in_w = in.word(0);
  uint32_t result = in_w & 0x1;
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
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range");
  uint32_t dist = bits.word(0);
  uint32_t out_num_words = out.num_words();
  uint32_t in_num_words = in.num_words();
  if (1 == out_num_words) {
    out.word(0) = in.word(0) << dist;
  } else
  if (2 == out_num_words) {
    uint64_t value = (in.num_words() > 1) ? in.word(1) : 0;  ;
             value = (value << 32) | in.word(0);
    uint64_t result = value << dist;
    out.word(0) = bitcast<uint32_t>(result);
    out.word(1) = bitcast<uint32_t>(result >> 32);
  } else {
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    if (dist < out.size()) {
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = 0;
      for (uint32_t i = 0, n = out_num_words - shift_words; i < n; ++i) {
        uint32_t curr = (i < in_num_words) ? in.word(i) : 0;
        uint32_t pad = uint64_t(prev) >> shift_bits_r;
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
  uint32_t size = in.size();
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range");
  uint32_t dist = bits.word(0);
  uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
  uint32_t out_num_words = out.num_words();
  uint32_t in_num_words = in.num_words();
  if (1 == in_num_words) {
    out.word(0) = in.word(0) >> dist;
  } else
  if (2 == in_num_words) {
    uint64_t value = (bitcast<uint64_t>(in.word(1)) << 32) | in.word(0);
    uint64_t result = value >> dist;    
    out.word(0) = bitcast<uint32_t>(result);
    if (out.num_words() > 1) {
      out.word(1) = bitcast<uint32_t>(result >> 32);
    }
  } else {        
    if (dist < size) {      
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = 0;
      for (int32_t i = in_num_words - 1 - shift_words; i >= 0; --i) {
        uint32_t curr = in.word(i + shift_words);
        uint32_t pad = uint64_t(prev) << shift_bits_l;
        if (uint32_t(i) < out_num_words) {
          out.word(i) = (curr >> shift_bits) | pad;
        }
        prev = curr;
      }
    } else {
      shift_words = in_num_words;
    }
  }  
  uint32_t rem_words = in_num_words - shift_words;
  if (rem_words < out_num_words) {
    std::fill_n(out.words() + rem_words, out_num_words - rem_words, 0x0);
  }
}

void ch::internal::bv_sra(bitvector& out, const bitvector& in, const bitvector& bits) {
  uint32_t size = in.size();
  CH_CHECK(bits.find_last() <= 31, "shift amount out of range");
  uint32_t dist = bits.word(0);
  uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
  uint32_t fill_value = in[size - 1] ? 0xffffffff : 0x0;  
  uint32_t out_num_words = out.num_words();
  uint32_t in_num_words = in.num_words();
  if (1 == in_num_words) {
    int value = sign_ext(in.word(0), size);
    out.word(0) = value >> dist;
  } else
  if (2 == in_num_words) {
    int64_t value = sign_ext((bitcast<uint64_t>(in.word(1)) << 32) | in.word(0), size);
    int64_t result = value >> dist;
    out.word(0) = bitcast<uint32_t>(result);
    if (out.num_words() > 1) {
      out.word(1) = bitcast<uint32_t>(result >> 32);
    }
  } else {
    if (dist < size) {
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = fill_value;
      for (int32_t i = in_num_words - 1 - shift_words; i >= 0; --i) {
        uint32_t curr = in.word(i + shift_words);
        uint32_t pad = uint64_t(prev) << shift_bits_l;
        if (uint32_t(i) < out_num_words) {
          out.word(i) = (curr >> shift_bits) | pad;
        }
        prev = curr;
      }
    } else {
      shift_words = in_num_words;
    }    
  }
  uint32_t rem_words = in_num_words - shift_words;
  if (rem_words < out_num_words) {
    std::fill_n(out.words() + rem_words, out_num_words - rem_words, fill_value);
  }
  if (fill_value) {
    out.clear_unused_bits();
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_add(bitvector& out, const bitvector& lhs, const bitvector& rhs, uint32_t cin) {
  assert(out.size() == lhs.size());
  assert(lhs.size() == rhs.size());

  uint32_t size = out.size();
  uint32_t num_words = out.num_words();

  for (uint32_t i = 0; i < num_words; ++i) {
    uint32_t a_w = lhs.word(i);
    uint32_t b_w = rhs.word(i);
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
  uint32_t size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    uint32_t a_w = lhs.word(0);
    uint32_t b_w = rhs.word(0);
    out.word(0) = a_w * b_w;
    out.clear_unused_bits();
  } else
  if (2 == lhs.num_words()
   && 2 == rhs.num_words()) {
    uint64_t a_w = (bitcast<uint64_t>(lhs.word(1)) << 32) | lhs.word(0);
    uint64_t b_w = (bitcast<uint64_t>(rhs.word(1)) << 32) | rhs.word(0);
    uint64_t o_w = a_w * b_w;
    out.word(0) = bitcast<uint32_t>(o_w);
    out.word(1) = bitcast<uint32_t>(o_w >> 32);
    out.clear_unused_bits();
  } else {
    CH_TODO();
  }
}

void ch::internal::bv_divu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  uint32_t size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    uint32_t a_w = lhs.word(0);
    uint32_t b_w = rhs.word(0);
    out.word(0) = b_w ? (a_w / b_w) : bitvector::WORD_MAX;
  } else
    if (2 == lhs.num_words()
     && 2 == rhs.num_words()) {
    uint64_t a_w = (bitcast<uint64_t>(lhs.word(1)) << 32) | lhs.word(0);
    uint64_t b_w = (bitcast<uint64_t>(rhs.word(1)) << 32) | rhs.word(0);
    uint64_t o_w = b_w ? (a_w / b_w) : 0xffffffffffffffff;
    out.word(0) = bitcast<uint32_t>(o_w);
    out.word(1) = bitcast<uint32_t>(o_w >> 32);
    out.clear_unused_bits();
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
    int32_t a_w = sign_ext(lhs.word(0), size);
    int32_t b_w = sign_ext(rhs.word(0), size);
    out.word(0) = b_w ? uint32_t(a_w / b_w) : bitvector::WORD_MAX;
    out.clear_unused_bits();
  } else
    if (2 == lhs.num_words()
     && 2 == rhs.num_words()) {
    int64_t a_w = sign_ext((bitcast<uint64_t>(lhs.word(1)) << 32) | lhs.word(0), size);
    int64_t b_w = sign_ext((bitcast<uint64_t>(rhs.word(1)) << 32) | rhs.word(0), size);
    int64_t o_w = b_w ? (a_w / b_w) : 0xffffffffffffffff;
    out.word(0) = bitcast<uint32_t>(o_w);
    out.word(1) = bitcast<uint32_t>(o_w >> 32);
    out.clear_unused_bits();
  } else {
    CH_TODO();
  }
}

void ch::internal::bv_modu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  uint32_t size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    uint32_t a_w = lhs.word(0);
    uint32_t b_w = rhs.word(0);
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
  uint32_t size = out.size();
  assert(lhs.size() == size);
  assert(rhs.size() == size);
  if (1 == lhs.num_words()
   && 1 == rhs.num_words()) {
    int32_t a_w = sign_ext(lhs.word(0), size);
    int32_t b_w = sign_ext(rhs.word(0), size);
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
    auto msb_blk_idx = msb_idx >> bitvector::WORD_SIZE_LOG;
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
