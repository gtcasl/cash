#include <cstring>
#include "bitvector.h"

using namespace std;
using namespace chdl_internal;

bitvector::bitvector(const bitvector& rhs) : m_words(nullptr), m_size(0) {
  this->resize(rhs.m_size, 0x0, false, false);
  std::copy(rhs.m_words, rhs.m_words + this->get_num_words(), m_words);
}

bitvector::bitvector(bitvector&& rhs) {
  m_words = rhs.m_words;
  m_size = rhs.m_size;
  rhs.m_words = nullptr;
  rhs.m_size = 0;
}

bitvector::bitvector(uint32_t size) : m_words(nullptr), m_size(0) {
  this->resize(size, 0, true, false);
}

bitvector::bitvector(const std::string& value, uint32_t size) : m_words(nullptr), m_size(0) {
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(char value, uint32_t size) : m_words(nullptr), m_size(0) {
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(uint32_t value, uint32_t size) : m_words(nullptr), m_size(0) {    
  this->resize(size, 0x0, false, false);
  this->operator =(value);
}

bitvector::bitvector(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_words(nullptr), m_size(0) {  
  this->resize(size, 0x0, false, false);
  this->operator =(value);  
}

bitvector::~bitvector() {
  if (m_words)
    delete [] m_words;
}

void bitvector::resize(uint32_t size, uint32_t defaultValue, bool initialize, bool preserve) {  
  uint32_t old_num_words = (m_size + WORD_MASK) >> WORD_SIZE_LOG;
  uint32_t new_num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  if (new_num_words != old_num_words) {
    uint32_t* words = new uint32_t[new_num_words];  
    if (m_words) {      
      if (preserve) {
        std::copy(m_words, m_words + std::min(new_num_words, old_num_words), words);
      }
      delete [] m_words;
    }
    if (initialize && new_num_words > old_num_words) {
      std::fill(words + old_num_words, words + new_num_words, defaultValue);
    }
    m_words = words;    
  }   
  m_size = size;
  if (initialize)
    this->clear_unused_bits();
}

void bitvector::clear_unused_bits() {
  uint32_t extra_bits = m_size & WORD_MASK;
  if (extra_bits) {
    uint32_t num_words = this->get_num_words();
    m_words[num_words-1] &= ~(~0UL << extra_bits);
  }
}

bitvector& bitvector::operator=(const bitvector& rhs) {
  if (m_size != rhs.m_size)
    this->resize(rhs.m_size, 0x0, false, false);
  std::copy(rhs.m_words, rhs.m_words + rhs.get_num_words(), m_words);
  return *this;
}

bitvector& bitvector::operator=(bitvector&& rhs) {
  delete[] m_words;
  m_size = rhs.m_size;
  m_words = rhs.m_words;
  rhs.m_size = 0;
  rhs.m_words = nullptr;
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
  default:
    CHDL_ABORT("invalid literal value");
  }
}

bitvector& bitvector::operator=(const std::string& value) {  
  int base = 0;
  int start = 0;
  
  switch (value.back()) {
  case 'b':
    base = 2;
    break;
  case 'o':
    base = 8;
    break;
  case 'h':
    base = 16;
    if (value.size() > 1 && (value[1] == 'x' || value[1] == 'X')) {
      start = 2;
    }
    break;
  default:
    CHDL_ABORT("invalid binary format, missing encoding base type.");
  }
  
  uint32_t log_base = CLOG2(base);
  uint32_t len = value.size() - 1; // remove type character
  
  // calculate binary size
  uint32_t size = 0;  
  for (uint32_t i = start; i < len; ++i) {
    char chr = value[i];
    if (chr == '\'') 
      continue; // skip separator character
    if (size == 0) {
       // calculate exact bit coverage for the first non zero character
       uint32_t v = chr2int(chr, base);
       if (v) {
         size += LOG2(v) + 1;
       }
    } else {
      size += log_base;
    }
  }
  
  CHDL_CHECK(size <= m_size, "literal value overflow");
  
  // clear unused words
  uint32_t num_words = this->get_num_words();
  uint32_t used_num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  if (used_num_words < num_words) {
    std::fill_n(m_words + used_num_words, num_words - used_num_words, 0x0);    
  }
  
  // write the value
  uint32_t w = 0;  
  uint32_t* dst = m_words;      
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
  assert(m_size);
  
  uint32_t value_;
  if (value == '0')
    value_ = 0x0;
  else if (value == '1')
    value_ = 0x1;
  else
    CHDL_ABORT("invalid character value");  
  
  // write the value
  m_words[0] = value_;
  
  // clear unused words
  uint32_t num_words = (m_size + WORD_MASK) >> WORD_SIZE_LOG;
  std::fill_n(m_words + 1, num_words - 1, 0x0);
}

bitvector& bitvector::operator=(uint32_t value) {
  assert(m_size);
  
  // check for extra bits
  uint32_t num_words = (m_size + WORD_MASK) >> WORD_SIZE_LOG;  
  CHDL_CHECK((1 < num_words) || 
                  ((1 == num_words) && 
                    (0 == (m_size & WORD_MASK) || 
                      (0 == (value >> (m_size & WORD_MASK))))), "input value overflow");  
  // write the value
  m_words[0] = value;
  
  // clear unused words
  std::fill_n(m_words + 1, num_words - 1, 0x0);
}

bitvector& bitvector::operator=(const std::initializer_list<uint32_t>& value) {
  assert(m_size);
  auto iterValue = value.begin();
  
  uint32_t num_words = (m_size + WORD_MASK) >> WORD_SIZE_LOG;   
  uint32_t used_num_words = value.size();
  
  // check for extra bits
  for (uint32_t i = num_words; i < used_num_words; ++i) {
    CHDL_CHECK(0 == *iterValue++, "input value overflow");
  }  
  CHDL_CHECK((value.size() < num_words) 
          || (0 == (m_size & WORD_MASK) || (0 == (*iterValue >> (m_size & WORD_MASK)))), "input value overflow");  
     
  // clear unused words
  uint32_t* dst = m_words + (num_words - 1);
  if (used_num_words < num_words) {
    uint32_t unused_words = num_words - used_num_words;
    std::fill_n(dst, unused_words, 0x0);  
    dst -= unused_words;
  }
  
  // write the value
  for (auto iterEnd = value.end(); iterValue != iterEnd; ++iterValue) {
    *dst-- = *iterValue;
  }
}

bool bitvector::operator==(const bitvector& rhs) const {
  assert(m_size > 0);
  assert(rhs.m_size > 0);
  if (m_size != rhs.m_size)
    return false;
  for (uint32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    if (m_words[i] != rhs.m_words[i])
      return false;
  }
  return true;
}

bool bitvector::operator<(const bitvector& rhs) const {
  assert(m_size > 0);
  assert(rhs.m_size > 0);
  assert(m_size == rhs.m_size);
  for (int32_t i = rhs.get_num_words() - 1; i >= 0; --i) {
    if (m_words[i] < rhs.m_words[i])
      return true;
    else if (m_words[i] > rhs.m_words[i])
      return false;
  }
  return false;
}

void bitvector::copy(uint32_t dst_offset, const bitvector& src, uint32_t src_offset, uint32_t src_length) {
  assert(m_size > 0);
  assert(src.m_size > 0);
  assert(src_offset + src_length <= src.m_size);
  assert(dst_offset + src_length <= m_size);
  if (src_length == m_size && src.m_size == m_size) {
    assert(dst_offset == 0 && src_offset == 0);
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
    uint32_t w = m_words[i];
    if (w) {
      int z = countTrailingZeros(w);
      return z + i * WORD_SIZE;
    }
  }
  return -1;
}

int32_t bitvector::find_last() const {
  for (int32_t i = this->get_num_words() - 1; i >= 0; --i) {
    uint32_t w = m_words[i];
    if (w) {
      int z = countLeadingZeros(w);
      return (WORD_MASK - z) + i * WORD_SIZE;
    }
  }
  return -1;
}

bool bitvector::is_empty() const {
  for (int32_t i = 0, n = this->get_num_words(); i < n; ++i) {
    if (m_words[i])
      return false;
  }
  return true;
}

void bitvector::readBytes(uint8_t* out, uint32_t sizeInBytes) const {
  assert(m_size > 0);
  assert(sizeInBytes * 8 >= m_size);
  uint32_t srcBytes = (m_size + 7) / 8;
  memcpy(out, m_words, srcBytes);
  if (sizeInBytes > srcBytes) {
    memset(out + srcBytes, 0, sizeInBytes - srcBytes);
  }
}

void bitvector::writeBytes(const uint8_t* in, uint32_t sizeInBytes) {
  assert(m_size > 0);
  assert(sizeInBytes * 8 >= m_size);
  uint32_t dstBytes = (m_size + 7) / 8;
  // check for overflow
  CHDL_CHECK(0 == (m_size % 8) || 0 ==(in[dstBytes-1] & ~((1 << (m_size % 8))-1)), "input value overflow");
  for (uint32_t i = dstBytes; i < sizeInBytes; ++i) {
    CHDL_CHECK(0 == in[i], "input value overflow"); 
  }  
  memcpy(m_words, in, dstBytes);  
}

void chdl_internal::Invert(bitvector& out, const bitvector& in) {
  assert(out.m_size == in.m_size);
  for (uint32_t i = 0, n = in.get_num_words(); i < n; ++i) {
    out.m_words[i] = ~in.m_words[i]; 
  }
  out.clear_unused_bits();
}

void chdl_internal::And(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = lhs.m_words[i] & rhs.m_words[i]; 
  }
}

void chdl_internal::Or(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = lhs.m_words[i] | rhs.m_words[i]; 
  }
}

void chdl_internal::Xor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = lhs.m_words[i] ^ rhs.m_words[i]; 
  }
}

void chdl_internal::Nand(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = ~(lhs.m_words[i] & rhs.m_words[i]); 
  }
  out.clear_unused_bits();
}

void chdl_internal::Nor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = ~(lhs.m_words[i] | rhs.m_words[i]); 
  }
  out.clear_unused_bits();
}

void chdl_internal::Xnor(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  assert(out.m_size == lhs.m_size);
  assert(lhs.m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    out.m_words[i] = ~(lhs.m_words[i] ^ rhs.m_words[i]); 
  }
  out.clear_unused_bits();
}

bool bitvector::andr() const {
  assert(m_size > 0);
  uint32_t in_w = m_words[0];
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = m_size; i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = m_words[j++];
    }
    in_w >>= 1;    
    result &= (in_w & 0x1);    
  }
  return (result != 0);
}

bool bitvector::orr() const {
  assert(m_size > 0);
  uint32_t in_w = m_words[0];
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = m_size; i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = m_words[j++];
    }    
    in_w >>= 1;
    result |= (in_w & 0x1);
  }
  return (result != 0);
}

bool bitvector::xorr() const {
  assert(m_size > 0);
  uint32_t in_w = m_words[0];
  uint32_t result = in_w & 0x1;
  for (uint32_t i = 1, j = 1, n = m_size; i < n; ++i) {
    if (0 == (i % bitvector::WORD_SIZE)) {
      in_w = m_words[j++];
    }    
    in_w >>= 1;
    result ^= (in_w & 0x1);
  }
  return (result != 0);
}

void chdl_internal::ShiftLeft(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.m_size == in.m_size);  
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.m_words[0] = in.m_words[0] << dist;
  } else {    
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;    
    if (dist < in.m_size) {      
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      if (shift_bits) {
        uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
        uint32_t prev = 0;
        for (uint32_t i = 0, n = num_words - shift_words; i < n; ++i) {
          uint32_t curr = in.m_words[i];
          out.m_words[i + shift_words] = (curr << shift_bits) | (prev >> shift_bits_r);
          prev = curr;
        }
      } else {
        for (uint32_t i = 0, n = num_words - shift_words; i < n; ++i) {
          out.m_words[i + shift_words] = in.m_words[i];
        }
      }
    } else {
      shift_words = num_words;
    }
    std::fill_n(out.m_words, shift_words, 0x0);
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}
  
void chdl_internal::RotateLeft(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.m_size == in.m_size);  
  if (dist > in.m_size)
    dist %= in.m_size;
  if (dist == 0)
    return;
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.m_words[0] = rotl(in.m_words[0], dist, in.m_size);
  } else {      
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    uint32_t shift_bits = dist & bitvector::WORD_MASK;
    if (shift_bits) {
      uint32_t shift_bits_r = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = in.m_words[num_words - 1];
      for (uint32_t i = 0, j = shift_words; i < num_words; ++i) {    
        uint32_t curr = in.m_words[i];      
        out.m_words[j] = (curr << shift_bits) | (prev >> shift_bits_r);
        prev = curr;
        if (++j == num_words) 
          j = 0;         
      }
    } else {
      for (uint32_t i = 0, j = shift_words; i < num_words; ++i) {    
        out.m_words[j] = in.m_words[i];
        if (++j == num_words) 
          j = 0;         
      }
    }
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

void chdl_internal::ShiftRight(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.m_size == in.m_size);  
  uint32_t num_words   = in.get_num_words(); 
  if (num_words == 1) {
    out.m_words[0] = in.m_words[0] >> dist;
  } else {    
    uint32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    if (dist < in.m_size) {      
      uint32_t shift_bits = dist & bitvector::WORD_MASK;
      if (shift_bits) {
        uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
        uint32_t prev = 0;
        for (int32_t i = num_words - 1 - shift_words; i >= 0; --i) {
          uint32_t curr = in.m_words[i + shift_words];
          out.m_words[i] = (curr >> shift_bits) | (prev << shift_bits_l);
          prev = curr;
        }
      } else {
        for (int32_t i = num_words - 1 - shift_words; i >= 0; --i) {
          out.m_words[i] = in.m_words[i + shift_words];
        }
      }
    } else {
      shift_words = num_words;
    }
    std::fill_n(out.m_words + (num_words - shift_words), shift_words, 0x0);
  }
}

void chdl_internal::RotateRight(bitvector& out, const bitvector& in, uint32_t dist) {
  assert(out.m_size == in.m_size);
  if (dist > in.m_size)
    dist %= in.m_size;
  if (dist == 0)
    return;
  uint32_t num_words = in.get_num_words();
  if (num_words == 1) {
    out.m_words[0] = rotr(in.m_words[0], dist, in.m_size);
  } else {
    int32_t shift_words = dist >> bitvector::WORD_SIZE_LOG;
    int32_t shift_bits = dist & bitvector::WORD_MASK;
    if (shift_bits) {
      uint32_t shift_bits_l = bitvector::WORD_SIZE - shift_bits;
      uint32_t prev = in.m_words[0];
      for (int32_t i = num_words - 1, j = i - shift_words; i >= 0; --i) {
        uint32_t curr = in.m_words[i];
        out.m_words[j] = (curr >> shift_bits) | (prev << shift_bits_l);
        prev = curr;
        if (j-- == 0) 
          j = num_words - 1;         
      }
    } else {
      for (int32_t i = num_words - 1, j = i - shift_words; i >= 0; --i) {
        out.m_words[j] = in.m_words[i];
        if (j-- == 0)
          j = num_words - 1;         
      }
    }
  }
  out.clear_unused_bits(); // clear extra bits added by left shift
}

std::ostream& chdl_internal::operator<<(std::ostream& os, const bitvector& b) {
  auto oldflags = os.flags();
  os.setf(std::ios_base::hex, std::ios_base::basefield);
  os << "0x";
  for (int32_t i = b.get_num_words() - 1; i >= 0; --i) {
    uint32_t word = b.get_word(i);
    os << word;
    if (i != 0) 
      os << "_";
  }
  os.flags(oldflags);
  return os;
}
