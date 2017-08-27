#include <cstring>
#include "bitvector.h"

using namespace cash::detail;

bitvector::bitvector(const bitvector& rhs) : words_(nullptr), size_(0) {
  this->resize(rhs.size_, 0x0, false, false);
  std::copy(rhs.words_, rhs.words_ + this->get_num_words(), words_);
}

bitvector::bitvector(bitvector&& rhs) {
  words_ = rhs.words_;
  size_ = rhs.size_;
  rhs.words_ = nullptr;
  rhs.size_ = 0;
}

bitvector::bitvector(uint32_t size) : words_(nullptr), size_(0) {
  this->resize(size, 0, true, false);
}

bitvector::bitvector(uint32_t size, const char* value) : words_(nullptr), size_(0) {
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, char value) : words_(nullptr), size_(0) {
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, uint32_t value) : words_(nullptr), size_(0) {
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(uint32_t size, const std::initializer_list<uint32_t>& value)
  : words_(nullptr), size_(0) {  
  this->resize(size, 0x0, false, false);
  this->operator =(value);  
}

bitvector::~bitvector() {
  if (words_) {
    delete [] words_;
  }
}

void bitvector::resize(uint32_t size, uint32_t value, bool initialize, bool preserve) {
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
  if (size_ != rhs.size_)
    this->resize(rhs.size_, 0x0, false, false);
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
  CH_ABORT("invalid literal value");
}

bitvector& bitvector::operator=(const char* value) {
  int base = 0;
  int start = 0;

  size_t len = strlen(value);
  
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
  
  uint32_t log_base = ilog2ceil(base);
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
  
  CH_CHECK(size <= size_, "literal value overflow");
  
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
                     uint32_t src_length) {
  assert(size_ > 0);
  assert(src.size_ > 0);
  assert(src_offset + src_length <= src.size_);
  assert(dst_offset + src_length <= size_);
  if (src_length == size_ && src.size_ == size_) {
    assert(0 == dst_offset && 0 == src_offset);
    *this = src;
  } else {  
    const_iterator iter_src(src.begin() + src_offset);
    iterator iter_dst(this->begin() + dst_offset);
    while (src_length--) {
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

void bitvector::read(uint8_t* out, uint32_t offset, uint32_t size) const {
  assert(offset + size <= size_);
  uint32_t m_offset = offset & 0xff;
  uint8_t rem_bits = (offset + size) & 0xff;
  if (m_offset) {
    uint8_t tmp = 0;
    const_iterator iter = this->begin() + offset;
    for (uint32_t i = 0; i < size; ++i) {
      uint32_t shift = i & 0x7;
      tmp |= (*iter++) << shift;
      if (shift == 0x7) {
        *out++ = tmp;
        tmp = 0;
      }
    }
    if (tmp) {
      if (rem_bits) {
        uint32_t sel_mask = ~(~0UL << rem_bits);
        *out = CH_BLEND(sel_mask, tmp, *out);
      } else {
        *out = tmp;
      }
    }
  } else {
    // byte-aligned offset
    uint32_t offset_in_bytes = offset / 8;
    uint32_t size_in_bytes = CH_CEILDIV(size, 8);
    uint8_t* src = reinterpret_cast<uint8_t*>(words_) + offset_in_bytes;
    if (rem_bits) {
      // copy all bytes except the last one
      memcpy(out, src, size_in_bytes - 1);
      // only update set bits from source in the last byte
      uint32_t sel_mask = ~(~0UL << rem_bits);
      out[size_in_bytes - 1] =
          CH_BLEND(sel_mask, src[size_in_bytes - 1], out[size_in_bytes - 1]);
    } else {
      memcpy(out, src, size_in_bytes);
    }
  }
}

void bitvector::write(const uint8_t* in, uint32_t offset, uint32_t size) {
  assert(offset + size <= size_);
  uint32_t m_offset = offset & 0xff;
  if (m_offset) {
    uint8_t tmp;
    iterator iter = this->begin() + offset;
    for (uint32_t i = 0; i < size; ++i) {
      uint32_t shift = i & 0x7;
      if (0 == shift) {
        tmp = *in++;
      }
      *iter++ = (tmp >> shift) & 0x1;
    }
  } else {
    // byte-aligned offset
    uint32_t offset_in_bytes = offset / 8;
    uint32_t size_in_bytes = CH_CEILDIV(size, 8);
    uint8_t rem_bits = (offset + size) & 0xff;
    uint8_t* dst = reinterpret_cast<uint8_t*>(words_) + offset_in_bytes;
    if (rem_bits) {
      // copy all bytes except the last one
      memcpy(dst, in, size_in_bytes - 1);
      // only update set bits from source in the last byte
      uint32_t sel_mask = ~(~0UL << rem_bits);
      dst[size_in_bytes - 1] =
          CH_BLEND(sel_mask, in[size_in_bytes - 1], dst[size_in_bytes - 1]);
    } else {
      memcpy(dst, in, size_in_bytes);
    }
  }
}

std::ostream& cash::detail::operator<<(std::ostream& os, const bitvector& b) {
  auto oldflags = os.flags();
  os.setf(std::ios_base::hex, std::ios_base::basefield);
  os << "0x";
  for (int32_t i = b.get_num_words() - 1; i >= 0; --i) {
    uint32_t word = b.get_word(i);
    os << word;
    if (i != 0) {
      os << "_";
    }
  }
  os.flags(oldflags);
  return os;
}
