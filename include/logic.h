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

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_bitbase;
template <typename T> class ch_numbase;

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

using ch_bool = ch_uint<1>;

template <typename T>
inline constexpr bool is_bitbase_v = is_logic_type_v<T>
              && std::is_base_of_v<ch_bitbase<ch_logic_t<T>>, ch_logic_t<T>>;

namespace detail {
template <typename T, typename U, typename Enable = void>
struct is_logic_op_system_constructible1_impl : std::false_type {};

template <typename T, typename U>
struct is_logic_op_system_constructible1_impl<T, U, std::enable_if_t<(
  is_strictly_constructible_v<ch_size_cast_t<T, ch_width_v<U>>, U>)>> : std::true_type {};

template <typename T, typename U, typename Enable = void>
struct is_logic_op_system_constructible0_impl {
  using next = std::false_type;
};

template <typename T, typename U>
struct is_logic_op_system_constructible0_impl<T, U, std::enable_if_t<(
    is_system_type_v<U> && is_resizable_v<T>)>> {
  using next = is_logic_op_system_constructible1_impl<T, U>;    
};
}

template <typename T, typename U>
inline constexpr bool is_logic_op_constructible_v = 
    is_strictly_constructible_v<T, U> 
 || detail::is_logic_op_system_constructible0_impl<std::decay_t<T>, std::decay_t<U>>::next::value;

///////////////////////////////////////////////////////////////////////////////

class logic_buffer : public lnode {
public:
  using base = lnode;

  logic_buffer(const logic_buffer& other) : lnode(other) {}

  logic_buffer& operator=(const logic_buffer& other) {
    this->write(0, other, 0, other.size());
    return *this;
  }

  const logic_buffer& source() const;
  
  logic_buffer& source();

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  lnodeimpl* clone() const;

  lnodeimpl* sliceref(size_t size, size_t start) const;  

protected:

  explicit logic_buffer(lnodeimpl* impl) : lnode(impl) {}

  explicit logic_buffer(const sdata_type& value) : lnode(value) {}

  logic_buffer(uint32_t size, const std::string& name);

  logic_buffer(uint32_t size,
               const logic_buffer& src,
               uint32_t src_offset,
               const std::string& name);

  void ensure_proxy();

  template <typename... Args> friend auto make_logic_buffer(Args&&... args);
};

template <typename... Args>
auto make_logic_buffer(Args&&... args) {
  CH_API_ENTRY(1);
  return logic_buffer(std::forward<Args>(args)...);
}

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
    assert(ch_width_v<T> == obj.__buffer().size());
    return obj.__buffer().source();
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(ch_width_v<T> == obj.__buffer().size());
    return make_logic_buffer(std::move(obj.__buffer()));
  }

  template <typename T>
  static void assign(T& obj, const sdata_type& src) {
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(ch_width_v<T> == src.size());
    const_cast<logic_buffer&>(obj.__buffer()).write(0, src, 0, ch_width_v<T>);
  }

  template <typename T, typename U>
  static void assign(T& obj, const U& src) {
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(ch_width_v<U> == src.__buffer().size());
    const_cast<logic_buffer&>(obj.__buffer()) = src.__buffer();
  }

  template <typename T, typename U>
  static void move(T& obj, U&& src) {
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(ch_width_v<U> == src.__buffer().size());
    const_cast<logic_buffer&>(obj.__buffer()) = src.__buffer();
  }

  template <typename T, typename U>
  static void write(T& obj,
                    uint32_t dst_offset,
                    const U& src,
                    uint32_t src_offset,
                    uint32_t length) {
    assert(ch_width_v<T> == obj.__buffer().size());
    const_cast<logic_buffer&>(obj.__buffer()).write(
          dst_offset, src.__buffer(), src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj) {
    assert(ch_width_v<T> == obj.__buffer().size());
    auto data = obj.__buffer().clone();
    return T(make_logic_buffer(data));
  }

  template <typename R, typename T>
  static auto slice(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    auto buffer = make_logic_buffer(ch_width_v<R>, "slice");
    buffer.write(0, obj.__buffer(), start, ch_width_v<R>);
    return std::add_const_t<R>(buffer);
  }

  template <typename R, typename T>
  static auto sliceref(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    auto data = obj.__buffer().sliceref(ch_width_v<R>, start);
    return R(make_logic_buffer(data));
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
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

  template <typename R, typename T, typename U>
  static auto do_min(const T& obj, const U& other) {
    return obj.template do_min<R>(other);
  }

  template <typename R, typename T, typename U>
  static auto do_max(const T& obj, const U& other) {
    return obj.template do_max<R>(other);
  }

  template <typename R, typename T>
  static auto do_abs(const T& obj) {
    return obj.template do_abs<R>();
  }
};

///////////////////////////////////////////////////////////////////////////////

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
  if constexpr (std::is_integral_v<T> || std::is_enum_v<T>) {
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
auto logic_op_cast(const T& obj) {
  static_assert(std::is_constructible_v<R, T>, "invalid cast");
  if constexpr ((is_signed_v<T> != is_signed_v<R> || !is_resizable_v<R>)) {
    return R(obj);
  } else
  if constexpr (is_logic_type_v<T>) {
    return obj.template as<ch_size_cast_t<R, ch_width_v<T>>>();
  } else
  if constexpr (is_system_type_v<T>) {
    return ch_size_cast_t<R, ch_width_v<T>>(make_logic_buffer(get_snode(obj)));
  } else
  if constexpr (std::is_integral_v<T> || std::is_enum_v<T>) {
    static const auto N = std::min(ch_width_v<T>, ch_width_v<R>);
    ch_size_cast_t<ch_system_t<T>, N> tmp(obj);
    return ch_size_cast_t<R, N>(make_logic_buffer(get_snode(tmp)));
  } else {
    return R(obj);
  }
}

template <typename T>
auto make_logic_type(const lnode& node) {
  return std::add_const_t<T>(make_logic_buffer(node.impl()));
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
    CH_API_ENTRY(1); \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s; \
    *self = s; \
    return s; \
  } \
  auto as_reg(const type& init) { \
    CH_API_ENTRY(1); \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s(init); \
    *self = s; \
    return s; \
  } \
  auto ref() { \
    CH_API_ENTRY(1); \
    auto self = reinterpret_cast<type*>(this); \
    return ch::internal::logic_accessor::sliceref<type>(*self, 0); \
  } \
  auto clone() const { \
    CH_API_ENTRY(1); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::logic_accessor::clone(*self); \
  }

#define CH_LOGIC_OPERATOR1B_IMPL(base, op, method) \
  friend auto op(const base& self) { \
    CH_API_ENTRY(1); \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self); \
  }

#define CH_LOGIC_OPERATOR1X_IMPL(base, op, method) \
  friend auto op(const base& self) { \
    CH_API_ENTRY(1); \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self); \
  }

#define CH_LOGIC_OPERATOR2B_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return op(reinterpret_cast<const ch_signed_t<T>&>(_lhs), rhs); \
      } else { \
        auto _rhs = logic_op_cast<T>(rhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return op(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return op(lhs, reinterpret_cast<const ch_signed_t<T>&>(_rhs)); \
      } else { \
        auto _lhs = logic_op_cast<T>(lhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return op(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }

#define CH_LOGIC_OPERATOR2X_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return op(reinterpret_cast<const ch_signed_t<T>&>(_lhs), rhs); \
      } else { \
        auto _rhs = logic_op_cast<T>(rhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return op(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return op(lhs, reinterpret_cast<const ch_signed_t<T>&>(_rhs)); \
      } else { \
        auto _lhs = logic_op_cast<T>(lhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return op(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }

#define CH_LOGIC_OPERATOR2Y_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto _rhs = ch_logic_t<U>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs); \
      if constexpr (std::is_integral_v<U>) { \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, ch_width_v<U>>>(_lhs, _rhs); \
      } \
    } else { \
      return op(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }
  
#define CH_LOGIC_OPERATOR2Z_IMPL(base, op, method) \
  T& op(const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<T&>(*this); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    _lhs = logic_accessor::method<T>(ch_clone(_lhs), _rhs); \
    return _lhs; \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  T& op(const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<T&>(*this); \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      reinterpret_cast<ch_signed_t<T>&>(_lhs).op(rhs); \
    } else { \
      auto _rhs = logic_op_cast<T>(rhs); \
      _lhs = logic_accessor::method<T>(ch_clone(_lhs), _rhs); \
    } \
    return _lhs; \
  }

#define CH_LOGIC_FUNCTION1B_DECL(base, func) \
  template <typename T> auto func(const base<T>& self);

#define CH_LOGIC_FUNCTION1X_DECL(base, func) \
  template <unsigned R, typename T> auto func(const base<T>& self);

#define CH_LOGIC_FUNCTION2B_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs);

#define CH_LOGIC_FUNCTION2X_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <unsigned R, typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs);

#define CH_LOGIC_FUNCTION1B_IMPL(base, func, method) \
  friend auto func(const base& self) { \
    CH_API_ENTRY(1); \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self); \
  }

#define CH_LOGIC_FUNCTION1X_IMPL(base, func, method) \
  friend auto func(const base& self) { \
    CH_API_ENTRY(1); \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self); \
  } \
  template <unsigned R> \
  friend auto func(const base& self) { \
    CH_API_ENTRY(1); \
    auto& _self = reinterpret_cast<const T&>(self); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_self); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_self); \
    } \
  }

#define CH_LOGIC_FUNCTION2B_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func(reinterpret_cast<const ch_signed_t<T>&>(_lhs), rhs); \
      } else { \
        auto _rhs = logic_op_cast<T>(rhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return func(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func(lhs, reinterpret_cast<const ch_signed_t<T>&>(_rhs)); \
      } else { \
        auto _lhs = logic_op_cast<T>(lhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return func(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }

#define CH_LOGIC_FUNCTION2X_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_lhs, _rhs); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func(reinterpret_cast<const ch_signed_t<T>&>(_lhs), rhs); \
      } else { \
        auto _rhs = logic_op_cast<T>(rhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return func(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func<R>(reinterpret_cast<const ch_signed_t<T>&>(_lhs), rhs); \
      } else { \
        auto _rhs = logic_op_cast<T>(rhs); \
        if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
          static_assert(ch_width_v<T> == R, "invalid output size"); \
          return logic_accessor::method<T>(_lhs, _rhs); \
        } else { \
          return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
        } \
      } \
    } else { \
      return func<R>(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func(lhs, reinterpret_cast<const ch_signed_t<T>&>(_rhs)); \
      } else { \
        auto _lhs = logic_op_cast<T>(lhs); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } \
    } else { \
      return func(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
        return func<R>(lhs, reinterpret_cast<const ch_signed_t<T>&>(_rhs)); \
      } else { \
        auto _lhs = logic_op_cast<T>(lhs); \
        if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
          static_assert(ch_width_v<T> == R, "invalid output size"); \
          return logic_accessor::method<T>(_lhs, _rhs); \
        } else { \
          return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
        } \
      } \
    } else { \
      return func<R>(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }

#define CH_LOGIC_FUNCTION2Y_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_lhs, _rhs); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto _rhs = ch_logic_t<U>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs); \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    CH_API_ENTRY(1); \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = ch_logic_t<U>(rhs); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
      } \
    } else { \
      return func<R>(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs); \
      if constexpr (std::is_integral_v<U>) { \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, ch_width_v<U>>>(_lhs, _rhs); \
      } \
    } else { \
      return func(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    CH_API_ENTRY(1); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return logic_accessor::method<T>(_lhs, _rhs); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs); \
      } \
    } else { \
      return func<R>(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs); \
    } \
  }

}
}
