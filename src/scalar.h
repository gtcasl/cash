#pragma once

#include "bitvector.h"
#include "arithm.h"

namespace ch {
namespace internal {

template <typename... Ts>
struct width_impl;

template <typename T>
struct width_impl<T> {
  static constexpr unsigned value = T::traits::bitwidth;
};

template <typename T0, typename... Ts>
struct width_impl<T0, Ts...> {
  static constexpr unsigned value = T0::traits::bitwidth + width_impl<Ts...>::value;
};

template <typename... Ts>
inline constexpr unsigned width_v = width_impl<std::decay_t<Ts>...>::value;

CH_DEF_SFINAE_CHECK(has_bitwidth, T::traits::bitwidth != 0);

///////////////////////////////////////////////////////////////////////////////

enum traits_type {
  traits_none,
  traits_logic,
  traits_scalar,
  traits_io,
};

enum class ch_direction {
  none  = 0x0,
  in    = 0x1,
  out   = 0x2,
  inout = 0x3,
};

struct non_ch_type {
  struct traits {
    static constexpr traits_type type = traits_none;
    static constexpr ch_direction direction = ch_direction::none;
    static constexpr unsigned bitwidth = 0;
  };
};

template <typename T>
using ch_type_t = std::conditional_t<has_bitwidth<T>::value, T, non_ch_type>;

template <bool resize, typename T0, typename T1>
struct deduce_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<has_bitwidth<D0>::value, D0, non_ch_type>;
  using U1 = std::conditional_t<has_bitwidth<D1>::value, D1, non_ch_type>;
  using type = std::conditional_t<(width_v<U0> != 0) && (width_v<U1> != 0),
    std::conditional_t<(width_v<U0> == width_v<U1>) || ((width_v<U0> > width_v<U1>) && resize), U0,
        std::conditional_t<(width_v<U0> < width_v<U1>) && resize, U1, non_ch_type>>,
          std::conditional_t<(width_v<U0> != 0), U0, U1>>;
};

template <bool resize, typename... Ts>
struct deduce_type;

template <bool resize, typename T0, typename T1>
struct deduce_type<resize, T0, T1> {
  using type = typename deduce_type_impl<resize, T0, T1>::type;
};

template <bool resize, typename T0, typename T1, typename... Ts>
struct deduce_type<resize, T0, T1, Ts...> {
  using type = typename deduce_type<resize, typename deduce_type_impl<resize, T0, T1>::type, Ts...>::type;
};

template <bool resize, typename... Ts>
using deduce_type_t = typename deduce_type<resize, Ts...>::type;

template <typename T0, typename T1>
struct deduce_first_type_impl {
  using D0 = std::decay_t<T0>;
  using D1 = std::decay_t<T1>;
  using U0 = std::conditional_t<has_bitwidth<D0>::value, D0, non_ch_type>;
  using U1 = std::conditional_t<has_bitwidth<D1>::value, D1, non_ch_type>;
  using type = std::conditional_t<(width_v<U0> != 0), U0, U1>;
};

template <typename T0, typename T1>
using deduce_first_type_t = typename deduce_first_type_impl<T0, T1>::type;

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class const_bit;

template <unsigned N> class ch_bit;

template <unsigned N> class const_scalar;

template <unsigned N> class ch_scalar;

template <unsigned Bitwidth,
          typename ScalarType,
          typename ConstType,
          typename ValueType,
          typename LogicType,
          typename Next = void>
struct scalar_traits {
  static constexpr traits_type type = traits_scalar;
  static constexpr ch_direction direction = ch_direction::none;
  static constexpr unsigned bitwidth = Bitwidth;
  using scalar_type = ScalarType;
  using const_type  = ConstType;
  using value_type  = ValueType;
  using logic_type  = LogicType;
  using next = Next;
};

template <typename T>
using scalar_type_t = typename std::decay_t<T>::traits::scalar_type;

template <typename T>
using value_type_t = typename std::decay_t<T>::traits::value_type;

template <typename T>
using const_type_t = typename std::decay_t<T>::traits::const_type;

template <typename T>
using is_value_type = is_true<std::is_same<T, value_type_t<T>>::value>;

template <typename T>
using is_const_type = is_true<std::is_same<T, const_type_t<T>>::value>;

template <typename T>
struct is_scalar_traits : std::false_type {};

template <unsigned Bitwidth,
          typename ScalarType,
          typename ConstType,
          typename ValueType,
          typename LogicType,
          typename Next>
struct is_scalar_traits<scalar_traits<Bitwidth, ScalarType, ConstType, ValueType, LogicType, Next>>
  : std::true_type
{};

CH_DEF_SFINAE_CHECK(is_scalar_type, is_scalar_traits<typename std::decay_t<T>::traits>::value);

CH_DEF_SFINAE_CHECK(is_scalar_compatible, (std::is_same<ch_scalar<width_v<T>>, T>::value
                                        || std::is_base_of<ch_scalar<width_v<T>>, T>::value));

template <typename... Ts>
using deduce_ch_scalar_t = std::conditional_t<
  is_scalar_compatible<deduce_type_t<false, Ts...>>::value, deduce_type_t<false, Ts...>, non_ch_type>;

template <typename T, unsigned N = width_v<T>>
using is_scalar_convertible = is_cast_convertible<ch_scalar<N>, T>;

template <typename T, typename R = ch_scalar<width_v<T>>>
using scalar_cast_t = std::conditional_t<is_scalar_type<T>::value, const T&, R>;

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer_impl;

using scalar_buffer_ptr = std::shared_ptr<scalar_buffer_impl>;

class scalar_buffer_impl {
public:
  explicit scalar_buffer_impl(unsigned size);

  scalar_buffer_impl(const scalar_buffer_impl& rhs);

  scalar_buffer_impl(scalar_buffer_impl&& rhs);

  explicit  scalar_buffer_impl(const bitvector& data);

  explicit scalar_buffer_impl(bitvector&& data);

  scalar_buffer_impl(unsigned size, const scalar_buffer_ptr& buffer, unsigned offset);

  virtual ~scalar_buffer_impl() {}

  scalar_buffer_impl& operator=(const scalar_buffer_impl& rhs);

  scalar_buffer_impl& operator=(scalar_buffer_impl&& rhs);

  virtual const bitvector& get_data() const;

  virtual void read(uint32_t dst_offset,
                    void* out,
                    uint32_t out_cbsize,
                    uint32_t src_offset,
                    uint32_t length) const;

  virtual void write(uint32_t dst_offset,
                     const void* in,
                     uint32_t in_cbsize,
                     uint32_t src_offset,
                     uint32_t length);

  void write(const bitvector& data) {
    this->write(0, data.get_words(), data.get_cbsize(), 0, size_);
  }

  void copy(const scalar_buffer_impl& rhs) {
    this->write(0,
                rhs.get_data().get_words(),
                rhs.get_data().get_cbsize(),
                rhs.get_offset(),
                rhs.get_size());
  }

  const scalar_buffer_ptr& get_source() const {
    return source_;
  }

  scalar_buffer_ptr& get_source() {
    return source_;
  }

  unsigned get_offset() const {
    return offset_;
  }

  unsigned get_size() const {
    return size_;
  }

protected:

  scalar_buffer_impl(const bitvector& value,
                     const scalar_buffer_ptr& source,
                     unsigned offset,
                     unsigned size)
    : value_(value)
    , source_(source)
    , offset_(offset)
    , size_(size)
  {}

  mutable bitvector value_;
  scalar_buffer_ptr source_;
  unsigned offset_;
  unsigned size_;
};

class scalar_buffer : public scalar_buffer_ptr {
public:
  using base = scalar_buffer_ptr;
  using base::operator*;
  using base::operator->;

  template <typename... Args>
  explicit scalar_buffer(Args&&... args)
    : base(new scalar_buffer_impl(std::forward<Args>(args)...))
  {}

  scalar_buffer(const scalar_buffer_ptr& rhs) : base(rhs) {}

  scalar_buffer(const scalar_buffer& rhs) : base(rhs) {}

  scalar_buffer(scalar_buffer&& rhs) : base(std::move(rhs)) {}

  scalar_buffer& operator=(const scalar_buffer& rhs) {
    base::operator =(rhs);
    return *this;
  }

  scalar_buffer& operator=(scalar_buffer&& rhs) {
    base::operator =(std::move(rhs));
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

class scalar_accessor {
public:
  template <typename T>
  static const auto& get_buffer(const T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static auto& get_buffer(T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static const auto& get_data(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    return obj.get_buffer()->get_data();
  }

  template <typename T>
  static auto copy_buffer(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    return scalar_buffer(*obj.get_buffer());
  }

  template <typename U, typename V,
            CH_REQUIRES(width_v<U> == width_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(width_v<U> == dst.get_buffer()->get_size());
    assert(width_v<V> == src.get_buffer()->get_size());
    *dst.get_buffer() = *src.get_buffer();
  }

  template <typename U, typename V,
            CH_REQUIRES(width_v<U> == width_v<V>)>
  static void move(U& dst, V&& src) {
    assert(width_v<U> == dst.get_buffer()->get_size());
    *dst.get_buffer() = std::move(*src.get_buffer());
  }

  template <typename D, typename T>
  static D cast(const T& obj) {
    return D(scalar_buffer(width_v<T>, obj.get_buffer(), 0));
  }
};

///////////////////////////////////////////////////////////////////////////////

#define CH_SCALAR_FRIEND_OPS(i, x) \
  CH_FRIEND_OP_EQ((), const const_scalar&, x) \
  CH_FRIEND_OP_NE((), const const_scalar&, x) \
  CH_FRIEND_OP_LT((), const const_scalar&, x) \
  CH_FRIEND_OP_LE((), const const_scalar&, x) \
  CH_FRIEND_OP_GT((), const const_scalar&, x) \
  CH_FRIEND_OP_GE((), const const_scalar&, x) \
  CH_FRIEND_OP_AND((), const const_scalar&, x) \
  CH_FRIEND_OP_OR((), const const_scalar&, x) \
  CH_FRIEND_OP_XOR((), const const_scalar&, x) \
  CH_FRIEND_OP_ADD((), const const_scalar&, x) \
  CH_FRIEND_OP_SUB((), const const_scalar&, x) \
  CH_FRIEND_OP_MULT((), const const_scalar&, x) \
  CH_FRIEND_OP_DIV((), const const_scalar&, x) \
  CH_FRIEND_OP_MOD((), const const_scalar&, x) \
  CH_FRIEND_OP_SLL((), const const_scalar&, x) \
  CH_FRIEND_OP_SRL((), const const_scalar&, x)

#define CH_SCALAR_OP_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_READONLY_INTERFACE(type) \
  template <typename R> \
  R as() const { \
    return ch::internal::scalar_accessor::cast<R>(*this); \
  } \
  auto asScalar() const { \
    return this->as<ch_scalar<type::traits::bitwidth>>(); \
  }

#define CH_SCALAR_WRITABLE_INTERFACE(type)

template <unsigned N>
class const_scalar {
public:
  using traits = scalar_traits<N, const_scalar, const_scalar, ch_scalar<N>, const_bit<N>>;

  const_scalar(const scalar_buffer& buffer = scalar_buffer(N))
    : buffer_(buffer)
  {}

  const_scalar(const const_scalar& rhs)
    : buffer_(scalar_accessor::copy_buffer(rhs))
  {}

  const_scalar(const_scalar&& rhs)
    : buffer_(std::move(rhs.buffer_))
  {}

  template <typename U,
            CH_REQUIRES(is_scalar_type<U>::value),
            CH_REQUIRES(N == width_v<U>)>
  explicit const_scalar(const U& rhs) :
    buffer_(scalar_accessor::copy_buffer(rhs))
  {}

  template <typename U,
            CH_REQUIRES(is_bitvector_convertible<U>::value)>
  explicit const_scalar(const U& value)
    : buffer_(bitvector(N, value))
  {}

  auto operator[](size_t index) const {
    return const_scalar<1>(scalar_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0) const {
    return const_scalar<M>(scalar_buffer(M, buffer_, start));
  }

  template <typename U,
            CH_REQUIRES(is_bitvector_castable<U>::value)>
  explicit operator U() const {
    return static_cast<U>(buffer_->get_data());
  }

  auto operator==(const const_scalar& rhs) const {
    return (buffer_->get_data() == rhs.buffer_->get_data());
  }

  auto operator!=(const const_scalar& rhs) const {
    return !(buffer_->get_data() == rhs.buffer_->get_data());
  }

  auto operator<(const const_scalar& rhs) const {
    return (buffer_->get_data() < rhs.buffer_->get_data());
  }

  auto operator>=(const const_scalar& rhs) const {
    return !(buffer_->get_data() < rhs.buffer_->get_data());
  }

  auto operator>(const const_scalar& rhs) const {
    return (rhs.buffer_->get_data() < buffer_->get_data());
  }

  auto operator<=(const const_scalar& rhs) const {
    return !(rhs.buffer_->get_data() < rhs.buffer_->get_data());
  }

  auto operator!() const {
    return (const_scalar(0x0) == *this);
  }

  auto operator~() const {
    bitvector ret(N);
    Inv(ret, buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator&(const const_scalar& rhs) const {
    bitvector ret(N);
    And(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator|(const const_scalar& rhs) const {
    bitvector ret(N);
    Or(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator^(const const_scalar& rhs) const {
    bitvector ret(N);
    Xor(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator-() const {
    bitvector ret(N);
    Negate(ret, buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator+(const const_scalar& rhs) const {
    bitvector ret(N);
    Add(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator-(const const_scalar& rhs) const {
    bitvector ret(N);
    Sub(ret, buffer_->get_data(), rhs.buffer_->get_data());
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator<<(const const_scalar& rhs) const {
    bitvector ret(N);
    auto shift = rhs.buffer_->get_data();
    CH_CHECK(shift.find_last() <= 31, "shift amount out of range");
    Sll(ret, buffer_->get_data(), shift.get_word(0));
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  auto operator>>(const const_scalar& rhs) const {
    bitvector ret(N);
    auto shift = rhs.buffer_->get_data();
    CH_CHECK(shift.find_last() <= 31, "shift amount out of range");
    Srl(ret, buffer_->get_data(), shift.get_word(0));
    return ch_scalar<N>(scalar_buffer(std::move(ret)));
  }

  CH_SCALAR_READONLY_INTERFACE(const_scalar)

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset = 0,
            uint32_t length = N) const {
    buffer_->read(dst_offset, out, out_cbsize, src_offset, length);
  }

protected:

  const scalar_buffer_ptr& get_buffer() const {
    return buffer_;
  }

  scalar_buffer_ptr& get_buffer() {
    return buffer_;
  }

  scalar_buffer buffer_;

  friend class scalar_accessor;

  friend std::ostream& operator<<(std::ostream& out, const const_scalar& rhs) {
    return out << scalar_accessor::get_data(rhs);
  }

  CH_FOR_EACH(CH_SCALAR_FRIEND_OPS, CH_SEP_SPACE, CH_SCALAR_OP_TYPES)
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_scalar : public const_scalar<N> {
public:
  using base = const_scalar<N>;
  using base::buffer_;
  using traits = scalar_traits<N, ch_scalar, const_scalar<N>, ch_scalar, ch_bit<N>>;

  ch_scalar(const scalar_buffer& buffer = scalar_buffer(N)) : base(buffer) {}

  ch_scalar(const ch_scalar& rhs) : base(rhs) {}

  ch_scalar(ch_scalar&& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_scalar_type<U>::value),
            CH_REQUIRES(N == width_v<U>)>
  explicit ch_scalar(const U& rhs)  : base(rhs) {}

  template <typename U, CH_REQUIRES(is_bitvector_convertible<U>::value)>
  explicit ch_scalar(const U& value)  : base(value) {}

  ch_scalar& operator=(const ch_scalar& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  ch_scalar& operator=(ch_scalar&& rhs) {
    scalar_accessor::move(*this, std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRES(is_scalar_type<U>::value),
            CH_REQUIRES(N == width_v<U>)>
  ch_scalar& operator=(const U& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum_v<U>)>
  ch_scalar& operator=(U value) {
    buffer_->write(bitvector(N, value));
    return *this;
  }

  auto operator[](size_t index) const {
    return const_scalar<1>(scalar_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    return ch_scalar<1>(scalar_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0) const {
    return const_scalar<M>(scalar_buffer(M, buffer_, start));
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return ch_scalar<M>(scalar_buffer(M, buffer_, start));
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = N) {
    buffer_->write(dst_offset, in, in_cbsize, src_offset, length);
  }
};

}
}
