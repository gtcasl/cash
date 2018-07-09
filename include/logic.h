#pragma once

#include "scalar.h"

namespace ch {
namespace internal {  

lnodeimpl* createAluNode(ch_op op, uint32_t size, bool is_signed, const lnode& in,
                         const source_location& sloc);

lnodeimpl* createAluNode(ch_op op, uint32_t size, bool is_signed, const lnode& lhs,
                         const lnode& rhs, const source_location& sloc);

lnodeimpl* createRotateNode(const lnode& next, uint32_t dist, bool right,
                            const source_location& sloc);

void registerTap(const std::string& name,
                 const lnode& node,
                 const source_location& sloc);

void createPrintNode(const std::string& format,
                     const std::initializer_list<lnode>& args,
                     const source_location& sloc);

///////////////////////////////////////////////////////////////////////////////

template <unsigned Bitwidth, bool Signed, typename LogicType, typename ScalarType>
struct logic_traits {
  static constexpr traits_type type = traits_logic;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using logic_type  = LogicType;
  using scalar_type = ScalarType;
};

template <typename T>
using ch_logic_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
inline constexpr bool is_logic_traits_v = is_true_v<(T::type & traits_logic)>;

CH_DEF_SFINAE_CHECK(is_logic_only, is_true_v<(std::decay_t<T>::traits::type == traits_logic)>);

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits_v<typename std::decay_t<T>::traits>);

template <typename T>
inline constexpr bool is_bit_base_v = std::is_base_of_v<ch_bit<ch_width_v<T>>, T>;

template <typename T, unsigned N = T::traits::bitwidth>
inline constexpr bool is_bit_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

///////////////////////////////////////////////////////////////////////////////

class logic_buffer {
public:

  explicit logic_buffer(const lnode& node);

  logic_buffer(uint32_t size, const source_location& sloc, const std::string& name = "");

  logic_buffer(const lnode& data, const source_location& sloc, const std::string& name = "");

  logic_buffer(uint32_t size,
               const logic_buffer& buffer,
               uint32_t offset,
               const source_location& sloc,
               const std::string& name = "");

  logic_buffer(const logic_buffer& other, const source_location& sloc);

  logic_buffer(const logic_buffer& other);

  logic_buffer(logic_buffer&& other);

  virtual ~logic_buffer() {}

  logic_buffer& operator=(const logic_buffer& other);

  logic_buffer& operator=(logic_buffer&& other);

  const lnode& data() const {
    return node_;
  }

  logic_buffer source() const;

  uint32_t size() const {
    return node_.size();
  }

  void write(uint32_t dst_offset,
             const lnode& data,
             uint32_t src_offset,
             uint32_t length,
             const source_location& sloc);

protected:

  lnode node_;
};

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static logic_buffer buffer(const T& obj) {
    return obj.buffer();
  }

  template <typename T>
  static lnode data(const T& obj) {
    assert(ch_width_v<T> == obj.buffer().size());
    return obj.buffer().data();
  }

  template <typename T>
  static auto copy(const T& obj, const source_location& sloc) {
    assert(ch_width_v<T> == obj.buffer().size());
    return logic_buffer(obj.buffer(), sloc);
  }

  template <typename T>
  static auto move(T&& obj) {
    assert(ch_width_v<T> == obj.buffer().size());
    return logic_buffer(std::move(obj.buffer()));
  }

  template <typename U, typename V>
  static void copy(U& dst, const V& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer().size());
    assert(ch_width_v<V> == src.buffer().size());
    dst.buffer() = src.buffer();
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    static_assert(ch_width_v<U> == ch_width_v<V>, "invalid size");
    assert(ch_width_v<U> == dst.buffer().size());
    dst.buffer() = std::move(src.buffer());
  }

  template <typename U, typename V>
  static void write(U& dst,
                    uint32_t dst_offset,
                    const V& src,
                    uint32_t src_offset,
                    uint32_t length,
                    const source_location& sloc) {
    auto data = src.buffer().data();
    dst.buffer().write(dst_offset, data, src_offset, length, sloc);
  }

  template <typename T>
  static auto clone(const T& obj, const source_location& sloc) {
    assert(ch_width_v<T> == obj.buffer().size());
    auto data = obj.buffer().data().clone(sloc);
    return T(logic_buffer(data, sloc));
  }

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(ch_width_v<T> == ch_width_v<R>, "invalid size");
    assert(ch_width_v<T> == obj.buffer().size());
    return R(obj.buffer());
  }

  template <typename T>
  static const source_location& sloc(const T& obj) {
    return obj.buffer().data().sloc();
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
  return logic_accessor::data(obj);
}

template <typename R, typename T>
lnode to_lnode(const T& obj, const source_location& sloc) {
  if constexpr (is_logic_type_v<T> && ch_width_v<T> == ch_width_v<R>) {
    return logic_accessor::data(obj);
  } else
  if constexpr (is_scbit_convertible_v<T, ch_width_v<R>>) {
    // directly convert scalars and integrals to lnodes
    return lnode(scalar_accessor::data(to_scalar<ch_width_v<R>>(obj)));
  } else {
    return logic_accessor::data(R(obj, sloc));
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
  auto node = createAluNode(op, ch_width_v<R>, Signed, get_lnode(a), sloc);
  return make_type<R>(node, sloc);
}

template <ch_op op, bool Signed, typename R, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_location& sloc) {
  auto node = createAluNode(op, ch_width_v<R>, Signed, get_lnode(a), get_lnode(b), sloc);
  return make_type<R>(node, sloc);
}

template <typename T>
using type_accessor_t = std::conditional_t<is_logic_traits_v<T>, logic_accessor, scalar_accessor>;

template <typename T>
struct sloc_arg {
  const T& value;
  source_location sloc;

  sloc_arg(const T& p_value, const source_location& p_sloc = CH_CUR_SLOC)
    : value(p_value), sloc(p_sloc)
  {}
};

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_INTERFACE(type) \
  template <typename R> \
  const auto as() const { \
  static_assert(ch::internal::is_logic_type_v<R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  template <typename R> \
  auto as() { \
    static_assert(ch::internal::is_logic_type_v<R>, "invalid type"); \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  const auto as_bit() const { \
    return this->as<ch::internal::ch_bit<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->as<ch::internal::ch_bit<type::traits::bitwidth>>(); \
  } \
  const auto as_int() const { \
    return this->as<ch::internal::ch_int<type::traits::bitwidth>>(); \
  } \
  auto as_int() { \
    return this->as<ch::internal::ch_int<type::traits::bitwidth>>(); \
  } \
  const auto as_uint() const { \
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
  }

#define CH_LOGIC_OPERATOR(name) \
  template <template <unsigned> typename T, unsigned N, typename Next = empty_base> \
  struct name : Next { \
    using Derived = T<N>; \
    using Next::Next; \
    using Next::operator=; \
    name(const Next& other, CH_SLOC) : Next(other, sloc) {} \
    name(Next&& other) : Next(std::move(other)) {} \
    name& operator=(const Next& other) { Next::operator=(other); return *this; } \
    name& operator=(Next&& other) { Next::operator=(std::move(other)); return *this; } \
    name(const name& other, CH_SLOC) : Next(other, sloc) {} \
    name(name&& other) : Next(std::move(other)) {} \
    name& operator=(const name& other) { Next::operator=(other); return *this; } \
    name& operator=(name&& other) { Next::operator=(std::move(other)); return *this; }

#define CH_LOGIC_OPERATOR_IMPL(op, opcode, rtype) \
  friend auto op(Derived lhs, const Derived& rhs) { \
    auto sloc = logic_accessor::sloc(lhs); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(Derived lhs, const T<M>& rhs) { \
    auto sloc = logic_accessor::sloc(lhs); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  } \
  template <unsigned M, CH_REQUIRE_0(M < N)> \
  friend auto op(T<M> lhs, const Derived& rhs) { \
    auto sloc = logic_accessor::sloc(lhs); \
    return make_logic_op<opcode, ch_signed_v<Derived>, rtype>(lhs, rhs, sloc); \
  }

CH_LOGIC_OPERATOR(logic_op_compare)
  CH_LOGIC_OPERATOR_IMPL(operator==, op_eq, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator!=, op_ne, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_logical)
  friend auto operator&&(Derived lhs, const Derived& rhs) {
    static_assert(1 == Derived::traits::bitwidth, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_and, false, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator||(Derived lhs, const Derived& rhs) {
    static_assert(1 == Derived::traits::bitwidth, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_or, false, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator!(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<op_eq, ch_signed_v<Derived>, ch_bit<1>>(self, Derived(0x0), sloc);
  }
};

CH_LOGIC_OPERATOR(logic_op_bitwise)
  friend auto operator~(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<op_inv, false, Derived>(self, sloc);
  }

  CH_LOGIC_OPERATOR_IMPL(operator&, op_and, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator|, op_or, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator^, op_xor, Derived)
};

CH_LOGIC_OPERATOR(logic_op_shift)
  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator<<(Derived lhs, const U& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<CH_WIDTH_OF(U)>(rhs);
    return make_logic_op<op_sll, ch_signed_v<Derived>, Derived>(lhs, _rhs, sloc);
  }

  template <unsigned M>
  friend auto operator<<(Derived lhs, const ch_bit<M>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_sll, ch_signed_v<Derived>, Derived>(lhs, rhs, sloc);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator>>(Derived lhs, const U& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<CH_WIDTH_OF(U)>(rhs);
    return make_logic_op<op_srl, ch_signed_v<Derived>, Derived>(lhs, _rhs, sloc);
  }

  template <unsigned M>
  friend auto operator>>(Derived lhs, const ch_bit<M>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_srl, ch_signed_v<Derived>, Derived>(lhs, rhs, sloc);
  }
};

CH_LOGIC_OPERATOR(logic_op_padding)
  template <typename R>
  R pad(CH_SLOC) const {
    static_assert(is_logic_type_v<R>, "invalid type");
    static_assert(ch_width_v<R> >= N, "invalid size");
    auto& self = reinterpret_cast<const Derived&>(*this);
    if constexpr (ch_width_v<R> > N) {
      return make_logic_op<op_pad, ch_signed_v<Derived>, R>(self, sloc);
    } else
    if constexpr (std::is_same_v<R, Derived>) {
      return self;
    } else {
      return R(*this, sloc);
    }
  }

  template <unsigned M>
  auto pad(CH_SLOC) const {
    return this->pad<T<M>>(sloc);
  }
};

CH_LOGIC_OPERATOR(logic_op_relational)
  CH_LOGIC_OPERATOR_IMPL(operator<, op_lt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator<=, op_le, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>, op_gt, ch_bit<1>)
  CH_LOGIC_OPERATOR_IMPL(operator>=, op_ge, ch_bit<1>)
};

CH_LOGIC_OPERATOR(logic_op_arithmetic)
  friend auto operator-(Derived self) {
    auto sloc = logic_accessor::sloc(self);
    return make_logic_op<op_neg, ch_signed_v<Derived>, Derived>(self, sloc);
  }

  CH_LOGIC_OPERATOR_IMPL(operator+, op_add, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator-, op_sub, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator*, op_mul, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator/, op_div, Derived)
  CH_LOGIC_OPERATOR_IMPL(operator%, op_mod, Derived)
};

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
