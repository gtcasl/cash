#pragma once

#include "common.h"

namespace ch {
namespace internal {

template <typename T> struct is_bitvector_array_type : std::false_type {};
template <> struct is_bitvector_array_type<uint8_t> : std::true_type {};
template <> struct is_bitvector_array_type<uint16_t> : std::true_type {};
template <> struct is_bitvector_array_type<uint32_t> : std::true_type {};
template <> struct is_bitvector_array_type<uint64_t> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_array_type_v = is_bitvector_array_type<T>::value;

template <typename T> struct is_bitvector_extended_type_impl : std::false_type {};

template <typename T, std::size_t N>
struct is_bitvector_extended_type_impl<std::array<T, N>> : std::true_type {};

template <typename T>
struct is_bitvector_extended_type_impl<std::vector<T>> : std::true_type {};

template <>
struct is_bitvector_extended_type_impl<std::string> : std::true_type {};

template <>
struct is_bitvector_extended_type_impl<const char*> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_extended_type_v = is_bitvector_extended_type_impl<T>::value;

class bitvector {
public:
  
  using word_t   = uint64_t;

  using xword_t  = std::conditional_t<sizeof(word_t) == 8, uint8_t,
                     std::conditional_t<sizeof(word_t) == 16, uint16_t, uint32_t>>;
  using yword_t  = std::conditional_t<sizeof(word_t) == 8, uint16_t,
                      std::conditional_t<sizeof(word_t) == 16, uint32_t, uint64_t>>;

  using sword_t  = std::make_signed_t<word_t>;
  using syword_t = std::make_signed_t<yword_t>;

  static constexpr unsigned WORD_LOGSIZE = ilog2(bitwidth_v<word_t>);
  static constexpr unsigned WORD_SIZE    = 1 << WORD_LOGSIZE;
  static constexpr unsigned WORD_MASK    = WORD_SIZE - 1;
  static constexpr word_t   WORD_MAX     = std::numeric_limits<word_t>::max();

  static constexpr unsigned XWORD_LOGSIZE = ilog2(bitwidth_v<xword_t>);
  static constexpr unsigned XWORD_SIZE    = 1 << XWORD_LOGSIZE;
  static constexpr unsigned XWORD_MASK    = XWORD_SIZE - 1;
  static constexpr xword_t  XWORD_MAX     = std::numeric_limits<xword_t>::max();
  
  class const_iterator;
  class iterator;
  
  using const_reference = bool;
  
  class reference {
  public:    
    
    reference& operator=(bool other) {
      if (other) {
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
    
    reference(word_t& word, word_t mask) : word_(word), mask_(mask) {}
    
    word_t& word_;
    word_t  mask_;
    
    friend class iterator;
    friend class bitvector;
  };  

  class iterator_base {
  public:

    bool operator==(const iterator_base& other) const {
      return offset_ == other.offset_;
    }

    bool operator!=(const iterator_base& other) const {
      return !(*this == other);
    }

  protected:

    iterator_base(const word_t* words, uint32_t offset)
      : words_(words)
      , offset_(offset)
    {}

    iterator_base(const iterator_base& other)
      : words_(other.words_)
      , offset_(other.offset_)
    {}

    iterator_base& operator=(const iterator_base& other) {
      words_ = other.words_;
      offset_ = other.offset_;
      return *this;
    }

    void increment() {
      if (0 == (++offset_ & WORD_MASK))
        ++words_;
    }

    void decrement() {
      if (0 == (offset_-- & WORD_MASK))
        --words_;
    }

    void advance(int delta) {
      int offset = (offset_ & WORD_MASK) + delta;
      if (offset >= 0) {
        words_ += (offset >> WORD_LOGSIZE);
      } else {
        words_ -= ((WORD_MASK - offset) >> WORD_LOGSIZE);
      }
      offset_ += delta;
    }

    const_reference const_ref() const {
      return (*words_ & (word_t(1) << (offset_ & WORD_MASK))) != 0;
    }

    reference ref() const {
      return reference(const_cast<word_t&>(*words_), word_t(1) << (offset_ & WORD_MASK));
    }

    const word_t* words_;
    uint32_t offset_;
  };
    
  class const_iterator : public iterator_base {
  public:
    using base = iterator_base;

    const_iterator(const const_iterator& other) : base(other) {}
    
    const_iterator& operator=(const const_iterator& other) {
      base::operator =(other);
      return *this;
    }
    
    const_reference operator*() const {
      return this->const_ref();
    }
    
    const_iterator& operator++() {
      this->increment();
      return *this;
    }
    
    const_iterator& operator--() {
      this->decrement();
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
    
    const_iterator(const word_t* words, uint32_t offset)
      : iterator_base(words, offset)
    {}
    
    friend class iterator;
    friend class bitvector;
  };
  
  class iterator : public const_iterator {
  public:
    using base = const_iterator;
    
    iterator(const iterator& other) : base(other) {}
    
    iterator(const const_iterator& other) : base(other) {}
    
    reference operator*() const {
      return this->ref();
    }
    
    iterator& operator++() {
      this->increment();
      return *this;
    } 
    
    iterator& operator--() {
      this->decrement();
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
    
    iterator(word_t* words, uint32_t offset)
      : const_iterator(words, offset)
    {}
    
    friend class bitvector;
  };

  class const_reverse_iterator : public iterator_base  {
  public:
    using base = iterator_base;

    const_reverse_iterator(const const_reverse_iterator& other)
      : base(other)
    {}

    const_reverse_iterator& operator=(const const_reverse_iterator& other) {
      base::operator =(other);
      return *this;
    }

    const_reference operator*() const {
      return this->const_ref();
    }

    const_reverse_iterator& operator++() {
      this->decrement();
      return *this;
    }

    const_reverse_iterator& operator--() {
      this->increment();
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

    const_reverse_iterator(const word_t* words, uint32_t offset)
      : iterator_base(words, offset)
    {}

    friend class reverse_iterator;
    friend class bitvector;
  };

  class reverse_iterator : public const_reverse_iterator {
  public:
    using base = const_reverse_iterator;

    reverse_iterator(const reverse_iterator& other) : base(other) {}

    reverse_iterator(const const_reverse_iterator& other) : base(other) {}

    reference operator*() const {
      return this->ref();
    }

    reverse_iterator& operator++() {
      this->decrement();
      return *this;
    }

    reverse_iterator& operator--() {
      this->increment();
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

    reverse_iterator(word_t* words, uint32_t offset)
      : const_reverse_iterator(words, offset) {}

    friend class bitvector;
  };
  
  bitvector() : words_(nullptr), size_(0) {}
  
  bitvector(const bitvector& other);
  
  bitvector(bitvector&& other);
  
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

  template <typename T, std::size_t N>
  explicit bitvector(uint32_t size, const std::array<T, N>& value) : bitvector(size) {
    static_assert(is_bitvector_array_type_v<T>, "invalid array type");
    this->operator =(value);
  }

  template <typename T>
  explicit bitvector(uint32_t size, const std::vector<T>& value) : bitvector(size) {
    static_assert(is_bitvector_array_type_v<T>, "invalid array type");
    this->operator =(value);
  }

  explicit bitvector(uint32_t size, const std::string& value);

  ~bitvector();
  
  bitvector& operator=(const bitvector& other);
  
  bitvector& operator=(bitvector&& other);

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

  template <typename T, std::size_t N>
  bitvector& operator=(const std::array<T, N>& value) {
    static_assert(is_bitvector_array_type_v<T>, "invalid array type");
    std::vector<T> tmp(N);
    std::reverse_copy(value.begin(), value.end(), tmp.begin());
    this->write(0, tmp.data(), N * sizeof(T), 0, N * CH_WIDTH_OF(T));
    return *this;
  }

  template <typename T>
  bitvector& operator=(const std::vector<T>& value) {
    static_assert(is_bitvector_array_type_v<T>, "invalid array type");
    std::vector<T> tmp(value.size);
    std::reverse_copy(value.begin(), value.end(), tmp.begin());
    this->write(0, tmp.data(), tmp.size() * sizeof(T), 0, tmp.size() * CH_WIDTH_OF(T));
    return *this;
  }

  bitvector& operator=(const std::string& value);
  
  const_reference at(uint32_t index) const;
  
  reference at(uint32_t index);
  
  auto operator[](uint32_t index) const {
    return this->at(index);
  }
  
  auto operator[](uint32_t index) {
    return this->at(index);
  }
  
  auto word(uint32_t index) const {
    assert(index < this->num_words());
    return words_[index];
  }
  
  auto& word(uint32_t index) {
    assert(index < this->num_words());
    return words_[index];
  }

  const auto* words() const {
    return words_;
  }

  auto* words() {
    return words_;
  }

  auto* emplace(word_t* words) {
    std::swap(words_, words);
    return words;
  }

  auto* emplace(word_t* words, uint32_t size) {
    std::swap(words_, words);
    size_ = size;
    return words;
  }
  
  uint32_t num_words() const {
    return (size_ + WORD_MASK) >> WORD_LOGSIZE;
  }

  uint32_t num_bytes() const {
    return (num_words() << WORD_LOGSIZE) / 8;
  }

  const void* data() const {
    return words_;
  }

  void* data() {
    return words_;
  }
  
  uint32_t size() const {
    return size_;
  }

  void clear();

  bool empty() const {
    return (0 == size_);
  }

  void resize(uint32_t size,
              uint32_t value = 0x0,
              bool initialize = false,
              bool preserve = false);

  void clear_unused_bits();
  
  void copy(uint32_t dst_offset,
            const bitvector& src,
            uint32_t src_offset,
            uint32_t length);
  
  void read(uint32_t src_offset,
            void* dst,
            uint32_t dst_cbsize,
            uint32_t dst_offset,
            uint32_t length) const;
  
  void write(uint32_t dst_offset,
             const void* src,
             uint32_t src_cbsize,
             uint32_t src_offset,
             uint32_t length);
  
  int find_first() const;
  
  int find_last() const;
  
  auto front() const {
    return this->at(0);
  }
  
  auto front() {
    return this->at(0);
  }
  
  auto back() const {
    return this->at(size_ - 1);
  }
  
  auto back() {
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

  bool operator==(const bitvector& other) const;

  bool operator!=(const bitvector& other) const {
    return !(*this == other);
  }

  void set();

  void reset();

  bool is_zero() const;

  bool is_neg() const {
    return this->at(size_ - 1);
  }

#define CH_DEF_CAST(type) \
  explicit operator type() const { \
    CH_CHECK(CH_WIDTH_OF(type) >= size_, "invalid size"); \
    if constexpr (bitwidth_v<type> <= WORD_SIZE) { \
      return bitcast<type>(words_[0]); \
    } else { \
      type ret(0); \
      memcpy(&ret, words_, CH_CEILDIV(size_, 8)); \
      return ret; \
    } \
  }
  CH_DEF_CAST(bool)
  CH_DEF_CAST(int8_t)
  CH_DEF_CAST(uint8_t)
  CH_DEF_CAST(int16_t)
  CH_DEF_CAST(uint16_t)
  CH_DEF_CAST(int32_t)
  CH_DEF_CAST(uint32_t)
  CH_DEF_CAST(int64_t)
  CH_DEF_CAST(uint64_t)
#undef CH_DEF_CAST

  void deadbeef();
  
protected:
  
  word_t*  words_;
  uint32_t size_;
};

std::ostream& operator<<(std::ostream& out, const bitvector& in);

///////////////////////////////////////////////////////////////////////////////

bool bv_ltu(const bitvector& lhs, const bitvector& rhs);
bool bv_lts(const bitvector& lhs, const bitvector& rhs);

void bv_inv(bitvector& out, const bitvector& in);
void bv_and(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_or(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_xor(bitvector& out, const bitvector& lhs, const bitvector& rhs);

bool bv_andr(const bitvector& in);
bool bv_orr(const bitvector& in);
bool bv_xorr(const bitvector& in);

void bv_slli(bitvector& out, const bitvector& in, uint32_t dist);
void bv_srli(bitvector& out, const bitvector& in, uint32_t dist);
void bv_srai(bitvector& out, const bitvector& in, uint32_t dist);

inline void bv_sll(bitvector& out, const bitvector& in, const bitvector& rhs) {
  CH_CHECK(rhs.find_last() <= 31, "shift amount out of range");
  bv_slli(out, in, static_cast<uint32_t>(rhs));
}

inline void bv_srl(bitvector& out, const bitvector& in, const bitvector& rhs) {
  CH_CHECK(rhs.find_last() <= 31, "shift amount out of range");
  bv_srli(out, in, static_cast<uint32_t>(rhs));
}

inline void bv_sra(bitvector& out, const bitvector& in, const bitvector& rhs) {
  CH_CHECK(rhs.find_last() <= 31, "shift amount out of range");
  bv_srai(out, in, static_cast<uint32_t>(rhs));
}

void bv_neg(bitvector& out, const bitvector& in);
void bv_add(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_sub(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_mul(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_divu(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_divs(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_modu(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_mods(bitvector& out, const bitvector& lhs, const bitvector& rhs);
void bv_divmodu(bitvector& quot, bitvector& rem, const bitvector& lhs, const bitvector& rhs);

void bv_zext(bitvector& out, const bitvector& in);
void bv_sext(bitvector& out, const bitvector& in);

inline void bv_abs(bitvector& out, const bitvector& in) {
  if (in.is_neg()) {
    bv_neg(out, in);
  } else {
    out = in;
  }
}

}
}
