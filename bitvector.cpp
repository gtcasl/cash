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

bitvector::bitvector(const std::string& value) : m_words(nullptr), m_size(0) {
  this->operator =(value);
}

bitvector::bitvector(uint32_t value, uint32_t size) : m_words(nullptr), m_size(0) {  
  uint32_t num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  CHDL_CHECK((1 < num_words) || 
                  ((1 == num_words) && 
                    (0 == (size & WORD_MASK) || 
                      (0 == (value >> (size & WORD_MASK))))), "input value out of bound");  
  this->resize(size, 0x0, true, false);
  m_words[0] = value;
}

bitvector::bitvector(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_words(nullptr), m_size(0) {  
  
  auto iterValue = value.begin();
  
  uint32_t num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;  
  int32_t n = num_words - value.size();
  
  for (int32_t i = n; i < 0; ++i, ++iterValue) {
    CHDL_CHECK(0 == *iterValue, "input value out of bound");
  }
  
  CHDL_CHECK((value.size() < num_words) 
          || (0 == (size & WORD_MASK) || (0 == (*iterValue >> (size & WORD_MASK)))), "input value out of bound");  
             
  this->resize(size, 0x0, false, false);
  
  uint32_t* dst = m_words + (num_words - 1);  
  
  
  for (int32_t i = 0; i < n; ++i) {
      *dst-- = 0x0;
  }
  
  for (auto iterEnd = value.end(); iterValue != iterEnd; ++iterValue) {
    *dst-- = *iterValue;
  }
}

bitvector::bitvector(char value, uint32_t size) : m_words(nullptr), m_size(0) {
  uint32_t value_;
  if (value == '0')
    value_ = 0x0;
  else if (value == '1')
    value_ = 0x1;
  else
    CHDL_ABORT("invalid character value");  
  this->resize(size, 0x0, false, false);
  m_words[0] = value_;
}

bitvector::~bitvector() {
  if (m_words)
    delete [] m_words;
}

void bitvector::resize(uint32_t size, uint32_t defaultValue, bool initialize, bool preserve) {  
  assert(size > 0);
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

bitvector& bitvector::operator=(const std::string& value) {
  std::vector<uint32_t> tmp;
  
  int base = 0;
  int start = 0;
  
  switch (value.back()) {
  case 'b':
    base = 2;
    break;
  case 'o':
    base = 8;
    break;
  case 'd':
    base = 10;
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
  uint32_t len(value.size() - 1); // remove type character
  uint32_t size = (len - start) * log_base;
    
  // get inline size 
  for (uint32_t i = start; i < len; ++i) {
    if (value[i] == '\'') { 
      size -= log_base; // adjust size if separator character
      continue; 
    }      
    if ((base == 16 && (value[i] == 'p' || value[i] == 'P')) 
     || (base != 16 && (value[i] == 'e' || value[i] == 'E'))) {
      len = i;
      size = stoul(value.substr(i + 1));      
      break;
    }
  }
  
  uint32_t num_words = (size + WORD_MASK) >> WORD_SIZE_LOG;
  tmp.resize(num_words, 0x0);
  
  uint32_t j = 0;
  uint32_t w = 0;  
  char str[2] = {0, 0};    
  for (uint32_t i = 0, n = len - start; i < n; ++i) {
    str[0] = value[len - i - 1];
    if (str[0] == '\'')
      continue; // skip separator character
    uint32_t v = strtol(str, nullptr, base);
    for (uint32_t k = 0; k < log_base; ++k) {
      uint32_t bit = (v >> k) & 0x1;  
      w |= (bit << (j % WORD_SIZE));
      if (0 == (++j % WORD_SIZE)) {
        tmp[(j - 1) >> WORD_SIZE_LOG] = w;
        w = 0;
      }
    }
  }  
  
  if (w) {
    tmp[j >> WORD_SIZE_LOG] = w;
  }
  
  if (this->get_num_words() != num_words) {
    this->resize(size, 0x0, false, false);    
  }
  
  uint32_t* dst = m_words;
  for (uint32_t v : tmp) {
    *dst++ = v;
  }
  
  return *this;
}

bool bitvector::operator==(const bitvector& rhs) const {
  if (m_size != rhs.m_size)
    return false;
  for (uint32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    if (m_words[i] != rhs.m_words[i])
      return false;
  }
  return true;
}

bool bitvector::operator<(const bitvector& rhs) const {
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

bitvector& bitvector::flip() {
  for (uint32_t i = 0, n = this->get_num_words(); i < n; ++i) {
    m_words[i] = ~m_words[i]; 
  }
  clear_unused_bits();
  return *this;
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

bool bitvector::to_bool() const {
  for (int32_t i = 0, n = this->get_num_words(); i < n; ++i) {
    if (m_words[i])
      return true;
  }
  return false;
}

bitvector& bitvector::operator&=(const bitvector& rhs) {
  assert(m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    m_words[i] &= rhs.m_words[i]; 
  }
  return *this;
}

bitvector& bitvector::operator|=(const bitvector& rhs) {
  assert(m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    m_words[i] |= rhs.m_words[i]; 
  }
  return *this;
}

bitvector& bitvector::operator^=(const bitvector& rhs) {
  assert(m_size == rhs.m_size);
  for (int32_t i = 0, n = rhs.get_num_words(); i < n; ++i) {
    m_words[i] ^= rhs.m_words[i]; 
  }
  return *this;
}

bitvector& bitvector::operator<<=(uint32_t dist) {
  if (dist > m_size)
    dist = m_size;
  uint32_t shift_words = dist >> WORD_SIZE_LOG;
  uint32_t shift_bits = dist & WORD_MASK;
  uint32_t num_words = this->get_num_words();  
  for (uint32_t i = 0, n = num_words - shift_words, prev = 0; i < n; ++i) {
    uint32_t curr = m_words[i];
    m_words[i + shift_words] = (curr << shift_bits) | (prev >> (WORD_SIZE - shift_bits));
    prev = curr;
  }  
  std::fill_n(m_words, shift_words, 0x0);
  clear_unused_bits(); // clear extra bits added by left shift
}

bitvector& bitvector::operator>>=(uint32_t dist) {
  if (dist > m_size)
    dist = m_size;
  uint32_t shift_words = dist >> WORD_SIZE_LOG;
  uint32_t shift_bits  = dist & WORD_MASK;
  uint32_t num_words   = this->get_num_words();  
  for (int32_t i = num_words - 1 - shift_words, prev = 0; i >= 0; --i) {
    uint32_t curr = m_words[i + shift_words];
    m_words[i] = (curr >> shift_bits) | (prev << (WORD_SIZE - shift_bits));
    prev = curr;
  }  
  std::fill_n(m_words + (num_words - shift_words), shift_words, 0x0);
}

std::ostream& chdl_internal::operator<<(std::ostream& os, const bitvector& b) {
  os << "0x";
  for (int32_t i = b.get_num_words() - 1; i >= 0; --i) {
    uint32_t word = b.get_word(i);
    os << std::hex << word;
    if (i != 0) 
      os << "_";
  }
  return os;
}
