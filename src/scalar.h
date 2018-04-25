#pragma once

#include "bitvector.h"
#include "arithm.h"

namespace ch {
namespace internal {

CH_DEF_SFINAE_CHECK(has_bitwidth, T::traits::bitwidth != 0);

///////////////////////////////////////////////////////////////////////////////

enum traits_type {
  traits_none      = 0x0,
  traits_logic     = 0x1,
  traits_scalar    = 0x2,
  traits_io        = 0x4,
  traits_logic_io  = traits_logic | traits_io,
  traits_scalar_io = traits_scalar | traits_io,
};

struct non_ch_type {
  struct traits {
    static constexpr traits_type type = traits_none;
    static constexpr unsigned bitwidth = 0;
    static constexpr bool is_signed = false;
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

template <unsigned N> class ch_scalar;
template <unsigned N> class ch_scint;
template <unsigned N> class ch_scuint;

template <unsigned N> class ch_logic;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

template <unsigned M, unsigned N>
ch_scalar<M> ch_pad(const ch_scalar<N>& obj);

template <unsigned Bitwidth, bool Signed, typename ScalarType, typename LogicType>
struct scalar_traits {
  static constexpr traits_type type  = traits_scalar;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using scalar_type = ScalarType;
  using logic_type  = LogicType;
};

template <typename T>
using scalar_type_t = typename std::decay_t<T>::traits::scalar_type;

template <typename T>
using is_scalar_traits = is_true<(T::type & traits_scalar)>;

CH_DEF_SFINAE_CHECK(is_scalar_only, is_true<(std::decay_t<T>::traits::type == traits_scalar)>::value);

CH_DEF_SFINAE_CHECK(is_scalar_type, is_scalar_traits<typename std::decay_t<T>::traits>::value);

CH_DEF_SFINAE_CHECK(is_scalar_compatible, (std::is_base_of<ch_scalar<width_v<T>>, T>::value));

template <typename... Ts>
using deduce_scalar_t = std::conditional_t<
  is_scalar_compatible<deduce_type_t<false, Ts...>>::value, deduce_type_t<false, Ts...>, non_ch_type>;

template <typename T, unsigned N = width_v<T>>
using is_scalar_convertible = is_cast_convertible<ch_scalar<N>, T>;

template <typename T, typename R = ch_scalar<width_v<T>>>
using scalar_cast_t = std::conditional_t<is_scalar_type<T>::value, const T&, R>;

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer;

using scalar_buffer_ptr = std::shared_ptr<scalar_buffer>;

class scalar_buffer {
public:
  explicit scalar_buffer(unsigned size);

  scalar_buffer(const scalar_buffer& rhs);

  scalar_buffer(scalar_buffer&& rhs);

  explicit  scalar_buffer(const bitvector& data);

  explicit scalar_buffer(bitvector&& data);

  scalar_buffer(unsigned size, const scalar_buffer_ptr& buffer, unsigned offset);

  virtual ~scalar_buffer() {}

  scalar_buffer& operator=(const scalar_buffer& rhs) {
    this->copy(rhs);
    return *this;
  }

  scalar_buffer& operator=(scalar_buffer&& rhs) {
    this->copy(rhs);
    return *this;
  }

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
    this->write(0, data.words(), data.cbsize(), 0, size_);
  }

  void copy(const scalar_buffer& rhs) {
    this->write(0,
                rhs.get_data().words(),
                rhs.get_data().cbsize(),
                rhs.get_offset(),
                rhs.size());
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

  unsigned size() const {
    return size_;
  }

protected:

  scalar_buffer(const bitvector& value,
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

template <typename... Args>
auto make_scalar_buffer(Args&&... args) {
  return std::make_shared<scalar_buffer>(std::forward<Args>(args)...);
}

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
    assert(width_v<T> == obj.get_buffer()->size());
    return obj.get_buffer()->get_data();
  }

  template <typename T>
  static auto copy_buffer(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->size());
    return make_scalar_buffer(*obj.get_buffer());
  }

  template <typename U, typename V,
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(width_v<U> == dst.get_buffer()->size());
    assert(width_v<V> == src.get_buffer()->size());
    *dst.get_buffer() = *src.get_buffer();
  }

  template <typename U, typename V,
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void move(U& dst, V&& src) {
    assert(width_v<U> == dst.get_buffer()->size());
    *dst.get_buffer() = std::move(*src.get_buffer());
  }

  template <typename D, typename T>
  static D cast(const T& obj) {
    return D(make_scalar_buffer(width_v<T>, obj.get_buffer(), 0));
  }
};

///////////////////////////////////////////////////////////////////////////////

typedef void (*ScalarFunc1)(bitvector& out, const bitvector& in);
typedef void (*ScalarFunc2)(bitvector& out, const bitvector& lhs, const bitvector& rhs);

template <typename R, typename A>
auto ScalarOp(const A& in, ScalarFunc1 func) {
  bitvector ret(width_v<R>);
  func(ret, scalar_accessor::get_data(in));
  return R(make_scalar_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto ScalarOp(const A& lhs, const B& rhs, ScalarFunc2 func) {
  bitvector ret(width_v<R>);
  func(ret, scalar_accessor::get_data(lhs), scalar_accessor::get_data(rhs));
  return R(make_scalar_buffer(std::move(ret)));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_SCALAR_FRIEND_OP1(i, x) \
  CH_FRIEND_OP1((), &&, const ch_scalar&, x) \
  CH_FRIEND_OP1((), ||, const ch_scalar&, x) \
  CH_FRIEND_OP1((), ==, const ch_scalar&, x) \
  CH_FRIEND_OP1((), !=, const ch_scalar&, x) \
  CH_FRIEND_OP1((), &, const ch_scalar&, x) \
  CH_FRIEND_OP1((), |, const ch_scalar&, x) \
  CH_FRIEND_OP1((), ^, const ch_scalar&, x)

#define CH_SCALAR_OP1_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_FRIEND_OP2(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ==, const ch_scalar&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), !=, const ch_scalar&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_scalar&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_scalar&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_scalar&, x) \

#define CH_SCALAR_OP2_TYPES \
  const ch_scalar<M>&

#define CH_SCALAR_FRIEND_OP3(i, x) \
  CH_FRIEND_OP3((), <<, const ch_scalar&, x, const ch_scalar<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3((), >>, const ch_scalar&, x, const ch_scalar<CH_WIDTH_OF(x)>&)

#define CH_SCALAR_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_SCALAR_INTERFACE(type) \
  template <typename R> \
  const auto as() const { \
    return ch::internal::scalar_accessor::cast<R>(*this); \
  } \
  template <typename R> \
  auto as() { \
    return ch::internal::scalar_accessor::cast<R>(*this); \
  } \
  const auto as_scalar() const { \
    return this->as<ch_scalar<type::traits::bitwidth>>(); \
  } \
  auto as_scalar() { \
    return this->as<ch_scalar<type::traits::bitwidth>>(); \
  } \
  const auto as_int() const { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  const auto as_uint() const { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  }

template <unsigned N>
class ch_scalar {
public:
  using traits = scalar_traits<N, false, ch_scalar, ch_logic<N>>;

  ch_scalar(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  ch_scalar(const ch_scalar& rhs)
    : buffer_(scalar_accessor::copy_buffer(rhs))
  {}

  ch_scalar(ch_scalar&& rhs)
    : buffer_(std::move(rhs.buffer_))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_scalar(const U& rhs)
    : buffer_(scalar_accessor::copy_buffer(rhs))
  {}

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(width_v<U> < N)>
  explicit ch_scalar(const U& rhs)
    : buffer_(scalar_accessor::copy_buffer(ch_pad<N>(rhs)))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit ch_scalar(const U& rhs)
    : buffer_(make_scalar_buffer(bitvector(N, rhs)))
  {}

  ch_scalar& operator=(const ch_scalar& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  ch_scalar& operator=(ch_scalar&& rhs) {
    scalar_accessor::move(*this, std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  ch_scalar& operator=(const U& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scalar_type<U>::value),
            CH_REQUIRE_0(width_v<U> < N)>
  ch_scalar& operator=(const U& rhs) {
    scalar_accessor::copy(*this, ch_pad<N>(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_scalar& operator=(U rhs) {
    buffer_->write(bitvector(N, rhs));
    return *this;
  }

  const auto operator[](size_t index) const {
    assert(index < N);
    return ch_scalar<1>(make_scalar_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    assert(index < N);
    return ch_scalar<1>(make_scalar_buffer(1, buffer_, index));
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_compatible<R>::value)>
  const auto slice(size_t start = 0) const {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_scalar_buffer(width_v<R>, buffer_, start));
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_compatible<R>::value)>
  const auto aslice(size_t start = 0) const {
    return this->slice<R>(start * width_v<R>);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return this->slice<ch_scalar<M>>(start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return this->slice<ch_scalar<M>>(start * M);
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_type<R>::value)>
  auto slice(size_t start = 0) {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_scalar_buffer(width_v<R>, buffer_, start));
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_type<R>::value)>
  auto aslice(size_t start = 0) {
    return this->slice<R>(start * width_v<R>);
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return this->slice<ch_scalar<M>>(start);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
    return this->slice<ch_scalar<M>>(start * M);
  }

  // compare operators

  auto operator==(const ch_scalar& rhs) const {
    return (buffer_->get_data() == rhs.buffer_->get_data());
  }

  auto operator!=(const ch_scalar& rhs) const {
    return !(buffer_->get_data() == rhs.buffer_->get_data());
  }

  // logic operators

  auto operator&&(const ch_scalar& rhs) const {
    static_assert(N == 1, "invalid size");
    return ScalarOp<ch_scalar>(*this, rhs, And);
  }

  auto operator||(const ch_scalar& rhs) const {
    static_assert(N == 1, "invalid size");
    return ScalarOp<ch_scalar>(*this, rhs, Or);
  }

  auto operator!() const {
    return (0x0 == *this);
  }

  // bitwise operators

  auto operator~() const {
    return ScalarOp<ch_scalar>(*this, Inv);
  }

  auto operator&(const ch_scalar& rhs) const {
    return ScalarOp<ch_scalar>(*this, rhs, And);
  }

  auto operator|(const ch_scalar& rhs) const {
    return ScalarOp<ch_scalar>(*this, rhs, Or);
  }

  auto operator^(const ch_scalar& rhs) const {
    return ScalarOp<ch_scalar>(*this, rhs, Xor);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scalar>(*this, rhs, Sll);
  }

  template <unsigned M>
  auto operator>>(const ch_scalar<M>& rhs) const {
    return ScalarOp<ch_scalar>(*this, rhs, Srl);
  }

  CH_SCALAR_INTERFACE(ch_scalar)

  template <typename U,
            CH_REQUIRE_0(is_bitvector_castable<U>::value),
            CH_REQUIRE_0(sizeof(U) * 8 >= N)>
  explicit operator U() const {
    return static_cast<U>(buffer_->get_data());
  }

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset = 0,
            uint32_t length = N) const {
    buffer_->read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = N) {
    buffer_->write(dst_offset, in, in_cbsize, src_offset, length);
  }

protected:

  const scalar_buffer_ptr& get_buffer() const {
    return buffer_;
  }

  scalar_buffer_ptr& get_buffer() {
    return buffer_;
  }

  scalar_buffer_ptr buffer_;

  friend class scalar_accessor;

  friend std::ostream& operator<<(std::ostream& out, const ch_scalar& rhs) {
    return out << scalar_accessor::get_data(rhs);
  }

  // friend operators

  CH_FOR_EACH(CH_SCALAR_FRIEND_OP1, CH_SEP_SPACE, CH_SCALAR_OP1_TYPES)
  CH_FOR_EACH(CH_SCALAR_FRIEND_OP2, CH_SEP_SPACE, CH_SCALAR_OP2_TYPES)
  CH_FOR_EACH(CH_SCALAR_FRIEND_OP3, CH_SEP_SPACE, CH_SCALAR_OP3_TYPES)
};

template <unsigned M, unsigned N>
ch_scalar<M> ch_pad(const ch_scalar<N>& obj) {
  static_assert(M >= N, "invalid pad size");
  if constexpr(M > N) {
    return ScalarOp<ch_scalar<M>>(obj, ZExt);
  } else {
    return obj;
  }
}

}
}
