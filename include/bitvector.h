#pragma once

#include "common.h"

namespace ch {
namespace internal {

template <typename T> struct is_bitvector_array_type : std::false_type {};
template <> struct is_bitvector_array_type <uint8_t> : std::true_type {};
template <> struct is_bitvector_array_type <uint16_t> : std::true_type {};
template <> struct is_bitvector_array_type <uint32_t> : std::true_type {};
template <> struct is_bitvector_array_type <uint64_t> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_array_type_v = is_bitvector_array_type<T>::value;

template <typename T> struct is_bitvector_convertible_impl : std::false_type {};
template <> struct is_bitvector_convertible_impl <bool> : std::true_type {};
template <> struct is_bitvector_convertible_impl <int8_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <uint8_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <int16_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <uint16_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <int32_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <uint32_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <int64_t> : std::true_type {};
template <> struct is_bitvector_convertible_impl <uint64_t> : std::true_type {};

template <>
struct is_bitvector_convertible_impl<std::initializer_list<uint32_t>> : std::true_type {};

template <typename T, std::size_t N>
struct is_bitvector_convertible_impl<std::array<T, N>> : std::true_type {};

template <typename T>
struct is_bitvector_convertible_impl<std::vector<T>> : std::true_type {};

template <>
struct is_bitvector_convertible_impl<std::string> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_convertible_v =
  is_true_v<(is_bitvector_convertible_impl<T>::value || std::is_enum_v<T>)>;

template <typename T> struct is_bitvector_castable : std::false_type {};
template <> struct is_bitvector_castable <bool> : std::true_type {};
template <> struct is_bitvector_castable <int8_t> : std::true_type {};
template <> struct is_bitvector_castable <uint8_t> : std::true_type {};
template <> struct is_bitvector_castable <int16_t> : std::true_type {};
template <> struct is_bitvector_castable <uint16_t> : std::true_type {};
template <> struct is_bitvector_castable <int32_t> : std::true_type {};
template <> struct is_bitvector_castable <uint32_t> : std::true_type {};
template <> struct is_bitvector_castable <int64_t> : std::true_type {};
template <> struct is_bitvector_castable <uint64_t> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_castable_v = is_bitvector_castable<T>::value;

class bitvector {
public:
  
  enum { 
    WORD_SIZE_LOG = 5, 
    WORD_SIZE     = 1 << WORD_SIZE_LOG,
    WORD_MASK     = WORD_SIZE - 1,
    WORD_MAX      = 0xFFFFFFFF,
  };
  
  class const_iterator;
  class iterator;
  
  using const_reference = bool;
  
  class reference {
  public:    
    
    reference& operator=(bool rhs) {
      if (rhs) {
        word_ |= mask_;
      } else {
        word_ &= ~mask_;
      }
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
      , offset_(rhs.offset_)
    {}
    
    const_iterator& operator=(const const_iterator& rhs) {
      words_ = rhs.words_;
      offset_ = rhs.offset_;
      return *this;
    }
    
    const_reference operator*() const {
      return (*words_ & (1 << (offset_ & WORD_MASK))) != 0;
    }
    
    bool operator==(const const_iterator& rhs) const {
      return offset_ == rhs.offset_;
    }
    
    bool operator!=(const const_iterator& rhs) const {
      return !(*this == rhs);
    }
    
    const_iterator& operator++() {
      if (0 == (++offset_ & WORD_MASK))
          ++words_;
      return *this;
    }
    
    const_iterator& operator--() {
      if (0 == (offset_-- & WORD_MASK))
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
    
    const_iterator(const uint32_t* words, uint32_t offset)
      : words_(words)
      , offset_(offset)
    {}
    
    void advance(int delta) {
      int offset = (offset_ & WORD_MASK) + delta;
      if (offset >= 0) {
        words_ += (offset >> WORD_SIZE_LOG);    
      } else {
        words_ -= ((WORD_MASK - offset) >> WORD_SIZE_LOG);
      }
      offset_ += delta;
    }
    
    const uint32_t* words_;
    uint32_t offset_;
    
    friend class iterator;
    friend class bitvector;
  };
  
  class iterator : public const_iterator {
  public:
    using base = const_iterator;
    using base::words_;
    using base::offset_;
    
    iterator(const iterator& rhs) : base(rhs) {}
    
    iterator(const const_iterator& rhs) : base(rhs) {}
    
    reference operator*() const {
      return reference(const_cast<uint32_t&>(*words_), 1 << (offset_ & WORD_MASK));
    }
    
    bool operator==(const iterator& rhs) const {
      return base::operator ==(rhs);
    }
    
    bool operator!=(const iterator& rhs) const {
      return base::operator !=(rhs);
    }
    
    iterator& operator++() {
      if (0 == (++offset_ & WORD_MASK))
          ++words_;
      return *this;
    } 
    
    iterator& operator--() {
      if (0 == (offset_-- & WORD_MASK))
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
    
    iterator(uint32_t* words, uint32_t offset)
      : const_iterator(words, offset) {}
    
    friend class bitvector;
  };

  class const_reverse_iterator {
  public:
    const_reverse_iterator(const const_reverse_iterator& rhs)
      : words_(rhs.words_)
      , offset_(rhs.offset_)
    {}

    const_reverse_iterator& operator=(const const_reverse_iterator& rhs) {
      words_ = rhs.words_;
      offset_ = rhs.offset_;
      return *this;
    }

    const_reference operator*() const {
      return (*words_ & (1 << (offset_ & WORD_MASK))) != 0;
    }

    bool operator==(const const_reverse_iterator& rhs) const {
      return offset_ == rhs.offset_;
    }

    bool operator!=(const const_reverse_iterator& rhs) const {
      return !(*this == rhs);
    }

    const_reverse_iterator& operator++() {
      if (0 == (offset_-- & WORD_MASK))
          --words_;
      return *this;
    }

    const_reverse_iterator& operator--() {
      if (0 == (++offset_ & WORD_MASK))
          ++words_;
      return *this;
    }

    const_reverse_iterator operator++(int) {
      const_reverse_iterator ret(*this);
      this->operator++();
      return ret;
    }

    const_reverse_iterator operator--(int) {
      const_reverse_iterator ret(*this);
      this->operator--();
      return ret;
    }

    const_reverse_iterator& operator+=(int dec) {
      this->advance(-dec);
      return *this;
    }

    const_reverse_iterator& operator-=(int incr) {
      this->advance(incr);
      return *this;
    }

    const_reverse_iterator operator+(int dec) const {
      const_reverse_iterator ret(*this);
      ret -= dec;
      return ret;
    }

    const_reverse_iterator operator-(int incr) const {
      const_reverse_iterator ret(*this);
      ret += incr;
      return ret;
    }

  protected:

    const_reverse_iterator(const uint32_t* words, uint32_t offset)
      : words_(words)
      , offset_(offset)
    {}

    void advance(int delta) {
      int offset = (offset_ & WORD_MASK) + delta;
      if (offset >= 0) {
        words_ += (offset >> WORD_SIZE_LOG);
      } else {
        words_ -= ((WORD_MASK - offset) >> WORD_SIZE_LOG);
      }
      offset_ += delta;
    }

    const uint32_t* words_;
    uint32_t offset_;

    friend class reverse_iterator;
    friend class bitvector;
  };

  class reverse_iterator : public const_reverse_iterator {
  public:
    using base = const_reverse_iterator;
    using base::words_;
    using base::offset_;

    reverse_iterator(const reverse_iterator& rhs) : base(rhs) {}

    reverse_iterator(const const_reverse_iterator& rhs) : base(rhs) {}

    reference operator*() const {
      return reference(const_cast<uint32_t&>(*words_), 1 << (offset_ & WORD_MASK));
    }

    bool operator==(const reverse_iterator& rhs) const {
      return base::operator ==(rhs);
    }

    bool operator!=(const reverse_iterator& rhs) const {
      return base::operator !=(rhs);
    }

    reverse_iterator& operator++() {
      if (0 == (offset_-- & WORD_MASK))
          --words_;
      return *this;
    }

    reverse_iterator& operator--() {
      if (0 == (++offset_ & WORD_MASK))
          ++words_;
      return *this;
    }

    reverse_iterator operator++(int) {
      reverse_iterator ret(*this);
      this->operator++();
      return ret;
    }

    reverse_iterator operator--(int) {
      reverse_iterator ret(*this);
      this->operator--();
      return ret;
    }

    reverse_iterator& operator+=(int dec) {
      this->advance(-dec);
      return *this;
    }

    reverse_iterator& operator-=(int incr) {
      this->advance(incr);
      return *this;
    }

    reverse_iterator operator+(int dec) const {
      reverse_iterator ret(*this);
      ret -= dec;
      return ret;
    }

    reverse_iterator operator-(int incr) const {
      reverse_iterator ret(*this);
      ret += incr;
      return ret;
    }

  protected:

    reverse_iterator(uint32_t* words, uint32_t offset)
      : const_reverse_iterator(words, offset) {}

    friend class bitvector;
  };
  
  bitvector() : words_(nullptr), size_(0) {}
  
  bitvector(const bitvector& rhs);
  
  bitvector(bitvector&& rhs);
  
  explicit bitvector(uint32_t size);

  explicit bitvector(uint32_t size, int8_t value)
    : bitvector(size, int64_t(value))
  {}

  explicit bitvector(uint32_t size, uint8_t value)
    : bitvector(size, uint64_t(value))
  {}

  explicit bitvector(uint32_t size, int16_t value)
    : bitvector(size, int64_t(value))
  {}

  explicit bitvector(uint32_t size, uint16_t value)
    : bitvector(size, uint64_t(value))
  {}

  explicit bitvector(uint32_t size, int32_t value)
    : bitvector(size, int64_t(value))
  {}

  explicit bitvector(uint32_t size, uint32_t value)
    : bitvector(size, uint64_t(value))
  {}

  explicit bitvector(uint32_t size, int64_t value);

  explicit bitvector(uint32_t size, uint64_t value);

  template <typename T, std::size_t N,
            CH_REQUIRE_0(is_bitvector_array_type_v<T>)>
  explicit bitvector(uint32_t size, const std::array<T, N>& value) : bitvector(size) {
    this->write(0, value.data(), N * sizeof(T), 0, N * CH_WIDTH_OF(T));
  }

  template <typename T,
            CH_REQUIRE_0(is_bitvector_array_type_v<T>)>
  explicit bitvector(uint32_t size, const std::vector<T>& value) : bitvector(size) {
    this->write(0, value.data(), value.size() * sizeof(T), 0, value.size() * CH_WIDTH_OF(T));
  }

  explicit bitvector(uint32_t size, const std::initializer_list<uint32_t>& value);

  explicit bitvector(uint32_t size, const std::string& value);

  ~bitvector();
  
  bitvector& operator=(const bitvector& rhs);
  
  bitvector& operator=(bitvector&& rhs);

  bitvector& operator=(int8_t value) {
    return this->operator=(int64_t(value));
  }

  bitvector& operator=(uint8_t value) {
    return this->operator=(uint64_t(value));
  }

  bitvector& operator=(int16_t value) {
    return this->operator=(int64_t(value));
  }

  bitvector& operator=(uint16_t value) {
    return this->operator=(uint64_t(value));
  }
  
  bitvector& operator=(int32_t value) {
    return this->operator=(int64_t(value));
  }

  bitvector& operator=(uint32_t value) {
    return this->operator=(uint64_t(value));
  }

  bitvector& operator=(int64_t value);

  bitvector& operator=(uint64_t value);

  template <typename T, std::size_t N,
            CH_REQUIRE_0(is_bitvector_array_type_v<T>)>
  bitvector& operator=(const std::array<T, N>& value) {
    this->write(0, value.data(), N * sizeof(T), 0, N * CH_WIDTH_OF(T));
    return *this;
  }

  template <typename T,
            CH_REQUIRE_0(is_bitvector_array_type_v<T>)>
  bitvector& operator=(const std::vector<T>& value) {
    this->write(0, value.data(), value.size() * sizeof(T), 0, value.size() * CH_WIDTH_OF(T));
    return *this;
  }

  bitvector& operator=(const std::initializer_list<uint32_t>& value);

  bitvector& operator=(const std::string& value);
  
  const_reference at(uint32_t idx) const;
  
  reference at(uint32_t idx);
  
  const_reference operator[](uint32_t idx) const {
    return this->at(idx);
  }
  
  reference operator[](uint32_t idx) {
    return this->at(idx);
  }
  
  uint32_t word(uint32_t widx) const {
    assert(widx < this->num_words());
    return words_[widx];
  }
  
  uint32_t& word(uint32_t widx) {
    assert(widx < this->num_words());
    return words_[widx];
  }

  const uint32_t* words() const {
    return words_;
  }

  uint32_t* words() {
    return words_;
  }

  uint32_t* words(uint32_t* words) {
    std::swap(words_, words);
    return words;
  }
  
  uint32_t num_words() const {
    return (size_ + WORD_MASK) >> WORD_SIZE_LOG;
  }
  
  uint32_t size() const {
    return size_;
  }

  uint32_t cbsize() const {
    return (num_words() << WORD_SIZE_LOG) / 8;
  }

  void clear();

  void resize(uint32_t size,
              uint32_t value = 0x0,
              bool initialize = false,
              bool preserve = false);

  void clear_unused_bits();
  
  void copy(uint32_t dst_offset,
            const bitvector& src,
            uint32_t src_offset,
            uint32_t length);
  
  void read(uint32_t dst_offset,
            void* dst,
            uint32_t dst_cbsize,
            uint32_t src_offset,
            uint32_t length) const;
  
  void write(uint32_t dst_offset,
             const void* src,
             uint32_t src_cbsize,
             uint32_t src_offset,
             uint32_t length);
  
  int find_first() const;
  
  int find_last() const;
  
  bool empty() const;
    
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
  
  auto begin() {
    return iterator(words_, 0);
  }
  
  auto end() {
    return iterator(nullptr, size_);
  }
  
  auto begin() const {
    return const_iterator(words_, 0);
  }
  
  auto end() const {
    return const_iterator(nullptr, size_);
  }

  auto rbegin() {
    return reverse_iterator(words_, size_ - 1);
  }

  auto rend() {
    return reverse_iterator(nullptr, -1);
  }

  auto rbegin() const {
    return const_reverse_iterator(words_, size_ - 1);
  }

  auto rend() const {
    return const_reverse_iterator(nullptr, -1);
  }

  bool operator==(const bitvector& rhs) const;

  bool operator<(const bitvector& rhs) const;

#define CH_DEF_CAST(type) \
  explicit operator type() const { \
    CH_CHECK(CH_WIDTH_OF(type) >= size_, "invalid size cast"); \
    return bitcast<type>(words_[0]); \
  }
  CH_DEF_CAST(bool)
  CH_DEF_CAST(int8_t)
  CH_DEF_CAST(uint8_t)
  CH_DEF_CAST(int16_t)
  CH_DEF_CAST(uint16_t)
  CH_DEF_CAST(int32_t)
  CH_DEF_CAST(uint32_t)
#undef CH_DEF_CAST

  explicit operator uint64_t() const {
    CH_CHECK(CH_WIDTH_OF(uint64_t) >= size_, "invalid size cast");
    return (static_cast<uint64_t>((size_ > 32) ? words_[1] : 0) << 32) | words_[0];
  }

  explicit operator int64_t() const {
    return this->operator uint64_t();
  }
  
protected:
  
  uint32_t* words_;
  uint32_t  size_;
};

std::ostream& operator<<(std::ostream& out, const bitvector& rhs);

///////////////////////////////////////////////////////////////////////////////

void ZExt(bitvector& out, const bitvector& in);
void SExt(bitvector& out, const bitvector& in);

void Inv(bitvector& out, const bitvector& in);
void And(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Or(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Xor(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Nand(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Nor(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Xnor(bitvector& out, const bitvector& lhs, const bitvector& rhs);

bool AndR(const bitvector& in);
bool OrR(const bitvector& in);
bool XorR(const bitvector& in);
bool NandR(const bitvector& in);
bool NorR(const bitvector& in);
bool XnorR(const bitvector& in);

void Sll(bitvector& out, const bitvector& in, const bitvector& bits);
void Srl(bitvector& out, const bitvector& in, const bitvector& bits);
void Sra(bitvector& out, const bitvector& in, const bitvector& bits);

void Add(bitvector& out, const bitvector& lhs, const bitvector& rhs, uint32_t cin);

inline void Add(bitvector& out, const bitvector& lhs, const bitvector& rhs) {
  Add(out, lhs, rhs, 0);
}

void Sub(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Neg(bitvector& out, const bitvector& in);
void Mult(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Div(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void Mod(bitvector& out, const bitvector& lhs, const bitvector& rhs);

void fAdd(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void fSub(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void fMult(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void fDiv(bitvector& out, const bitvector& lhs, const bitvector& rhs);

}
}
