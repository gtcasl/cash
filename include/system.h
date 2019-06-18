#pragma once

#include "traits.h"

namespace ch {
namespace internal {

template <unsigned N> class ch_scbit;
template <unsigned N> class ch_scint;
template <unsigned N> class ch_scuint;

using ch_scbool = ch_scuint<1>;

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
  explicit system_buffer(const sdata_type& data);

  system_buffer(sdata_type&& data);

  system_buffer(uint32_t size, const std::string& name);

  system_buffer(uint32_t size,
                const system_buffer_ptr& buffer,
                uint32_t offset,
                const std::string& name);

  system_buffer(const system_buffer& other);

  system_buffer(system_buffer&& other);

  virtual ~system_buffer() {}

  system_buffer& operator=(const system_buffer& other);

  system_buffer& operator=(system_buffer&& other);

  virtual const sdata_type& data() const;

  const auto& source() const {
    return source_;
  }

  const auto& value() const {
    return value_;
  }

  auto offset() const {
    return offset_;
  }

  auto size() const {
    return size_;
  }

  auto name() const {
    return name_;
  }

  std::string to_verilog() const;

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

  system_buffer_ptr source_;
  mutable sdata_type value_;
  uint32_t offset_;
  uint32_t size_;
  std::string name_;
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
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return obj.__buffer();
  }

  template <typename T>
  static const auto& data(const T& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return obj.__buffer()->data();
  }

  template <typename T>
  static const auto& source(const T& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return obj.__buffer()->source();
  }

  template <typename T>
  static auto copy(const T& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return make_system_buffer(*obj.__buffer());
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return make_system_buffer(std::move(*obj.__buffer()));
  }

  template <typename T>
  static std::string to_verilog(const T& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return obj.__buffer()->to_verilog();
  }

  template <typename U>
  static void assign(U& dst, const sdata_type& src) {
    assert(ch_width_v<U> == src.size());
    assert(ch_width_v<U> == dst.__buffer()->size());
    dst.__buffer()->write(0, src, 0, ch_width_v<U>);
  }

  template <typename U, typename V>
  static void assign(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.__buffer()->size());
    assert(ch_width_v<V> == src.__buffer()->size());
    *dst.__buffer() = *src.__buffer();
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.__buffer()->size());
    *dst.__buffer() = std::move(*src.__buffer());
  }

  template <typename U, typename V>
  static void write(U& dst,
                    uint32_t dst_offset,
                    const V& src,
                    uint32_t src_offset,
                    uint32_t length) {
    auto data = src.__buffer()->data();
    dst.__buffer()->write(dst_offset, data, src_offset, length);
  }

  template <typename R, typename T>
  static auto sliceref(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return R(make_system_buffer(ch_width_v<R>, obj.__buffer(), start, "sliceref"));
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(obj.__buffer()->size() == ch_width_v<T>);
    return R(obj.__buffer());
  }
};

///////////////////////////////////////////////////////////////////////////////

sdata_type sdata_from_fill(uint64_t value, uint32_t size, uint32_t count);

template <typename T>
auto get_snode(const T& obj) {
  return system_accessor::data(obj);
}

typedef void (*SystemFunc1)(block_type* out,
                            uint32_t out_size,
                            const block_type* in,
                            uint32_t in_size);

typedef void (*SystemFunc2)(block_type* out,
                            uint32_t out_size,
                            const block_type* lhs,
                            uint32_t lhs_size,
                            const block_type* rhs,
                            uint32_t rhs_size);

typedef void (*SystemFunc3)(block_type* out,
                            uint32_t out_size,
                            const block_type* lhs,
                            uint32_t lhs_size,
                            uint32_t rhs);

template <typename R, typename A>
auto make_system_op(SystemFunc1 func, const A& in) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(in);
  func(ret.words(), ch_width_v<R>, u.words(), ch_width_v<A>);
  return std::add_const_t<R>(make_system_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_system_op(SystemFunc2 func, const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(lhs);
  auto& v = system_accessor::data(rhs);
  func(ret.words(), ch_width_v<R>, u.words(), ch_width_v<A>, v.words(), ch_width_v<B>);
  return std::add_const_t<R>(make_system_buffer(std::move(ret)));
}

template <typename R, typename A, typename B>
auto make_system_op(SystemFunc3 func, const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto& u = system_accessor::data(lhs);
  auto v = static_cast<uint32_t>(rhs);
  func(ret.words(), ch_width_v<R>, u.words(), u.size(), v);
  return std::add_const_t<R>(make_system_buffer(std::move(ret)));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_SYSTEM_INTERFACE(type) \
  template <typename __R> \
  auto as() const { \
    static_assert(ch::internal::is_system_type_v<__R>, "invalid type"); \
    return ch::internal::system_accessor::cast<std::add_const_t<__R>>(*this); \
  } \
  template <typename __R> \
  auto as() { \
    static_assert(ch::internal::is_system_type_v<__R>, "invalid type"); \
    return ch::internal::system_accessor::cast<__R>(*this); \
  } \
  auto as_scbit() const { \
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  auto as_scbit() { \
    return this->as<ch_scbit<type::traits::bitwidth>>(); \
  } \
  auto as_scint() const { \
    return this->as<ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_scint() { \
    return this->as<ch_scint<type::traits::bitwidth>>(); \
  } \
  auto as_scuint() const { \
    return this->as<ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto as_scuint() { \
    return this->as<ch_scuint<type::traits::bitwidth>>(); \
  } \
  auto ref() { \
    return ch::internal::system_accessor::sliceref<type>(*this, 0); \
  }

#define CH_SYSTEM_OPERATOR_IMPL(type, op, body) \
  friend auto op(const type& lhs, const type& rhs) { \
    CH_REM body; \
  } \
  template <typename __U, \
            CH_REQUIRE(is_strictly_constructible_v<type, __U>)> \
  friend auto op(const type& lhs, const __U& _rhs) { \
    type rhs(_rhs); \
    CH_REM body; \
  } \
  template <typename __U, \
            CH_REQUIRE(is_strictly_constructible_v<type, __U>)> \
  friend auto op(const __U& _lhs, const type& rhs) { \
    type lhs(_lhs); \
    CH_REM body; \
  }

#define CH_SYSTEM_OP_EQUALITY(type) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator==, ( \
    auto lhs_w = system_accessor::data(lhs).words(); \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return bv_eq<false, block_type, ClearBitAccessor<block_type>>(lhs_w, N, rhs_w, N)); \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator!=, ( \
    auto lhs_w = system_accessor::data(lhs).words(); \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return !bv_eq<false, block_type, ClearBitAccessor<block_type>>(lhs_w, N, rhs_w, N)); \
  )

#define CH_SYSTEM_OP_LOGICAL(type) \
  friend auto operator&&(const type& lhs, const type& rhs) { \
    auto lhs_w = system_accessor::data(lhs).words(); \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return bv_orr(lhs_w, N) && bv_orr(rhs_w, N); \
  } \
  friend auto operator&&(const type& lhs, bool rhs) { \
    auto lhs_w = system_accessor::data(lhs).words(); \
    return bv_orr(lhs_w, N) && rhs; \
  } \
  friend auto operator&&(bool lhs, const type& rhs) { \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return lhs && bv_orr(rhs_w, N); \
  } \
  friend auto operator||(const type& lhs, const type& rhs) { \
    auto lhs_w = system_accessor::data(lhs).words(); \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return bv_orr(lhs_w, N) || bv_orr(rhs_w, N); \
  } \
  friend auto operator||(const type& lhs, bool rhs) { \
    auto lhs_w = system_accessor::data(lhs).words(); \
    return bv_orr(lhs_w, N) || rhs; \
  } \
  friend auto operator||(bool lhs, const type& rhs) { \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return lhs || bv_orr(rhs_w, N); \
  } \
  friend auto operator!(const type& self) { \
    return !bv_orr(system_accessor::data(self).words(), N); \
  }

#define CH_SYSTEM_OP_BITWISE(type) \
  friend auto operator~(const type& self) { \
    auto func = bv_inv<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>; \
    return make_system_op<type>(func, self); \
  } \
  CH_SYSTEM_OPERATOR_IMPL(type, operator&, (return make_system_op<type>(bv_and<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, lhs, rhs))) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator|, (return make_system_op<type>(bv_or<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, lhs, rhs))) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator^, (return make_system_op<type>(bv_xor<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, lhs, rhs))) \

#define CH_SYSTEM_OP_SHIFT(type) \
  template <typename U, \
            CH_REQUIRE(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)> \
  friend auto operator<<(const type& lhs, const U& rhs) { \
    static_assert(ch_width_v<U> <= 32, "invalid size"); \
    return make_system_op<type, type, ch_scbit<ch_width_v<U>>>( \
      bv_shl, lhs, rhs \
    ); \
  } \
  template <typename U, \
            CH_REQUIRE(std::is_convertible_v<U, ch_scbit<ch_width_v<U>>>)> \
  friend auto operator>>(const type& lhs, const U& rhs) { \
    static_assert(ch_width_v<U> <= 32, "invalid size"); \
    return make_system_op<type, type, ch_scbit<ch_width_v<U>>>( \
      bv_shr<ch_signed_v<type>>, lhs, rhs \
    ); \
  } \

#define CH_SYSTEM_OP_CAST(type) \
  template <typename U, \
            CH_REQUIRE(std::is_integral_v<U>)> \
  explicit operator U() const { \
    static_assert(bitwidth_v<U> >= type::traits::bitwidth, "invalid size"); \
    auto ret = static_cast<U>(system_accessor::data(reinterpret_cast<const type&>(*this))); \
    if constexpr(ch_signed_v<type> && (bitwidth_v<U> > type::traits::bitwidth)) { \
      return sign_ext(ret, type::traits::bitwidth); \
    } else { \
      return ret; \
    } \
  } \
  explicit operator sdata_type() const { \
    return system_accessor::data(reinterpret_cast<const type&>(*this)); \
  }

#define CH_SYSTEM_OP_RELATIONAL(type) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator<, ( \
    auto lhs_w = system_accessor::data(lhs).words(); \
    auto rhs_w = system_accessor::data(rhs).words(); \
    return bv_lt<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>(lhs_w, N, rhs_w, N);) \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator>=, (return !(lhs < rhs))) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator>, (return (rhs < lhs))) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator<=, (return !(rhs < lhs))) \

#define CH_SYSTEM_OP_ARITHMETIC(type) \
  friend auto operator-(const type& self) { \
    return make_system_op<type>(bv_neg<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, self); \
  } \
  CH_SYSTEM_OPERATOR_IMPL(type, operator+, ( \
    return make_system_op<type>(bv_add<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, lhs, rhs)) \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator-, ( \
    return make_system_op<type>(bv_sub<ch_signed_v<type>, block_type, ClearBitAccessor<block_type>>, lhs, rhs)) \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator*, ( \
    return make_system_op<type>(bv_mul<ch_signed_v<type>>, lhs, rhs)) \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator/, ( \
    return make_system_op<type>(bv_div<ch_signed_v<type>>, lhs, rhs);) \
  ) \
  CH_SYSTEM_OPERATOR_IMPL(type, operator%, ( \
    return make_system_op<type>(bv_mod<ch_signed_v<type>>, lhs, rhs);) \
  )

#define CH_SYSTEM_OP_SLICE(type) \
  template <typename R> \
  auto slice(size_t start = 0) const { \
    static_assert(ch_width_v<R> <= N, "invalid size"); \
    assert(start + ch_width_v<R> <= N); \
    R ret; \
    auto& self = reinterpret_cast<const type&>(*this); \
    system_accessor::write(ret, 0, self, start, ch_width_v<R>); \
    return std::add_const_t<R>(ret); \
  } \
  template <typename R> \
  auto aslice(size_t start = 0) const { \
    return this->slice<R>(start * ch_width_v<R>); \
  } \
  template <unsigned M> \
  auto slice(size_t start = 0) const { \
    return this->slice<type<M>>(start); \
  } \
  template <unsigned M> \
  auto aslice(size_t start = 0) const { \
    return this->aslice<type<M>>(start); \
  } \
  template <typename R> \
    auto sliceref(size_t start = 0) { \
    auto& self = reinterpret_cast<const type&>(*this); \
    return system_accessor::sliceref<R>(self, start); \
  } \
  template <typename R> \
  auto asliceref(size_t start = 0) { \
    return this->sliceref<R>(start * ch_width_v<R>); \
  } \
  template <unsigned M> \
  auto sliceref(size_t start = 0) { \
    return this->sliceref<type<M>>(start); \
  } \
  template <unsigned M> \
  auto asliceref(size_t start = 0) { \
    return this->asliceref<type<M>>(start); \
  }

}
}
