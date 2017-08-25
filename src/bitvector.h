#pragma once

#include "common.h"

namespace cash {
namespace detail {

class bitvector {
public:
  
  enum { 
    WORD_SIZE_LOG = 5, 
    WORD_SIZE     = 1 << WORD_SIZE_LOG,
    WORD_MASK     = WORD_SIZE - 1,
  };
  
  class const_iterator;
  class iterator;
  
  using const_reference = bool;
  
  class reference {
  public:    
    
    reference& operator=(bool rhs) {
      if (rhs)
        word_ |= mask_;
      else
        word_ &= ~mask_;
      return *this;
    }
    
    operator bool() const {
      return (word_ & mask_) != 0;
    }
    
  protected:
    
    reference(uint32_t& word, uint32_t mask)
      : word_(word), mask_(mask) {}
    
    uint32_t& word_;
    uint32_t  mask_;
    
    friend class iterator;
    friend class bitvector;
  };  
    
  class const_iterator {
  public:        
    const_iterator(const const_iterator& rhs) 
      : words_(rhs.words_)
      , index_(rhs.index_)
    {}
    
    const_iterator& operator=(const const_iterator& rhs) {
      words_ = rhs.words_;
      index_ = rhs.index_;
      return *this;
    }
    
    const_reference operator*() const {
      return (*words_ & (1 << (index_ & WORD_MASK))) != 0;
    }
    
    bool operator==(const const_iterator& rhs) const {
      return index_ == rhs.index_;
    }
    
    bool operator!=(const const_iterator& rhs) const {
      return !(*this == rhs);
    }
    
    const_iterator& operator++() {
      if (0 == (++index_ & WORD_MASK))
          ++words_;
      return *this;
    }
    
    const_iterator& operator--() {
      if (0 == (index_-- & WORD_MASK))
          --words_;
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
      : words_(words)
      , index_(index) 
    {}
    
    void advance(int delta) {
      int offset = (index_ & WORD_MASK) + delta;
      if (offset >= 0) {
        words_ += (offset >> WORD_SIZE_LOG);    
      } else {
        words_ -= ((WORD_MASK - offset) >> WORD_SIZE_LOG);
      }
      index_ += delta;
    }
    
    const uint32_t* words_;
    uint32_t index_;
    
    friend class iterator;
    friend class bitvector;
  };
  
  class iterator : public const_iterator {
  public:
    using base = const_iterator;
    using base::words_;
    using base::index_;
    
    iterator(const iterator& rhs) : base(rhs) {}
    
    iterator(const const_iterator& rhs) : base(rhs) {}
    
    reference operator*() const {
      return reference(const_cast<uint32_t&>(*words_), 1 << (index_ & WORD_MASK));
    }
    
    bool operator==(const iterator& rhs) const {
      return base::operator ==(rhs);
    }
    
    bool operator!=(const iterator& rhs) const {
      return base::operator !=(rhs);
    }
    
    iterator& operator++() {
      if (0 == (++index_ & WORD_MASK))
          ++words_;
      return *this;
    } 
    
    iterator& operator--() {
      if (0 == (index_-- & WORD_MASK))
          --words_;
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
    
    iterator(uint32_t* words, uint32_t index)
      : const_iterator(words, index) {}
    
    friend class bitvector;
  };
  
  bitvector() : words_(nullptr), size_(0) {}
  
  bitvector(const bitvector& rhs);
  
  bitvector(bitvector&& rhs);
  
  explicit bitvector(uint32_t size);
  
  bitvector(uint32_t size, bool value)
    : bitvector(size, value ? '1' : '0')
  {}

  bitvector(uint32_t size, char value);

  bitvector(uint32_t size, const char* value);
    
  bitvector(uint32_t size, int8_t value)
    : bitvector(size, bitcast<uint32_t>(value))
  {}
  
  bitvector(uint32_t size, uint8_t value)
    : bitvector(size, bitcast<uint32_t>(value))
  {}
  
  bitvector(uint32_t size, int16_t value)
    : bitvector(size, bitcast<uint32_t>(value))
  {}
  
  bitvector(uint32_t size, uint16_t value)
    : bitvector(size, bitcast<uint32_t>(value))
  {}
  
  bitvector(uint32_t size, int32_t value)
    : bitvector(size, bitcast<uint32_t>(value))
  {}

  bitvector(uint32_t size, uint32_t value);
  
  bitvector(uint32_t size, int64_t value)
    : bitvector(size, {bitcast<uint32_t>(value >> 32), bitcast<uint32_t>(value)})
  {}
  
  bitvector(uint32_t size, uint64_t value)
    : bitvector(size, {bitcast<uint32_t>(value >> 32), bitcast<uint32_t>(value)})
  {}

  bitvector(uint32_t size, const std::initializer_list<uint32_t>& value);
  
  ~bitvector();
  
  void resize(uint32_t size,
              uint32_t value = 0,
              bool initialize = true,
              bool preserve = true);
  
  bitvector& operator=(const bitvector& rhs);
  
  bitvector& operator=(bitvector&& rhs);

  bitvector& operator=(bool value) {
    return this->operator =(value ? '1' : '0');
  }

  bitvector& operator=(char value);
  
  bitvector& operator=(const char* value);
  
  bitvector& operator=(uint32_t value);
  
  bitvector& operator=(const std::initializer_list<uint32_t>& value);
  
  bitvector& operator=(int8_t value) {
    return this->operator=(bitcast<uint32_t>(value));
  }
  
  bitvector& operator=(uint8_t value) {
    return this->operator=(bitcast<uint32_t>(value));
  }
  
  bitvector& operator=(int16_t value) {
    return this->operator=(bitcast<uint32_t>(value));
  }
  
  bitvector& operator=(uint16_t value) {
    return this->operator=(bitcast<uint32_t>(value));
  }
  
  bitvector& operator=(int32_t value) {
    return this->operator=(bitcast<uint32_t>(value));
  }
  
  bitvector& operator=(int64_t value) {
    return this->operator=(
      {bitcast<uint32_t>(value >> 32), bitcast<uint32_t>(value)}
    );
  }
  
  bitvector& operator=(uint64_t value) {
    return this->operator=(
      {bitcast<uint32_t>(value >> 32), bitcast<uint32_t>(value)}
    );
  }
  
  const_reference at(uint32_t idx) const {
    assert(idx < size_);
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    return (words_[widx] & mask) != 0;
  }
  
  reference at(uint32_t idx) {
    assert(idx < size_);
    uint32_t widx = idx >> WORD_SIZE_LOG;
    uint32_t wbit = idx & WORD_MASK;
    uint32_t mask = 1 << wbit;
    return reference(words_[widx], mask);
  }
  
  const_reference operator[](uint32_t idx) const {
    return this->at(idx);
  }
  
  reference operator[](uint32_t idx) {
    return this->at(idx);
  }
  
  uint32_t get_word(uint32_t widx) const {
    assert(widx < this->get_num_words());
    return words_[widx];
  }
  
  void set_word(uint32_t widx, uint32_t word) {
    assert(widx < this->get_num_words());
    words_[widx] = word;
  }

  const uint32_t* get_words() const {
    return words_;
  }

  uint32_t* get_words() {
    return words_;
  }
  
  uint32_t get_num_words() const {
    return (size_ + WORD_MASK) >> WORD_SIZE_LOG;;
  }
  
  uint32_t get_size() const {
    return size_;
  }

  void clear_unused_bits();
  
  void copy(uint32_t dst_offset,
            const bitvector& src,
            uint32_t src_offset,
            uint32_t src_length);
  
  void read(uint8_t* out, uint32_t offset, uint32_t size) const;
  
  void write(const uint8_t* in, uint32_t offset, uint32_t size);
  
  int32_t find_first() const;
  
  int32_t find_last() const;
  
  bool is_empty() const;
    
  const_reference front() const {
    return this->at(0);
  }
  
  reference front() {
    return this->at(0);
  }
  
  const_reference back() const {
    return this->at(size_ - 1);
  }
  
  reference back() {
    return this->at(size_ - 1);
  }
  
  iterator begin() {
    return iterator(words_, 0);
  }
  
  iterator end() {
    return iterator(nullptr, size_);
  }
  
  const_iterator begin() const {
    return const_iterator(words_, 0);
  }
  
  const_iterator end() const {
    return const_iterator(nullptr, size_);
  }

  bool operator==(const bitvector& rhs) const;

  bool operator<(const bitvector& rhs) const;

#define CH_DEF_CAST(type) \
  explicit operator type() const { \
    CH_CHECK(sizeof(type) * 8 >= size_, "invalid cast, cannot cast %d-bit vector to %ld-bit value", size_, sizeof(type) * 8); \
    return bitcast<type>(words_[0]); \
  }
  CH_DEF_CAST(bool)
  CH_DEF_CAST(char)
  CH_DEF_CAST(int8_t)
  CH_DEF_CAST(uint8_t)
  CH_DEF_CAST(int16_t)
  CH_DEF_CAST(uint16_t)
  CH_DEF_CAST(int32_t)
  CH_DEF_CAST(uint32_t)
#undef CH_DEF_CAST

  explicit operator uint64_t() const {
    CH_CHECK(sizeof(uint64_t) * 8 >= size_, "invalid cast, cannot cast %d-bit vector to 64-bit value", size_);
    return (static_cast<uint64_t>((size_ > 32) ? words_[1] : 0) << 32) | words_[0];
  }

  explicit operator int64_t() const {
    return this->operator uint64_t();
  }
  
protected:
  
  uint32_t* words_;
  uint32_t  size_;
};

std::ostream& operator<<(std::ostream& os, const bitvector& b);

}
}
