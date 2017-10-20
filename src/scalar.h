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

template <unsigned N> class const_scalar_slice;

template <unsigned N> class ch_scalar_slice;

template <typename ScalarType, typename LogicType>
struct scalar_traits {
  using scalar_type = ScalarType;
  using logic_type = LogicType;
};

template <typename T>
using scalar_type_t = typename T::traits::scalar_type;

template <typename T>
struct is_scalar_traits : std::false_type {};

template <typename ScalarType, typename LogicType>
struct is_scalar_traits<scalar_traits<ScalarType, LogicType>> : std::true_type {};

CH_DEF_SFINAE_CHECK(is_scalar_type, is_scalar_traits<typename T::traits>::value);

CH_DEF_SFINAE_CHECK(is_scalar_compatible, (std::is_same<ch_scalar<T::bitsize>, T>::value
                                        || std::is_base_of<ch_scalar<T::bitsize>, T>::value));

template <typename... Ts>
using deduce_ch_scalar_t = std::conditional_t<
  is_scalar_compatible<deduce_type_t<Ts...>>::value, deduce_type_t<Ts...>, non_bitsize_type>;

template <typename T, unsigned N = std::decay_t<T>::bitsize>
struct is_scalar_convertible {
  static constexpr bool value = is_cast_convertible<ch_scalar<N>, T>::value;
};

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer {
public:
  scalar_buffer(unsigned size);

  scalar_buffer(const scalar_buffer& rhs);

  scalar_buffer(scalar_buffer&& rhs);

  scalar_buffer(const bitvector& data);

  scalar_buffer(bitvector&& data);

  scalar_buffer(unsigned size, const scalar_buffer& buffer, unsigned offset = 0);

  scalar_buffer& operator=(const scalar_buffer& rhs);

  scalar_buffer& operator=(scalar_buffer&& rhs);

  void set_data(const bitvector& data);

  const bitvector& get_data() const;

  void read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const;

  void write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length);

  scalar_buffer clone() const;

  void copy(const scalar_buffer& rhs);

  auto get_size() const {
    return size_;
  }

private:
  using shared_buffer = std::pair<bitvector, uint64_t>;
  std::shared_ptr<shared_buffer> buffer_;
  mutable bitvector proxy_;
  mutable uint64_t version_;
  unsigned offset_;
  unsigned size_;
};

struct scalar_accessor {
  template <typename T>
  static const scalar_buffer& get_buffer(const T& obj) {
    return obj.get_buffer();
  }
  template <typename T>
  static scalar_buffer& get_buffer(T& obj) {
    return obj.get_buffer();
  }
  template <typename T>
  static const bitvector& get_data(const T& obj) {
    return obj.get_buffer().get_data();
  }
};

#define CH_SCALAR_TYPE_INTERFACE() \
  void read(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset = 0, uint32_t length = bitsize) const { \
    this->get_buffer().read(dst_offset, out, out_cbsize, src_offset, length); \
  } \
  void write(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset = 0, uint32_t length = bitsize) { \
    this->get_buffer().write(dst_offset, in, in_cbsize, src_offset, length); \
  }

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_scalar {
public:
  static constexpr unsigned bitsize = N;
  using traits = scalar_traits<ch_scalar, ch_bit<N>>;

  ch_scalar() : buffer_(N) {}

  ch_scalar(const ch_scalar& rhs) : buffer_(rhs.buffer_.clone()) {}

  ch_scalar(ch_scalar&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  ch_scalar(const const_scalar_slice<N>& rhs)
    : buffer_(scalar_accessor::get_buffer(rhs).clone()) {}

  explicit ch_scalar(const scalar_buffer& buffer) : buffer_(buffer) {
    assert(buffer.get_size() == N);
  }

  explicit ch_scalar(const bitvector& value) : buffer_(value) {}

  explicit ch_scalar(bitvector&& value) : buffer_(std::move(value)) {}

  template <typename U, CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit ch_scalar(const U& value) : buffer_(bitvector(N, value)) {}

  ch_scalar& operator=(const ch_scalar& rhs) {
    buffer_.copy(rhs.buffer_);
    return *this;
  }

  ch_scalar& operator=(ch_scalar&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

  ch_scalar& operator=(const const_scalar_slice<N>& rhs) {
    buffer_.copy(scalar_accessor::get_buffer(rhs));
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum<U>::value)>
  ch_scalar& operator=(const U& value) {
    buffer_.set_data(bitvector(N, value));
    return *this;
  }

  const auto operator[](size_t index) const {
    return const_scalar_slice<1>(buffer_, index);
  }

  const auto operator[](size_t index) {
    return ch_scalar_slice<1>(buffer_, index);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_scalar_slice<M>(buffer_, start);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) {
    return ch_scalar_slice<M>(buffer_, start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_scalar_slice<M>(buffer_, start * M);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) {
    return ch_scalar_slice<M>(buffer_, start * M);
  }

  template <typename U, CH_REQUIRES(can_bitvector_cast<U>::value)>
  explicit operator U() const {
    return static_cast<U>(buffer_.get_data());
  }

  CH_SCALAR_TYPE_INTERFACE();

protected:

  const scalar_buffer& get_buffer() const {
    return buffer_;
  }

  scalar_buffer& get_buffer() {
    return buffer_;
  }

  scalar_buffer buffer_;

  friend class scalar_accessor;

  friend std::ostream& operator<<(std::ostream& out, const ch_scalar& rhs) {
    return out << scalar_accessor::get_data(rhs);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class const_scalar_slice {
public:
  static constexpr unsigned bitsize = N;
  using traits = scalar_traits<const_scalar_slice, ch_bit<N>>;

  const_scalar_slice(const scalar_buffer& buffer, unsigned start = 0)
    : buffer_(scalar_buffer(N, buffer, start))
  {}

  const_scalar_slice(const const_scalar_slice& rhs)
    : buffer_(rhs.buffer_.clone())
  {}

  const_scalar_slice(const_scalar_slice&& rhs)
    : buffer_(std::move(rhs.buffer_))
  {}

  const auto operator[](size_t index) const {
    return const_scalar_slice<1>(scalar_buffer(1, buffer_, index));
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_scalar_slice<M>(scalar_buffer(M, buffer_, start));
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return const_scalar_slice<M>(scalar_buffer(M, buffer_, start * M));
  }

protected:

  const scalar_buffer& get_buffer() const {
    return buffer_;
  }

  scalar_buffer& get_buffer() {
    return buffer_;
  }

  scalar_buffer buffer_;

  friend class scalar_accessor;
};

template <unsigned N>
class ch_scalar_slice : public const_scalar_slice<N> {
public:
  using base = const_scalar_slice<N>;
  using traits = scalar_traits<ch_scalar_slice, ch_bit<N>>;
  using base::buffer_;

  ch_scalar_slice(const scalar_buffer& buffer, unsigned start = 0) : base(buffer, start) {}

  ch_scalar_slice(const ch_scalar_slice& rhs) : base(rhs) {}

  ch_scalar_slice(ch_scalar_slice&& rhs) : base(std::move(rhs)) {}

  ch_scalar_slice& operator=(const ch_scalar_slice& rhs) {
    buffer_.copy(rhs.buffer_);
    return *this;
  }

  ch_scalar_slice& operator=(ch_scalar_slice&& rhs) {
    buffer_ = std::move(rhs.buffer_);
    return *this;
  }

  ch_scalar_slice& operator=(const ch_scalar<N>& rhs) {
    buffer_.copy(rhs.buffer_);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum<U>::value)>
  ch_scalar_slice& operator=(const U& value) {
    buffer_.set_data(bitvector(N, value));
    return *this;
  }

  auto operator[](size_t index) {
    return ch_scalar_slice<1>(scalar_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return ch_scalar_slice<M>(scalar_buffer(M, buffer_, start));
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
    return ch_scalar_slice<M>(scalar_buffer(M, buffer_, start * M));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
bitvector get_bitvector(const T& x) {
  return bitvector(N, x);
}

template <unsigned N>
const bitvector& get_bitvector(const ch_scalar<N>& x) {
  return scalar_accessor::get_data(x);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator==(const A& a, const B& b) {
  return (get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a) == get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator!=(const A& a, const B& b) {
  return !(get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a) == get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator<(const A& a, const B& b) {
  return (get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a) < get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator>=(const A& a, const B& b) {
  return !(get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a) < get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator>(const A& a, const B& b) {
  return (get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b) < get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
bool operator<=(const A& a, const B& b) {
  return !(get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b) < get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a));
}

template <unsigned N>
bool operator!(const ch_scalar<N>& a) {
  bitvector ret(N);
  Inverse(ret, scalar_accessor::get_data(a));
  return ch_scalar<N>(std::move(ret));
}

template <unsigned N>
const auto operator~(const ch_scalar<N>& a) {
  bitvector ret(N);
  Inverse(ret, scalar_accessor::get_data(a));
  return ch_scalar<N>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator&(const A& a, const B& b) {
  bitvector ret(deduce_ch_scalar_t<A, B>::bitsize);
  And(ret, get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a), get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
  return deduce_ch_scalar_t<A, B>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator|(const A& a, const B& b) {
  bitvector ret(deduce_ch_scalar_t<A, B>::bitsize);
  Or(ret, get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a), get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
  return deduce_ch_scalar_t<A, B>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator^(const A& a, const B& b) {
  bitvector ret(deduce_ch_scalar_t<A, B>::bitsize);
  Xor(ret, get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a), get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
  return deduce_ch_scalar_t<A, B>(std::move(ret));
}

template <unsigned N>\
const auto operator<<(const ch_scalar<N>& a, uint32_t b) {
  bitvector ret(N);
  SLL(ret, scalar_accessor::get_data(a), b);
  return ch_scalar<N>(std::move(ret));
}

template <unsigned N>
const auto operator>>(const ch_scalar<N>& a, uint32_t b) {
  bitvector ret(N);
  SRL(ret, scalar_accessor::get_data(a), b);
  return ch_scalar<N>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator+(const A& a, const B& b) {
  bitvector ret(deduce_ch_scalar_t<A, B>::bitsize);
  Add(ret, get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a), get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
  return deduce_ch_scalar_t<A, B>(std::move(ret));
}

template <typename A, typename B,
          CH_REQUIRES(deduce_ch_scalar_t<A, B>::bitsize != 0),
          CH_REQUIRES(is_scalar_convertible<A, deduce_ch_scalar_t<A, B>::bitsize>::value),
          CH_REQUIRES(is_scalar_convertible<B, deduce_ch_scalar_t<A, B>::bitsize>::value), CH_VOID_T>
const auto operator-(const A& a, const B& b) {
  bitvector ret(deduce_ch_scalar_t<A, B>::bitsize);
  Sub(ret, get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(a), get_bitvector<deduce_ch_scalar_t<A, B>::bitsize>(b));
  return deduce_ch_scalar_t<A, B>(std::move(ret));
}

template <unsigned N>
const auto operator-(const ch_scalar<N>& a) {
  bitvector ret(N);
  Negate(ret, scalar_accessor::get_data(a));
  return ch_scalar<N>(std::move(ret));
}

}
}
