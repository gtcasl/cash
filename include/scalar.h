#pragma once

#include "bitvector.h"
#include "traits.h"

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

template <typename T>
inline constexpr bool is_scbit_base_v = std::is_base_of_v<ch_scbit<width_v<T>>, T>;

template <typename T, unsigned N>
inline constexpr bool is_scbit_convertible_v = std::is_constructible_v<ch_scbit<N>, T>;

template <unsigned N, typename T>
auto to_scalar(T&& obj) {
  if constexpr (is_scalar_type_v<T> && width_v<T> == N) {
    return std::move(obj);
  } else {
    return ch_scbit<N>(std::forward<T>(obj));
  }
}

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

  scalar_buffer& operator=(const scalar_buffer& rhs);

  scalar_buffer& operator=(scalar_buffer&& rhs);

  void write(uint32_t dst_offset,
             const bitvector& src,
             uint32_t src_offset,
             uint32_t length);

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

  void copy(const scalar_buffer& rhs);

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

  template <typename U, typename V>
  static void write(U& dst,
                    uint32_t dst_offset,
                    const V& src,
                    uint32_t src_offset,
                    uint32_t length) {
    auto data = src.buffer()->data();
    dst.buffer()->write(dst_offset, data, src_offset, length);
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
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  auto as_scbit() { \
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  const auto as_scint() const { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_scint() { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  const auto as_scuint() const { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto as_scuint() { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  }

#define CH_SCALAR_OPERATOR(name) \
  template <typename Derived, typename Next = empty_base> \
  struct name : Next { \
    using Next::Next; \
    using Next::operator=; \
    name(const Next& rhs) : Next(rhs) {} \
    name(Next&& rhs) : Next(std::move(rhs)) {} \
    name& operator=(const Next& rhs) { Next::operator=(rhs); return *this; } \
    name& operator=(Next&& rhs) { Next::operator=(std::move(rhs)); return *this; } \
    name(const name& rhs) : Next(rhs) {} \
    name(name&& rhs) : Next(std::move(rhs)) {} \
    name& operator=(const name& rhs) { Next::operator=(rhs); return *this; } \
    name& operator=(name&& rhs) { Next::operator=(std::move(rhs)); return *this; }

CH_SCALAR_OPERATOR(scalar_op_compare)
  friend auto operator==(const Derived& lhs, const Derived& rhs) {
    return (scalar_accessor::data(lhs) == scalar_accessor::data(rhs));
  }
  friend auto operator!=(const Derived& lhs, const Derived& rhs) {
    return (scalar_accessor::data(lhs) != scalar_accessor::data(rhs));
  }
};

CH_SCALAR_OPERATOR(scalar_op_logical)
  friend auto operator&&(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    return static_cast<bool>(make_scalar_op<ch_scbit<1>>(lhs, rhs, And));
  }

  friend auto operator||(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    return static_cast<bool>(make_scalar_op<ch_scbit<1>>(lhs, rhs, Or));
  }

  friend auto operator!(const Derived& self) {
    return (0x0 == self);
  }
};

CH_SCALAR_OPERATOR(scalar_op_bitwise)
  friend auto operator~(const Derived& self) {
    return make_scalar_op<Derived>(self, Inv);
  }

  friend auto operator&(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, And);
  }

  friend auto operator|(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Or);
  }

  friend auto operator^(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Xor);
  }
};

CH_SCALAR_OPERATOR(scalar_op_shift)
  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator<<(const Derived& lhs, const U& rhs) {
    auto _rhs = ch_scbit<CH_WIDTH_OF(U)>(rhs);
    return make_scalar_op<Derived>(lhs, _rhs, Sll);
  }

  template <unsigned M>
  friend auto operator<<(const Derived& lhs, const ch_scbit<M>& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Sll);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator>>(const Derived& lhs, const U& rhs) {
    auto _rhs = ch_scbit<CH_WIDTH_OF(U)>(rhs);
    return make_scalar_op<Derived>(lhs, _rhs, (signed_v<Derived> ? Sra : Srl));
  }

  template <unsigned M>
  friend auto operator>>(const Derived& lhs, const ch_scbit<M>& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, (signed_v<Derived> ? Sra : Srl));
  }
};

CH_SCALAR_OPERATOR(scalar_cast_op)
  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit operator U() const {
    static_assert(CH_WIDTH_OF(U) >= Derived::traits::bitwidth, "invalid size");
    auto ret = static_cast<U>(scalar_accessor::data(reinterpret_cast<const Derived&>(*this)));
    if constexpr(signed_v<Derived> && (CH_WIDTH_OF(U) > Derived::traits::bitwidth)) {
      return sign_ext(ret, Derived::traits::bitwidth);
    } else {
      return ret;
    }
  }
};

CH_SCALAR_OPERATOR(scalar_op_relational)
  friend auto operator<(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() < rhs.buffer_->data());
  }

  friend auto operator>=(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() >= rhs.buffer_->data());
  }

  friend auto operator>(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() > rhs.buffer_->data());
  }

  friend auto operator<=(const Derived& lhs, const Derived& rhs) {
    return (lhs.buffer_->data() <= rhs.buffer_->data());
  }
};

CH_SCALAR_OPERATOR(scalar_op_arithmetic)
  friend auto operator-(const Derived& self) {
    return make_scalar_op<Derived>(self, Neg);
  }

  friend auto operator+(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Add);
  }

  friend auto operator-(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Sub);
  }

  friend auto operator*(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Mult);
  }

  friend auto operator/(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Div);
  }

  friend auto operator%(const Derived& lhs, const Derived& rhs) {
    return make_scalar_op<Derived>(lhs, rhs, Mod);
  }
};

}
}
