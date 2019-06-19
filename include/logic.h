#pragma once

#include "system.h"
#include "lnode.h"

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

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

using ch_bool = ch_uint<1>;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

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

template <typename R, bool preserve = false, typename T>
auto to_lnode(const T& obj) {
  if constexpr (is_logic_type_v<T>) {
    if constexpr (preserve || ch_width_v<T> <= ch_width_v<R>) {
      if constexpr (is_object_type_v<R>
                 && ch_width_v<T> < ch_width_v<R>
                 && ch_signed_v<T> != ch_signed_v<R>) {
        return lnode(createOpNode(ch_op::pad, ch_width_v<R>, ch_signed_v<T>, get_lnode(obj)));
      } else {
        return get_lnode(obj);
      }
    } else {
      logic_buffer tmp(ch_width_v<R>, "slice");
      tmp.write(0, get_lnode(obj), 0, ch_width_v<R>);
      return tmp;
    }
  } else
  if constexpr (is_system_type_v<T>) {
    if constexpr (preserve || ch_width_v<T> <= ch_width_v<R>) {
      if constexpr (is_object_type_v<R>
                 && ch_width_v<T> < ch_width_v<R>
                 && ch_signed_v<T> != ch_signed_v<R>) {
        sdata_type tmp(ch_width_v<R>);
        bv_pad<ch_signed_v<T>>(tmp.words(), ch_width_v<R>, system_accessor::data(obj).words(), ch_width_v<T>);
        return lnode(tmp);
      } else {
        return lnode(get_snode(obj));
      }
    } else {
      sdata_type tmp(ch_width_v<R>);
      tmp.copy(0, get_snode(obj), 0, ch_width_v<R>);
      return lnode(tmp);
    }
  } else
  if constexpr (is_scbit_convertible_v<T, ch_width_v<R>>) {
    if constexpr (preserve
               && ch_width_v<T> < ch_width_v<R>
               && ch_signed_v<T> == ch_signed_v<R>) {
      return lnode(get_snode(ch_scbit<ch_width_v<T>>(obj)));
    } else {
      return lnode(get_snode(ch_scbit<ch_width_v<R>>(obj)));
    }
  } else {
    return get_lnode(R(obj));
  }
}

template <unsigned N, typename T>
auto to_lnode(const T& obj) {
  return to_lnode<ch_bit<N>>(obj);
}

template <typename R, typename T>
auto logic_operand(const T& obj) {
  static_assert(!is_logic_type_v<T>);
  if constexpr (is_system_type_v<T>) {
    return size_cast_t<R, ch_width_v<T>>(logic_buffer(get_snode(obj)));
  } else
  if constexpr (std::is_integral_v<T>) {
    static const auto N = std::min(ch_width_v<T>, ch_width_v<R>);
    return size_cast_t<R, N>(logic_buffer(get_snode(ch_scbit<N>(obj))));
  } else {
    return R(obj);
  }
}

template <typename T>
auto make_type(const lnode& node) {
  return std::add_const_t<T>(logic_buffer(node.impl()));
}

template <ch_op op, bool Signed, typename R, typename A>
auto make_logic_op(const A& a) {
  if (CH_OP_IS_BOOLEAN(op)) {
    return make_type<R>(createOpNode(op, ch_width_v<R>, Signed, to_lnode<R, true>(a)));
  } else {
    return make_type<R>(createOpNode(op, ch_width_v<R>, Signed, to_lnode<R, false>(a)));
  }
}

template <ch_op op, bool Signed, typename R, typename A, typename B>
auto make_logic_op(const A& a, const B& b) {
  if constexpr (op_flags::shift == CH_OP_CLASS(op)) {
    return make_type<R>(createOpNode(
        op, ch_width_v<R>, Signed, to_lnode<B, true>(a), to_lnode<ch_logic_t<B>, true>(b)));
  } else {
    return make_type<R>(createOpNode(
        op, ch_width_v<R>, Signed, to_lnode<B, true>(a), to_lnode<A, true>(b)));
  }
}

template <typename R, typename T>
using logic_op_ret = std::conditional_t<is_object_type_v<T>
                                     && ((ch_width_v<T> > ch_width_v<R>)
                                      || (ch_width_v<T> == ch_width_v<R> && ch_signed_v<T>)),
                                        ch_logic_t<T>, R>;

template <unsigned R, typename T>
using logic_func_ret = std::conditional_t<R, size_cast_t<T, R>, T>;

template <typename T> class ch_bit_base;

template <typename T>
inline constexpr bool is_bit_base_v = is_logic_type_v<T>
              && std::is_base_of_v<ch_bit_base<ch_logic_t<T>>, ch_logic_t<T>>;

template <typename T, unsigned N = ch_width_v<T>>
inline constexpr bool is_bit_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_INTERFACE(type) \
  template <typename __R> \
  auto as() const { \
  static_assert(ch::internal::is_logic_type_v<__R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<std::add_const_t<__R>>((const type&)*this); \
  } \
  template <typename __R> \
  auto as() { \
    static_assert(ch::internal::is_logic_type_v<__R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<__R>((type&)*this); \
  } \
  auto as_bit() const { \
    return this->as<ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->as<ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_int() const { \
    return this->as<ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->as<ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_uint() const { \
    return this->as<ch_uint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() { \
    return this->as<ch_uint<type::traits::bitwidth>>(); \
  } \
  auto as_reg() { \
    CH_SOURCE_LOCATION(1); \
    ch_reg<type> s; \
    (*this) = s; \
    return s; \
  } \
  auto as_reg(const type& init) { \
    CH_SOURCE_LOCATION(1); \
    ch_reg<type> s(init); \
    (*this) = s; \
    return s; \
  } \
  auto ref() { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::sliceref<type>((type&)*this, 0); \
  } \
  auto clone() const { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::clone((const type&)*this); \
  }

#define CH_LOGIC_OPERATOR1_IMPL(type, opcode, op, method) \
  friend auto op(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(self.value); \
    } else { \
      return ch::internal::logic_accessor::method<type>(self.value); \
    } \
  }

#define CH_LOGIC_OPERATOR2_IMPL(type, opcode, op, method) \
  template <typename U, \
            CH_REQUIRE(is_bit_base_v<U>)> \
  friend auto op(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(lhs.value, rhs); \
    } else { \
      return ch::internal::logic_accessor::method<logic_op_ret<type, U>>(lhs.value, rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(!is_bit_base_v<U>)> \
  friend auto op(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    static_assert(is_strictly_constructible_v<type, U> || is_system_type_v<U>, "invalid type"); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(lhs.value, rhs); \
    } else { \
      return ch::internal::logic_accessor::method<logic_op_ret<type, U>>(lhs.value, rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(!is_bit_base_v<U>)> \
  friend auto op(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    static_assert(is_strictly_constructible_v<type, U> || is_system_type_v<U>, "invalid type"); \
    auto _lhs = logic_operand<type>(lhs); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(_lhs, rhs.value); \
    } else { \
      return ch::internal::logic_accessor::method<logic_op_ret<type, U>>(_lhs, rhs.value); \
    } \
  }

#define CH_LOGIC_FUNCTION1_DECL(func) \
  template <unsigned R = 0, typename T> auto func(const sloc_proxy<T>& self);

#define CH_LOGIC_FUNCTION1_IMPL(type, opcode, func, method) \
  template <unsigned R = 0> \
  friend auto func(const sloc_proxy<type>& self) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(self.value); \
    } else { \
      return ch::internal::logic_accessor::method<logic_func_ret<R, type>>(self.value); \
    } \
  }

#define CH_LOGIC_FUNCTION2_DECL(func) \
  template <unsigned R = 0, typename T> auto func(const sloc_proxy<T>& lhs, const sloc_proxy<T>& rhs); \
  template <unsigned R = 0, typename T, typename U> auto func(const sloc_proxy<T>& lhs, const U& rhs); \
  template <unsigned R = 0, typename T, typename U> auto func(const U& lhs, const sloc_proxy<T>& rhs);

#define CH_LOGIC_FUNCTION2_IMPL(type, opcode, func, method) \
  template <unsigned R = 0, typename U, \
            CH_REQUIRE(is_bit_base_v<U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(lhs.value, rhs); \
    } else { \
      return ch::internal::logic_accessor::method<logic_func_ret<R, type>>(lhs.value, rhs); \
    } \
  } \
  template <unsigned R = 0, typename U, \
            CH_REQUIRE(!is_bit_base_v<U>)> \
  friend auto func(const sloc_proxy<type>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    static_assert(is_strictly_constructible_v<type, U> || is_system_type_v<U>, "invalid type"); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(lhs.value, rhs); \
    } else { \
      return ch::internal::logic_accessor::method<logic_func_ret<R, type>>(lhs.value, rhs); \
    } \
  } \
  template <unsigned R = 0, typename U, \
            CH_REQUIRE(!is_bit_base_v<U>)> \
  friend auto func(const U& lhs, const sloc_proxy<type>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    static_assert(is_strictly_constructible_v<type, U> || is_system_type_v<U>, "invalid type"); \
    auto _lhs = logic_operand<type, U>(lhs); \
    if constexpr (CH_OP_IS_BOOLEAN(opcode)) { \
      return ch::internal::logic_accessor::method(_lhs, rhs.value); \
    } else { \
      return ch::internal::logic_accessor::method<logic_func_ret<R, type>>(_lhs, rhs.value); \
    } \
  }

#define CH_LOGIC_OP_SLICE(type) \
  template <typename R> \
  auto slice(size_t start = 0) const { \
    static_assert(ch_width_v<R> <= ch_width_v<type>, "invalid size"); \
    assert(start + ch_width_v<R> <= ch_width_v<type>); \
    auto self = reinterpret_cast<const type*>(this); \
    return logic_accessor::slice<R>(*self, start); \
  } \
  template <unsigned M> \
  auto slice(size_t start = 0) const { \
    CH_SOURCE_LOCATION(1); \
    return this->slice<size_cast_t<type,M>>(start); \
  } \
  template <typename R> \
  auto aslice(size_t start = 0) const { \
    CH_SOURCE_LOCATION(1); \
    return this->slice<R>(start * ch_width_v<R>); \
  } \
  template <unsigned M> \
  auto aslice(size_t start = 0) const { \
    CH_SOURCE_LOCATION(1); \
    return this->aslice<size_cast_t<type,M>>(start); \
  } \
  template <typename R> \
  auto sliceref(size_t start = 0) { \
    static_assert(ch_width_v<R> <= ch_width_v<type>, "invalid size"); \
    assert(start + ch_width_v<R> <= ch_width_v<type>); \
    CH_SOURCE_LOCATION(1); \
    auto self = reinterpret_cast<type*>(this); \
    return logic_accessor::sliceref<R>(*self, start); \
  } \
  template <unsigned M> \
  auto sliceref(size_t start = 0) { \
    CH_SOURCE_LOCATION(1); \
    return this->sliceref<size_cast_t<type,M>>(start); \
  } \
  template <typename R> \
  auto asliceref(size_t start = 0) { \
    CH_SOURCE_LOCATION(1); \
    return this->sliceref<R>(start * ch_width_v<R>); \
  } \
  template <unsigned M> \
  auto asliceref(size_t start = 0) { \
    CH_SOURCE_LOCATION(1); \
    return this->asliceref<size_cast_t<type,M>>(start); \
  }
}
}
