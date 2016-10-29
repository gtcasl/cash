#pragma once

#include "common.h"

namespace chdl_internal {

class bitvector {
public:
  
  enum { 
    WORD_SIZE_LOG = 5, 
    WORD_SIZE     = 1 << WORD_SIZE_LOG,
    WORD_MASK     = WORD_SIZE - 1,
  };
  
  class const_iterator;
  class iterator;
  
  typedef bool const_reference;
  
  class reference {
  public:    
    
    reference& operator=(bool rhs) {
      if (rhs)
        m_word |= m_mask;
      else
        m_word &= ~m_mask;
    }
    
    operator bool() const {
      return (m_word & m_mask) != 0;
    }
    
  protected:
    
    reference(uint32_t& word, uint32_t mask) : m_word(word), m_mask(mask) {}
    
    uint32_t& m_word;
    uint32_t  m_mask;
    
    friend class iterator;
    friend class bitvector;
  };  
    
  class const_iterator {
  public:        
    const_iterator(const const_iterator& rhs) 
      : m_words(rhs.m_words)
      , m_index(rhs.m_index)
    {}
    
    ~const_iterator() {}
    
    const_iterator& operator=(const const_iterator& rhs) {
      m_words = rhs.m_words;
      m_index = rhs.m_index;
      return *this;
    }
    
    const_reference operator*() const {
      return (*m_words & (1 << (m_index & WORD_MASK))) != 0;
    }
    
    bool operator==(const const_iterator& rhs) const {
      return m_index == rhs.m_index;
    }
    
    bool operator!=(const const_iterator& rhs) const {
      return !(*this == rhs);
    }
    
    const_iterator& operator++() {
      if (0 == (++m_index & WORD_MASK))
          ++m_words;
      return *this;
    }
    
    const_iterator& operator--() {
      if (0 == (m_index-- & WORD_MASK))
          --m_words;
      return *this;
    }
    
    const_iterator operator++(int) {
      const_iterator ret(*this);
      this->operator++();
      return ret;
    }
    
    const_iterator operator--(int) {
      const_iterator ret(*this);
      this->operator--();
      return ret;
    }
    
    const_iterator& operator+=(int incr) {
      this->advance(incr);
      return *this;
    }
    
    const_iterator& operator-=(int dec) {
      this->advance(-dec);      
      return *this;
    }
    
    const_iterator operator+(int incr) const {
      const_iterator ret(*this);
      ret += incr;
      return ret;
    }
    
    const_iterator operator-(int dec) const {
      const_iterator ret(*this);
      ret -= dec;
      return ret;
    }
    
  protected:
    
    const_iterator(const uint32_t* words, uint32_t index) 
      : m_words(words)
      , m_index(index) 
    {}
    
    void advance(int delta) {
      int offset = (m_index & WORD_MASK) + delta;
      if (offset >= 0) {
        m_words += (offset >> WORD_SIZE_LOG);    
      } else {
        m_words -= ((WORD_MASK - offset) >> WORD_SIZE_LOG);
      }
      m_index += delta;
    }
    
    uint32_t  m_index;
    const uint32_t* m_words;
    
    friend class iterator;
    friend class bitvector;
  };
  
  class iterator : public const_iterator {
  public:
    using base = const_iterator;
    using base::m_words;
    using base::m_index;
    
    iterator(const iterator& rhs) : base(rhs) {}
    
    iterator(const const_iterator& rhs) : base(rhs) {}
    
    ~iterator() {}    
    
    reference operator*() const {
      return reference(const_cast<uint32_t&>(*m_words), 1 << (m_index & WORD_MASK));
    }
    
    bool operator==(const iterator& rhs) const {
      return base::operator ==(rhs);
    }
    
    bool operator!=(const iterator& rhs) const {
      return base::operator !=(rhs);
    }
    
    iterator& operator++() {
      if (0 == (++m_index & WORD_MASK))
          ++m_words;
      return *this;
    } 
    
    iterator& operator--() {
      if (0 == (m_index-- & WORD_MASK))
          --m_words;
      return *this;
    }
    
    iterator operator++(int) {
      iterator ret(*this);
      this->operator++();
      return ret;
    }
    
    iterator operator--(int) {
      iterator ret(*this);
      this->operator--();
      return ret;
    }
    
    iterator& operator+=(int incr) {
      this->advance(incr);
      return *this;
    }
    
    iterator& operator-=(int dec) {
      this->advance(-dec);      
      return *this;
    }
    
    iterator operator+(int incr) const {
      iterator ret(*this);
      ret += incr;
      return ret;
    }
    
    iterator operator-(int dec) const {
      iterator ret(*this);
      ret -= dec;
      return ret;
    }
    
  protected:  
    
    iterator(uint32_t* words, uint32_t index) : const_iterator(words, index) {}
    
    friend class bitvector;
  };
  
  bitvector() : m_words(nullptr), m_size(0) {}
  
  bitvector(const bitvector& rhs);
  
  bitvector(bitvector&& rhs);
  
  explicit bitvector(uint32_t size);
  
  bitvector(const std::string& value);
  
  bitvector(uint32_t value, uint32_t size);
  
  bitvector(const std::initializer_list<uint32_t>& value, uint32_t size);
  
  bitvector(char value, uint32_t size);
    
  bitvector(int8_t value, uint32_t size) : bitvector(bit_cast<uint32_t>(value), size) {}
  
  bitvector(uint8_t value, uint32_t size) : bitvector(bit_cast<uint32_t>(value), size) {}
  
  bitvector(int16_t value, uint32_t size) : bitvector(bit_cast<uint32_t>(value), size) {}
  
  bitvector(uint16_t value, uint32_t size) : bitvector(bit_cast<uint32_t>(value), size) {}
  
  bitvector(int32_t value, uint32_t size) : bitvector(bit_cast<uint32_t>(value), size) {}  
  
  bitvector(int64_t value, uint32_t size) : bitvector({bit_cast<uint32_t>(value >> 32), bit_cast<uint32_t>(value)}, size) {}
  
  bitvector(uint64_t value, uint32_t size) : bitvector({bit_cast<uint32_t>(value >> 32), bit_cast<uint32_t>(value)}, size) {}  
  
  ~bitvector();
  
  void resize(uint32_t size, uint32_t defaultValue = 0x0, bool initialize = true, bool preserve = true);
  
  bitvector& operator=(const bitvector& rhs);
  
  bitvector& operator=(bitvector&& rhs);
  
  bitvector& operator=(const std::string& value);
  
  const_reference at(uint32_t idx) const {
    assert(idx < m_size);
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    return (m_words[widx] & mask) != 0;
  }
  
  reference at(uint32_t idx) {
    assert(idx < m_size);
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    return reference(m_words[widx], mask);
  }
  
  const_reference operator[](uint32_t idx) const {
    return this->at(idx);
  }
  
  reference operator[](uint32_t idx) {
    return this->at(idx);
  }
  
  uint32_t get_word(uint32_t widx) const {
    assert(widx < this->get_num_words());
    return m_words[widx];
  }
  
  void set_word(uint32_t widx, uint32_t word) {
    assert(widx < this->get_num_words());
    m_words[widx] = word;
  }
  
  uint32_t get_num_words() const {
    return (m_size + WORD_MASK) >> WORD_SIZE_LOG;;
  }
  
  uint32_t get_size() const {
    return m_size;
  }
  
  void copy(uint32_t dst_offset, const bitvector& src, uint32_t src_offset, uint32_t src_length);
  
  bitvector& flip();
  
  int32_t find_first() const;
  
  int32_t find_last() const;
  
  bitvector& flip(uint32_t idx) {
    assert(idx < m_size);
    m_words[idx >> WORD_SIZE_LOG] ^= 1 << (idx & WORD_MASK);
    return *this;
  }
  
  bool to_bool() const;
  
  bitvector operator~() const {
    bitvector ret(*this);
    ret.flip();
    return ret;
  }
  
  bitvector operator<<(uint32_t dist) const {
    bitvector ret(*this);
    ret <<= dist;
    return ret;
  }
  
  bitvector operator>>(uint32_t dist) const {
    bitvector ret(*this);
    ret >>= dist;
    return ret;
  }
  
  bitvector& operator<<=(uint32_t dist);
  
  bitvector& operator>>=(uint32_t dist);
  
  bitvector& operator&=(const bitvector& rhs);
  
  bitvector& operator|=(const bitvector& rhs);
  
  bitvector& operator^=(const bitvector& rhs);
  
  bool operator==(const bitvector& rhs) const;
  
  bool operator<(const bitvector& rhs) const;
  
  bool operator!=(const bitvector& rhs) const {
    return !(*this == rhs);
  }
  
  bool operator>(const bitvector& rhs) const {
    return (rhs < *this);
  }
  
  bool operator<=(const bitvector& rhs) const {
    return !(*this > rhs);
  }
  
  bool operator>=(const bitvector& rhs) const {
    return !(*this < rhs);
  }
    
  bitvector operator&(const bitvector& rhs) const {
    bitvector ret(*this);
    ret &= rhs;
    return ret;
  }
  
  bitvector operator|(const bitvector& rhs) const {
    bitvector ret(*this);
    ret |= rhs;
    return ret;
  }
  
  bitvector operator^(const bitvector& rhs) const {
    bitvector ret(*this);
    ret ^= rhs;
    return ret;
  }
  
  const_reference front() const {
    return this->at(0);
  }
  
  reference front() {
    return this->at(0);
  }
  
  const_reference back() const {
    return this->at(m_size - 1);
  }
  
  reference back() {
    return this->at(m_size - 1);
  }
  
  iterator begin() {
    return iterator(m_words, 0);
  }
  
  iterator end() {
    return iterator(nullptr, m_size);
  }
  
  const_iterator begin() const {
    return const_iterator(m_words, 0);
  }
  
  const_iterator end() const {
    return const_iterator(nullptr, m_size);
  }
  
protected:
  
  void clear_unused_bits();
  
  uint32_t* m_words;
  uint32_t  m_size;
};

}
