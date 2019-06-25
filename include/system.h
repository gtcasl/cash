#pragma once

#include "lnode.h"

namespace ch {
namespace internal {

template <typename T> class ch_sbit_base;
template <typename T> class ch_snumber_base;

template <unsigned N> class ch_sbit;
template <unsigned N> class ch_sint;
template <unsigned N> class ch_suint;

using ch_sbool = ch_suint<1>;

template <typename T>
inline constexpr bool is_sbit_base_v = is_system_type_v<T>
              && std::is_base_of_v<ch_sbit_base<ch_system_t<T>>, ch_system_t<T>>;

template <typename T, unsigned N>
inline constexpr bool is_sbit_convertible_v = std::is_constructible_v<ch_sbit<N>, T>;

template <unsigned N, typename T>
auto to_system(T&& obj) {
  if constexpr (is_system_type_v<T> && ch_width_v<T> == N) {
    return std::move(obj);
  } else {
    return ch_sbit<N>(std::forward<T>(obj));
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

  template <unsigned N, typename T>
  static auto resize(const T& obj) {
    assert(obj.__buffer()->size() == ch_width_v<T>);
    assert(ch_width_v<T> <= N);
    if constexpr (ch_width_v<T> < N) {
      sdata_type tmp(N);
      bv_pad<is_signed_v<T>>(tmp.words(), N, system_accessor::data(obj).words(), ch_width_v<T>);
      return make_system_buffer(std::move(tmp));
    } else {
      return make_system_buffer(*obj.__buffer());
    }
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
  static auto slice(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.__buffer()->size() == ch_width_v<T>);
    R ret;
    system_accessor::write(ret, 0, obj, start, ch_width_v<R>);
    return std::add_const_t<R>(ret);
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

  template <typename T>
  static std::ostream& do_print(const T& obj, std::ostream& out) {
    return obj.do_print(out);
  }
};

///////////////////////////////////////////////////////////////////////////////

sdata_type sdata_from_fill(uint64_t value, uint32_t size, uint32_t count);

template <typename T>
auto& get_snode(const T& obj) {
  return system_accessor::data(obj);
}

template <typename R, typename T>
auto system_cast(const T& obj) {
  static_assert(std::is_constructible_v<R, T>, "invalid cast");
  if constexpr ((is_signed_v<T> != is_signed_v<R>) || !is_resizable_v<R>) {
    return R(obj);
  } else
  if constexpr (is_system_type_v<T>) {
    return obj.template as<ch_size_cast_t<R, ch_width_v<T>>>();
  } else
  if constexpr (std::is_integral_v<T>) {
    static const auto N = std::min(ch_width_v<T>, ch_width_v<R>);
    return ch_size_cast_t<R, N>(obj);
  } else {
    return R(obj);
  }
}

#define CH_OP_FUNC(value, func) \
  if constexpr (op == value) { \
    return func<block_type>; \
  }

#define CH_OP_FUNC_S(value, func) \
  if constexpr (op == value) { \
    return func<is_signed_v<R>, block_type>; \
  }

#define CH_OP_FUNC_X(value, func) \
  if constexpr (op == value) { \
    return func<sign_enable, block_type, StaticBitAccessor<block_type, resize_enable, sign_enable>>; \
  }

template <ch_op op, typename A>
auto get_op_function1() {
  CH_OP_FUNC(ch_op::notl, bv_not)
  else CH_OP_FUNC(ch_op::andr, bv_andr)
  else CH_OP_FUNC(ch_op::orr, bv_orr)
  else CH_OP_FUNC(ch_op::xorr, bv_xorr)
}

template <typename R, ch_op op, typename A>
auto get_op_function1() {
  static const bool sign_enable = is_signed_v<R>;
  static const bool resize_enable = (ch_width_v<R> > ch_width_v<A>);
  CH_OP_FUNC_X(ch_op::inv, bv_inv)
  else CH_OP_FUNC_X(ch_op::neg, bv_neg)
  else CH_OP_FUNC_S(ch_op::pad, bv_pad)
}

template <ch_op op, typename A, typename B>
auto get_op_function2() {
  static const auto resize_type = CH_OP_RESIZE(op);
  static_assert(op_flags::resize_src == resize_type, "invalid type");
  static const bool sign_enable = is_signed_v<A>;
  static const bool resize_enable = (ch_width_v<A> != ch_width_v<B>);
  CH_OP_FUNC_X(ch_op::eq, bv_eq)
  else CH_OP_FUNC_X(ch_op::lt, bv_lt)
}

template <typename R, ch_op op, typename A, typename B>
auto get_op_function2() {
  static const auto resize_type = CH_OP_RESIZE(op);
  static const bool sign_enable = is_signed_v<R>;
  if constexpr (0 != (int)resize_type) {
    static_assert(op_flags::resize_dst == resize_type, "invalid type");
    static const bool resize_enable = (ch_width_v<A> < ch_width_v<R>)
                                   || (ch_width_v<B> < ch_width_v<R>);
    CH_OP_FUNC_X(ch_op::andb, bv_and)
    else CH_OP_FUNC_X(ch_op::orb, bv_or)
    else CH_OP_FUNC_X(ch_op::xorb, bv_xor)
    else CH_OP_FUNC_X(ch_op::add, bv_add)
    else CH_OP_FUNC_X(ch_op::sub, bv_sub)
  } else {
    CH_OP_FUNC(ch_op::andl, bv_andl)
    else CH_OP_FUNC(ch_op::orl, bv_orl)
    else CH_OP_FUNC(ch_op::shl, bv_shl)
    else CH_OP_FUNC_S(ch_op::shr, bv_shr)
    else CH_OP_FUNC_S(ch_op::mul, bv_mul)
    else CH_OP_FUNC_S(ch_op::div, bv_div)
    else CH_OP_FUNC_S(ch_op::mod, bv_mod)
  }
}

template <typename T>
auto make_system_type(sdata_type&& sdata) {
  return std::add_const_t<T>(make_system_buffer(std::forward<sdata_type>(sdata)));
}

template <typename T>
auto make_system_type(const sdata_type& sdata) {
  return std::add_const_t<T>(make_system_buffer(sdata));
}

template <ch_op op, typename A>
auto make_system_op(const A& in) {
  auto func = get_op_function1<op, A>();
  auto in_w = get_snode(in).words();
  return func(in_w, ch_width_v<A>);
}

template <typename R, ch_op op, typename A>
auto make_system_op(const A& in) {
  sdata_type ret(ch_width_v<R>);
  auto func = get_op_function1<R, op, A>();
  auto in_w = get_snode(in).words();
  func(ret.words(), ch_width_v<R>, in_w, ch_width_v<A>);
  return make_system_type<R>(std::move(ret));
}

template <ch_op op, typename A, typename B>
auto make_system_op(const A& lhs, const B& rhs) {
  auto func = get_op_function2<op, A, B>();
  auto lhs_w = get_snode(lhs).words();
  auto rhs_w = get_snode(rhs).words();
  return func(lhs_w, ch_width_v<A>, rhs_w, ch_width_v<B>);
}

template <typename R, ch_op op, typename A, typename B>
auto make_system_op(const A& lhs, const B& rhs) {
  sdata_type ret(ch_width_v<R>);
  auto func = get_op_function2<R, op, A, B>();
  auto lhs_w = get_snode(lhs).words();
  if constexpr (op_flags::shift == CH_OP_CLASS(op)) {
    auto dist = static_cast<uint32_t>(rhs);
    func(ret.words(), ch_width_v<R>, lhs_w, ch_width_v<A>, dist);
  } else {
    auto rhs_w = get_snode(rhs).words();
    func(ret.words(), ch_width_v<R>, lhs_w, ch_width_v<A>, rhs_w, ch_width_v<B>);
  }
  return make_system_type<R>(std::move(ret));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_SYSTEM_INTERFACE(type) \
  template <typename __R> \
  auto as() const { \
    static_assert(ch::internal::is_system_type_v<__R>, "invalid type"); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::system_accessor::cast<std::add_const_t<__R>>(*self); \
  } \
  template <typename __R> \
  auto as() { \
    static_assert(ch::internal::is_system_type_v<__R>, "invalid type"); \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::system_accessor::cast<__R>(*self); \
  } \
  auto as_bit() const { \
    return this->template as<ch_sbit<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->template as<ch_sbit<type::traits::bitwidth>>(); \
  } \
  auto as_int() const { \
    return this->template as<ch_sint<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->template as<ch_sint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() const { \
    return this->template as<ch_suint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() { \
    return this->template as<ch_suint<type::traits::bitwidth>>(); \
  } \
  auto ref() { \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::system_accessor::sliceref<type>(*self, 0); \
  }

#define CH_SYSTEM_OPERATOR1B_IMPL(base, op, method) \
  friend auto op(const base& self) { \
    return ch::internal::system_accessor::method((const T&)self); \
  }

#define CH_SYSTEM_OPERATOR1X_IMPL(base, op, method) \
  friend auto op(const base& self) { \
    return ch::internal::system_accessor::method<T>((const T&)self); \
  }

#define CH_SYSTEM_OPERATOR2B_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method((const T&)lhs, (const T&)rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return op((const ch_signed_t<T>&)lhs, rhs); \
    } else { \
      auto _rhs = system_cast<T>(rhs); \
      return ch::internal::system_accessor::method((const T&)lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return op(lhs, (const ch_signed_t<T>&)rhs); \
    } else { \
      auto _lhs = system_cast<T>(lhs); \
      return ch::internal::system_accessor::method(_lhs, (const T&)rhs); \
    } \
  }

#define CH_SYSTEM_OPERATOR2X_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return op((const ch_signed_t<T>&)lhs, rhs); \
    } else { \
      auto _rhs = system_cast<T>(rhs); \
      return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return op(lhs, (const ch_signed_t<T>&)rhs); \
    } else { \
      auto _lhs = system_cast<T>(lhs); \
      return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
    } \
  }

#define CH_SYSTEM_OPERATOR2Y_IMPL(base, op, method) \
  friend auto op(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const base& lhs, const U& rhs) { \
    auto _rhs = ch_system_t<U>(rhs); \
    return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const base& rhs) { \
    auto _lhs = system_cast<T>(lhs); \
    return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
  }

#define CH_SYSTEM_FUNCTION1B_DECL(base, func) \
  template <typename T> auto func(const base<T>& self);

#define CH_SYSTEM_FUNCTION1X_DECL(base, func) \
  template <unsigned R = 0, typename T> auto func(const base<T>& self);

#define CH_SYSTEM_FUNCTION1B_IMPL(base, func, method) \
  friend auto func(const base& self) { \
    return ch::internal::system_accessor::method((const T&)self); \
  }

#define CH_SYSTEM_FUNCTION1X_IMPL(base, func, method) \
  friend auto func(const base& self) { \
    return ch::internal::system_accessor::method<T>((const T&)self); \
  } \
  template <unsigned R> \
  friend auto func(const base& self) { \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::system_accessor::method<T>((const T&)self); \
    } else { \
      return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>((const T&)self); \
    } \
  }

#define CH_SYSTEM_FUNCTION2B_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs);

#define CH_SYSTEM_FUNCTION2X_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <unsigned R, typename T> auto func(const base<T>& lhs, const base<T>& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs); \
  template <typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs); \
  template <unsigned R, typename T, typename U, CH_REQUIRE(is_strictly_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs);

#define CH_SYSTEM_FUNCTION2B_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method((const T&)lhs, (const T&)rhs); \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func((const ch_signed_t<T>&)lhs, rhs); \
    } else { \
      auto _rhs = system_cast<T>(rhs); \
      return ch::internal::system_accessor::method((const T&)lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func(lhs, (const ch_signed_t<T>&)rhs); \
    } else { \
      auto _lhs = system_cast<T>(lhs); \
      return ch::internal::system_accessor::method(_lhs, (const T&)rhs); \
    } \
  }

#define CH_SYSTEM_FUNCTION2X_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs) { \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
    } else { \
      return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>((const T&)lhs, (const T&)rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func((const ch_signed_t<T>&)lhs, rhs); \
    } else { \
      auto _rhs = system_cast<T>(rhs); \
      return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func<R>((const ch_signed_t<T>&)lhs, rhs); \
    } else { \
      auto _rhs = system_cast<T>(rhs); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
      } else { \
        return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>((const T&)lhs, _rhs); \
      } \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func(lhs, (const ch_signed_t<T>&)rhs); \
    } else { \
      auto _lhs = system_cast<T>(lhs); \
      return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    if constexpr (!std::is_integral_v<U> && is_signed_v<U> && !is_signed_v<T>) { \
      return func<R>(lhs, (const ch_signed_t<T>&)rhs); \
    } else { \
      auto _lhs = system_cast<T>(lhs); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
      } else { \
        return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>(_lhs, (const T&)rhs); \
      } \
    } \
  }

#define CH_SYSTEM_FUNCTION2Y_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs) { \
    return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs) { \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::system_accessor::method<T>((const T&)lhs, (const T&)rhs); \
    } else { \
      return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>((const T&)lhs, (const T&)rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    auto _rhs = ch_system_t<U>(rhs); \
    return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs) { \
    auto _rhs = ch_system_t<U>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::system_accessor::method<T>((const T&)lhs, _rhs); \
    } else { \
      return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>((const T&)lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    auto _lhs = system_cast<T>(lhs); \
    return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRE(is_strictly_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs) { \
    auto _lhs = system_cast<T>(lhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return ch::internal::system_accessor::method<T>(_lhs, (const T&)rhs); \
    } else { \
      return ch::internal::system_accessor::method<ch_size_cast_t<T, R>>(_lhs, (const T&)rhs); \
    } \
  }

#define CH_SYSTEM_OP_CAST(type) \
  template <typename U, \
            CH_REQUIRE(std::is_integral_v<U>)> \
  explicit operator U() const { \
    static_assert(bitwidth_v<U> >= type::traits::bitwidth, "invalid size"); \
    auto self = reinterpret_cast<const type*>(this); \
    auto ret = static_cast<U>(system_accessor::data(*self)); \
    if constexpr(is_signed_v<type> && (bitwidth_v<U> > type::traits::bitwidth)) { \
      return sign_ext(ret, type::traits::bitwidth); \
    } else { \
      return ret; \
    } \
  }

}
}
