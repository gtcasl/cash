#pragma once

#include "bitvector.h"
#include "arithm.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_scbit;
template <unsigned N> class ch_scint;
template <unsigned N> class ch_scuint;

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

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
inline constexpr bool is_scalar_traits_v = is_true_v<(T::type & traits_scalar)>;

CH_DEF_SFINAE_CHECK(is_scalar_only, is_true_v<(std::decay_t<T>::traits::type == traits_scalar)>);

CH_DEF_SFINAE_CHECK(is_scalar_type, is_scalar_traits_v<typename std::decay_t<T>::traits>);

template <typename T, unsigned N = width_v<T>>
inline constexpr bool is_scalar_convertible_v = std::is_constructible_v<ch_scbit<N>, T>;

template <typename T, typename R = ch_scbit<width_v<T>>>
using scalar_cast_t = std::conditional_t<is_scalar_type_v<T>, const T&, R>;

///////////////////////////////////////////////////////////////////////////////

class scalar_buffer;

using scalar_buffer_ptr = std::shared_ptr<scalar_buffer>;

class scalar_buffer {
public:
  explicit scalar_buffer(uint32_t size);

  scalar_buffer(const scalar_buffer& rhs);

  scalar_buffer(scalar_buffer&& rhs);

  explicit scalar_buffer(const bitvector& data);

  explicit scalar_buffer(bitvector&& data);

  scalar_buffer(uint32_t size, const scalar_buffer_ptr& buffer, uint32_t offset);

  virtual ~scalar_buffer() {}

  virtual const bitvector& data() const;

  const scalar_buffer_ptr& source() const {
    return source_;
  }

  uint32_t offset() const {
    return offset_;
  }

  uint32_t size() const {
    return size_;
  }

  scalar_buffer& operator=(const scalar_buffer& rhs) {
    this->copy(rhs);
    return *this;
  }

  scalar_buffer& operator=(scalar_buffer&& rhs) {
    this->copy(rhs);
    return *this;
  }

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
                rhs.data().words(),
                rhs.data().cbsize(),
                rhs.offset(),
                rhs.size());
  }
protected:

  scalar_buffer(const bitvector& value,
                const scalar_buffer_ptr& source,
                uint32_t offset,
                uint32_t size)
    : value_(value)
    , source_(source)
    , offset_(offset)
    , size_(size)
  {}

  mutable bitvector value_;
  scalar_buffer_ptr source_;
  uint32_t offset_;
  uint32_t size_;
};

template <typename... Args>
auto make_scalar_buffer(Args&&... args) {
  return std::make_shared<scalar_buffer>(std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

class scalar_accessor {
public:
  template <typename T>
  static const auto& buffer(const T& obj) {
    return obj.buffer();
  }

  template <typename T>
  static auto& buffer(T& obj) {
    return obj.buffer();
  }

  template <typename T>
  static const auto& data(const T& obj) {
    assert(width_v<T> == obj.buffer()->size());
    return obj.buffer()->data();
  }

  template <typename T>
  static auto copy_buffer(const T& obj) {
    assert(width_v<T> == obj.buffer()->size());
    return make_scalar_buffer(*obj.buffer());
  }

  template <typename U, typename V>
  static void copy(U& dst, const V& src) {
    static_assert(width_v<U> == width_v<V>, "invalid size");
    assert(width_v<U> == dst.buffer()->size());
    assert(width_v<V> == src.buffer()->size());
    *dst.buffer() = *src.buffer();
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    static_assert(width_v<U> == width_v<V>, "invalid size");
    assert(width_v<U> == dst.buffer()->size());
    *dst.buffer() = std::move(*src.buffer());
  }

  template <typename R, typename T>
  static R cast(const T& obj) {
    static_assert(width_v<T> == width_v<R>, "invalid size");
    return R(make_scalar_buffer(width_v<T>, obj.buffer(), 0));
  }
};

///////////////////////////////////////////////////////////////////////////////

typedef void (*ScalarFunc1)(bitvector& out, const bitvector& in);
typedef void (*ScalarFunc2)(bitvector& out, const bitvector& lhs, const bitvector& rhs);

template <typename R, typename A>
auto make_scalar_op(const A& in, ScalarFunc1 func) {
  bitvector ret(width_v<R>);
  func(ret, scalar_accessor::data(in));
  return R(make_scalar_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_scalar_op(const A& lhs, const B& rhs, ScalarFunc2 func) {
  bitvector ret(width_v<R>);
  func(ret, scalar_accessor::data(lhs), scalar_accessor::data(rhs));
  return R(make_scalar_buffer(std::move(ret)));
}

template <typename A>
auto make_scalar_op(const A& in, ScalarFunc1 func) {
  return make_scalar_op<A, A>(in, func);
}

template <typename A, typename B>
auto make_scalar_op(const A& lhs, const B& rhs, ScalarFunc2 func) {
  return make_scalar_op<A, A, B>(lhs, rhs, func);
}

///////////////////////////////////////////////////////////////////////////////

#define CH_SCALAR_INTERFACE(type) \
  template <typename R> \
  const auto as() const { \
    static_assert(ch::internal::is_scalar_type_v<R>, "invalid type"); \
    return ch::internal::scalar_accessor::cast<R>(*this); \
  } \
  template <typename R> \
  auto as() { \
    static_assert(ch::internal::is_scalar_type_v<R>, "invalid type"); \
    return ch::internal::scalar_accessor::cast<R>(*this); \
  } \
  const auto as_scbit() const { \
    return this->as<ch_scbit<ch::internal::width_v<type>>>(); \
  } \
  auto as_scbit() { \
    return this->as<ch_scbit<ch::internal::width_v<type>>>(); \
  } \
  const auto as_scint() const { \
    return this->as<ch::internal::ch_scint<ch::internal::width_v<type>>>(); \
  } \
  auto as_scint() { \
    return this->as<ch::internal::ch_scint<ch::internal::width_v<type>>>(); \
  } \
  const auto as_scuint() const { \
    return this->as<ch::internal::ch_scuint<ch::internal::width_v<type>>>(); \
  } \
  auto as_scuint() { \
    return this->as<ch::internal::ch_scuint<ch::internal::width_v<type>>>(); \
  }

template <typename Derived>
class ch_scalar_integer;

template <typename Derived>
class ch_scalar_base {
public:
  using self = Derived;

  ch_scalar_base(const scalar_buffer_ptr& buffer) : buffer_(buffer) {
    assert(width_v<Derived> == buffer->size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scalar_base(const U& rhs)
    : buffer_(make_scalar_buffer(bitvector(width_v<Derived> , rhs)))
  {}

  template <typename U>
  ch_scalar_base(const ch_scalar_base<U>& rhs)
    : buffer_(scalar_accessor::copy_buffer(rhs)) {
    static_assert(width_v<U> == width_v<Derived>, "invalid size");
  }

  ch_scalar_base(const ch_scalar_base& rhs)
    : buffer_(scalar_accessor::copy_buffer(rhs))
  {}

  ch_scalar_base(ch_scalar_base&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  ch_scalar_base& operator=(const ch_scalar_base& rhs) {
    scalar_accessor::copy(*this, rhs);
    return *this;
  }

  ch_scalar_base& operator=(ch_scalar_base&& rhs) {
    scalar_accessor::move(*this, std::move(rhs));
    return *this;
  }

  // subscript operators

  const auto operator[](size_t index) const {
    assert(index < width_v<Derived>);
    return ch_scbit<1>(make_scalar_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    assert(index < width_v<Derived>);
    return ch_scbit<1>(make_scalar_buffer(1, buffer_, index));
  }

  // slicing operators

  template <typename R,
            CH_REQUIRE_0(is_scalar_type_v<R>)>
  const auto slice(size_t start = 0) const {
    static_assert(width_v<R> <= width_v<Derived>, "invalid size");
    assert((start + width_v<R>) <= width_v<Derived>);
    return R(make_scalar_buffer(width_v<R>, buffer_, start));
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_type_v<R>)>
  const auto aslice(size_t start = 0) const {
    return this->slice<R>(start * width_v<R>);
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return this->slice<ch_scbit<M>>(start);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0) const {
    return this->slice<ch_scbit<M>>(start * M);
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_type_v<R>)>
  auto slice(size_t start = 0) {
    static_assert(width_v<R> <= width_v<Derived>, "invalid size");
    assert((start + width_v<R>) <= width_v<Derived>);
    return R(make_scalar_buffer(width_v<R>, buffer_, start));
  }

  template <typename R,
            CH_REQUIRE_0(is_scalar_type_v<R>)>
  auto aslice(size_t start = 0) {
    return this->slice<R>(start * width_v<R>);
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return this->slice<ch_scbit<M>>(start);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) {
    return this->slice<ch_scbit<M>>(start * M);
  }

  // padding operators

  template <typename R,
            CH_REQUIRE_0(is_scalar_type_v<R>)>
  R pad() const {
    static_assert(width_v<R> >= width_v<Derived>, "invalid size");
    if constexpr (width_v<R> > width_v<Derived>) {
      return make_scalar_op<R>(*this, (signed_v<Derived> ? SExt : ZExt));
    } else
    if constexpr (std::is_same_v<R, Derived>) {
      return *this;
    } else {
      return R(*this);
    }
  }

  template <unsigned M>
  auto pad() const {
    return this->pad<ch_scbit<M>>();
  }

  // compare operators

  friend auto operator==(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() == rhs.buffer_->data());
  }

  friend auto operator!=(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() != rhs.buffer_->data());
  }

  // logic operators

  friend auto operator&&(const Derived& lhs, const Derived& rhs) {
    static_assert(width_v<Derived> == 1, "invalid size");
    return static_cast<bool>(make_scalar_op<ch_scbit<1>>(lhs, rhs, And));
  }

  friend auto operator||(const Derived& lhs, const Derived& rhs) {
    static_assert(width_v<Derived> == 1, "invalid size");
    return static_cast<bool>(make_scalar_op<ch_scbit<1>>(lhs, rhs, Or));
  }

  auto operator!() const {
    return (0x0 == *this);
  }

  // bitwise operators

  auto operator~() const {
    return make_scalar_op(*this, Inv);
  }

  friend auto operator&(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, And);
  }

  friend auto operator|(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Or);
  }

  friend auto operator^(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op(lhs, rhs, Xor);
  }

  // shift operators

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator<<(const Derived& lhs, const U& rhs) {
    auto _rhs = ch_scbit<CH_WIDTH_OF(U)>(rhs);
    return make_scalar_op(lhs, _rhs, Sll);
  }

  template <typename U>
  friend auto operator<<(const Derived& lhs, const ch_scalar_integer<U>& rhs) {
    return make_scalar_op(lhs, rhs, Sll);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator>>(const Derived& lhs, const U& rhs) {
    auto _rhs = ch_scbit<CH_WIDTH_OF(U)>(rhs);
    return make_scalar_op(lhs, _rhs, (signed_v<Derived> ? Sra : Srl));
  }

  template <typename U>
  friend auto operator>>(const Derived& lhs, const ch_scalar_integer<U>& rhs) {
    return make_scalar_op(lhs, rhs, (signed_v<Derived> ? Sra : Srl));
  }

  // cast operators

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit operator U() const {
    static_assert(CH_WIDTH_OF(U) >= width_v<Derived>, "invalid size");
    auto ret = static_cast<U>(buffer_->data());
    if constexpr(signed_v<Derived> &&
                 std::is_signed_v<U> &&
                 (CH_WIDTH_OF(U) > width_v<Derived>)) {
      return sign_ext(ret, width_v<Derived>);
    } else {
      return ret;
    }
  }

  // bits access

  void read(uint32_t dst_offset,
            void* out,
            uint32_t out_cbsize,
            uint32_t src_offset = 0,
            uint32_t length = width_v<Derived>) const {
    buffer_->read(dst_offset, out, out_cbsize, src_offset, length);
  }

  void write(uint32_t dst_offset,
             const void* in,
             uint32_t in_cbsize,
             uint32_t src_offset = 0,
             uint32_t length = width_v<Derived>) {
    buffer_->write(dst_offset, in, in_cbsize, src_offset, length);
  }

  CH_SCALAR_INTERFACE(Derived)

protected:

  const scalar_buffer_ptr& buffer() const {
    return buffer_;
  }

  scalar_buffer_ptr buffer_;

  friend class scalar_accessor;

  friend std::ostream& operator<<(std::ostream& out, const Derived& rhs) {
    return out << scalar_accessor::data(rhs);
  }
};

template <unsigned N>
class ch_scbit : public ch_scalar_base<ch_scbit<N>> {
public:
  using traits = scalar_traits<N, false, ch_scbit, ch_bit<N>>;
  using base = ch_scalar_base<ch_scbit>;

  ch_scbit(const scalar_buffer_ptr& buffer = make_scalar_buffer(N))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_scbit(const U& rhs) : base(rhs) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_scbit(const ch_scbit<M>& rhs) : base(rhs.template pad<N>()) {}

  template <typename U>
  explicit ch_scbit(const ch_scalar_base<U>& rhs) : base(rhs) {}

  ch_scbit(const ch_scbit& rhs) : base(rhs) {}

  ch_scbit(ch_scbit&& rhs) : base(std::move(rhs)) {}

  ch_scbit& operator=(const ch_scbit& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_scbit& operator=(ch_scbit&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }
};

}
}
