#pragma once

#include "bv.h"

namespace ch {
namespace internal {

template <typename T> struct is_bitvector_array_type_impl : std::false_type {};
template <> struct is_bitvector_array_type_impl<int8_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<uint8_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<int16_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<uint16_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<int32_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<uint32_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<int64_t> : std::true_type {};
template <> struct is_bitvector_array_type_impl<uint64_t> : std::true_type {};

template <typename T>
inline constexpr bool is_bitvector_array_type_v = is_bitvector_array_type_impl<std::decay_t<T>>::value;

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
inline constexpr bool is_bitvector_extended_type_v = is_bitvector_extended_type_impl<std::decay_t<T>>::value;

template <typename word_t>
class bitvector {
public:
  static_assert(std::is_integral_v<word_t> && std::is_unsigned_v<word_t>, "invalid type");
  typedef word_t  block_type;
  typedef size_t  size_type;

  class const_iterator;
  class iterator;

  using const_reference = bool;

  class reference {
  public:

    reference& operator=(bool other) {
      auto mask = word_t(1) << lsb_;
      if (other) {
        word_ |= mask;
      } else {
        word_ &= ~mask;
      }
      return *this;
    }

    operator bool() const {
      return (word_ >> lsb_) & 0x1;
    }

  protected:

    reference(word_t& word, uint32_t lsb) : word_(word), lsb_(lsb) {}

    word_t& word_;
    uint32_t lsb_;

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
      if (0 == (++offset_ % bitwidth_v<word_t>)) {
        ++words_;
      }
    }

    void decrement() {
      if (0 == (offset_-- % bitwidth_v<word_t>)) {
        --words_;
      }
    }

    void advance(int delta) {
      int offset = (offset_ % bitwidth_v<word_t>) + delta;
      if (offset >= 0) {
        words_ += (offset / bitwidth_v<word_t>);
      } else {
        words_ -= ((bitwidth_v<word_t> - 1 - offset) / bitwidth_v<word_t>);
      }
      offset_ += delta;
    }

    const_reference const_ref() const {
      uint32_t lsb = offset_ % bitwidth_v<word_t>;
      return (*words_ >> lsb) & 0x1;
    }

    reference ref() const {
      uint32_t lsb = offset_ % bitwidth_v<word_t>;
      return reference(const_cast<word_t&>(*words_), lsb);
    }

    const word_t* words_;
    uint32_t offset_;
  };

  class const_iterator : public iterator_base {
  public:
    using base = iterator_base;

    const_iterator(const const_iterator& other) : base(other) {}

    const_iterator& operator=(const const_iterator& other) {
      base::operator=(other);
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
      base::operator=(other);
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
      ret += dec;
      return ret;
    }

    const_reverse_iterator operator-(int incr) const {
      const_reverse_iterator ret(*this);
      ret -= incr;
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
      ret += dec;
      return ret;
    }

    reverse_iterator operator-(int incr) const {
      reverse_iterator ret(*this);
      ret -= incr;
      return ret;
    }

  protected:

    reverse_iterator(word_t* words, uint32_t offset)
      : const_reverse_iterator(words, offset) {}

    friend class bitvector;
  };

  bitvector() : words_(nullptr), size_(0) {}

  explicit bitvector(uint32_t size)
    : bitvector() {
    this->resize(size);
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U> || is_bitvector_extended_type_v<U>)>
  explicit bitvector(uint32_t size, U value)
    : bitvector(size) {
    this->operator=(value);
  }

  bitvector(const bitvector& other)
    : bitvector(other.size_) {
    std::copy_n(other.words_, other.num_words(), words_);
  }

  bitvector(bitvector&& other) {
    words_ = other.words_;
    size_  = other.size_;
    other.size_ = 0;
    other.words_ = nullptr;
  }

  ~bitvector() {
    this->clear();
  }

  bitvector& operator=(const bitvector& other) {
    this->resize(other.size_);
    std::copy_n(other.words_, other.num_words(), words_);
    return *this;
  }

  bitvector& operator=(bitvector&& other) {
    if (words_) {
      delete [] words_;
    }
    size_  = other.size_;
    words_ = other.words_;
    other.size_ = 0;
    other.words_ = nullptr;
    return *this;
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U> && std::is_signed_v<U>)>
  bitvector& operator=(U value) {
    bv_assign<U>(words_, size_, value);
    return *this;
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U> && std::is_unsigned_v<U>)>
  bitvector& operator=(U value) {
    bv_assign<U>(words_, size_, value);
    return *this;
  }

  bitvector& operator=(const std::string& value) {
    bv_assign(words_, size_, value);
    return *this;
  }

  template <typename U, std::size_t N>
  bitvector& operator=(const std::array<U, N>& value) {
    static_assert(is_bitvector_array_type_v<U>, "invalid array type");
    for (std::size_t i = 0; i < N; ++i) {
      this->write(i * bitwidth_v<U>, value.data(), sizeof(U), (N - 1 - i) * bitwidth_v<U>, bitwidth_v<U>);
    }
    auto src_num_words = ceildiv<uint32_t>(N * bitwidth_v<U>, bitwidth_v<word_t>);
    auto num_words = this->num_words();
    std::fill_n(words_ + src_num_words, num_words - src_num_words, 0);
    return *this;
  }

  template <typename U>
  bitvector& operator=(const std::vector<U>& value) {
    static_assert(is_bitvector_array_type_v<U>, "invalid array type");
    for (std::size_t i = 0, n = value.size(); i < n; ++i) {
      this->write(i * bitwidth_v<U>, value.data(), sizeof(U), (n - 1 - i) * bitwidth_v<U>, bitwidth_v<U>);
    }
    auto src_num_words = ceildiv<uint32_t>(value.size() * bitwidth_v<U>, bitwidth_v<word_t>);
    auto num_words = this->num_words();
    std::fill_n(words_ + src_num_words, num_words - src_num_words, 0);
    return *this;
  }

  const_reference at(uint32_t index) const {
    assert(index < size_);
    uint32_t idx = index / bitwidth_v<word_t>;
    uint32_t lsb = index % bitwidth_v<word_t>;
    return (words_[idx] >> lsb) & 0x1;
  }

  reference at(uint32_t index) {
    assert(index < size_);
    uint32_t idx = index / bitwidth_v<word_t>;
    uint32_t lsb = index % bitwidth_v<word_t>;
    return reference(words_[idx], lsb);
  }

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

  auto* words() const {
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
    return ceildiv(size_, bitwidth_v<word_t>);
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

  bool empty() const {
    return (0 == size_);
  }

  void clear() {
    delete [] words_;
    size_ = 0;
  }

  void resize(uint32_t size) {
    uint32_t old_num_words = ceildiv(size_, bitwidth_v<word_t>);
    uint32_t new_num_words = ceildiv(size, bitwidth_v<word_t>);
    if (new_num_words != old_num_words) {
      auto words = new word_t[new_num_words];
      if (words_) {
        delete [] words_;
      }
      words_ = words;      
    }
    size_ = size;

    // initialize content
    bv_init(words_, size);
  }

  void copy(uint32_t dst_offset,
            const bitvector<word_t>& src,
            uint32_t src_offset,
            uint32_t length) {
    assert(size_ && src.size_);
    assert(src_offset + length <= src.size_);
    assert(dst_offset + length <= size_);
    bv_copy<word_t>(words_, dst_offset, src.words(), src_offset, length);
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U> && std::is_unsigned_v<U>)>
  void read(uint32_t src_offset,
            U* out,
            uint32_t dst_offset,
            uint32_t length) const {
    this->read(src_offset, out, sizeof(U), dst_offset, length);
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U> && std::is_unsigned_v<U>)>
  void write(uint32_t dst_offset,
             const U* in,
             uint32_t src_offset,
             uint32_t length) {
    this->write(dst_offset, in, sizeof(U), src_offset, length);
  }

  int find_first() const {
    return bv_lsb(words_, size_);
  }

  int find_last() const {
    return bv_msb(words_, size_);
  }

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
    return reverse_iterator(words_, 0) - (size_-1);
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

  bool operator==(const bitvector& other) const {
    if (size_ != other.size_)
      return false;
    for (uint32_t i = 0, n = other.num_words(); i < n; ++i) {
      if (words_[i] != other.words_[i])
        return false;
    }
    return true;
  }

  bool operator!=(const bitvector<word_t>& other) const {
    return !(*this == other);
  }

  void reset() {
    bv_reset(words_, size_);
  }

  bool is_zero() const {    
    return bv_is_zero(words_, size_);
  }

  bool is_one() const {
    return bv_is_one(words_, size_);
  }

  bool is_ones() const {
    return bv_is_ones(words_, size_);
  }

  bool is_neg() const {
    return bv_is_neg(words_, size_);
  }

#define CH_DEF_CAST(type) \
  explicit operator type() const { \
    return bv_cast<type, word_t>(words_, size_); \
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

  void read(uint32_t src_offset,
            void* dst,
            uint32_t byte_alignment,
            uint32_t dst_offset,
            uint32_t length) const {    
    CH_CHECK(src_offset + length <= size_, "out of bound access");
    assert(ispow2(byte_alignment) && byte_alignment <= 8);
    byte_alignment = std::min<uint32_t>(byte_alignment, sizeof(word_t));

    switch (byte_alignment) {
    case 1:
      bv_copy<uint8_t>(reinterpret_cast<uint8_t*>(dst), dst_offset,
                         reinterpret_cast<const uint8_t*>(words_), src_offset,
                         length);
      break;
    case 2:
      bv_copy<uint16_t>(reinterpret_cast<uint16_t*>(dst), dst_offset,
                          reinterpret_cast<const uint16_t*>(words_), src_offset,
                          length);
      break;
    case 4:
      bv_copy<uint32_t>(reinterpret_cast<uint32_t*>(dst), dst_offset,
                          reinterpret_cast<const uint32_t*>(words_), src_offset,
                          length);
      break;
    case 8:
      bv_copy<uint64_t>(reinterpret_cast<uint64_t*>(dst), dst_offset,
                          reinterpret_cast<const uint64_t*>(words_), src_offset,
                          length);
      break;
    default:
      CH_ABORT("invalid alignement value %d", byte_alignment);
    }
  }

  void write(uint32_t dst_offset,
             const void* src,
             uint32_t byte_alignment,
             uint32_t src_offset,
             uint32_t length) {
    CH_CHECK(dst_offset + length <= size_, "out of bound access");
    byte_alignment = std::min<uint32_t>(byte_alignment, sizeof(word_t));

    switch (byte_alignment) {
    case 1:
      bv_copy<uint8_t>(reinterpret_cast<uint8_t*>(words_), dst_offset,
                         reinterpret_cast<const uint8_t*>(src), src_offset,
                         length);
      break;
    case 2:
      bv_copy<uint16_t>(reinterpret_cast<uint16_t*>(words_), dst_offset,
                          reinterpret_cast<const uint16_t*>(src), src_offset,
                          length);
      break;
    case 4:
      bv_copy<uint32_t>(reinterpret_cast<uint32_t*>(words_), dst_offset,
                          reinterpret_cast<const uint32_t*>(src), src_offset,
                          length);
      break;
    case 8:
      bv_copy<uint64_t>(reinterpret_cast<uint64_t*>(words_), dst_offset,
                          reinterpret_cast<const uint64_t*>(src), src_offset,
                          length);
      break;
    default:
      CH_ABORT("invalid alignement value %d", byte_alignment);
    }
  }

protected:

  word_t* words_;
  uint32_t size_;
};

template <typename word_t>
std::ostream& operator<<(std::ostream& out, const bitvector<word_t>& in) {
  out << "0x";
  auto oldflags = out.flags();
  out.setf(std::ios_base::hex, std::ios_base::basefield);

  uint32_t quad(0);
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

}
}
