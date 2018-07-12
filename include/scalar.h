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
using ch_scalar_t = typename std::decay_t<T>::traits::scalar_type;

template <typename T>
inline constexpr bool is_scalar_traits_v = is_true_v<(T::type & traits_scalar)>;

CH_DEF_SFINAE_CHECK(is_scalar_only, is_true_v<(std::decay_t<T>::traits::type == traits_scalar)>);

CH_DEF_SFINAE_CHECK(is_scalar_type, is_scalar_traits_v<typename std::decay_t<T>::traits>);

template <typename T>
inline constexpr bool is_scbit_base_v = std::is_base_of_v<ch_scbit<ch_width_v<T>>, T>;

template <typename T, unsigned N>
inline constexpr bool is_scbit_convertible_v = std::is_constructible_v<ch_scbit<N>, T>;

template <unsigned N, typename T>
auto to_scalar(T&& obj) {
  if constexpr (is_scalar_type_v<T> && ch_width_v<T> == N) {
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

  explicit scalar_buffer(const bitvector& data);

  explicit scalar_buffer(bitvector&& data);

  scalar_buffer(uint32_t size, const scalar_buffer_ptr& buffer, uint32_t offset);

  scalar_buffer(const scalar_buffer& other);

  scalar_buffer(scalar_buffer&& other);

  virtual ~scalar_buffer() {}

  scalar_buffer& operator=(const scalar_buffer& other);

  scalar_buffer& operator=(scalar_buffer&& other);

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
                uint32_t size);

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
    assert(ch_width_v<T> == obj.buffer()->size());
    return obj.buffer();
  }

  template <typename T>
  static auto& buffer(T& obj) {
    assert(ch_width_v<T> == obj.buffer()->size());
    return obj.buffer();
  }

  template <typename T>
  static const auto& data(const T& obj) {
    assert(ch_width_v<T> == obj.buffer()->size());
    return obj.buffer()->data();
  }

  template <typename T>
  static auto copy(const T& obj) {
    assert(ch_width_v<T> == obj.buffer()->size());
    return make_scalar_buffer(*obj.buffer());
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(ch_width_v<T> == obj.buffer()->size());
    return make_scalar_buffer(std::move(*obj.buffer()));
  }

  template <typename U, typename V>
  static void copy(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer()->size());
    assert(ch_width_v<V> == src.buffer()->size());
    *dst.buffer() = *src.buffer();
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer()->size());
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
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    return R(make_scalar_buffer(ch_width_v<T>, obj.buffer(), 0));
  }
};

///////////////////////////////////////////////////////////////////////////////

typedef void (*ScalarFunc1)(bitvector& out, const bitvector& in);
typedef void (*ScalarFunc2)(bitvector& out, const bitvector& lhs, const bitvector& rhs);

template <typename R, typename A>
auto make_scalar_op(ScalarFunc1 func, const A& in) {
  bitvector ret(ch_width_v<R>);
  func(ret, scalar_accessor::data(in));
  return R(make_scalar_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_scalar_op(ScalarFunc2 func, const A& lhs, const B& rhs) {
  bitvector ret(ch_width_v<R>);
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
  template <template <unsigned> typename T, unsigned N, typename Next = empty_base> \
  struct name : Next { \
    using Derived = T<N>; \
    using Next::Next; \
    using Next::operator=; \
    name(const Next& other) : Next(other) {} \
    name(Next&& other) : Next(std::move(other)) {} \
    name& operator=(const Next& other) { Next::operator=(other); return *this; } \
    name& operator=(Next&& other) { Next::operator=(std::move(other)); return *this; } \
    name(const name& other) : Next(other) {} \
    name(name&& other) : Next(std::move(other)) {} \
    name& operator=(const name& other) { Next::operator=(other); return *this; } \
    name& operator=(name&& other) { Next::operator=(std::move(other)); return *this; }

#define CH_SCALAR_OPERATOR_IMPL(op, body) \
  friend auto op(const Derived& lhs, const Derived& rhs) { \
    CH_REM body; \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(const Derived& lhs, const T<M>& _rhs) { \
    auto rhs = _rhs.template pad<N>(); \
    CH_REM body; \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(const T<M>& _lhs, const Derived& rhs) { \
    auto lhs = _lhs.template pad<N>(); \
    CH_REM body; \
  }

CH_SCALAR_OPERATOR(scalar_op_equality)
  CH_SCALAR_OPERATOR_IMPL(operator==, (return scalar_accessor::data(lhs) == scalar_accessor::data(rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator!=, (return scalar_accessor::data(lhs) != scalar_accessor::data(rhs)))
};

CH_SCALAR_OPERATOR(scalar_op_logical)
  friend auto operator&&(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    auto ret = make_scalar_op<ch_scbit<1>>(bv_and, lhs, rhs);
    return static_cast<bool>(ret);
  }

  friend auto operator||(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    auto ret = make_scalar_op<ch_scbit<1>>(bv_or, lhs, rhs);
    return static_cast<bool>(ret);
  }

  friend auto operator!(const Derived& self) {
    return (0x0 == self);
  }
};

CH_SCALAR_OPERATOR(scalar_op_bitwise)
  friend auto operator~(const Derived& self) {
    return make_scalar_op<Derived>(bv_inv, self);
  }

  CH_SCALAR_OPERATOR_IMPL(operator&, (return make_scalar_op<Derived>(bv_and, lhs, rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator|, (return make_scalar_op<Derived>(bv_or, lhs, rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator^, (return make_scalar_op<Derived>(bv_xor, lhs, rhs)))
};

CH_SCALAR_OPERATOR(scalar_op_shift)
  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator<<(const Derived& lhs, const U& rhs) {
    return make_scalar_op<Derived, Derived, ch_scbit<ch_width_v<U>>>(bv_sll, lhs, rhs);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator>>(const Derived& lhs, const U& rhs) {
    return make_scalar_op<Derived, Derived, ch_scbit<ch_width_v<U>>>(
                            (ch_signed_v<Derived> ? bv_sra : bv_srl), lhs, rhs);
  }
};

CH_SCALAR_OPERATOR(scalar_op_cast)
  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit operator U() const {
    static_assert(CH_WIDTH_OF(U) >= Derived::traits::bitwidth, "invalid size");
    auto ret = static_cast<U>(scalar_accessor::data(reinterpret_cast<const Derived&>(*this)));
    if constexpr(ch_signed_v<Derived> && (CH_WIDTH_OF(U) > Derived::traits::bitwidth)) {
      return sign_ext(ret, Derived::traits::bitwidth);
    } else {
      return ret;
    }
  }
};

CH_SCALAR_OPERATOR(scalar_op_padding)
  template <typename R>
  R pad() const {
    static_assert(is_scalar_type_v<R>, "invalid type");
    static_assert(ch_width_v<R> >= N, "invalid size");
    auto& self = reinterpret_cast<const Derived&>(*this);
    if constexpr (ch_width_v<R> > N) {
      if constexpr (ch_signed_v<Derived>) {
        return make_scalar_op<R>(bv_sext, self);
      } else {
        return make_scalar_op<R>(bv_zext, self);
      }
    } else
    if constexpr (std::is_same_v<R, Derived>) {
      return self;
    } else {
      return R(self);
    }
  }
  template <unsigned M>
  auto pad() const {
    return this->pad<T<M>>();
  }
};

CH_SCALAR_OPERATOR(scalar_op_relational)
  CH_SCALAR_OPERATOR_IMPL(operator<, (if constexpr (ch_signed_v<Derived>) {
                                        return bv_lts(lhs.buffer_->data(), rhs.buffer_->data());
                                      } else {
                                        return bv_ltu(lhs.buffer_->data(), rhs.buffer_->data());
                                      }))
  CH_SCALAR_OPERATOR_IMPL(operator>=, (return !(lhs < rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator>, (return (rhs < lhs)))
  CH_SCALAR_OPERATOR_IMPL(operator<=, (return !(rhs < lhs)))
};

CH_SCALAR_OPERATOR(scalar_op_arithmetic)
  friend auto operator-(const Derived& self) {
    return make_scalar_op<Derived>(bv_neg, self);
  }
  CH_SCALAR_OPERATOR_IMPL(operator+, (return make_scalar_op<Derived>(bv_add, lhs, rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator-, (return make_scalar_op<Derived>(bv_sub, lhs, rhs)))
  CH_SCALAR_OPERATOR_IMPL(operator*, (return make_scalar_op<Derived>(bv_mul, lhs, rhs)))

  CH_SCALAR_OPERATOR_IMPL(operator/, (if constexpr (ch_signed_v<Derived>) {
                                         return make_scalar_op<Derived>(bv_divs, lhs, rhs);
                                      } else {
                                         return make_scalar_op<Derived>(bv_divu, lhs, rhs);
                                      }))

  CH_SCALAR_OPERATOR_IMPL(operator%, (if constexpr (ch_signed_v<Derived>) {
                                        return make_scalar_op<Derived>(bv_mods, lhs, rhs);
                                     } else {
                                        return make_scalar_op<Derived>(bv_modu, lhs, rhs);
                                     }))
};

}
}
