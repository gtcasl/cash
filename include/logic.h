#pragma once

#include "system.h"

namespace ch {
namespace internal {  

lnodeimpl* createOpNode(ch_op op, uint32_t size, bool is_signed, const lnode& in);

lnodeimpl* createOpNode(ch_op op,
                        uint32_t size,
                        bool is_signed,
                        const lnode& lhs,
                        const lnode& rhs);

lnodeimpl* createRotateNode(const lnode& next, uint32_t dist, bool right);

lnodeimpl* createShuffleNode(const lnode& in, const std::vector<unsigned>& indices);

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_bit_base;
template <typename T> class ch_number_base;

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

using ch_bool = ch_uint<1>;

template <typename T>
inline constexpr bool is_bit_base_v = is_logic_type_v<T>
              && std::is_base_of_v<ch_bit_base<ch_logic_t<T>>, ch_logic_t<T>>;

template <typename T, unsigned N = ch_width_v<T>>
inline constexpr bool is_bit_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

///////////////////////////////////////////////////////////////////////////////

class logic_buffer : public lnode {
public:

  explicit logic_buffer(lnodeimpl* impl) : lnode(impl) {}

  explicit logic_buffer(const sdata_type& value) : lnode(value) {}

  logic_buffer(uint32_t size,
               const std::string& name,
               const sloc_getter& slg = sloc_getter());

  logic_buffer(uint32_t size,
               const logic_buffer& src,
               uint32_t src_offset,
               const std::string& name,
               const sloc_getter& slg = sloc_getter());

  const logic_buffer& source() const;

  logic_buffer& source();

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  lnodeimpl* clone() const;

  lnodeimpl* sliceref(size_t size, size_t start) const;

protected:

  void ensure_proxy();
};

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static auto& buffer(const T& obj) {
    assert(obj.__buffer().size() == ch_width_v<T>);
    return obj.__buffer();
  }

  template <typename T>
  static auto& source(const T& obj) {
    assert(obj.__buffer().size() == ch_width_v<T>);
    return obj.__buffer().source();
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(obj.__buffer().size() == ch_width_v<T>);
    return logic_buffer(std::move(obj.__buffer()));
  }

  template <typename U>
  static void assign(U& dst, const sdata_type& src) {
    assert(ch_width_v<U> == src.size());
    const_cast<logic_buffer&>(dst.__buffer()).write(0, src, 0, ch_width_v<U>);
  }

  template <typename U, typename V>
  static void assign(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.__buffer().size());
    assert(ch_width_v<V> == src.__buffer().size());
    const_cast<logic_buffer&>(dst.__buffer()).write(
          0, src.__buffer(), 0, ch_width_v<U>);
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    logic_accessor::assign(dst, src);
  }

  template <typename U, typename V>
  static void write(U& dst,
                    uint32_t dst_offset,
                    const V& src,
                    uint32_t src_offset,
                    uint32_t length) {
    const_cast<logic_buffer&>(dst.__buffer()).write(
          dst_offset, src.__buffer(), src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj) {
    assert(obj.__buffer().size() == ch_width_v<T>);
    auto data = obj.__buffer().clone();
    return T(logic_buffer(data));
  }

  template <typename R, typename T>
  static auto slice(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.__buffer().size() == ch_width_v<T>);
    logic_buffer buffer(ch_width_v<R>, "slice");
    buffer.write(0, obj.__buffer(), start, ch_width_v<R>);
    return std::add_const_t<R>(buffer);
  }

  template <typename R, typename T>
  static auto sliceref(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.__buffer().size() == ch_width_v<T>);
    auto data = obj.__buffer().sliceref(ch_width_v<R>, start);
    return R(logic_buffer(data));
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(obj.__buffer().size() == ch_width_v<T>);
    return R(obj.__buffer());
  }

  template <typename T>
  static const auto& name(const T& obj) {
    return obj.__buffer().name();
  }

  template <typename T, typename U>
  static auto do_eq(const T& obj, const U& other) {
    return obj.do_eq(other);
  }

  template <typename T, typename U>
  static auto do_ne(const T& obj, const U& other) {
    return obj.do_ne(other);
  }

  template <typename T>
  static auto do_not(const T& obj) {
    return obj.do_not();
  }

  template <typename T, typename U>
  static auto do_andl(const T& obj, const U& other) {
    return obj.do_andl(other);
  }

  template <typename T, typename U>
  static auto do_orl(const T& obj, const U& other) {
    return obj.do_orl(other);
  }

  template <typename R, typename T>
  static auto do_inv(const T& obj) {
    return obj.template do_inv<R>();
  }

  template <typename R, typename T, typename U>
  static auto do_and(const T& obj, const U& other) {
    return obj.template do_and<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_or(const T& obj, const U& other) {
    return obj.template do_or<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_xor(const T& obj, const U& other) {
    return obj.template do_xor<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_shl(const T& obj, const U& other) {
    return obj.template do_shl<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_shr(const T& obj, const U& other) {
    return obj.template do_shr<R>(other);
  }

  template <typename T>
  static auto do_andr(const T& obj) {
    return obj.do_andr();
  }

  template <typename T>
  static auto do_orr(const T& obj) {
    return obj.do_orr();
  }

  template <typename T>
  static auto do_xorr(const T& obj) {
    return obj.do_xorr();
  }

  template <typename T, typename U>
  static auto do_lt(const T& obj, const U& other) {
    return obj.do_lt(other);
  }

  template <typename T, typename U>
  static auto do_le(const T& obj, const U& other) {
    return obj.do_le(other);
  }

  template <typename T, typename U>
  static auto do_gt(const T& obj, const U& other) {
    return obj.do_gt(other);
  }

  template <typename T, typename U>
  static auto do_ge(const T& obj, const U& other) {
    return obj.do_ge(other);
  }

  template <typename R, typename T>
  static auto do_neg(const T& obj) {
    return obj.template do_neg<R>();
  }

  template <typename R, typename T, typename U>
  static auto do_add(const T& obj, const U& other) {
    return obj.template do_add<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_sub(const T& obj, const U& other) {
    return obj.template do_sub<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_mul(const T& obj, const U& other) {
    return obj.template do_mul<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_div(const T& obj, const U& other) {
    return obj.template do_div<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_mod(const T& obj, const U& other) {
    return obj.template do_mod<R>(other);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
auto to_logic(T&& obj) {
  if constexpr (is_logic_type_v<T> && ch_width_v<T> == N) {
    return std::move(obj);
  } else {
    return ch_bit<N>(std::forward<T>(obj));
  }
}

template <typename T>
auto get_lnode(const T& obj) {
  return logic_accessor::buffer(obj);
}

template <typename R, typename T>
auto to_lnode(const T& obj) {
  static_assert(std::is_constructible_v<R, T>, "invalid cast");
  if constexpr (is_logic_type_v<T>
             && (ch_width_v<T> == ch_width_v<R>)) {
    return get_lnode(obj);
  } else
  if constexpr (is_system_type_v<T>) {
    if constexpr (ch_width_v<T> == ch_width_v<R>) {
      return lnode(get_snode(obj));
    } else {
      ch_system_t<R> tmp(obj);
      return lnode(get_snode(tmp));
    }
  } else
  if constexpr (std::is_integral_v<T>) {
    ch_system_t<R> tmp(obj);
    return lnode(get_snode(tmp));
  } else {
    return get_lnode(R(obj));
  }
}

template <unsigned N, typename T>
auto to_lnode(const T& obj) {
  return to_lnode<ch_bit<N>>(obj);
}

template <typename R, typename T>
auto logic_cast(const T& obj) {
  static_assert(std::is_constructible_v<R, T>, "invalid cast");
  if constexpr ((is_signed_v<T> != is_signed_v<R> || !is_resizable_v<R>)) {
    return R(obj);
  } else
  if constexpr (is_logic_type_v<T>) {
    return obj.template as<ch_size_cast_t<R, ch_width_v<T>>>();
  } else
  if constexpr (is_system_type_v<T>) {
    return ch_size_cast_t<R, ch_width_v<T>>(logic_buffer(get_snode(obj)));
  } else
  if constexpr (std::is_integral_v<T>) {
    static const auto N = std::min(ch_width_v<T>, ch_width_v<R>);
    ch_size_cast_t<ch_system_t<T>, N> tmp(obj);
    return ch_size_cast_t<R, N>(logic_buffer(get_snode(tmp)));
  } else {
    return R(obj);
  }
}

template <typename T>
auto make_logic_type(const lnode& node) {
  return std::add_const_t<T>(logic_buffer(node.impl()));
}

template <ch_op op, typename A>
auto make_logic_op(const A& a) {
  auto node = createOpNode(op, 1, false, get_lnode(a));
  return make_logic_type<ch_bool>(node);
}

template <typename R, ch_op op, typename A>
auto make_logic_op(const A& a) {
  auto node = createOpNode(op, ch_width_v<R>, is_signed_v<R>, get_lnode(a));
  return make_logic_type<R>(node);
}

template <ch_op op, typename A, typename B>
auto make_logic_op(const A& a, const B& b) {
  auto node = createOpNode(op, 1, is_signed_v<A>, get_lnode(a), get_lnode(b));
  return make_logic_type<ch_bool>(node);
}

template <typename R, ch_op op, typename A, typename B>
auto make_logic_op(const A& a, const B& b) {
  auto node = createOpNode(op, ch_width_v<R>, is_signed_v<R>, get_lnode(a), get_lnode(b));
  return make_logic_type<R>(node);
}

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_INTERFACE(type) \
  template <typename __R> \
  auto as() const { \
    static_assert(ch::internal::is_logic_type_v<__R>, "invalid type"); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::logic_accessor::cast<std::add_const_t<__R>>(*self); \
  } \
  template <typename __R> \
  auto as() { \
    static_assert(ch::internal::is_logic_type_v<__R>, "invalid type"); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::logic_accessor::cast<__R>(*self); \
  } \
  auto as_bit() const { \
    return this->template as<ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->template as<ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_int() const { \
    return this->template as<ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->template as<ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_uint() const { \
    return this->template as<ch_uint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() { \
    return this->template as<ch_uint<type::traits::bitwidth>>(); \
  } \
  auto as_reg() { \
    CH_SOURCE_LOCATION(1); \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s; \
    *self = s; \
    return s; \
  } \
  auto as_reg(const type& init) { \
    CH_SOURCE_LOCATION(1); \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s(init); \
    *self = s; \
    return s; \
  } \
  auto ref() { \
    CH_SOURCE_LOCATION(1); \
    auto self = reinterpret_cast<type*>(this); \
    return ch::internal::logic_accessor::sliceref<type>(*self, 0); \
  } \
  auto clone() const { \
    CH_SOURCE_LOCATION(1); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::logic_accessor::clone(*self); \
  }

#define CH_LOGIC_OPERATOR1B_IMPL(type, op, method) \
  friend auto op(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method(self.value); \
  }

#define CH_LOGIC_OPERATOR1X_IMPL(type, op, method) \
  friend auto op(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(self.value); \
  }

#define CH_LOGIC_OPERATOR2B_IMPL(type, op, method) \
  friend auto op(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method(lhs.value, rhs.value); \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (!is_signed_v<type> && is_signed_v<U>) { \
        return op((const ch_signed_t<type>&)lhs.value, rhs); \
      } else { \
        auto _rhs = logic_cast<type>(rhs); \
        return ch::internal::logic_accessor::method(lhs.value, _rhs); \
      } \
    } else { \
      return op(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (is_signed_v<U> && !is_signed_v<type>) { \
        return op(lhs, (const ch_signed_t<type>&)rhs.value); \
      } else { \
        auto _lhs = logic_cast<type>(lhs); \
        return ch::internal::logic_accessor::method(_lhs, rhs.value); \
      } \
    } else { \
      return op(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

#define CH_LOGIC_OPERATOR2X_IMPL(type, op, method) \
  friend auto op(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (!is_signed_v<type> && is_signed_v<U>) { \
        return op((const ch_signed_t<type>&)lhs.value, rhs); \
      } else { \
        auto _rhs = logic_cast<type>(rhs); \
        return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
      } \
    } else { \
      return op(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (is_signed_v<U> && !is_signed_v<type>) { \
        return op(lhs, (const ch_signed_t<type>&)rhs.value); \
      } else { \
        auto _lhs = logic_cast<type>(lhs); \
        return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
      } \
    } else { \
      return op(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

#define CH_LOGIC_OPERATOR2Y_IMPL(type, op, method) \
  friend auto op(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _rhs = ch_logic_t<U>(rhs); \
      return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
    } else { \
      return op(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto op(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _lhs = logic_cast<type>(lhs); \
      return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
    } else { \
      return op(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

#define CH_LOGIC_FUNCTION1B_DECL(func) \
  template <typename T> auto func(const sloc_proxy<T>& self);

#define CH_LOGIC_FUNCTION1X_DECL(func) \
  template <unsigned R, typename T> auto func(const sloc_proxy<T>& self);

#define CH_LOGIC_FUNCTION1B_IMPL(type, func, method) \
  friend auto func(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method(self.value); \
  }

#define CH_LOGIC_FUNCTION1X_IMPL(type, func, method) \
  friend auto func(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(self.value); \
  } \
  template <unsigned R> \
  friend auto func(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<type>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::logic_accessor::method<type>(self.value); \
    } else { \
      return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(self.value); \
    } \
  }

#define CH_LOGIC_FUNCTION2B_DECL(func) \
  template <typename T> auto func(const sloc_proxy<T>& lhs, const sloc_proxy<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const sloc_proxy<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const U& lhs, const sloc_proxy<T>& rhs);

#define CH_LOGIC_FUNCTION2X_DECL(func) \
  template <typename T> auto func(const sloc_proxy<T>& lhs, const sloc_proxy<T>& rhs); \
  template <unsigned R, typename T> auto func(const sloc_proxy<T>& lhs, const sloc_proxy<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const sloc_proxy<T>& lhs, const U& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const sloc_proxy<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const U& lhs, const sloc_proxy<T>& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_resize_constructible_v<T, U>)> auto func(const U& lhs, const sloc_proxy<T>& rhs);

#define CH_LOGIC_FUNCTION2B_IMPL(type, func, method) \
  friend auto func(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method(lhs.value, rhs.value); \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (!is_signed_v<type> && is_signed_v<U>) { \
        return func((const ch_signed_t<type>&)lhs.value, rhs); \
      } else { \
        auto _rhs = logic_cast<type>(rhs); \
        return ch::internal::logic_accessor::method(lhs.value, _rhs); \
      } \
    } else { \
      return func(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (is_signed_v<U> && !is_signed_v<type>) { \
        return func(lhs, (const ch_signed_t<type>&)rhs.value); \
      } else { \
        auto _lhs = logic_cast<type>(lhs); \
        return ch::internal::logic_accessor::method(_lhs, rhs.value); \
      } \
    } else { \
      return func(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

#define CH_LOGIC_FUNCTION2X_IMPL(type, func, method) \
  friend auto func(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
  } \
  template <unsigned R> \
  friend auto func(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
      static_assert(ch_width_v<type> == R, "invalid output size"); \
      return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
    } else { \
      return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(lhs.value, rhs.value); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (!is_signed_v<type> && is_signed_v<U>) { \
        return func((const ch_signed_t<type>&)lhs.value, rhs); \
      } else { \
        auto _rhs = logic_cast<type>(rhs); \
        return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
      } \
    } else { \
      return func(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (!is_signed_v<type> && is_signed_v<U>) { \
        return func<R>((const ch_signed_t<type>&)lhs.value, rhs); \
      } else { \
        auto _rhs = logic_cast<type>(rhs); \
        if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
          static_assert(ch_width_v<type> == R, "invalid output size"); \
          return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
        } else { \
          return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(lhs.value, _rhs); \
        } \
      } \
    } else { \
      return func<R>(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (is_signed_v<U> && !is_signed_v<type>) { \
        return func(lhs, (const ch_signed_t<type>&)rhs.value); \
      } else { \
        auto _lhs = logic_cast<type>(lhs); \
        return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
      } \
    } else { \
      return func(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      if constexpr (is_signed_v<U> && !is_signed_v<type>) { \
        return func<R>(lhs, (const ch_signed_t<type>&)rhs.value); \
      } else { \
        auto _lhs = logic_cast<type>(lhs); \
        if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
          static_assert(ch_width_v<type> == R, "invalid output size"); \
          return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
        } else { \
          return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(_lhs, rhs.value); \
        } \
      } \
    } else { \
      return func<R>(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

#define CH_LOGIC_FUNCTION2Y_IMPL(type, func, method) \
  friend auto func(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
  } \
  template <unsigned R> \
  friend auto func(const sloc_proxy<type>& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
      static_assert(ch_width_v<type> == R, "invalid output size"); \
      return ch::internal::logic_accessor::method<type>(lhs.value, rhs.value); \
    } else { \
      return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(lhs.value, rhs.value); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _rhs = ch_logic_t<U>(rhs); \
      return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
    } else { \
      return func(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _rhs = ch_logic_t<U>(rhs); \
      if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
        static_assert(ch_width_v<type> == R, "invalid output size"); \
        return ch::internal::logic_accessor::method<type>(lhs.value, _rhs); \
      } else { \
        return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(lhs.value, _rhs); \
      } \
    } else { \
      return func<R>(lhs.value, ch_size_cast_t<type, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _lhs = logic_cast<type>(lhs); \
      return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
    } else { \
      return func(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_resize_constructible_v<type, U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (is_strictly_constructible_v<type, U>) { \
      auto _lhs = logic_cast<type>(lhs); \
      if constexpr (ch_width_v<type> == R || !is_resizable_v<type>) { \
        static_assert(ch_width_v<type> == R, "invalid output size"); \
        return ch::internal::logic_accessor::method<type>(_lhs, rhs.value); \
      } else { \
        return ch::internal::logic_accessor::method<ch_size_cast_t<type, R>>(_lhs, rhs.value); \
      } \
    } else { \
      return func<R>(ch_size_cast_t<type, ch_width_v<U>>(lhs), rhs.value); \
    } \
  }

}
}
