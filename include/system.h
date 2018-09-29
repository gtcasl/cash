#pragma once

#include "traits.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_scbit;
template <unsigned N> class ch_scint;
template <unsigned N> class ch_scuint;

template <typename T>
inline constexpr bool is_scbit_base_v = std::is_base_of_v<ch_scbit<ch_width_v<T>>, T>;

template <typename T, unsigned N>
inline constexpr bool is_scbit_convertible_v = std::is_constructible_v<ch_scbit<N>, T>;

template <unsigned N, typename T>
auto to_system(T&& obj) {
  if constexpr (is_system_type_v<T> && ch_width_v<T> == N) {
    return std::move(obj);
  } else {
    return ch_scbit<N>(std::forward<T>(obj));
  }
}

///////////////////////////////////////////////////////////////////////////////

class system_buffer;

using system_buffer_ptr = std::shared_ptr<system_buffer>;

class system_buffer {
public:
  explicit system_buffer(uint32_t size);

  explicit system_buffer(const sdata_type& data);

  explicit system_buffer(sdata_type&& data);

  system_buffer(uint32_t size, const system_buffer_ptr& buffer, uint32_t offset);

  system_buffer(const system_buffer& other);

  system_buffer(system_buffer&& other);

  virtual ~system_buffer() {}

  system_buffer& operator=(const system_buffer& other);

  system_buffer& operator=(system_buffer&& other);

  virtual const sdata_type& data() const;

  const system_buffer_ptr& source() const {
    return source_;
  }

  const sdata_type& value() const {
    return value_;
  }

  uint32_t offset() const {
    return offset_;
  }

  uint32_t size() const {
    return size_;
  }

  void copy(uint32_t dst_offset,
            const system_buffer& src,
            uint32_t src_offset,
            uint32_t length);

  virtual void read(uint32_t src_offset,
                    sdata_type& dst,
                    uint32_t dst_offset,
                    uint32_t length) const;

  virtual void write(uint32_t dst_offset,
                     const sdata_type& src,
                     uint32_t src_offset,
                     uint32_t length);

  virtual void read(uint32_t src_offset,
                    void* out,
                    uint32_t byte_alignment,
                    uint32_t dst_offset,
                    uint32_t length) const;

  virtual void write(uint32_t dst_offset,
                     const void* in,
                     uint32_t byte_alignment,
                     uint32_t src_offset,
                     uint32_t length);

protected:

  system_buffer(const sdata_type& value,
                const system_buffer_ptr& source,
                uint32_t offset,
                uint32_t size);

  system_buffer_ptr source_;
  mutable sdata_type value_;
  uint32_t offset_;
  uint32_t size_;
};

template <typename... Args>
auto make_system_buffer(Args&&... args) {
  return std::make_shared<system_buffer>(std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

class system_accessor {
public:
  template <typename T>
  static const auto& buffer(const T& obj) {
    assert(obj.buffer()->size() == ch_width_v<T>);
    return obj.buffer();
  }

  template <typename T>
  static const auto& data(const T& obj) {
    assert(obj.buffer()->size() == ch_width_v<T>);
    return obj.buffer()->data();
  }

  template <typename T>
  static auto copy(const T& obj) {
    assert(obj.buffer()->size() == ch_width_v<T>);
    return make_system_buffer(*obj.buffer());
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(obj.buffer()->size() == ch_width_v<T>);
    return make_system_buffer(std::move(*obj.buffer()));
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
  static auto ref(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.buffer()->size() == ch_width_v<T>);
    return R(make_system_buffer(ch_width_v<R>, obj.buffer(), start));
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(obj.buffer()->size() == ch_width_v<T>);
    return R(obj.buffer());
  }
};

///////////////////////////////////////////////////////////////////////////////

typedef void (*SystemFunc1)(block_type* out,
                            const block_type* in,
                            uint32_t size);

typedef void (*SystemFunc2)(block_type* out,
                            const block_type* lhs,
                            const block_type* rhs,
                            uint32_t size);

typedef void (*SystemFunc3)(block_type* out,
                            uint32_t out_size,
                            const block_type* lhs,
                            uint32_t lhs_size,
                            uint32_t rhs);

typedef void (*SystemFunc4)(block_type* out,
                            uint32_t out_size,
                            const block_type* lhs,
                            uint32_t lhs_size,
                            const block_type* rhs,
                            uint32_t rhs_size);

template <typename R, typename A>
auto make_system_op(SystemFunc1 func, const A& in) {
  sdata_type ret(ch_width_v<R>);
  func(ret.words(), system_accessor::data(in).words(), ch_width_v<R>);
  return R(make_system_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_system_op(SystemFunc2 func, const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(lhs);
  auto& v = system_accessor::data(rhs);
  func(ret.words(), u.words(), v.words(), ch_width_v<R>);
  return R(make_system_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_system_op(SystemFunc3 func, const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(lhs);
  func(ret.words(), ch_width_v<R>, u.words(), u.size(), static_cast<uint32_t>(rhs));
  return R(make_system_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_system_op(SystemFunc4 func, const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(lhs);
  auto& v = system_accessor::data(rhs);
  func(ret.words(), ch_width_v<R>, u.words(), u.size(), v.words(), v.size());
  return R(make_system_buffer(std::move(ret)));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_SYSTEM_INTERFACE(type) \
  template <typename U, CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)> \
  void read(uint32_t src_offset, \
            U* out, \
            uint32_t dst_offset = 0, \
            uint32_t length = type::traits::bitwidth) const { \
    this->buffer()->read(src_offset, out, sizeof(U), dst_offset, length); \
  } \
  template <typename U, CH_REQUIRE_0(std::is_integral_v<U> && std::is_unsigned_v<U>)> \
  void write(uint32_t dst_offset, \
             const U* in, \
             uint32_t src_offset = 0, \
             uint32_t length = type::traits::bitwidth) { \
    this->buffer()->write(dst_offset, in, sizeof(U), src_offset, length); \
  } \
  template <typename R> \
  std::add_const_t<R> as() const { \
    static_assert(ch::internal::is_system_type_v<R>, "invalid type"); \
    return ch::internal::system_accessor::cast<R>(*this); \
  } \
  template <typename R> \
  auto as() { \
    static_assert(ch::internal::is_system_type_v<R>, "invalid type"); \
    return ch::internal::system_accessor::cast<R>(*this); \
  } \
  auto as_scbit() const { \
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  auto as_scbit() { \
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  auto as_scint() const { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_scint() { \
    return this->as<ch::internal::ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_scuint() const { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto as_scuint() { \
    return this->as<ch::internal::ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto ref() { \
    return ch::internal::system_accessor::ref<type>(*this, 0); \
  }

#define CH_SYSTEM_OPERATOR(name) \
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

#define CH_SYSTEM_OPERATOR_IMPL(op, body) \
  friend auto op(const Derived& lhs, const Derived& rhs) { \
    CH_REM body; \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(const Derived& lhs, const T<M>& _rhs) { \
    T<N> rhs(_rhs); \
    CH_REM body; \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(const T<M>& _lhs, const Derived& rhs) { \
    T<N> lhs(_lhs); \
    CH_REM body; \
  }

CH_SYSTEM_OPERATOR(system_op_equality)
  CH_SYSTEM_OPERATOR_IMPL(operator==, (return bv_eq(system_accessor::data(lhs).words(), system_accessor::data(rhs).words(), N)))
  CH_SYSTEM_OPERATOR_IMPL(operator!=, (return !bv_eq(system_accessor::data(lhs).words(), system_accessor::data(rhs).words(), N)))
};

CH_SYSTEM_OPERATOR(system_op_logical)
  friend auto operator&&(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    return bv_orr(system_accessor::data(lhs).words(), N) && bv_orr(system_accessor::data(rhs).words(), N);
  }

  friend auto operator||(const Derived& lhs, const Derived& rhs) {
    static_assert(Derived::traits::bitwidth == 1, "invalid size");
    return bv_orr(system_accessor::data(lhs).words(), N) || bv_orr(system_accessor::data(rhs).words(), N);
  }

  friend auto operator!(const Derived& self) {
    return !bv_orr(system_accessor::data(self).words(), N);
  }
};

CH_SYSTEM_OPERATOR(system_op_bitwise)
  friend auto operator~(const Derived& self) {
    return make_system_op<Derived>(bv_inv, self);
  }

  CH_SYSTEM_OPERATOR_IMPL(operator&, (return make_system_op<Derived>(bv_and, lhs, rhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator|, (return make_system_op<Derived>(bv_or, lhs, rhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator^, (return make_system_op<Derived>(bv_xor, lhs, rhs)))
};

CH_SYSTEM_OPERATOR(system_op_shift)
  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator<<(const Derived& lhs, const U& rhs) {
    return make_system_op<Derived, Derived, ch_scbit<ch_width_v<U>>>(bv_sll, lhs, rhs);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)>
  friend auto operator>>(const Derived& lhs, const U& rhs) {
    if constexpr (ch_signed_v<Derived>) {
      return make_system_op<Derived, Derived, ch_scbit<ch_width_v<U>>>(bv_sra, lhs, rhs);
    } else {
      return make_system_op<Derived, Derived, ch_scbit<ch_width_v<U>>>(bv_srl, lhs, rhs);
    }
  }
};

CH_SYSTEM_OPERATOR(system_op_cast)
  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  explicit operator U() const {
    static_assert(bitwidth_v<U> >= Derived::traits::bitwidth, "invalid size");
    auto ret = static_cast<U>(system_accessor::data(reinterpret_cast<const Derived&>(*this)));
    if constexpr(ch_signed_v<Derived> && (bitwidth_v<U> > Derived::traits::bitwidth)) {
      return sign_ext(ret, Derived::traits::bitwidth);
    } else {
      return ret;
    }
  }

  explicit operator sdata_type() const {
    return system_accessor::data(reinterpret_cast<const Derived&>(*this));
  }
};

CH_SYSTEM_OPERATOR(system_op_relational)
  CH_SYSTEM_OPERATOR_IMPL(operator<, (
      if constexpr (ch_signed_v<Derived>) {
        return bv_slt(system_accessor::data(lhs).words(), system_accessor::data(rhs).words(), N);
      } else {
        return bv_ult(system_accessor::data(lhs).words(), system_accessor::data(rhs).words(), N);
      }))
  CH_SYSTEM_OPERATOR_IMPL(operator>=, (return !(lhs < rhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator>, (return (rhs < lhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator<=, (return !(rhs < lhs)))
};

CH_SYSTEM_OPERATOR(system_op_arithmetic)
  friend auto operator-(const Derived& self) {
    return make_system_op<Derived>(bv_neg, self);
  }
  CH_SYSTEM_OPERATOR_IMPL(operator+, (return make_system_op<Derived>(bv_add, lhs, rhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator-, (return make_system_op<Derived>(bv_sub, lhs, rhs)))
  CH_SYSTEM_OPERATOR_IMPL(operator*, (return make_system_op<Derived>(bv_mult, lhs, rhs)))

  CH_SYSTEM_OPERATOR_IMPL(operator/, (if constexpr (ch_signed_v<Derived>) {
                                         return make_system_op<Derived>(bv_sdiv, lhs, rhs);
                                      } else {
                                         return make_system_op<Derived>(bv_udiv, lhs, rhs);
                                      }))

  CH_SYSTEM_OPERATOR_IMPL(operator%, (if constexpr (ch_signed_v<Derived>) {
                                        return make_system_op<Derived>(bv_smod, lhs, rhs);
                                     } else {
                                        return make_system_op<Derived>(bv_umod, lhs, rhs);
                                     }))
};

CH_SYSTEM_OPERATOR(system_op_slice)
  template <typename R>
  std::add_const_t<R> slice(size_t start = 0) const {
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert(start + ch_width_v<R> <= N);
    R ret;
    auto& self = reinterpret_cast<const Derived&>(*this);
    system_accessor::write(ret, 0, self, start, ch_width_v<R>);
    return ret;
  }

  template <typename R>
  auto aslice(size_t start = 0) const {
    return this->slice<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  auto slice(size_t start = 0) const {
    return this->slice<T<M>>(start);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) const {
    return this->aslice<T<M>>(start);
  }

  template <typename R>
    auto sliceref(size_t start = 0) {
    auto& self = reinterpret_cast<const Derived&>(*this);
    return system_accessor::ref<R>(self, start);
  }

  template <typename R>
  auto asliceref(size_t start = 0) {
    return this->sliceref<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  auto sliceref(size_t start = 0) {
    return this->sliceref<T<M>>(start);
  }

  template <unsigned M>
  auto asliceref(size_t start = 0) {
    return this->asliceref<T<M>>(start);
  }
};

}
}
