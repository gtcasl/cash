#include "bitvector.h"

using namespace ch::internal;

bitvector::bitvector(const bitvector& rhs) : words_(nullptr), size_(0) {
  this->resize(rhs.size_);
  std::copy(rhs.words_, rhs.words_ + this->get_num_words(), words_);
}

bitvector::bitvector(bitvector&& rhs) {
  words_ = rhs.words_;
  size_ = rhs.size_;
  rhs.words_ = nullptr;
  rhs.size_ = 0;
}

bitvector::bitvector(uint32_t size)
  : words_(nullptr), size_(0) {
  this->resize(size, 0, true);
}

bitvector::bitvector(uint32_t size, char value)
  : words_(nullptr), size_(0) {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, uint32_t value)
  : words_(nullptr), size_(0) {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size,
                     const std::initializer_list<uint32_t>& value)
  : words_(nullptr), size_(0) {
  this->resize(size);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, const std::string& value)
  : words_(nullptr), size_(0) {
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
    uint32_t* words = new uint32_t[new_num_words];  
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
    uint32_t num_words = this->get_num_words();
    words_[num_words-1] &= ~(~0UL << extra_bits);
  }
}

bitvector& bitvector::operator=(const bitvector& rhs) {
  if (size_ != rhs.size_) {
    this->resize(rhs.size_);
  }
  std::copy(rhs.words_, rhs.words_ + rhs.get_num_words(), words_);
  return *this;
}

bitvector& bitvector::operator=(bitvector&& rhs) {
  delete[] words_;
  size_ = rhs.size_;
  words_ = rhs.words_;
  rhs.size_ = 0;
  rhs.words_ = nullptr;
  return *this;
}

bitvector& bitvector::operator=(const std::initializer_list<uint32_t>& value) {
  assert(size_);
  auto iterValue = value.begin();

  uint32_t num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  uint32_t used_num_words = value.size();

  // check for extra bits
  for (uint32_t i = num_words; i < used_num_words; ++i) {
    CH_CHECK(0 == *iterValue++, "input value overflow");
  }
  CH_CHECK((value.size() < num_words)
          || (0 == (size_ & WORD_MASK) || (0 == (*iterValue >> (size_ & WORD_MASK)))), "input value overflow");

  // clear unused words
  uint32_t* dst = words_ + (num_words - 1);
  if (used_num_words < num_words) {
    uint32_t unused_words = num_words - used_num_words;
    std::fill_n(dst, unused_words, 0x0);
    dst -= unused_words;
  }

  // write the value
  for (auto iterEnd = value.end(); iterValue != iterEnd; ++iterValue) {
    *dst-- = *iterValue;
  }

  return *this;
}

static uint32_t chr2int(char x, int base) {
  switch (base) {
  case 2:
    if (x >= '0' && x <= '1')
      return (x - '0');
    break;
  case 8:
    if (x >= '0' && x <= '7')
      return (x - '0');
    break;
  case 16:
    if (x >= '0' && x <= '9')
      return (x - '0');
    if (x >= 'A' && x <= 'F')
      return (x - 'A') + 10;
    if (x >= 'a' && x <= 'f')
      return (x - 'a') + 10;
    break;
  }  
  CH_ABORT("invalid scalar value");
}

bitvector& bitvector::operator=(const std::string& value) {
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
       uint32_t v = chr2int(chr, base);
       if (v) {
         size += ilog2(v) + 1;
       }
    } else {
      size += log_base;
    }
  }
  
  CH_CHECK(size <= size_, "scalar value overflow");
  
  // clear unused words
  uint32_t num_words = this->get_num_words();
  uint32_t used_num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  if (used_num_words < num_words) {
    std::fill_n(words_ + used_num_words, num_words - used_num_words, 0x0);    
  }
  
  // write the value
  uint32_t w = 0;  
  uint32_t* dst = words_;      
  for (uint32_t i = 0, j = 0, n = len - start; i < n; ++i) {
    char chr = value[len - i - 1];
    if (chr == '\'')
      continue; // skip separator character
    uint32_t v = chr2int(chr, base);
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

bitvector& bitvector::operator=(char value) {
  uint32_t _value;
  if (value == '0')
    _value = 0x0;
  else if (value == '1')
    _value = 0x1;
  else
    CH_ABORT("invalid character value");
  return this->operator=(_value);
}

bitvector& bitvector::operator=(uint32_t value) {
  assert(size_);
  
  // check for extra bits
  uint32_t num_words = (size_ + WORD_MASK) >> WORD_SIZE_LOG;  
  CH_CHECK((1 < num_words)
        || ((1 == num_words)
         && (0 == (size_ & WORD_MASK)
          || (0 == (value >> (size_ & WORD_MASK))))), "input value overflow");

  // write the value
  words_[0] = value;
  
  // clear unused words
  std::fill_n(words_ + 1, num_words - 1, 0x0);

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

bool bitvector::operator==(const bitvector& rhs) const {
  if (size_ != rhs.size_)
    return false;
  for (uint32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    if (words_[i] != rhs.words_[i])
      return false;
  }
  return true;
}

bool bitvector::operator<(const bitvector& rhs) const {
  assert(size_ == rhs.size_);
  for (int32_t i = rhs.get_num_words() - 1; i >= 0; --i) {
    if (words_[i] < rhs.words_[i])
      return true;
    else if (words_[i] > rhs.words_[i])
      return false;
  }
  return false;
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

int32_t bitvector::find_first() const {
  for (uint32_t i = 0, n = this->get_num_words(); i < n; ++i) {
    uint32_t w = words_[i];
    if (w) {
      int z = ctz(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

int32_t bitvector::find_last() const {
  for (int32_t i = this->get_num_words() - 1; i >= 0; --i) {
    uint32_t w = words_[i];
    if (w) {
      int z = clz(w);
      return (WORD_MASK - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

bool bitvector::is_empty() const {
  for (int32_t i = 0, n = this->get_num_words(); i < n; ++i) {
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
  uint8_t* b_dst = reinterpret_cast<uint8_t*>(dst) + b_dst_offset;
  uint32_t dst_rem = dst_offset & 0x7;
  uint32_t src_rem = src_offset & 0x7;
  uint32_t end_rem = (dst_offset + length) & 0x7;

  if (0 == src_rem
   && 0 == dst_rem) {
    // byte-aligned offsets
    uint32_t b_length = CH_CEILDIV(length, 8);
    uint32_t b_src_offset = src_offset / 8;
    uint8_t* b_src = reinterpret_cast<uint8_t*>(words_) + b_src_offset;
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
    const_iterator iter = this->begin() + src_offset;
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
    if (tmp) {
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
  const uint8_t* b_src = reinterpret_cast<const uint8_t*>(src) + b_src_offset;
  uint32_t dst_rem = dst_offset & 0x7;
  uint32_t src_rem = src_offset & 0x7;

  if (0 == dst_rem
   && 0 == src_rem) {
    // byte-aligned offsets
    uint32_t b_length = CH_CEILDIV(length, 8);
    uint32_t b_dst_offset = dst_offset / 8;
    uint8_t* b_dst = reinterpret_cast<uint8_t*>(words_) + b_dst_offset;
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
    iterator iter = this->begin() + dst_offset;
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

///////////////////////////////////////////////////////////////////////////////

std::ostream& ch::internal::operator<<(std::ostream& out, const bitvector& rhs) {
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);
  out << "0x";
  for (int32_t i = rhs.get_num_words() - 1; i >= 0; --i) {
    uint32_t word = rhs.get_word(i);
    out << word;
    if (i != 0) {
      out << "_";
    }
  }
  out.flags(oldflags);
  return out;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::Inv(bitvector& out, const bitvector& in) {
  assert(out.get_size() == in.get_size());
  for (uint32_t i = 0, n = in.get_num_words(); i < n; ++i) {
    out.set_word(i, ~in.get_word(i));
  }
  out.clear_unused_bits();
}

void ch::internal::And(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) & rhs.get_word(i));
  }
}

void ch::internal::Or(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) | rhs.get_word(i));
  }
}

void ch::internal::Xor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == lhs.get_size());
  assert(lhs.get_size() == rhs.get_size());
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.set_word(i, lhs.get_word(i) ^ rhs.get_word(i));
  }
}

///////////////////////////////////////////////////////////////////////////////

bool ch::internal::AndR(const bitvector& in) {
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

bool ch::internal::OrR(const bitvector& in) {
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

bool ch::internal::XorR(const bitvector& in) {
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

///////////////////////////////////////////////////////////////////////////////

void ch::internal::Sll(bitvector& out, const bitvector& in, uint32_t dist) {
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

void ch::internal::Srl(bitvector& out, const bitvector& in, uint32_t dist) {
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

void ch::internal::Sra(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(in.get_size() >= 2);
  assert(out.get_size() == in.get_size());
  Srl(out, in, dist);
  auto msb_idx = in.get_size() - 1;
  out[msb_idx] = in[msb_idx];
  out[msb_idx-1] = 0;
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::Add(bitvector& out, const bitvector& lhs, const bitvector& rhs, uint32_t cin) {
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

void ch::internal::Sub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  bitvector minus_b(out.get_size());
  Inv(minus_b, rhs);
  Add(out, lhs, minus_b, 1);
}

void ch::internal::Negate(bitvector& out, const bitvector& in) {
  bitvector zero(out.get_size(), 0x0);
  Sub(out, zero, in);
}

///////////////////////////////////////////////////////////////////////////////

void ch::internal::fAdd(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = bitcast<float>(a_value);
  float b_valuef = bitcast<float>(b_value);
  float resultf = a_valuef + b_valuef;
  uint32_t result = bitcast<uint32_t>(resultf);
  out.set_word(0, result);
}

void ch::internal::fSub(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = bitcast<float>(a_value);
  float b_valuef = bitcast<float>(b_value);
  float resultf = a_valuef - b_valuef;
  uint32_t result = bitcast<uint32_t>(resultf);
  out.set_word(0, result);
}

void ch::internal::fMult(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = bitcast<float>(a_value);
  float b_valuef = bitcast<float>(b_value);
  float resultf = a_valuef * b_valuef;
  uint32_t result = bitcast<uint32_t>(resultf);
  out.set_word(0, result);
}

void ch::internal::fDiv(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.get_size() == 32);
  assert(lhs.get_size() == 32);
  assert(rhs.get_size() == 32);
  uint32_t a_value = lhs.get_word(0);
  uint32_t b_value = rhs.get_word(0);
  float a_valuef = bitcast<float>(a_value);
  float b_valuef = bitcast<float>(b_value);
  float resultf = a_valuef / b_valuef;
  uint32_t result = bitcast<uint32_t>(resultf);
  out.set_word(0, result);
}
