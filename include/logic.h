#pragma once

#include "system.h"

namespace ch {
namespace internal {  

lnodeimpl* createOpNode(ch_op op, 
                        uint32_t size, 
                        bool is_signed, 
                        const lnode& in,
                        const std::string& name,
                        const source_location& sloc);

lnodeimpl* createOpNode(ch_op op,
                        uint32_t size,
                        bool is_signed,
                        const lnode& lhs,
                        const lnode& rhs,
                        const std::string& name,
                        const source_location& sloc);

///////////////////////////////////////////////////////////////////////////////

class ch_ostream;

template <typename T> class ch_bitbase;
template <typename T> class ch_numbase;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

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

  const logic_buffer& source() const;
  
  logic_buffer& source();

  void write(uint32_t dst_offset,
             const lnode& in,
             uint32_t src_offset,
             uint32_t length);

  lnodeimpl* clone(const std::string& name, const source_location& sloc) const;

  lnodeimpl* sliceref(size_t size, 
                      size_t start, 
                      const std::string& name, 
                      const source_location& sloc) const;  

protected:

  logic_buffer(lnodeimpl* impl) : lnode(impl) {}

  logic_buffer(const sdata_type& value) : lnode(value)  {}

  logic_buffer(uint32_t size, 
               const std::string& name,
               const source_location& sloc);

  logic_buffer(uint32_t size,
               const logic_buffer& src,
               uint32_t src_offset,
               const std::string& name,
               const source_location& sloc);  
  
  void ensure_proxy() const;

  friend auto make_logic_buffer(lnodeimpl* impl);

  friend auto make_logic_buffer(const sdata_type& value);

  friend auto make_logic_buffer(uint32_t size, 
                                const source_info& srcinfo);

  friend auto make_logic_buffer(uint32_t size,
                                const logic_buffer& src,
                                uint32_t src_offset, 
                                const source_info& srcinfo);
};

inline auto make_logic_buffer(lnodeimpl* impl) {
  return logic_buffer(impl);
}

inline auto make_logic_buffer(const sdata_type& value) {
  return logic_buffer(value);
}

inline auto make_logic_buffer(uint32_t size, 
                              const source_info& srcinfo) {
  return logic_buffer(size, srcinfo.name(), srcinfo.sloc());
}

inline auto make_logic_buffer(uint32_t size,
                              const logic_buffer& src,
                              uint32_t src_offset, 
                              const source_info& srcinfo) {
  return logic_buffer(size, src, src_offset, srcinfo.name(), srcinfo.sloc());
}

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static auto& size(const T& obj) {
    return obj.__buffer().size();
  }

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
    return obj.__buffer();
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
    const_cast<logic_buffer&>(obj.__buffer()).write(0, src.__buffer(), 0, ch_width_v<T>);
  }

  template <typename T, typename U>
  static void move(T& obj, U&& src) {
    static_assert(ch_width_v<T> == ch_width_v<U>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(ch_width_v<U> == src.__buffer().size());
    const_cast<logic_buffer&>(obj.__buffer()).write(0, src.__buffer(), 0, ch_width_v<T>);
  }

  template <typename T, typename U>
  static void write(T& obj,
                    uint32_t dst_offset,
                    const U& src,
                    uint32_t src_offset,
                    uint32_t length) {
    assert(ch_width_v<T> == obj.__buffer().size());
    const_cast<logic_buffer&>(obj.__buffer()).write(dst_offset, src.__buffer(), src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj, const source_info& srcinfo) {
    assert(ch_width_v<T> == obj.__buffer().size());
    auto data = obj.__buffer().clone(srcinfo.name(), srcinfo.sloc());
    return T(make_logic_buffer(data));
  }

  template <typename R, typename T>
  static auto slice(const T& obj, size_t start, const source_info& srcinfo) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    auto buffer = make_logic_buffer(ch_width_v<R>, srcinfo);
    buffer.write(0, obj.__buffer(), start, ch_width_v<R>);
    return std::add_const_t<R>(buffer);
  }

  template <typename R, typename T>
  static auto sliceref(const T& obj, size_t start, const source_info& srcinfo) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(ch_width_v<T> == obj.__buffer().size());
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    auto data = obj.__buffer().sliceref(ch_width_v<R>, start, srcinfo.name(), srcinfo.sloc());
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

  template <typename T>
  static auto srcinfo(const T& obj) {
    return source_info(obj.__buffer().sloc(), obj.__buffer().name());
  }

  template <typename T, typename U>
  static auto do_eq(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_eq(other, srcinfo);
  }

  template <typename T, typename U>
  static auto do_ne(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_ne(other, srcinfo);
  }

  template <typename T>
  static auto do_not(const T& obj, const source_info& srcinfo) {
    return obj.do_not(srcinfo);
  }

  template <typename T, typename U>
  static auto do_andl(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_andl(other, srcinfo);
  }

  template <typename T, typename U>
  static auto do_orl(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_orl(other, srcinfo);
  }

  template <typename R, typename T>
  static auto do_inv(const T& obj, const source_info& srcinfo) {
    return obj.template do_inv<R>(srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_and(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_and<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_or(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_or<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_xor(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_xor<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_shl(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_shl<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_shr(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_shr<R>(other, srcinfo);
  }

  template <typename T>
  static auto do_andr(const T& obj, const source_info& srcinfo) {
    return obj.do_andr(srcinfo);
  }

  template <typename T>
  static auto do_orr(const T& obj, const source_info& srcinfo) {
    return obj.do_orr(srcinfo);
  }

  template <typename T>
  static auto do_xorr(const T& obj, const source_info& srcinfo) {
    return obj.do_xorr(srcinfo);
  }

  template <typename T, typename U>
  static auto do_lt(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_lt(other, srcinfo);
  }

  template <typename T, typename U>
  static auto do_le(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_le(other, srcinfo);
  }

  template <typename T, typename U>
  static auto do_gt(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_gt(other, srcinfo);
  }

  template <typename T, typename U>
  static auto do_ge(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.do_ge(other, srcinfo);
  }

  template <typename R, typename T>
  static auto do_neg(const T& obj, const source_info& srcinfo) {
    return obj.template do_neg<R>(srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_add(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_add<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_sub(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_sub<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_mul(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_mul<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_div(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_div<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_mod(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_mod<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_min(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_min<R>(other, srcinfo);
  }

  template <typename R, typename T, typename U>
  static auto do_max(const T& obj, const U& other, const source_info& srcinfo) {
    return obj.template do_max<R>(other, srcinfo);
  }

  template <typename R, typename T>
  static auto do_abs(const T& obj, const source_info& srcinfo) {
    return obj.template do_abs<R>(srcinfo);
  }

  template <typename T>
  static void do_print(const T& obj, ch_ostream& out) {
    obj.do_print(out);
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
auto get_lnode(const T& obj) {
  return logic_accessor::buffer(obj);
}

template <typename R, typename T>
auto to_lnode(const T& obj, const source_info& srcinfo) {
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
    return get_lnode(R(obj, srcinfo));
  }
}

template <unsigned N, typename T>
auto to_lnode(const T& obj, const source_info& srcinfo) {
  return to_lnode<ch_bit<N>>(obj, srcinfo);
}

template <typename R, typename T>
auto logic_op_cast(const T& obj, const source_info& srcinfo) {
  static_assert(std::is_constructible_v<R, T>, "invalid cast");
  if constexpr ((is_signed_v<T> != is_signed_v<R> || !is_resizable_v<R>)) {
    return R(obj, srcinfo);
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
    return R(obj, srcinfo);
  }
}

template <typename T>
auto make_logic_type(const lnode& node) {
  return std::add_const_t<T>(make_logic_buffer(node.impl()));
}

template <ch_op op, typename A>
auto make_logic_op(const A& a, const source_info& srcinfo) {
  auto node = createOpNode(op, 1, false, get_lnode(a), srcinfo.name(), srcinfo.sloc());
  return make_logic_type<ch_bool>(node);
}

template <typename R, ch_op op, typename A>
auto make_logic_op(const A& a, const source_info& srcinfo) {
  auto node = createOpNode(op, ch_width_v<R>, is_signed_v<R>, get_lnode(a), srcinfo.name(), srcinfo.sloc());
  return make_logic_type<R>(node);
}

template <ch_op op, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_info& srcinfo) {
  auto node = createOpNode(op, 1, is_signed_v<A>, get_lnode(a), get_lnode(b), srcinfo.name(), srcinfo.sloc());
  return make_logic_type<ch_bool>(node);
}

template <typename R, ch_op op, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_info& srcinfo) {
  auto node = createOpNode(op, ch_width_v<R>, is_signed_v<R>, get_lnode(a), get_lnode(b), srcinfo.name(), srcinfo.sloc());
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
  auto as_reg(CH_SRC_INFO) { \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s(srcinfo); \
    *self = s; \
    return s; \
  } \
  auto as_reg(const type& init, CH_SRC_INFO) { \
    auto self = reinterpret_cast<type*>(this); \
    ch_reg<type> s(init, srcinfo); \
    *self = s; \
    return s; \
  } \
  auto ref(CH_SRC_INFO) { \
    auto self = reinterpret_cast<type*>(this); \
    return ch::internal::logic_accessor::sliceref<type>(*self, 0, srcinfo); \
  } \
  auto clone(CH_SRC_INFO) const { \
    auto self = reinterpret_cast<const type*>(this); \
    return ch::internal::logic_accessor::clone(*self, srcinfo); \
  }

#define CH_LOGIC_OPERATOR1B_IMPL(base, op, method) \
  friend auto op(const srcinfo_arg<base>& self) { \
    auto& _self = reinterpret_cast<const T&>(self.data); \
    return logic_accessor::method<T>(_self, self.srcinfo); \
  }

#define CH_LOGIC_OPERATOR1X_IMPL(base, op, method) \
  friend auto op(const srcinfo_arg<base>& self) { \
    auto& _self = reinterpret_cast<const T&>(self.data); \
    return logic_accessor::method<T>(_self, self.srcinfo); \
  }

#define CH_LOGIC_OPERATOR2B_IMPL(base, op, method) \
  friend auto op(const srcinfo_arg<base>& lhs, const base& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const srcinfo_arg<base>& lhs, const U& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = logic_op_cast<T>(rhs, lhs.srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
    } else { \
      return op(_lhs, srcinfo_arg(ch_size_cast_t<T, ch_width_v<U>>(rhs), lhs.srcinfo)); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const srcinfo_arg<base>& rhs) { \
    auto& _rhs = reinterpret_cast<const T&>(rhs.data); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs, rhs.srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, rhs.srcinfo); \
    } else { \
      return op(srcinfo_arg(ch_size_cast_t<T, ch_width_v<U>>(lhs), rhs.srcinfo), _rhs); \
    } \
  }

#define CH_LOGIC_OPERATOR2X_IMPL(base, op, method) \
  friend auto op(const srcinfo_arg<base>& lhs, const base& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const srcinfo_arg<base>& lhs, const U& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = logic_op_cast<T>(rhs, lhs.srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
    } else { \
      auto _rhs = srcinfo_arg(ch_size_cast_t<T, ch_width_v<U>>(rhs), lhs.srcinfo); \
      return op(_lhs, _rhs); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto op(const U& lhs, const srcinfo_arg<base>& rhs) { \
    auto& _rhs = reinterpret_cast<const T&>(rhs.data); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs, rhs.srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, rhs.srcinfo); \
    } else { \
      return op(srcinfo_arg(ch_size_cast_t<T, ch_width_v<U>>(lhs), rhs.srcinfo), _rhs); \
    } \
  }

#define CH_LOGIC_OPERATOR2Y_IMPL(base, op, method) \
  friend auto op(const srcinfo_arg<base>& lhs, const base& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
  } \
  template <typename U, \
            CH_REQUIRES(is_bitbase_v<U> || is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto op(const srcinfo_arg<base>& lhs, const U& rhs) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs.data); \
    auto _rhs = ch_logic_t<U>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, lhs.srcinfo); \
  } \
  template <typename U, \
            CH_REQUIRES(is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto op(const U& lhs, const srcinfo_arg<base>& rhs) { \
    auto _lhs = ch_logic_t<U>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs.data); \
    return logic_accessor::method<ch_logic_t<U>>(_lhs, _rhs, rhs.srcinfo); \
  }
  
#define CH_LOGIC_OPERATOR2Z_IMPL(base, op, method) \
  T& op(const srcinfo_arg<base>& rhs) { \
    auto& self = reinterpret_cast<T&>(*this); \
    auto& _rhs = reinterpret_cast<const T&>(rhs.data); \
    self = logic_accessor::method<T>(ch_clone(self, rhs.srcinfo), _rhs, rhs.srcinfo); \
    return self; \
  } \
  T& op(T rhs) { \
    auto& self = reinterpret_cast<T&>(*this); \
    auto srcinfo = logic_accessor::srcinfo(rhs); \
    self = logic_accessor::method<T>(ch_clone(self, srcinfo), rhs, srcinfo); \
    return self; \
  }

#define CH_LOGIC_FUNCTION1B_DECL(base, func) \
  template <typename T> auto func(const base<T>& self, CH_SRC_INFO);

#define CH_LOGIC_FUNCTION1X_DECL(base, func) \
  template <unsigned R, typename T> auto func(const base<T>& self, CH_SRC_INFO);

#define CH_LOGIC_FUNCTION2B_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& , CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs, CH_SRC_INFO);

#define CH_LOGIC_FUNCTION2X_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <unsigned R, typename T> auto func(const base<T>& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& , CH_SRC_INFO); \
  template <unsigned R, typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const base<T>& lhs, const U& rhs, CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <unsigned R, typename T, typename U, CH_REQUIRES(is_logic_op_constructible_v<T, U>)> auto func(const U& lhs, const base<T>& rhs, CH_SRC_INFO);

#define CH_LOGIC_FUNCTION2Y_DECL(base, func) \
  template <typename T> auto func(const base<T>& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <unsigned R, typename T> auto func(const base<T>& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_bitbase_v<U> || is_sbitbase_v<U> || std::is_integral_v<U>)> auto func(const base<T>& lhs, const U& rhs, CH_SRC_INFO); \
  template <unsigned R, typename T, typename U, CH_REQUIRES(is_bitbase_v<U> || is_sbitbase_v<U> || std::is_integral_v<U>)> auto func(const base<T>& lhs, const U& rhs, CH_SRC_INFO); \
  template <typename T, typename U, CH_REQUIRES(is_sbitbase_v<U> || std::is_integral_v<U>)> auto func(const U& lhs, const base<T>& rhs, CH_SRC_INFO); \
  template <unsigned R, typename T, typename U, CH_REQUIRES(is_sbitbase_v<U> || std::is_integral_v<U>)> auto func(const U& lhs, const base<T>& rhs, CH_SRC_INFO);

#define CH_LOGIC_FUNCTION1B_IMPL(base, func, method) \
  friend auto func(const base& self, CH_SRC_INFO) { \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self, srcinfo); \
  }

#define CH_LOGIC_FUNCTION1X_IMPL(base, func, method) \
  friend auto func(const base& self, CH_SRC_INFO) { \
    auto& _self = reinterpret_cast<const T&>(self); \
    return logic_accessor::method<T>(_self, srcinfo); \
  } \
  template <unsigned R> \
  friend auto func(const base& self, CH_SRC_INFO) { \
    auto& _self = reinterpret_cast<const T&>(self); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_self, srcinfo); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_self, srcinfo); \
    } \
  }

#define CH_LOGIC_FUNCTION2B_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = logic_op_cast<T>(rhs, srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return func(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs), srcinfo); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs, srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return func(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs, srcinfo); \
    } \
  }

#define CH_LOGIC_FUNCTION2X_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs, srcinfo); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = logic_op_cast<T>(rhs, srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return func(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs), srcinfo); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const base& lhs, const U& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _rhs = logic_op_cast<T>(rhs, srcinfo); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs, srcinfo); \
      } \
    } else { \
      return func<R>(_lhs, ch_size_cast_t<T, ch_width_v<U>>(rhs), srcinfo); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs, srcinfo); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return func(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs, srcinfo); \
    } \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRES(is_logic_op_constructible_v<T, U>)> \
  friend auto func(const U& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (is_strictly_constructible_v<T, U>) { \
      auto _lhs = logic_op_cast<T>(lhs, srcinfo); \
      if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
        static_assert(ch_width_v<T> == R, "invalid output size"); \
        return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
      } else { \
        return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs, srcinfo); \
      } \
    } else { \
      return func<R>(ch_size_cast_t<T, ch_width_v<U>>(lhs), _rhs, srcinfo); \
    } \
  }

#define CH_LOGIC_FUNCTION2Y_IMPL(base, func, method) \
  friend auto func(const base& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
  } \
  template <unsigned R> \
  friend auto func(const base& lhs, const base& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs, srcinfo); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_bitbase_v<U> || is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto func(const base& lhs, const U& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto _rhs = ch_logic_t<U>(rhs); \
    return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRES(is_bitbase_v<U> || is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto func(const base& lhs, const U& rhs, CH_SRC_INFO) { \
    auto& _lhs = reinterpret_cast<const T&>(lhs); \
    auto _rhs = ch_logic_t<U>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<T>(_lhs, _rhs, srcinfo); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<T, R>>(_lhs, _rhs, srcinfo); \
    } \
  } \
  template <typename U, \
            CH_REQUIRES(is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto func(const U& lhs, const base& rhs, CH_SRC_INFO) { \
    auto _lhs = ch_logic_t<U>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    return logic_accessor::method<ch_logic_t<U>>(_lhs, _rhs, srcinfo); \
  } \
  template <unsigned R, typename U, \
            CH_REQUIRES(is_sbitbase_v<U> || std::is_integral_v<U>)> \
  friend auto func(const U& lhs, const base& rhs, CH_SRC_INFO) { \
    auto _lhs = ch_logic_t<U>(lhs); \
    auto& _rhs = reinterpret_cast<const T&>(rhs); \
    if constexpr (ch_width_v<T> == R || !is_resizable_v<T>) { \
      static_assert(ch_width_v<T> == R, "invalid output size"); \
      return logic_accessor::method<ch_logic_t<U>>(_lhs, _rhs, srcinfo); \
    } else { \
      return logic_accessor::method<ch_size_cast_t<ch_logic_t<U>, R>>(_lhs, _rhs, srcinfo); \
    } \
  }

}
}
