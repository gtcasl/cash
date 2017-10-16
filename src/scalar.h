#pragma once

#include "bitvector.h"

namespace ch {
namespace internal {

CH_DEF_SFINAE_CHECK(has_bitsize, T::bitsize != 0);
static_assert(!has_bitsize<int>::value, ":-(");

///////////////////////////////////////////////////////////////////////////////

struct non_bitsize_type {
  static constexpr unsigned bitsize = 0;
};

template <typename T0, typename T1>
struct deduce_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<has_bitsize<D0>::value, D0, non_bitsize_type>;
  using U1 = std::conditional_t<has_bitsize<D1>::value, D1, non_bitsize_type>;
  using type = std::conditional_t<
    (U0::bitsize != 0) && (U1::bitsize != 0),
    std::conditional_t<(U0::bitsize != U1::bitsize), non_bitsize_type, U0>,
    std::conditional_t<(U0::bitsize != 0), U0, U1>>;
};

template <typename... Ts>
struct deduce_type;

template <typename T0, typename T1>
struct deduce_type<T0, T1> {
  using type = typename deduce_type_impl<T0, T1>::type;
};

template <typename T0, typename T1, typename... Ts>
struct deduce_type<T0, T1, Ts...> {
  using type = typename deduce_type<typename deduce_type_impl<T0, T1>::type, Ts...>::type;
};

template <typename... Ts>
using deduce_type_t = typename deduce_type<Ts...>::type;

template <typename T0, typename T1>
struct deduce_first_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<has_bitsize<D0>::value, D0, non_bitsize_type>;
  using U1 = std::conditional_t<has_bitsize<D1>::value, D1, non_bitsize_type>;
  using type = std::conditional_t<(U0::bitsize != 0), U0, U1>;
};

template <typename T0, typename T1>
using deduce_first_type_t = typename deduce_first_type_impl<T0, T1>::type;

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class ch_bit;

template <unsigned N> class ch_scalar;

template <typename T, unsigned N> class const_scalar_slice;

template <typename T, unsigned N> class ch_scalar_slice;

template <typename ScalarType, typename LogicType>
struct scalar_traits {
  using scalar_type = ScalarType;
  using logic_type = LogicType;
};

template <typename T>
struct is_scalar_traits : std::false_type {};

template <typename ScalarType, typename LogicType>
struct is_scalar_traits<scalar_traits<ScalarType, LogicType>> : std::true_type {};

template <typename T>
using is_scalar_type = is_scalar_traits<typename T::traits>;

CH_DEF_SFINAE_CHECK(is_ch_scalar, (std::is_same<ch_scalar<T::bitsize>, T>::value
                                || std::is_base_of<ch_scalar<T::bitsize>, T>::value));

template <typename... Ts>
using deduce_ch_scalar_t = std::conditional_t<
  is_ch_scalar<deduce_type_t<Ts...>>::value, deduce_type_t<Ts...>, non_bitsize_type>;

template <typename T, unsigned N = std::decay_t<T>::bitsize>
struct is_ch_scalar_convertible {
  static constexpr bool value = is_cast_convertible<ch_scalar<N>, T>::value;
};

///////////////////////////////////////////////////////////////////////////////

class bytes_store {
public:
  bytes_store(unsigned size)
    : local_(size)
    , local_outdated_(false)
    , size_(size)
    , shared_(nullptr)
    , offset_(0)
  {}

  bytes_store(const bytes_store& rhs)
    : local_(rhs.local_)
    , local_outdated_(false)
    , size_(rhs.size_)
    , shared_(0)
    , offset_(0)  {
    assert(nullptr == rhs.shared_ && 0 == rhs.offset_);
  }

  bytes_store(bytes_store&& rhs)
    : local_(std::move(rhs.local_))
    , local_outdated_(rhs.local_outdated_)
    , size_(rhs.size_)
    , shared_(rhs.shared_)
    , offset_(rhs.offset_)
  {}

  bytes_store(unsigned size, const bytes_store& store, unsigned offset = 0)
    : local_outdated_(true)
    , size_(size)
    , shared_(store.data())
    , offset_(store.offset_ + offset) {
    assert(nullptr == shared_ || offset + size <= shared_->get_size());
  }

  bytes_store& operator=(const bytes_store& rhs) {
    assert(size_ == rhs.size_);
    data()->copy(offset_, *rhs.data(), rhs.offset_, size_);
    local_outdated_ = true;
    return *this;
  }

  bytes_store& operator=(bytes_store&& rhs) {
    local_ = std::move(rhs.local_);
    local_outdated_ = rhs.local_outdated_;
    size_   = rhs.size_;
    shared_ = rhs.shared_;
    offset_ = rhs.offset_;
    return *this;
  }

  bitvector* data() const {
     return shared_ ? shared_ : &local_;
  }

  void set_value(const bitvector& value) {
    if (shared_) {
      shared_->copy(offset_, value, 0, size_);
      local_outdated_ = true;
    } else {
      local_ = value;
    }
  }

  void set_value(bitvector&& value) {
    if (shared_) {
      shared_->copy(offset_, value, 0, size_);
      local_outdated_ = true;
    } else {
      local_ = std::move(value);
    }
  }

  const bitvector& get_value() const {
    if (shared_ && local_outdated_) {
      local_.resize(size_);
      local_.copy(0, *shared_, offset_, size_);
      local_outdated_ = false;
    }
    return local_;
  }

  void read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const {
    assert(src_offset + length <= size_);
    assert(offset_ + src_offset + length <= data()->get_size());
    data()->read(dst_offset, out, out_cbsize, offset_ + src_offset, length);
  }

  void write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) {
    assert(dst_offset + length <= size_);
    assert(offset_ + dst_offset + length <= data()->get_size());
    data()->write(offset_ + dst_offset, in, in_cbsize, src_offset, length);
    local_outdated_ = true;
  }

private:

  mutable bitvector local_;
  mutable bool local_outdated_;
  unsigned   size_;
  bitvector* shared_;
  unsigned   offset_;
};

#define CH_SCALAR_TYPE_INTERFACE() \
  void read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset = 0, uint32_t length = bitsize) const { \
    _.read(dst_offset, out, out_cbsize, src_offset, length); \
  } \
  void write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset = 0, uint32_t length = bitsize) { \
    _.write(dst_offset, in, in_cbsize, src_offset, length); \
  }

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_scalar {
public:
  static constexpr unsigned bitsize = N;
  using traits = scalar_traits<ch_scalar, ch_bit<N>>;

  constexpr ch_scalar() : _(N) {}
  constexpr ch_scalar(const ch_scalar& rhs) : _(rhs._) {}
  constexpr ch_scalar(ch_scalar&& rhs) : _(std::move(rhs._)) {}

  explicit ch_scalar(const bytes_store& store, unsigned offset = 0) : _(N, store, offset) {}

  explicit ch_scalar(const bitvector& value) : _(N) {
    _.set_value(value);
  }

  explicit ch_scalar(bitvector&& value) : _(N) {
    _.set_value(value);
  }

  template <unsigned M>
  explicit ch_scalar(const const_scalar_slice<ch_scalar<M>, N>& slice) : _(N) {
    _.write(0, slice.container_.get_value().get_words(), slice.start_, N);
  }

  template <typename U, CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit ch_scalar(const U& value) : _(N) {
    _.set_value(bitvector(N, value));
  }

  ch_scalar& operator=(const ch_scalar& rhs) {
    _ = rhs._;
    return *this;
  }

  ch_scalar& operator=(ch_scalar&& rhs) {
    _ = std::move(rhs._);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  ch_scalar& operator=(const U& value) {
    _.set_value(bitvector(value));
    return *this;
  }

  const auto operator[](size_t index) const {
    return const_scalar_slice<ch_scalar, 1>(*this, index);
  }

  const auto operator[](size_t index) {
    return ch_scalar_slice<ch_scalar, 1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_scalar_slice<ch_scalar, M>(*this, start);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) {
    return ch_scalar_slice<ch_scalar, M>(*this, start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_scalar_slice<ch_scalar, M>(*this, start * M);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) {
    return ch_scalar_slice<ch_scalar, M>(*this, start * M);
  }

  template <typename U, CH_REQUIRES(can_bitvector_cast<U>::value)>
  operator U() const {
    return static_cast<U>(_.get_value());
  }

  const bitvector& get_value() const {
    return _.get_value();
  }

  CH_SCALAR_TYPE_INTERFACE();

protected:

  bytes_store _;

  friend std::ostream& operator<<(std::ostream& out, const ch_scalar& rhs) {
    return out << rhs.get_value();
  }
};

template <typename T>
bitvector get_bitvector(const T& x) {
  return bitvector(x);
}

template <unsigned N>
const bitvector& get_bitvector(const ch_scalar<N>& x) {
  return x.get_value();
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator==(const A& a, const B& b) {
  return (get_bitvector(a) == get_bitvector(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator!=(const A& a, const B& b) {
  return !(get_bitvector(a) == get_bitvector(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator<(const A& a, const B& b) {
  return (get_bitvector(a) < get_bitvector(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator>=(const A& a, const B& b) {
  return !(get_bitvector(a) < get_bitvector(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator>(const A& a, const B& b) {
  return (get_bitvector(b) < get_bitvector(a));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator<=(const A& a, const B& b) {
  return !(get_bitvector(b) < get_bitvector(a));
}

template <unsigned N>
bool operator!(const ch_scalar<N>& a) {
  bitvector ret;
  Inverse(ret, a.get_value());
  return ch_scalar<N>(std::move(ret));
}

template <unsigned N>
const auto operator~(const ch_scalar<N>& a) {
  bitvector ret;
  Inverse(ret, a.get_value());
  return ch_scalar<N>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator&(const A& a, const B& b) {
  bitvector ret;
  And(ret, get_bitvector(a), get_bitvector(b));
  return deduce_ch_scalar_t<A, B>::bitsize(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator|(const A& a, const B& b) {
  bitvector ret;
  Or(ret, get_bitvector(a), get_bitvector(b));
  return deduce_ch_scalar_t<A, B>::bitsize(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator^(const A& a, const B& b) {
  bitvector ret;
  Xor(ret, get_bitvector(a), get_bitvector(b));
  return deduce_ch_scalar_t<A, B>::bitsize(std::move(ret));
}

template <unsigned N>\
const auto operator<<(const ch_scalar<N>& a, uint32_t b) {
  bitvector ret;
  SLL(ret, a.get_value(), b);
  return ch_scalar<N>(std::move(ret));
}

template <unsigned N>
const auto operator>>(const ch_scalar<N>& a, uint32_t b) {
  bitvector ret;
  SLL(ret, a.get_value(), b);
  return ch_scalar<N>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator+(const A& a, const B& b) {
  bitvector ret;
  Add(ret, get_bitvector(a), get_bitvector(b));
  return deduce_ch_scalar_t<A, B>::bitsize(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_ch_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_ch_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator-(const A& a, const B& b) {
  bitvector ret;
  Sub(ret, get_bitvector(a), get_bitvector(b));
  return deduce_ch_scalar_t<A, B>::bitsize(std::move(ret));
}

template <unsigned N>
const auto operator-(const ch_scalar<N>& a) {
  bitvector ret;
  Negate(ret, a.get_value());
  return ch_scalar<N>(std::move(ret));
}

template <typename T, unsigned N>
class const_scalar_slice {
public:
  static constexpr unsigned bitsize = N;
  using scalar_type = const_scalar_slice<T, N>;
  using logic_type = ch_bit<N>;

  const_scalar_slice(const T& container, unsigned start = 0)
    : container_(const_cast<T&>(container))
    , start_(start) {
    static_assert(N <= T::bitsize, "invalid container size");
    assert(N + start <= T::bitsize);
  }

protected:

  void write(const bitvector& value) {
    assert(value.get_size() == N);
    container_.write(start_, value.get_words(), value.get_cbsize(), 0, N);
  }

  T& container_;
  unsigned start_;

  template <unsigned M> friend class ch_scalar;
};

template <typename T, unsigned N>
class ch_scalar_slice : public const_scalar_slice<T, N> {
public:
  using base = const_scalar_slice<T, N>;
  using logic_type = ch_bit<N>;

  ch_scalar_slice(const T& container, unsigned start = 0)
    : base(container, start)
  {}

  ch_scalar_slice& operator=(const ch_scalar<N>& rhs) {
    this->write(rhs.get_value());
    return *this;
  }

  template <typename U, CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  ch_scalar_slice& operator=(const U& value) {
    this->write(bitvector(value), 0);
    return *this;
  }
};

}
}
