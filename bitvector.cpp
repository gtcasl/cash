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

bitvector::bitvector(uint32_t size, uint32_t defaultValue) : m_words(nullptr), m_size(0) {
  this->resize(size, defaultValue, true, false);
}

bitvector::bitvector(const std::string& value) : m_words(nullptr), m_size(0) {
  this->operator =(value);
}

bitvector::bitvector(const std::initializer_list<uint32_t>& value, uint32_t size) 
  : m_words(nullptr), m_size(0) {  
  CHDL_REQUIRED(0 == (*value.begin() >> (size & WORD_MASK)), "initializer list size mismatch");  
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
    m_words[num_words-1] &= ~(WORD_MASK << extra_bits);
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
  
  uint32_t N = value.size();
  uint32_t L(N - 1);
    
  for (uint32_t i = 0; i <= L; ++i) {
    if (value[i] == 'e' || value[i] == 'E') {
      N = stoul(value.substr(i + 1));
      L = i - 1;
      break;
    }
  }
  
  uint32_t num_words = (N + WORD_MASK) >> WORD_SIZE_LOG;
  tmp.resize(num_words, 0x0);
  
  {
    uint32_t j = 0;
    uint32_t v = 0;
    
    for (uint32_t i = 0, j = 0; i <= L;) {
      uint32_t c = (value[L - i] - '0');
      v |= (c << (i % WORD_SIZE));
      if (0 == (++i % WORD_SIZE))
        tmp[j++] = v;
    }  
    tmp[j] = v;
  }
  
  if (this->get_num_words() != num_words) {
    this->resize(N, 0x0, false, false);    
  }
  
  uint32_t* dst = m_words;
  for (uint32_t v : tmp) {
    *dst++ = v;
  }
  
  return *this;
}

bitvector& bitvector::operator=(const std::initializer_list<uint32_t>& value) {
  size_t num_words = value.size();  
  if (this->get_num_words() != num_words) {
    this->resize(num_words * WORD_SIZE, 0x0, false, false);    
  }
  
  uint32_t* dst = m_words + (num_words - 1);
  for (uint32_t v : value) {
    *dst-- = v;
  }
  
  return *this;
}

bool bitvector::operator==(const std::initializer_list<uint32_t>& value) const {
  size_t num_words = value.size();  
  if (this->get_num_words() != num_words)
    return false;
  uint32_t* dst = m_words + (num_words - 1);
  for (uint32_t v : value) {
    if (*dst++ != v)
      return false;
  }
  return true;
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
  for (int32_t i = 0, n = this->get_num_words(); i < n; ++i) {
    m_words[i] = ~m_words[i]; 
  }
  clear_unused_bits();
  return *this;
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
