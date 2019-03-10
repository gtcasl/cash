#pragma once

#include "system.h"
#include "lnode.h"

namespace ch {
namespace internal {  

lnodeimpl* createOpNode(ch_op op, uint32_t size, bool is_signed, const lnode& in,
                        const source_location& sloc);

lnodeimpl* createOpNode(ch_op op, uint32_t size, bool is_signed, const lnode& lhs,
                        const lnode& rhs, const source_location& sloc);

lnodeimpl* createRotateNode(const lnode& next, uint32_t dist, bool right,
                            const source_location& sloc);

lnodeimpl* createShuffleNode(const lnode& in, const std::vector<unsigned>& indices,
                             const source_location& sloc);

void registerTap(const lnode& node,
                 const std::string& name,
                 const source_location& sloc);

void createPrintNode(const std::string& format,
                     const std::vector<lnode>& args,
                     const source_location& sloc);

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class ch_bit;
template <unsigned N> class ch_int;
template <unsigned N> class ch_uint;

template <typename T>
inline constexpr bool is_bit_base_v = std::is_base_of_v<ch_bit<ch_width_v<T>>, T>;

template <typename T, unsigned N = ch_width_v<T>>
inline constexpr bool is_bit_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

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
  static auto copy(const T& obj, const source_location& sloc) {
    assert(obj.buffer().size() == ch_width_v<T>);
    return logic_buffer(obj.buffer(), sloc);
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(obj.buffer().size() == ch_width_v<T>);
    return logic_buffer(std::move(obj.buffer()));
  }

  template <typename U>
  static void assign(U& dst, const sdata_type& src) {
    assert(ch_width_v<U> == src.size());
    const_cast<logic_buffer&>(dst.buffer()).write(
          0, src, 0, ch_width_v<U>, source_location());
  }

  template <typename U, typename V>
  static void assign(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer().size());
    assert(ch_width_v<V> == src.buffer().size());
    const_cast<logic_buffer&>(dst.buffer()).write(
          0, src.buffer(), 0, ch_width_v<U>, source_location());
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
                    uint32_t length,
                    const source_location& sloc) {
    const_cast<logic_buffer&>(dst.buffer()).write(
          dst_offset, src.buffer(), src_offset, length, sloc);
  }

  template <typename T>
  static auto clone(const T& obj, const source_location& sloc) {
    assert(obj.buffer().size() == ch_width_v<T>);
    auto data = obj.buffer().clone(sloc);
    return T(logic_buffer(data, sloc));
  }

  template <typename R, typename T>
  static auto slice(const T& obj, size_t start, const source_location& sloc) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.buffer().size() == ch_width_v<T>);
    logic_buffer buffer(ch_width_v<R>, sloc);
    buffer.write(0, obj.buffer(), start, ch_width_v<R>, sloc);
    return R(buffer);
  }

  template <typename R, typename T>
  static auto ref(const T& obj, size_t start, const source_location& sloc) {
    static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
    assert(start + ch_width_v<R> <= ch_width_v<T>);
    assert(obj.buffer().size() == ch_width_v<T>);
    logic_buffer buffer(ch_width_v<R>, obj.buffer(), start, sloc);
    return R(buffer);
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(obj.buffer().size() == ch_width_v<T>);
    return R(obj.buffer());
  }

  template <typename T>
  static const auto& sloc(const T& obj) {
    return obj.buffer().sloc();
  }

  template <typename T>
  static const auto& name(const T& obj) {
    return obj.buffer().name();
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N, typename T>
auto to_logic(T&& obj, const source_location& sloc) {
  if constexpr (is_logic_type_v<T> && ch_width_v<T> == N) {
    return std::move(obj);
  } else {
    return ch_bit<N>(std::forward<T>(obj), sloc);
  }
}

template <typename T>
lnode get_lnode(const T& obj) {
  return logic_accessor::buffer(obj);
}

template <typename R, typename T>
lnode to_lnode(const T& obj, const source_location& sloc) {
  if constexpr (is_logic_type_v<T> && ch_width_v<T> == ch_width_v<R>) {
    return logic_accessor::buffer(obj);
  } else
  if constexpr (is_scbit_convertible_v<T, ch_width_v<R>>) {
    // directly convert integrals to lnodes
    return lnode(system_accessor::data(to_system<ch_width_v<R>>(obj)));
  } else {
    return logic_accessor::buffer(R(obj, sloc));
  }
}

template <unsigned N, typename T>
lnode to_lnode(const T& obj, const source_location& sloc) {
  return to_lnode<ch_bit<N>, T>(obj, sloc);
}

template <typename T>
auto make_type(const lnode& node, const source_location& sloc) {
  return T(logic_buffer(node, sloc));
}

template <ch_op op, bool Signed, typename R, typename A>
auto make_logic_op(const A& a, const source_location& sloc) {
  auto node = createOpNode(op, ch_width_v<R>, Signed, get_lnode(a), sloc);
  return make_type<R>(node, sloc);
}

template <ch_op op, bool Signed, typename R, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_location& sloc) {
  auto node = createOpNode(op, ch_width_v<R>, Signed, get_lnode(a), get_lnode(b), sloc);
  return make_type<R>(node, sloc);
}

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct sloc_arg {
  const T& value;
  source_location sloc;

  sloc_arg(const T& p_value, const source_location& p_sloc = CH_CUR_SLOC)
    : value(p_value)
    , sloc(p_sloc)
  {}
};

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
  auto as_reg(CH_SLOC) { \
    ch_reg<type> s(sloc); \
    (*this) = s; \
    return s; \
  } \
  auto as_reg(const type& init, CH_SLOC) { \
    ch_reg<type> s(init, sloc); \
    (*this) = s; \
    return s; \
  } \
  auto ref(CH_SLOC) { \
    return ch::internal::logic_accessor::ref<type>(*this, 0, sloc); \
  } \
  auto clone(CH_SLOC) const { \
    return ch::internal::logic_accessor::clone(*this, sloc); \
  }

#define CH_LOGIC_OPERATOR(name) \
  template <template <unsigned> typename T, unsigned N, typename Base = empty_base> \
  struct name : Base { \
    using Derived = T<N>; \
    using Base::Base; \
    using Base::operator=;

#define CH_LOGIC_OPERATOR_IMPL(op, opcode, rtype) \
  friend auto op(const Derived lhs, const Derived& rhs) { \
    auto sloc = logic_accessor::sloc(lhs); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  }

#define CH_LOGIC_ASSIGN_IMPL(op, opcode, rtype) \
  auto op(Derived rhs) { \
    auto sloc = logic_accessor::sloc(rhs); \
    auto lhs = reinterpret_cast<const Derived*>(this)->clone(); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  auto op(T<M> rhs) { \
    auto sloc = logic_accessor::sloc(rhs); \
    auto lhs = reinterpret_cast<const Derived*>(this)->clone(); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  }

#define CH_LOGIC_FUNCTION_EQUALITY(func, op, type) \
  template <unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs, CH_SLOC) { \
    return make_logic_op<op, false, ch_bit<1>>(lhs, rhs, sloc); \
  } \
  template <unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs, CH_SLOC) { \
    return make_logic_op<op, false, ch_bit<1>, type<N>, type<ch_width_v<U>>>(lhs, rhs, sloc); \
  } \
  template <unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs, CH_SLOC) { \
    return make_logic_op<op, false, ch_bit<1>, type<ch_width_v<U>>, type<N>>(lhs, rhs, sloc); \
  }

#define CH_LOGIC_FUNCTION_RELATIONAL(func, op, type) \
  CH_LOGIC_FUNCTION_EQUALITY(func, op, type)

#define CH_LOGIC_FUNCTION_BITWISE1(func, op, type) \
  template <unsigned R = 0, unsigned N> \
  auto func(const type<N>& in, CH_SLOC) { \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>>(ch_slice<R>(in, {0, sloc}), sloc); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                std::conditional_t<(R != 0), type<R>, type<N>>>(in, sloc); \
    } \
  }

#define CH_LOGIC_FUNCTION_BITWISE2(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs, CH_SLOC) { \
    if constexpr (R && R < N && R < M) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>>( \
                            ch_slice<R>(lhs, {0, sloc}), ch_slice<R>(rhs, {0, sloc}), sloc); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>>(ch_slice<R>(lhs, {0, sloc}), rhs, sloc); \
    } else \
    if constexpr (R && R < M) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>>(lhs, ch_slice<R>(rhs, {0, sloc}), sloc); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, M)>>>(lhs, rhs, sloc); \
    } \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs, CH_SLOC) { \
    if constexpr (R && R < N && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<R>, type<R>>( \
                            ch_slice<R>(lhs, {0, sloc}), ch_slice<R>(type<ch_width_v<U>>(rhs), {0, sloc}), sloc); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<R>, type<ch_width_v<U>>>(\
        ch_slice<R>(lhs, {0, sloc}), rhs, sloc); \
    } else \
    if constexpr (R && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<N>, type<R>>( \
                             lhs, ch_slice<R>(type<ch_width_v<U>>(rhs), {0, sloc}), sloc); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                            type<N>, type<ch_width_v<U>>>(lhs, rhs, sloc); \
    } \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs, CH_SLOC) { \
    if constexpr (R && R < ch_width_v<U> && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<R>, type<R>>( \
                            ch_slice<R>(type<ch_width_v<U>>(lhs, {0, sloc})), ch_slice<R>(rhs, {0, sloc}), sloc); \
    } else \
    if constexpr (R && R < ch_width_v<U>) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<R>, type<N>>( \
                            ch_slice<R>(type<ch_width_v<U>>(lhs), {0, sloc}), rhs, sloc); \
    } else \
    if constexpr (R && R < N) { \
      return make_logic_op<op, ch_signed_v<type<N>>, type<R>, type<ch_width_v<U>>, type<R>>( \
                            lhs, ch_slice<R>(rhs, {0, sloc}), sloc); \
    } else { \
      return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                            type<ch_width_v<U>>, type<N>>(lhs, rhs, sloc); \
    } \
  }

#define CH_LOGIC_FUNCTION_SHIFT(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<N>>, \
                            type<N>, type<M>>(lhs, rhs, sloc); \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<ch_bit<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<N>>, \
                            type<N>, ch_logic_t<U>>(lhs, rhs, sloc); \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<ch_bit<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<U>, \
                         std::conditional_t<(R != 0), type<R>, ch_logic_t<U>>, \
                            ch_logic_t<U>, type<N>>(lhs, rhs, sloc); \
  }

#define CH_LOGIC_FUNCTION_ARITHMETIC1(func, op, type) \
  CH_LOGIC_FUNCTION_BITWISE1(func, op, type)

#define CH_LOGIC_FUNCTION_ARITHMETIC2(func, op, type) \
  CH_LOGIC_FUNCTION_BITWISE2(func, op, type)

#define CH_LOGIC_FUNCTION_ARITHMETIC3(func, op, type) \
  template <unsigned R = 0, unsigned N, unsigned M = N> \
  auto func(const type<N>& lhs, const type<M>& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, M)>>>(lhs, rhs, sloc); \
  } \
  template <unsigned R = 0, unsigned N, typename U, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const type<N>& lhs, const U& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                            type<N>, type<ch_width_v<U>>>(lhs, rhs, sloc); \
  } \
  template <unsigned R = 0, typename U, unsigned N, \
            CH_REQUIRE_0(is_strictly_constructible_v<type<ch_width_v<U>>, U>)> \
  auto func(const U& lhs, const type<N>& rhs, CH_SLOC) { \
    return make_logic_op<op, ch_signed_v<type<N>>, \
                         std::conditional_t<(R != 0), type<R>, type<std::max(N, ch_width_v<U>)>>, \
                            type<ch_width_v<U>>, type<N>>(lhs, rhs, sloc); \
  }

CH_LOGIC_OPERATOR(logic_op_equality)
  CH_LOGIC_OPERATOR_IMPL(operator==, ch_op::eq, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator!=, ch_op::ne, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_logical)
  friend auto operator!(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<ch_op::notl, false, ch_bit<1>>(self, sloc);
  }

  friend auto operator&&(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<ch_op::andl, false, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator||(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<ch_op::orl, false, ch_bit<1>>(lhs, rhs, sloc);
  }
};

CH_LOGIC_OPERATOR(logic_op_bitwise)
  friend auto operator~(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<ch_op::inv, false, Derived>(self, sloc);
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
  friend auto operator<<(Derived lhs, const U& rhs) {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<ch_op::shl,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         ch_bit<ch_width_v<U>>>(lhs, rhs, sloc);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_convertible_v<U, ch_bit<ch_width_v<U>>>)>
  friend auto operator>>(Derived lhs, const U& rhs) {
    static_assert(ch_width_v<U> <= 32, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<ch_op::shr,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         ch_bit<ch_width_v<U>>>(lhs, rhs, sloc);
  }

  template <unsigned M>
  auto operator<<=(T<M> rhs) {
    static_assert(M <= 32, "invalid size");
    auto sloc = logic_accessor::sloc(rhs);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shl,
                         ch_signed_v<Derived>,
                         Derived>(lhs, rhs, sloc);
  }

  template <unsigned M>
  auto operator>>=(T<M> rhs) {
    static_assert(M <= 32, "invalid size");
    auto sloc = logic_accessor::sloc(rhs);
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shr,
                         ch_signed_v<Derived>,
                         Derived>(lhs, rhs, sloc);
  }

  auto operator<<=(const sloc_arg<uint32_t>& rhs) {
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shl,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         ch_uint<32>>(lhs, rhs.value, rhs.sloc);
  }

  auto operator>>=(const sloc_arg<uint32_t>& rhs) {
    auto lhs = reinterpret_cast<const Derived*>(this)->clone();
    return make_logic_op<ch_op::shr,
                         ch_signed_v<Derived>,
                         Derived,
                         Derived,
                         ch_uint<32>>(lhs, rhs.value, rhs.sloc);
  }
};

CH_LOGIC_OPERATOR(logic_op_relational)
  CH_LOGIC_OPERATOR_IMPL(operator<, ch_op::lt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator<=, ch_op::le, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>, ch_op::gt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>=, ch_op::ge, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_arithmetic)
  friend auto operator-(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<ch_op::neg, ch_signed_v<Derived>, Derived>(self, sloc);
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
  std::add_const_t<R> slice(const sloc_arg<size_t>& start = 0) const {
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert(start.value + ch_width_v<R> <= N);
    auto& self = reinterpret_cast<const Derived&>(*this);
    return logic_accessor::slice<R>(self, start.value, start.sloc);
  }

  template <unsigned M>
  auto slice(const sloc_arg<size_t>& start = 0) const {
    return this->slice<T<M>>(start);
  }

  template <typename R>
  auto aslice(const sloc_arg<size_t>& start = 0) const {
    auto index = sloc_arg<size_t>(start.value * ch_width_v<R>, start.sloc);
    return this->slice<R>(index);
  }

  template <unsigned M>
  auto aslice(const sloc_arg<size_t>& start = 0) const {
    return this->aslice<T<M>>(start);
  }

  template <typename R>
  auto sliceref(const sloc_arg<size_t>& start = 0) {
    static_assert(ch_width_v<R> <= N, "invalid size");
    assert(start.value + ch_width_v<R> <= N);
    auto& self = reinterpret_cast<const Derived&>(*this);
    return logic_accessor::ref<R>(self, start.value, start.sloc);
  }

  template <unsigned M>
  auto sliceref(const sloc_arg<size_t>& start = 0) {
    return this->sliceref<T<M>>(start);
  }

  template <typename R>
  auto asliceref(const sloc_arg<size_t>& start = 0) {
    auto index = sloc_arg<size_t>(start.value * ch_width_v<R>, start.sloc);
    return this->sliceref<R>(index);
  }

  template <unsigned M>
  auto asliceref(const sloc_arg<size_t>& start = 0) {
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
