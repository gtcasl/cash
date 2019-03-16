#pragma once

#include "system.h"
#include "lnode.h"

namespace ch {
namespace internal {  

lnodeimpl* createOpNode(ch_op op, uint32_t size, bool is_signed, const lnode& in);

lnodeimpl* createOpNode(ch_op op, uint32_t size, bool is_signed,
                        const lnode& lhs, const lnode& rhs);

lnodeimpl* createRotateNode(const lnode& next, uint32_t dist, bool right);

lnodeimpl* createShuffleNode(const lnode& in, const std::vector<unsigned>& indices);

void registerTap(const lnode& node, const std::string& name);

void createPrintNode(const std::string& format, const std::vector<lnode>& args);

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

template <typename T>
inline constexpr bool is_bit_base_v = std::is_base_of_v<ch_bit<ch_width_v<T>>, T>;

template <typename T, unsigned N = ch_width_v<T>>
inline constexpr bool is_bit_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

template <typename T> class ch_reg;

using logic_buffer = lnode;

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static auto& buffer(const T& obj) {
    assert(obj.buffer().size() == ch_width_v<T>);
    return obj.buffer();
  }

  template <typename T>
  static auto& source(const T& obj) {
    assert(obj.buffer().size() == ch_width_v<T>);
    return obj.buffer().source();
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(obj.buffer().size() == ch_width_v<T>);
    return logic_buffer(std::move(obj.buffer()));
  }

  template <typename U>
  static void assign(U& dst, const sdata_type& src) {
    assert(ch_width_v<U> == src.size());
    const_cast<logic_buffer&>(dst.buffer()).write(0, src, 0, ch_width_v<U>);
  }

  template <typename U, typename V>
  static void assign(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer().size());
    assert(ch_width_v<V> == src.buffer().size());
    const_cast<logic_buffer&>(dst.buffer()).write(0, src.buffer(), 0, ch_width_v<U>);
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
    const_cast<logic_buffer&>(dst.buffer()).write(dst_offset, src.buffer(), src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj) {
    assert(obj.buffer().size() == ch_width_v<T>);
    auto data = obj.buffer().clone();
    return T(logic_buffer(data, "clone"));
  }

  template <typename R, typename T>
  static auto slice(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.buffer().size() == ch_width_v<T>);
    logic_buffer buffer(ch_width_v<R>, "slice");
    buffer.write(0, obj.buffer(), start, ch_width_v<R>);
    return R(buffer);
  }

  template <typename R, typename T>
  static auto ref(const T& obj, size_t start) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.buffer().size() == ch_width_v<T>);
    logic_buffer buffer(ch_width_v<R>, obj.buffer(), start, "sliceref");
    return R(buffer);
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(obj.buffer().size() == ch_width_v<T>);
    return R(obj.buffer());
  }

  template <typename T>
  static const auto& name(const T& obj) {
    return obj.buffer().name();
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
lnode get_lnode(const T& obj) {
  return logic_accessor::buffer(obj);
}

template <typename R, typename T>
lnode to_lnode(const T& obj) {
  if constexpr (is_logic_type_v<T>) {
    if constexpr (ch_width_v<T> <= ch_width_v<R>) {
      return get_lnode(obj);
    } else {
      lnode tmp(ch_width_v<R>, "slice");
      tmp.write(0, get_lnode(obj), 0, ch_width_v<R>);
      return tmp;
    }
  } else
  if constexpr (is_system_type_v<T>) {
    if constexpr (ch_width_v<T> <= ch_width_v<R>) {
      return lnode(get_snode(obj));
    } else {
      sdata_type tmp(ch_width_v<R>);
      tmp.copy(0, get_snode(obj), 0, ch_width_v<R>);
      return lnode(tmp);
    }
  } else
  if constexpr (is_scbit_convertible_v<T, ch_width_v<R>>) {
    return lnode(get_snode(ch_scbit<ch_width_v<R>>(obj)));
  } else {
    return get_lnode(R(obj));
  }
}

template <unsigned N, typename T>
lnode to_lnode(const T& obj) {
  return to_lnode<ch_bit<N>, T>(obj);
}

template <typename T>
auto make_type(const lnode& node) {
  return T(logic_buffer(node, node.name()));
}

template <ch_op op, bool Signed, typename R, typename A, typename DA = A>
auto make_logic_op(const A& a) {
  auto node = createOpNode(op, ch_width_v<R>, Signed, to_lnode<DA>(a));
  return make_type<R>(node);
}

template <ch_op op, bool Signed, typename R, typename A, typename B, typename DA = A, typename DB = B>
auto make_logic_op(const A& a, const B& b) {
  auto node = createOpNode(op, ch_width_v<R>, Signed, to_lnode<DA>(a), to_lnode<DB>(b));
  return make_type<R>(node);
}

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_INTERFACE(type) \
  template <typename R> \
  std::add_const_t<R> as() const { \
  static_assert(ch::internal::is_logic_type_v<R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  template <typename R> \
  auto as() { \
    static_assert(ch::internal::is_logic_type_v<R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  auto as_bit() const { \
    return this->as<ch::internal::ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->as<ch::internal::ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_int() const { \
    return this->as<ch::internal::ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->as<ch::internal::ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_uint() const { \
    return this->as<ch::internal::ch_uint<type::traits::bitwidth>>(); \
  } \
  auto as_uint() { \
    return this->as<ch::internal::ch_uint<type::traits::bitwidth>>(); \
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
    return ch::internal::logic_accessor::ref<type>(*this, 0); \
  } \
  auto clone() const { \
    CH_SOURCE_LOCATION(1); \
    return ch::internal::logic_accessor::clone(*this); \
  }

#define CH_LOGIC_OPERATOR(name) \
  template <template <unsigned> typename T, unsigned N, typename Base = empty_base> \
  struct name : Base { \
    using Derived = T<N>; \
    using Base::Base; \
    using Base::operator=;

#define CH_LOGIC_OPERATOR_IMPL(op, opcode, rtype) \
  friend auto op(const Derived& lhs, const Derived& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs); \
  } \
  template <typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<Derived, U>)> \
  friend auto op(const Derived& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype, Derived, U, Derived, Derived>(lhs, rhs); \
  } \
  template <typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<Derived, U>)> \
  friend auto op(const U& lhs, const Derived& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype, U, Derived, Derived, Derived>(lhs, rhs); \
  }

#define CH_LOGIC_ASSIGN_IMPL(op, opcode, rtype) \
  auto op(const Derived& rhs) { \
    CH_SOURCE_LOCATION(1); \
    auto lhs = reinterpret_cast<const Derived*>(this)->clone(); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs); \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  auto op(const T<M>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    auto lhs = reinterpret_cast<const Derived*>(this)->clone(); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs); \
  }

#define CH_LOGIC_FUNCTION_EQUALITY(func, op, type) \
  template <unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, false, ch_bit<1>>(lhs, rhs); \
  } \
  template <unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, false, ch_bit<1>, type<N>, U, type<N>, type<ch_width_v<U>>>(lhs, rhs); \
  } \
  template <unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, false, ch_bit<1>, U, type<N>, type<ch_width_v<U>>, type<N>>(lhs, rhs); \
  }

#define CH_LOGIC_FUNCTION_RELATIONAL(func, op, type) \
  CH_LOGIC_FUNCTION_EQUALITY(func, op, type)

#define CH_LOGIC_FUNCTION_BITWISE1(func, op, type) \
  template <unsigned R = 0, unsigned N> \
  auto func(const type<N>& in) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, type<R>>(in); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                std::conditional_t<(R != 0), type<R>, type<N>>>(in); \
    } \
  }

#define CH_LOGIC_FUNCTION_BITWISE2(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs) { \
    CH_SOURCE_LOCATION(1); \
   if constexpr (R && R < N && R < M) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, type<M>, type<R>, type<R>>(lhs, rhs); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, type<M>, type<R>, type<M>>(lhs, rhs); \
    } else \
    if constexpr (R && R < M) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, type<M>, type<N>, type<R>>(lhs, rhs); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, M)>>>(lhs, rhs); \
    } \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (R && R < N && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, U, type<R>, type<R>>(lhs, rhs); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, U, type<R>, type<ch_width_v<U>>>(lhs, rhs); \
    } else \
    if constexpr (R && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, U, type<N>, type<R>>(lhs, rhs); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                         type<N>, U, type<N>, type<ch_width_v<U>>>(lhs, rhs); \
    } \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    if constexpr (R && R < ch_width_v<U> && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, U, type<N>, type<R>, type<R>>(lhs, rhs); \
    } else \
    if constexpr (R && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, U, type<N>, type<R>, type<N>>(lhs, rhs); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, U, type<N>, type<ch_width_v<U>>, type<R>>(lhs, rhs); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                         U, type<N>, type<ch_width_v<U>>, type<N>>(lhs, rhs); \
    } \
  }

#define CH_LOGIC_FUNCTION_SHIFT(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<N>>>(lhs, rhs); \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<ch_bit<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<N>>, \
                         type<N>, U, type<N>, ch_logic_t<U>>(lhs, rhs); \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<ch_bit<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<U>, \
                         std::conditional_t<(R != 0), type<R>, ch_logic_t<U>>, \
                         U, type<N>, ch_logic_t<U>, type<N>>(lhs, rhs); \
  }

#define CH_LOGIC_FUNCTION_ARITHMETIC1(func, op, type) \
  CH_LOGIC_FUNCTION_BITWISE1(func, op, type)

#define CH_LOGIC_FUNCTION_ARITHMETIC2(func, op, type) \
  CH_LOGIC_FUNCTION_BITWISE2(func, op, type)

#define CH_LOGIC_FUNCTION_ARITHMETIC3(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, M)>>>(lhs, rhs); \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                         type<N>, U, type<N>, type<ch_width_v<U>>>(lhs, rhs); \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs) { \
    CH_SOURCE_LOCATION(1); \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                         U, type<N>, type<ch_width_v<U>>, type<N>>(lhs, rhs); \
  }

CH_LOGIC_OPERATOR(logic_op_equality)
  CH_LOGIC_OPERATOR_IMPL(operator==, ch_op::eq, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator!=, ch_op::ne, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_logical)
  friend auto operator!(const Derived& self) {
    CH_SOURCE_LOCATION(1);
    return make_logic_op<ch_op::notl, false, ch_bit<1>>(self);
  }
  CH_LOGIC_OPERATOR_IMPL(operator&&, ch_op::andl, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator||, ch_op::orl, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_bitwise)
  friend auto operator~(const Derived& self) {
    CH_SOURCE_LOCATION(1);
    return make_logic_op<ch_op::inv, false, Derived>(self);
  }

  CH_LOGIC_OPERATOR_IMPL(operator&, ch_op::andb, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator|, ch_op::orb, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator^, ch_op::xorb, Derived)

  CH_LOGIC_ASSIGN_IMPL(operator&=, ch_op::andb, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator|=, ch_op::orb, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator^=, ch_op::xorb, Derived)
};

CH_LOGIC_OPERATOR(logic_op_shift)
  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_bit<ch_width_v<U>>>)>
  friend auto operator<<(const Derived& lhs, const U& rhs) {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    CH_SOURCE_LOCATION(1);
    return make_logic_op<ch_op::shl,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         U,
                         Derived,
                         ch_bit<ch_width_v<U>>>(lhs, rhs);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_bit<ch_width_v<U>>>)>
  friend auto operator>>(const Derived& lhs, const U& rhs) {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    CH_SOURCE_LOCATION(1);
    return make_logic_op<ch_op::shr,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         U,
                         Derived,
                         ch_bit<ch_width_v<U>>>(lhs, rhs);
  }

  template <unsigned M>
  auto operator<<=(const T<M>& rhs) {
    static_assert(M <= 32, "invalid size");
    CH_SOURCE_LOCATION(1);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shl, ch_signed_v<Derived>, Derived>(lhs, rhs);
  }

  template <unsigned M>
  auto operator>>=(const T<M>& rhs) {
    static_assert(M <= 32, "invalid size");
    CH_SOURCE_LOCATION(1);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shr, ch_signed_v<Derived>, Derived>(lhs, rhs);
  }

  auto operator<<=(uint32_t rhs) {
    CH_SOURCE_LOCATION(1);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shl,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         uint32_t,
                         Derived,
                         ch_uint<32>>(lhs, rhs, rhs);
  }

  auto operator>>=(uint32_t& rhs) {
    CH_SOURCE_LOCATION(1);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shr,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         uint32_t,
                         Derived,
                         ch_uint<32>>(lhs, rhs, rhs);
  }
};

CH_LOGIC_OPERATOR(logic_op_relational)
  CH_LOGIC_OPERATOR_IMPL(operator<, ch_op::lt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator<=, ch_op::le, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>, ch_op::gt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>=, ch_op::ge, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_arithmetic)
  friend auto operator-(const Derived& self) {
    CH_SOURCE_LOCATION(1);
    return make_logic_op<ch_op::neg, ch_signed_v<Derived>, Derived>(self);
  }

  CH_LOGIC_OPERATOR_IMPL(operator+, ch_op::add, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator-, ch_op::sub, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator*, ch_op::mul, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator/, ch_op::div, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator%, ch_op::mod, Derived)

  CH_LOGIC_ASSIGN_IMPL(operator+=, ch_op::add, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator-=, ch_op::sub, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator*=, ch_op::mul, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator/=, ch_op::div, Derived)
  CH_LOGIC_ASSIGN_IMPL(operator%=, ch_op::mod, Derived)
};

CH_LOGIC_OPERATOR(logic_op_slice)
  template <typename R>
  std::add_const_t<R> slice(size_t start = 0) const {
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert(start + ch_width_v<R> <= N);
    auto& self = reinterpret_cast<const Derived&>(*this);
    return logic_accessor::slice<R>(self, start);
  }

  template <unsigned M>
  auto slice(size_t start = 0) const {
    CH_SOURCE_LOCATION(1);
    return this->slice<T<M>>(start);
  }

  template <typename R>
  auto aslice(size_t start = 0) const {
    CH_SOURCE_LOCATION(1);
    return this->slice<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  auto aslice(size_t start = 0) const {
    CH_SOURCE_LOCATION(1);
    return this->aslice<T<M>>(start);
  }

  template <typename R>
  auto sliceref(size_t start = 0) {
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert(start + ch_width_v<R> <= N);
    CH_SOURCE_LOCATION(1);
    auto& self = reinterpret_cast<const Derived&>(*this);
    return logic_accessor::ref<R>(self, start);
  }

  template <unsigned M>
  auto sliceref(size_t start = 0) {
    CH_SOURCE_LOCATION(1);
    return this->sliceref<T<M>>(start);
  }

  template <typename R>
  auto asliceref(size_t start = 0) {
    CH_SOURCE_LOCATION(1);
    return this->sliceref<R>(start * ch_width_v<R>);
  }

  template <unsigned M>
  auto asliceref(size_t start = 0) {
    CH_SOURCE_LOCATION(1);
    return this->asliceref<T<M>>(start);
  }
};

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(x, #x)
#else
  #define CH_TAP(x)
#endif
