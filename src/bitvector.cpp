#include "bitvector.h"

using namespace ch::internal;

bitvector::bitvector(const bitvector& other)
  : bitvector() {
  this->resize(other.size_);
  std::copy_n(other.words_, other.num_words(), words_);
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
  uint32_t old_num_words = (size_ + WORD_MASK) >> WORD_LOGSIZE;
  uint32_t new_num_words = (size + WORD_MASK) >> WORD_LOGSIZE;
  if (new_num_words != old_num_words) {
    auto words = new word_t[new_num_words];
    if (words_) {      
      if (preserve) {
        std::copy_n(words_, std::min(new_num_words, old_num_words), words);
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
    this->clear_extra_bits();
  }
}

void bitvector::clear_extra_bits() {
  uint32_t extra_bits = size_ & WORD_MASK;
  if (extra_bits) {
    uint32_t num_words = this->num_words();
    words_[num_words-1] &= ~(WORD_MAX << extra_bits);
  }
}

bitvector& bitvector::operator=(const bitvector& other) {
  if (0 == size_) {
    this->resize(other.size_);
  }
  assert(size_ == other.size_);
  std::copy_n(other.words_, other.num_words(), words_);
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
  if (value < 0) {
    CH_CHECK(1 + log2ceil(~value + 1) <= size_, "value out of range");
  } else {
    CH_CHECK(log2ceil(value + 1) <= size_, "value out of range");
  }

  // write the value
  if (value >= 0) {
    this->reset();
    if (0 == value)
      return *this;
  } else {
    this->set();
  }
  if constexpr (WORD_SIZE == 64) {
    words_[0] = value;
  } else {
    auto len = std::min<uint32_t>(this->num_words(), 64 / WORD_SIZE);
    std::copy_n((const word_t*)&value, len, words_);
  }
  this->clear_extra_bits();
  return *this;
}

bitvector& bitvector::operator=(uint64_t value) {
  assert(size_);
  // check for extra bits
  CH_CHECK(log2ceil(value + 1) <= size_, "value out of range");
  // write the value
  this->reset();
  if constexpr (WORD_SIZE == 64) {
    words_[0] = value;
  } else {
    auto len = std::min<uint32_t>(this->num_words(), 64 / WORD_SIZE);
    std::copy_n((const word_t*)&value, len, words_);
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
  len -= 2; // remove type info
  
  // calculate binary size
  uint32_t size = 0;  
  for (uint32_t i = start; i < len; ++i) {
    char chr = value[i];
    if (chr == '\'') 
      continue; // skip separator character
    if (0 == size) {
       // calculate exact bit coverage for the first non zero character
       int v = char2int(chr, base);
       if (v) {
         size += log2ceil(v+1);
       }
    } else {
      size += log_base;
    }
  }
  CH_CHECK(size_ >= size, "value out of range");
  
  // clear extra words
  uint32_t num_words = this->num_words();
  uint32_t src_num_words = (size + WORD_MASK) >> WORD_LOGSIZE;
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
  uint32_t widx = index >> WORD_LOGSIZE;
  uint32_t wbit = index & WORD_MASK;
  auto mask = word_t(1) << wbit;
  return (words_[widx] & mask) != 0;
}

bitvector::reference bitvector::at(uint32_t index) {
  assert(index < size_);
  uint32_t widx = index >> WORD_LOGSIZE;
  uint32_t wbit = index & WORD_MASK;
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

int bitvector::find_first() const {
  assert(size_);
  auto w = words_[0];
  if (w)
    return count_trailing_zeros<word_t>(w);

  for (uint32_t i = 1, n = this->num_words(); i < n; ++i) {
    auto w = words_[i];
    if (w) {
      int z = count_trailing_zeros<word_t>(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

int bitvector::find_last() const {
  assert(size_);
  int32_t i = this->num_words() - 1;
  auto w = words_[i];
  if (w) {
    int z = count_leading_zeros<word_t>(w);
    return (WORD_SIZE - z) + i * WORD_SIZE;
  }

  --i;
  for (; i >= 0; --i) {
    auto w = words_[i];
    if (w) {
      int z = count_leading_zeros<word_t>(w);
      return (WORD_SIZE - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

void bitvector::set() {
  assert(size_);
  words_[0] = WORD_MAX;
  std::fill_n(words_ + 1, this->num_words() - 1, WORD_MAX);
  this->clear_extra_bits();
}

void bitvector::reset() {
  assert(size_);
  words_[0] = 0;
  std::fill_n(words_ + 1, this->num_words() - 1, 0);
}

bool bitvector::is_zero() const {
  assert(size_);
  if (words_[0])
    return false;

  for (uint32_t i = 1, n = this->num_words(); i < n; ++i) {
    if (words_[i])
      return false;
  }
  return true;
}

template <typename T>
void copy_bits(T* dst, uint32_t dst_offset, const T* src, uint32_t src_offset, uint32_t length) {
  static_assert(std::is_integral_v<T> && std::is_unsigned_v<T>, "invalid type");
  static unsigned constexpr WORD_SIZE = bitwidth_v<T>;
  static constexpr unsigned WORD_MASK = WORD_SIZE - 1;
  static constexpr T        WORD_MAX  = std::numeric_limits<T>::max();

  uint32_t w_src_begin_idx = src_offset / WORD_SIZE;
  uint32_t w_src_begin_rem = src_offset & WORD_MASK;
  uint32_t src_end         = src_offset + length - 1;
  uint32_t w_src_end_idx   = (src_end / WORD_SIZE) - w_src_begin_idx;
  auto w_src               = src + w_src_begin_idx;

  uint32_t w_dst_begin_idx = dst_offset / WORD_SIZE;
  uint32_t w_dst_begin_rem = dst_offset & WORD_MASK;
  uint32_t dst_end         = dst_offset + length - 1;
  uint32_t w_dst_end_idx   = (dst_end / WORD_SIZE) - w_dst_begin_idx;
  uint32_t w_dst_end_rem   = dst_end & WORD_MASK;
  auto w_dst               = dst + w_dst_begin_idx;

  if (length <= WORD_SIZE) {
    T src_block = (w_src[0] >> w_src_begin_rem);
    if (1 == w_src_end_idx) {
      src_block |= (w_src[1] << (WORD_SIZE - w_src_begin_rem));
    }
    if (0 == w_dst_end_idx) {
      T sel_mask = (WORD_MAX >> (WORD_SIZE - length)) << w_dst_begin_rem;
      w_dst[0] = blend<T>(sel_mask, w_dst[0], (src_block << w_dst_begin_rem));
    } else {
      T sel_mask = WORD_MAX << w_dst_begin_rem;
      w_dst[0] = blend<T>(sel_mask, w_dst[0], (src_block << w_dst_begin_rem));
      src_block = src_block >> (WORD_SIZE - w_dst_begin_rem);
      sel_mask = (WORD_MAX << 1) << w_dst_end_rem;
      w_dst[1] = blend<T>(sel_mask, src_block, w_dst[1]);
    }
  } else
  if (0 == w_dst_begin_rem
   && 0 == w_src_begin_rem) {
    // update aligned blocks
    if (WORD_MASK == w_dst_end_rem) {
      std::copy_n(w_src, w_dst_end_idx + 1, w_dst);
    } else {
      std::copy_n(w_src, w_dst_end_idx, w_dst);
      // update remining block
      T src_block = w_src[w_dst_end_idx];
      T sel_mask = (WORD_MAX << 1) << w_dst_end_rem;
      w_dst[w_dst_end_idx] = blend<T>(sel_mask, src_block, w_dst[w_dst_end_idx]);
    }
  } else
  if (0 == w_dst_begin_rem) {
    // update first block
    T src_block = *w_src++ >> w_src_begin_rem;
    src_block |= w_src[0] << (WORD_SIZE - w_src_begin_rem);
    w_dst[0] = src_block;

    // update intermediate blocks
    auto w_dst_end = (w_dst++) + w_dst_end_idx;
    while (w_dst < w_dst_end) {
      T tmp = *w_src++ >> w_src_begin_rem;
      *w_dst++ = tmp | (w_src[0] << (WORD_SIZE - w_src_begin_rem));
    }

    // update remining blocks
    src_block = w_src[0] >> w_src_begin_rem;
    if (w_src_end_idx > w_dst_end_idx) {
      src_block |= (w_src[1] << (WORD_SIZE - w_src_begin_rem));
    }
    T sel_mask = (WORD_MAX << 1) << w_dst_end_rem;
    w_dst[0] = blend<T>(sel_mask, src_block, w_dst[0]);
  } else
  if (0 == w_src_begin_rem) {
    // update first block
    T src_block = *w_src++;
    T sel_mask = WORD_MAX << w_dst_begin_rem;
    w_dst[0] = blend<T>(sel_mask, w_dst[0], (src_block << w_dst_begin_rem));

    // update intermediate blocks
    auto w_dst_end = (w_dst++) + w_src_end_idx;
    while (w_dst < w_dst_end) {
      auto tmp = *w_src++;
      *w_dst++ = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
      src_block = tmp;
    }

    // update remining blocks
    src_block = (w_src[0] << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
    if (w_src_end_idx < w_dst_end_idx) {
      *w_dst++ = src_block;
      src_block = (w_src[0] >> 1) >> (WORD_MASK - w_dst_begin_rem);
    }
    sel_mask = (WORD_MAX << 1) << w_dst_end_rem;
    w_dst[0] = blend<T>(sel_mask, src_block, w_dst[0]);
  } else {
    // update first block
    T src_block = *w_src++ >> w_src_begin_rem;
    src_block |= (w_src[0] << (WORD_SIZE - w_src_begin_rem));
    T sel_mask = WORD_MAX << w_dst_begin_rem;
    w_dst[0] = blend<T>(sel_mask, w_dst[0], (src_block << w_dst_begin_rem));

    // update intermediate blocks
    auto w_dst_end = (w_dst++) + std::min(w_src_end_idx, w_dst_end_idx);
    while (w_dst < w_dst_end) {
      T tmp = *w_src++ >> w_src_begin_rem;
      tmp |= (w_src[0] << (WORD_SIZE - w_src_begin_rem));
      *w_dst++ = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
      src_block = tmp;
    }

    // update remining blocks
    T tmp = w_src[0] >> w_src_begin_rem;
    if (w_src_end_idx < w_dst_end_idx) {
      src_block = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
      *w_dst++ = src_block;
      src_block = (tmp >> 1) >> (WORD_MASK - w_dst_begin_rem);
    } else
    if (w_src_end_idx == w_dst_end_idx) {
      src_block = (tmp << w_dst_begin_rem) | ((src_block >> 1) >> (WORD_MASK - w_dst_begin_rem));
    } else {
      src_block = (tmp | (w_src[1] << (WORD_SIZE - w_src_begin_rem))) << w_dst_begin_rem;
    }
    sel_mask = (WORD_MAX << 1) << w_dst_end_rem;
    w_dst[0] = blend<T>(sel_mask, src_block, w_dst[0]);
  }
}

void bitvector::copy(uint32_t dst_offset,
                     const bitvector& src,
                     uint32_t src_offset,
                     uint32_t length) {
  assert(size_ && src.size_);
  assert(src_offset + length <= src.size_);
  assert(dst_offset + length <= size_);  

  if (size_ <= WORD_SIZE
   && src.size() <= WORD_SIZE) {
    word_t sel_mask =  (WORD_MAX >> (WORD_SIZE - length)) << dst_offset;
    words_[0] = blend<word_t>(sel_mask, words_[0],  ((src.word(0) >> src_offset) << dst_offset));
  } else {
    copy_bits<word_t>(words_, dst_offset, src.words(), src_offset, length);
  }
}

void bitvector::read(
    uint32_t src_offset,
    void* dst,
    uint32_t byte_alignment,
    uint32_t dst_offset,
    uint32_t length) const {
  CH_CHECK(src_offset + length <= size_, "out of bound access");
  assert(ispow2(byte_alignment) && byte_alignment <= 8);

  byte_alignment = std::min<uint32_t>(byte_alignment, sizeof(word_t));

  switch (byte_alignment) {
  case 1:
    copy_bits<uint8_t>(reinterpret_cast<uint8_t*>(dst), dst_offset,
                       reinterpret_cast<const uint8_t*>(words_), src_offset,
                       length);
    break;
  case 2:
    copy_bits<uint16_t>(reinterpret_cast<uint16_t*>(dst), dst_offset,
                        reinterpret_cast<const uint16_t*>(words_), src_offset,
                        length);
    break;
  case 4:
    copy_bits<uint32_t>(reinterpret_cast<uint32_t*>(dst), dst_offset,
                        reinterpret_cast<const uint32_t*>(words_), src_offset,
                        length);
    break;
  case 8:
    copy_bits<uint64_t>(reinterpret_cast<uint64_t*>(dst), dst_offset,
                        reinterpret_cast<const uint64_t*>(words_), src_offset,
                        length);
    break;
  default:
    CH_ABORT("invalid alignement value %d", byte_alignment);
  }
}

void bitvector::write(
    uint32_t dst_offset,
    const void* src,
    uint32_t byte_alignment,
    uint32_t src_offset,
    uint32_t length) {
  CH_CHECK(dst_offset + length <= size_, "out of bound access");

  byte_alignment = std::min<uint32_t>(byte_alignment, sizeof(word_t));

  switch (byte_alignment) {
  case 1:
    copy_bits<uint8_t>(reinterpret_cast<uint8_t*>(words_), dst_offset,
                       reinterpret_cast<const uint8_t*>(src), src_offset,
                       length);
    break;
  case 2:
    copy_bits<uint16_t>(reinterpret_cast<uint16_t*>(words_), dst_offset,
                        reinterpret_cast<const uint16_t*>(src), src_offset,
                        length);
    break;
  case 4:
    copy_bits<uint32_t>(reinterpret_cast<uint32_t*>(words_), dst_offset,
                        reinterpret_cast<const uint32_t*>(src), src_offset,
                        length);
    break;
  case 8:
    copy_bits<uint64_t>(reinterpret_cast<uint64_t*>(words_), dst_offset,
                        reinterpret_cast<const uint64_t*>(src), src_offset,
                        length);
    break;
  default:
    CH_ABORT("invalid alignement value %d", byte_alignment);
  }
}

void bitvector::deadbeef() {
  for (uint32_t i = 0, n = this->num_words(); i < n; ++i) {
    words_[i] = bit_cast<word_t>(0xdeadbeefdeadbeef);
  }
  this->clear_extra_bits();
}

std::ostream& ch::internal::operator<<(std::ostream& out, const bitvector& in) {
  out << "0x";
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);

  int quad(0);
  bool skip_zeros = true;  
  uint32_t size = in.size();

  for (auto it = in.begin() + (size - 1); size;) {
    quad = (quad << 0x1) | *it--;
    if (0 == (--size & 0x3)) {
      if (0 == size || (quad != 0 ) || !skip_zeros) {
        out << quad;
        skip_zeros = false;
      }
      quad = 0;
    }
  }
  if (0 != (size & 0x3)) {
    out << quad;
  }
  out.flags(oldflags);
  return out;
}

///////////////////////////////////////////////////////////////////////////////

bool ch::internal::bv_eq(const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == rhs.size());
  if (lhs.word(0) != rhs.word(0))
    return false;
  for (uint32_t i = 1, n = lhs.num_words(); i < n; ++i) {
    if (lhs.word(i) != rhs.word(i))
      return false;
  }
  return true;
}

bool ch::internal::bv_ltu(const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == rhs.size());
  if (lhs.size() <= bitvector::WORD_SIZE)
    return lhs.word(0) < rhs.word(0);

  for (int32_t i = rhs.num_words() - 1; i >= 0; --i) {
    if (lhs.word(i) < rhs.word(i))
      return true;
    if (lhs.word(i) > rhs.word(i))
      return false;
  }
  return false;
}

bool ch::internal::bv_lts(const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == rhs.size());
  if (lhs.size() <= bitvector::WORD_SIZE) {
    bitvector::sword_t u = sign_ext(lhs.word(0), lhs.size());
    bitvector::sword_t v = sign_ext(rhs.word(0), rhs.size());
    return u < v;
  }

  // compare most signicant bits
  uint32_t msb_idx = lhs.size() - 1;
  bool lhs_is_neg = lhs[msb_idx];
  bool rhs_is_neg = rhs[msb_idx];
  if (lhs_is_neg != rhs_is_neg)
    return lhs_is_neg;

  // same-sign words comparison
  for (int32_t i = rhs.num_words() - 1; i >= 0; --i) {
    if (lhs.word(i) < rhs.word(i))
      return true;
    if (lhs.word(i) > rhs.word(i))
      return false;
  }

  return false;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_inv(bitvector& out, const bitvector& in) {
  assert(in.size() && in.size() == out.size());

  out.word(0) = ~in.word(0);
  for (uint32_t i = 1, n = in.num_words(); i < n; ++i) {
    out.word(i) = ~in.word(i);
  }

  out.clear_extra_bits();
}

void ch::internal::bv_and(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == out.size());
  assert(rhs.size() && rhs.size() == out.size());

  out.word(0) = lhs.word(0) & rhs.word(0);
  for (int32_t i = 1, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) & rhs.word(i);
  }
}

void ch::internal::bv_or(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == out.size());
  assert(rhs.size() && rhs.size() == out.size());

  out.word(0) = lhs.word(0) | rhs.word(0);
  for (int32_t i = 1, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) | rhs.word(i);
  }
}

void ch::internal::bv_xor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == out.size());
  assert(rhs.size() && rhs.size() == out.size());

  out.word(0) = lhs.word(0) ^ rhs.word(0);
  for (int32_t i = 1, n = rhs.num_words(); i < n; ++i) {
    out.word(i) = lhs.word(i) ^ rhs.word(i);
  }
}

///////////////////////////////////////////////////////////////////////////////

bool ch::internal::bv_andr(const bitvector& in) {
  assert(in.size());
  auto rem = in.size() & bitvector::WORD_MASK;
  auto max = rem ? ((bitvector::word_t(1) << rem) - 1) : bitvector::WORD_MAX;
  for (int32_t i = in.num_words() - 1; i >= 0; --i) {
    if (in.word(i) != max)
      return false;
     max = bitvector::WORD_MAX;
  }
  return true;
}

bool ch::internal::bv_orr(const bitvector& in) {
  assert(in.size());
  if (in.word(0))
    return true;
  for (uint32_t i = 1, n = in.num_words(); i < n; ++i) {
    if (in.word(i))
      return true;
  }
  return false;
}

bool ch::internal::bv_xorr(const bitvector& in) {
  assert(in.size());
  bool ret = false;
  bitvector::word_t tmp = in.word(0);
  for (uint32_t i = 1, n = in.num_words(); i < n; ++i) {
    tmp ^= in.word(i);
  }
  for (uint32_t i = 0, n = std::min(in.size(), bitvector::WORD_SIZE); i < n; ++i) {
    ret ^= tmp & 0x1;
    tmp >>= 1;
  }
  return ret;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_slli(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(in.size() && in.size() <= out.size());
  uint32_t out_num_words = out.num_words();
  if (1 == out_num_words) {
    out.word(0) = in.word(0) << dist;
  } else {    
    uint32_t shift_words = std::min(dist >> bitvector::WORD_LOGSIZE, out_num_words);
    std::fill_n(out.words(), shift_words, 0x0);
    uint32_t shift_bits = dist & bitvector::WORD_MASK;
    uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
    bitvector::word_t carry_mask = shift_bits ? bitvector::WORD_MAX : 0;
    bitvector::word_t carry(0);
    uint32_t count = out_num_words - shift_words;
    uint32_t i = 0;
    for (uint32_t n = std::min(in.num_words(), count); i < n; ++i) {
      auto curr = in.word(i);
      out.word(i + shift_words) = (curr << shift_bits) | (carry & carry_mask);
      carry = curr >> shift_bits_r;
    }
    if ((i < count)) {
      out.word((i++) + shift_words) = carry & carry_mask;
      std::fill_n(out.words() + i + shift_words, count - i, 0x0);
    }
  }
  out.clear_extra_bits();
}

void ch::internal::bv_srli(bitvector& out, const bitvector& in, uint32_t dist) {    
  assert(in.size() && in.size() >= out.size());
  uint32_t in_num_words = in.num_words();
  if (1 == in_num_words) {
    out.word(0) = in.word(0) >> dist;
  } else {
    uint32_t shift_words = std::min(dist >> bitvector::WORD_LOGSIZE, in_num_words);
    int32_t rem_words = in_num_words - shift_words;
    int32_t out_num_words = out.num_words();
    if (rem_words < out_num_words) {
      std::fill_n(out.words() + rem_words, out_num_words - rem_words, 0x0);
    }
    uint32_t shift_bits = dist & bitvector::WORD_MASK;
    uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
    bitvector::word_t carry_mask = shift_bits ? bitvector::WORD_MAX : 0;
    bitvector::word_t carry(0);
    int32_t i = in_num_words - 1 - shift_words;
    if (i >= out_num_words) {
      carry = in.word(out_num_words + shift_words) << shift_bits_l;
      i = out_num_words - 1;
    }
    for (; i >= 0; --i) {
      auto curr = in.word(i + shift_words);
      out.word(i) = (curr >> shift_bits) | (carry & carry_mask);
      carry = curr << shift_bits_l;
    }
  }
}

void ch::internal::bv_srai(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(in.size() && in.size() >= out.size());
  bitvector::word_t fill_value = in.is_neg() ? bitvector::WORD_MAX : bitvector::word_t(0);
  uint32_t in_num_words = in.num_words();
  if (1 == in_num_words) {
    bitvector::sword_t value = sign_ext(in.word(0), in.size());
    out.word(0) = value >> dist;
  } else {
    uint32_t shift_words = std::min(dist >> bitvector::WORD_LOGSIZE, in_num_words);
    int32_t rem_words = in_num_words - shift_words;
    int32_t out_num_words = out.num_words();
    if (rem_words < out_num_words) {
      std::fill_n(out.words() + rem_words, out_num_words - rem_words, fill_value);
    }
    uint32_t shift_bits = dist & bitvector::WORD_MASK;
    uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
    bitvector::word_t carry_mask = shift_bits ? bitvector::WORD_MAX : 0;
    bitvector::word_t carry(fill_value << shift_bits_l);
    int32_t i = in_num_words - 1 - shift_words;
    if (i >= out_num_words) {
      carry = in.word(out_num_words + shift_words) << shift_bits_l;
      i = out_num_words - 1;
    }
    for (; i >= 0; --i) {
      auto curr = in.word(i + shift_words);
      out.word(i) = (curr >> shift_bits) | (carry & carry_mask);
      carry = curr << shift_bits_l;
    }
  }
  if (fill_value) {
    out.clear_extra_bits();
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_add(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == out.size());
  assert(rhs.size() && rhs.size() == out.size());
  if (lhs.size() <= bitvector::WORD_SIZE) {
    out.word(0) = lhs.word(0) + rhs.word(0);
  } else {
    bitvector::word_t carry(0);
    for (uint32_t i = 0, n = out.num_words(); i < n; ++i) {
      auto a = lhs.word(i);
      auto b = rhs.word(i);
      bitvector::word_t c = a + b;
      bitvector::word_t d = c + carry;
      carry = (c < a) || (d < carry);
      out.word(i) = d;
    }
  }
  out.clear_extra_bits();
}

void ch::internal::bv_sub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && lhs.size() == out.size());
  assert(rhs.size() && rhs.size() == out.size());
  if (lhs.size() <= bitvector::WORD_SIZE) {
    out.word(0) = lhs.word(0) - rhs.word(0);
  } else {
    bitvector::word_t borrow(0);
    for (uint32_t i = 0, n = out.num_words(); i < n; ++i) {
      auto a = lhs.word(i);
      auto b = rhs.word(i);
      bitvector::word_t c = a - b;
      bitvector::word_t d = c - borrow;
      borrow = (a < c) || (c < d);
      out.word(i) = d;
    }
  }
  out.clear_extra_bits();
}

void ch::internal::bv_neg(bitvector& out, const bitvector& in) {
  assert(in.size() && in.size() == out.size());
  if (in.size() <= bitvector::WORD_SIZE) {
    out.word(0) = -in.word(0);
  } else {
    bitvector::word_t borrow(0);
    for (uint32_t i = 0, n = out.num_words(); i < n; ++i) {
      auto a = in.word(i);
      bitvector::word_t b = -a - borrow;
      borrow = (a != 0) || (b != 0);
      out.word(i) = b;
    }
  }
  out.clear_extra_bits();
}

void ch::internal::bv_mul(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size() && out.size());
  if (out.size() <= bitvector::WORD_SIZE) {
    assert(lhs.size() <= bitvector::WORD_SIZE);
    assert(rhs.size() <= bitvector::WORD_SIZE);
    out.word(0) = lhs.word(0) * rhs.word(0);
  } else {
    auto m = ceildiv<int>(lhs.find_last(), 8 * sizeof(bitvector::xword_t));
    auto n = ceildiv<int>(rhs.find_last(), 8 * sizeof(bitvector::xword_t));
    auto p = ceildiv<int>(out.size(), 8 * sizeof(bitvector::xword_t));

    auto u = reinterpret_cast<const bitvector::xword_t*>(lhs.data());
    auto v = reinterpret_cast<const bitvector::xword_t*>(rhs.data());
    auto w = reinterpret_cast<bitvector::xword_t*>(out.data());

    out.reset();

    for (int i = 0; i < n; ++i) {
      bitvector::xword_t tot(0);
      for (int j = 0, k = std::min(m, p - i); j < k; ++j) {
        auto c = bitvector::yword_t(u[j]) * v[i] + w[i+j] + tot;
        tot = c >> bitvector::XWORD_SIZE;
        w[i+j] = c;
      }
      if (i+m < p) {
        w[i+m] = tot;
      }
    }
  }  

  out.clear_extra_bits();
}

void ch::internal::bv_divmodu(bitvector& quot, bitvector& rem, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size());
  auto m  = ceildiv<int>(lhs.find_last(), 8 * sizeof(bitvector::xword_t));
  auto n  = ceildiv<int>(rhs.find_last(), 8 * sizeof(bitvector::xword_t));
  auto qn = ceildiv<int>(quot.size(), 8 * sizeof(bitvector::xword_t));
  auto rn = ceildiv<int>(rem.size(), 8 * sizeof(bitvector::xword_t));

  CH_CHECK(n >= 1, "invalid size");

  // reset the outputs
  if (qn)
    quot.reset();
  if (rn)
    rem.reset();

  auto u = reinterpret_cast<const bitvector::xword_t*>(lhs.data());
  auto v = reinterpret_cast<const bitvector::xword_t*>(rhs.data());
  auto q = reinterpret_cast<bitvector::xword_t*>(quot.data());
  auto r = reinterpret_cast<bitvector::xword_t*>(rem.data());

  // early exit
  if (m <= 0 || m < n || u[m] < v[n]) {
    if (rn) {
      for (int i = 0; i < std::min(m, rn); ++i) {
        r[i] = u[i];
      }
    }
    return;
  }

  std::vector<bitvector::xword_t> tu(2 * (m + 1), 0), tv(2 * n, 0);
  auto un = tu.data();
  auto vn = tv.data();

  // normalize
  int s = count_leading_zeros<bitvector::xword_t>(v[n - 1]);
  un[m] = u[m - 1] >> (bitvector::XWORD_SIZE - s);
  for (int i = m - 1; i > 0; --i) {
    un[i] = (u[i] << s) | (u[i - 1] >> (bitvector::XWORD_SIZE - s));
  }
  un[0] = u[0] << s;
  for (int i = n - 1; i > 0; --i) {
    vn[i] = (v[i] << s) | (v[i - 1] >> (bitvector::XWORD_SIZE - s));
  }
  vn[0] = v[0] << s;

  auto h = vn[n - 1];

  for (int j = m - n; j >= 0; --j) {
    // estimate quotient
    auto w = (bitvector::yword_t(un[j + n]) << bitvector::XWORD_SIZE) | un[j + n - 1];
    auto qhat = w / h;

    // multiply and subtract
    bitvector::xword_t k(0);
    for (int i = 0; i < n; ++i) {
      auto p = qhat * vn[i];
      auto w = un[i + j] - k - (p & bitvector::XWORD_MAX);
      k = (p >> bitvector::XWORD_SIZE) - (w >> bitvector::XWORD_SIZE);
      un[i + j] = w;
    }    

    bitvector::syword_t t(un[j + n] - k);
    un[j + n] = t;

    if (j < qn)
      q[j] = qhat;

    // overflow handling
    if (t < 0) {
      if (j < qn)
        --q[j];
      bitvector::yword_t k(0);
      for (int i = 0; i < n; ++i) {
        auto w = un[i + j] + k + vn[i];
        k = (w >> bitvector::XWORD_SIZE);
        un[i + j] = w;
      }
      un[j + n] += k;
    }
  }

  // unnormalize remainder
  if (rn) {
    for (int i = 0; i < std::min(n, rn); ++i) {
      r[i] = (un[i] >> s) | (un[i + 1] << (bitvector::XWORD_SIZE - s));
    }
  }
}

void ch::internal::bv_divu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size() && out.size());
  if (lhs.size() <= bitvector::WORD_SIZE
   && rhs.size() <= bitvector::WORD_SIZE
   && out.size() <= bitvector::WORD_SIZE) {
    out.word(0) = lhs.word(0) / rhs.word(0);
  } else {
    bitvector r;
    bv_divmodu(out, r, lhs, rhs);
  }
}

void ch::internal::bv_divs(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size() && out.size());
  if (lhs.size() <= bitvector::WORD_SIZE
   && rhs.size() <= bitvector::WORD_SIZE
   && out.size() <= bitvector::WORD_SIZE) {
    bitvector::sword_t u = sign_ext(lhs.word(0), lhs.size());
    bitvector::sword_t v = sign_ext(rhs.word(0), rhs.size());
    out.word(0) = u / v;
    out.clear_extra_bits();
  } else {
    bitvector r, u(lhs.size()), v(rhs.size());
    bv_abs(u, lhs);
    bv_abs(v, rhs);
    bv_divmodu(out, r, u, v);
    if (lhs.is_neg() ^ rhs.is_neg()) {
      bv_neg(out, out);
    }
  }
}

void ch::internal::bv_modu(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size() && out.size());
  if (lhs.size() <= bitvector::WORD_SIZE
   && rhs.size() <= bitvector::WORD_SIZE
   && out.size() <= bitvector::WORD_SIZE) {
    out.word(0) = lhs.word(0) % rhs.word(0);
  } else {
    bitvector q;
    bv_divmodu(q, out, lhs, rhs);
  }
}

void ch::internal::bv_mods(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(lhs.size() && rhs.size() && out.size());
  if (lhs.size() <= bitvector::WORD_SIZE
   && rhs.size() <= bitvector::WORD_SIZE
   && out.size() <= bitvector::WORD_SIZE) {
    bitvector::sword_t u = sign_ext(lhs.word(0), lhs.size());
    bitvector::sword_t v = sign_ext(rhs.word(0), rhs.size());
    out.word(0) = u % v;
    out.clear_extra_bits();
  } else {
    bitvector q, u(lhs.size()), v(rhs.size());
    bv_abs(u, lhs);
    bv_abs(v, rhs);
    bv_divmodu(q, out, u, v);
    if (lhs.is_neg()) {
      bv_neg(out, out);
    }
  }
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::bv_zext(bitvector& out, const bitvector& in) {
  assert(in.size() && in.size() <= out.size());
  if (out.size() <= bitvector::WORD_SIZE) {
    out.word(0) = in.word(0);
    return;
  }

  std::copy_n(in.words(), in.num_words(), out.words());
  std::fill(out.words() + in.num_words(),
            out.words() + out.num_words(),
            0);
}

void ch::internal::bv_sext(bitvector& out, const bitvector& in) {
  assert(in.size() && in.size() <= out.size());
  if (out.size() <= bitvector::WORD_SIZE) {
    if (in.is_neg()) {
      out.word(0) = sign_ext(in.word(0), in.size());
      out.clear_extra_bits();
    } else {
      out.word(0) = in.word(0);
    }
    return;
  }

  if (in.is_neg()) {
    uint32_t msb = in.size() - 1;
    uint32_t msb_blk_idx = msb >> bitvector::WORD_LOGSIZE;
    uint32_t msb_blk_rem = msb & bitvector::WORD_MASK;
    auto msb_blk = in.word(msb_blk_idx);
    std::copy_n(in.words(), in.num_words(), out.words());
    out.word(msb_blk_idx) = msb_blk | (bitvector::WORD_MAX << msb_blk_rem);
    std::fill(out.words() + in.num_words(),
              out.words() + out.num_words(),
              bitvector::WORD_MAX);
    out.clear_extra_bits();
  } else {
    std::copy_n(in.words(), in.num_words(), out.words());
    std::fill(out.words() + in.num_words(),
              out.words() + out.num_words(),
              0);
  }
}
