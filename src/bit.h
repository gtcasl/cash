#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

void registerTap(const std::string& name, const lnode& node);

void createPrintNode(const std::string& format, const std::initializer_list<lnode>& args);

///////////////////////////////////////////////////////////////////////////////

template <unsigned N> class const_bit;

template <unsigned N> class bit;

template <unsigned N> class bit_concat;

template <typename T> class ch_seq;

template <unsigned Bitwidth,
          typename LogicType,
          typename ConstType,
          typename ValueType,
          typename ScalarType,
          typename Next = void>
struct logic_traits {
  static constexpr traits_type type = traits_logic;
  static constexpr ch_direction direction = ch_direction::none;
  static constexpr unsigned bitwidth = Bitwidth;
  using logic_type  = LogicType;
  using const_type  = ConstType;
  using value_type  = ValueType;
  using scalar_type = ScalarType;
  using next        = Next;
};

template <typename T>
using logic_type_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
using bit_value_t = typename logic_type_t<T>::traits::value_type;

template <typename T>
struct is_logic_traits : std::false_type {};

template <unsigned Bitwidth,
          typename LogicType,
          typename ConstType,
          typename ValueType,
          typename ScalarType,
          typename Next>
struct is_logic_traits<
    logic_traits<Bitwidth, LogicType, ConstType, ValueType, ScalarType, Next>
  > : std::true_type {};

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits<typename std::decay_t<T>::traits>::value);

CH_DEF_SFINAE_CHECK(is_logic_compatible, is_logic_traits<typename std::decay_t<T>::traits>::value
                                      || is_logic_traits<typename std::decay_t<T>::traits::next>::value);

CH_DEF_SFINAE_CHECK(is_bit_compatible, ((is_logic_traits<typename std::decay_t<T>::traits>::value
                                      || is_logic_traits<typename std::decay_t<T>::traits::next>::value)
                                     && std::is_base_of<const_bit<width_v<T>>, logic_type_t<T>>::value));

template <typename... Ts>
using deduce_ch_bit_t = std::conditional_t<
  is_bit_compatible<deduce_type_t<false, Ts...>>::value,
  deduce_type_t<false, Ts...>,
  non_ch_type>;

template <typename T0, typename T1>
using deduce_first_ch_bit_t = std::conditional_t<
  (is_bit_compatible<T0>::value || is_bit_compatible<T1>::value),
  deduce_first_type_t<T0, T1>,
  non_ch_type>;

template <typename T, unsigned N = T::traits::bitwidth>
using is_bit_convertible = is_cast_convertible<ch_bit<N>, T>;

template <typename... Ts>
using are_all_bit_convertible = conjunction<is_bit_convertible<Ts>::value...>;

template <typename... Ts>
using are_all_logic_type = conjunction<is_logic_type<Ts>::value...>;

template <typename... Ts>
using are_all_logic_compatible = conjunction<is_logic_compatible<Ts>::value...>;

///////////////////////////////////////////////////////////////////////////////

class bit_buffer_impl;

using bit_buffer_ptr = std::shared_ptr<bit_buffer_impl>;

class bit_buffer_impl {
public:
  explicit bit_buffer_impl(unsigned size,
                           const source_location& sloc = source_location(),
                           const std::string& name = "");

  bit_buffer_impl(const bit_buffer_impl& rhs,
                  const source_location& sloc = source_location(),
                  const std::string& name = "");

  bit_buffer_impl(bit_buffer_impl&& rhs);

  explicit bit_buffer_impl(const lnode& data,
                           const source_location& sloc = source_location(),
                           const std::string& name = "");

  bit_buffer_impl(unsigned size,
                  const bit_buffer_ptr& buffer,
                  unsigned offset,
                  const source_location& sloc = source_location(),
                  const std::string& name = "");

  virtual ~bit_buffer_impl() {}

  bit_buffer_impl& operator=(const bit_buffer_impl& rhs);

  bit_buffer_impl& operator=(bit_buffer_impl&& rhs);

  virtual const lnode& get_data() const;

  virtual void write(uint32_t dst_offset,
                     const lnode& data,
                     uint32_t src_offset,
                     uint32_t length);

  void write(const lnode& data) {
    this->write(0, data, 0, data.get_size());
  }

  void copy(const bit_buffer_impl& rhs) {
    this->write(0, rhs.get_data(), 0, rhs.get_size());
  }

  uint32_t get_id() const {
    return id_;
  }

  unsigned get_size() const {
    return value_.get_size();
  }

  const bit_buffer_ptr& get_source() const {
    return source_;
  }

  bit_buffer_ptr& get_source() {
    return source_;
  }

  unsigned get_offset() const {
    return offset_;
  }

protected:

  bit_buffer_impl(const lnode& value,
                  const bit_buffer_ptr& source,
                  unsigned offset);
  uint32_t id_;
  lnode value_;
  bit_buffer_ptr source_;
  unsigned offset_;
};

///////////////////////////////////////////////////////////////////////////////

class bit_buffer : public bit_buffer_ptr {
public:
  using base = bit_buffer_ptr;
  using base::operator*;
  using base::operator->;

  template <typename... Args>
  explicit bit_buffer(Args&&... args)
    : base(new bit_buffer_impl(std::forward<Args>(args)...))
  {}

  bit_buffer(const bit_buffer_ptr& rhs) : base(rhs) {}

  bit_buffer(const bit_buffer& rhs) : base(rhs) {}

  bit_buffer(bit_buffer&& rhs) : base(std::move(rhs)) {}

  bit_buffer& operator =(const bit_buffer& rhs) {
    base::operator =(rhs);
    return *this;
  }

  bit_buffer& operator =(bit_buffer&& rhs) {
    base::operator =(std::move(rhs));
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

class bit_accessor {
public:
  template <typename T>
  static const bit_buffer_ptr& get_buffer(const T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static bit_buffer_ptr& get_buffer(T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static const lnode& get_data(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    return obj.get_buffer()->get_data();
  }

  template <typename T>
  static void set_data(const T& obj, const lnode& data) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    auto& obj_data = obj.get_buffer()->get_data();
    const_cast<lnode&>(data).set_var_id(obj_data.get_var_id());
    const_cast<lnode&>(data).set_source_location(obj_data.get_source_location());
    obj.get_buffer()->write(data);
  }

  template <typename T>
  static auto copy_buffer(const T& obj,
                          const source_location& sloc = CH_SOURCE_LOCATION,
                          const std::string& name = "") {
    assert(width_v<T> == obj.get_buffer()->get_size());
    return bit_buffer(*obj.get_buffer(), sloc, name);
  }

  template <typename U, typename V,
            CH_REQUIRE_0(is_logic_compatible<U>::value),
            CH_REQUIRE_0(is_logic_compatible<V>::value),
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(width_v<U> == dst.get_buffer()->get_size());
    assert(width_v<V> == src.get_buffer()->get_size());
    *dst.get_buffer() = *src.get_buffer();
  }

  template <typename U, typename V,
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void move(U& dst, V&& src) {
    assert(width_v<U> == dst.get_buffer()->get_size());
    *dst.get_buffer() = std::move(*src.get_buffer());
  }

  template <typename U, typename V>
  static void write(U& dst,
                    unsigned dst_offset,
                    const V& src,
                    unsigned src_offset,
                    unsigned length) {
    auto data = src.get_buffer()->get_data();
    dst.get_buffer()->write(dst_offset, data, src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj, const source_location& sloc) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    auto data = obj.get_buffer()->get_data().clone();
    return bit_value_t<T>(bit_buffer(data, sloc));
  }

  template <typename D, typename T>
  static auto cast(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->get_size());
    return D(obj.get_buffer());
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = ch_bit<width_v<T>>>
using logic_cast_t = std::conditional_t<is_logic_compatible<T>::value, const T&, R>;

template <typename T, unsigned N = width_v<T>,
          CH_REQUIRE_0(is_bit_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  return bit_accessor::get_data(static_cast<logic_cast_t<T, ch_bit<N>>>(rhs));
}

template <typename T, typename R,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value)>
lnode get_lnode(const T& rhs) {
  return bit_accessor::get_data(static_cast<logic_cast_t<T, R>>(rhs));
}

template <typename T>
auto make_type(const lnode& node) {
  return T(bit_buffer(node));
}

template <typename T>
using type_buffer_t = std::conditional_t<is_logic_traits<T>::value, bit_buffer, scalar_buffer>;

template <typename T>
using type_accessor_t = std::conditional_t<is_logic_traits<T>::value, bit_accessor, scalar_accessor>;

template <typename T, typename U, typename Q = typename T::traits, typename X = typename ch_type_t<U>::traits>
using aggregate_init_cast_t = std::conditional_t<X::bitwidth != 0,
      std::conditional_t<(Q::type == X::type),
                         const U&,
                         std::conditional_t<is_logic_traits<Q>::value,
                                            ch_bit<X::bitwidth>,
                                            ch_scalar<X::bitwidth>>>,
      std::conditional_t<is_logic_traits<Q>::value,
                         ch_bit<Q::bitwidth>,
                         ch_scalar<Q::bitwidth>>>;

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op, unsigned N, typename A, typename B>
auto OpBinary(const A& a, const B& b) {
  auto node = createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b));
  return make_type<ch_bit<N>>(node);
}

template <ch_alu_op op, unsigned N, unsigned M, typename A, typename B>
auto OpShiftOp(const A& a, const B& b) {
  auto node = createAluNode(op, get_lnode<A, N>(a), get_lnode<B, M>(b));
  return make_type<ch_bit<N>>(node);
}

template <ch_alu_op op, unsigned N, typename A, typename B>
auto OpCompare(const A& a, const B& b) {
  auto node = createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b));
  return make_type<ch_bit<1>>(node);
}

template <ch_alu_op op, unsigned N>
auto OpUnary(const const_bit<N>& a) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode(a)));
}

template <ch_alu_op op, unsigned N>
auto OpReduce(const const_bit<N>& a) {
  return make_type<ch_bit<1>>(createAluNode(op, get_lnode(a)));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_BIT_FRIEND_OPS(i, x) \
  CH_FRIEND_BOOL_AND((), const const_bit&, x) \
  CH_FRIEND_BOOL_OR((), const const_bit&, x) \
  CH_FRIEND_OP_EQ((), const const_bit&, x) \
  CH_FRIEND_OP_NE((), const const_bit&, x) \
  CH_FRIEND_OP_LT((), const const_bit&, x) \
  CH_FRIEND_OP_LE((), const const_bit&, x) \
  CH_FRIEND_OP_GT((), const const_bit&, x) \
  CH_FRIEND_OP_GE((), const const_bit&, x) \
  CH_FRIEND_OP_AND((), const const_bit&, x) \
  CH_FRIEND_OP_OR((), const const_bit&, x) \
  CH_FRIEND_OP_XOR((), const const_bit&, x) \
  CH_FRIEND_OP_ADD((), const const_bit&, x) \
  CH_FRIEND_OP_SUB((), const const_bit&, x) \
  CH_FRIEND_OP_MULT((), const const_bit&, x) \
  CH_FRIEND_OP_DIV((), const const_bit&, x) \
  CH_FRIEND_OP_MOD((), const const_bit&, x) \
  CH_FRIEND_OP_SLL((), const const_bit&, x) \
  CH_FRIEND_OP_SRL((), const const_bit&, x)

#define CH_BIT_OP_TYPES \
  const_scalar<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_READONLY_INTERFACE(type) \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type<R>::value)> \
  ch::internal::const_type_t<R> as() const { \
    return ch::internal::bit_accessor::cast<ch::internal::const_type_t<R>>(*this); \
  } \
  ch::internal::const_bit<type::traits::bitwidth> asBits() const { \
    return this->as<ch::internal::const_bit<type::traits::bitwidth>>(); \
  }

#define CH_LOGIC_WRITABLE_INTERFACE(type) \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type<R>::value)> \
  R as() { \
    return ch::internal::bit_accessor::cast<R>(*this); \
  } \
  ch_bit<type::traits::bitwidth> asBits() { \
    return this->as<ch_bit<type::traits::bitwidth>>(); \
  } \
  const ch_seq<type> asSeq(const source_location& sloc = CH_SOURCE_LOCATION) { \
    ch_seq<type> s(sloc); \
    (*this) = s; \
    return s; \
  } \
  const ch_seq<type> asSeq(const type& init, const source_location& sloc = CH_SOURCE_LOCATION) { \
    ch_seq<type> s(init, sloc); \
    (*this) = s; \
    return s; \
  }

template <unsigned N>
class const_bit {
public:  
  using traits = logic_traits<N, const_bit, const_bit, ch_bit<N>, const_bit<N>>;

  const_bit(const bit_buffer& buffer = bit_buffer(N, CH_SOURCE_LOCATION))
    : buffer_(buffer)
  {}

  const_bit(const const_bit& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_bit(bit_accessor::copy_buffer(rhs, sloc))
  {}

  const_bit(const_bit&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  const_bit(const const_scalar<N>& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_bit(bit_buffer(scalar_accessor::get_data(rhs), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit const_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_bit(bit_accessor::copy_buffer(rhs, sloc))
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> == N)>
  explicit const_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_bit(bit_buffer(scalar_accessor::get_data(rhs), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit const_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : const_bit(bit_buffer(bitvector(N, rhs), sloc))
  {}

  // slicing operators

  auto operator[](size_t index) const {
    assert(index < N);
    return const_bit<1>(bit_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    static_assert(M <= N, "invalid size");
    assert((start + M) <= N);
    return const_bit<M>(bit_buffer(M, buffer_, start, sloc));
  }

  template <unsigned M>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    return this->slice<M>(start * M, sloc);
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return const_type_t<R>(bit_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  // compare operators

  auto operator==(const const_bit& rhs) const {
    return OpCompare<alu_eq, N>(*this, rhs);
  }

  auto operator!=(const const_bit& rhs) const {
    return OpCompare<alu_ne, N>(*this, rhs);
  }

  auto operator<(const const_bit& rhs) const {
    return OpCompare<alu_lt, N>(*this, rhs);
  }

  auto operator<=(const const_bit& rhs) const {
    return OpCompare<alu_le, N>(*this, rhs);
  }

  auto operator>(const const_bit& rhs) const {
    return OpCompare<alu_gt, N>(*this, rhs);
  }

  auto operator>=(const const_bit& rhs) const {
    return OpCompare<alu_ge, N>(*this, rhs);
  }

  // logical operators

  auto operator&&(const const_bit& rhs) const {
    static_assert(N == 1, "invalid size");
    return OpBinary<alu_and, 1>(*this, rhs);
  }

  auto operator||(const const_bit& rhs) const {
    static_assert(N == 1, "invalid size");
    return OpBinary<alu_or, 1>(*this, rhs);
  }

  auto operator!() const {
    return (*this == 0x0);
  }

  // bitwise operators

  auto operator~() const {
    return OpUnary<alu_inv>(*this);
  }

  auto operator&(const const_bit& rhs) const {
    return OpBinary<alu_and, N>(*this, rhs);
  }

  auto operator|(const const_bit& rhs) const {
    return OpBinary<alu_or, N>(*this, rhs);
  }

  auto operator^(const const_bit& rhs) const {
    return OpBinary<alu_xor, N>(*this, rhs);
  }

  // arithmetic operators

  auto operator-() const {
    return OpUnary<alu_neg>(*this);
  }

  auto operator+(const const_bit& rhs) const {
    return OpBinary<alu_add, N>(*this, rhs);
  }

  auto operator-(const const_bit& rhs) const {
    return OpBinary<alu_sub, N>(*this, rhs);
  }

  auto operator*(const const_bit& rhs) const {
    return OpBinary<alu_mult, N>(*this, rhs);
  }

  auto operator/(const const_bit& rhs) const {
    return OpBinary<alu_div, N>(*this, rhs);
  }

  auto operator%(const const_bit& rhs) const {
    return OpBinary<alu_mod, N>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const const_bit<M>& rhs) const {
    return OpShiftOp<alu_sll, N, M>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const const_bit<M>& rhs) const {
    return OpShiftOp<alu_srl, N, M>(*this, rhs);
  }

  CH_LOGIC_READONLY_INTERFACE(const_bit)

protected:

  const bit_buffer_ptr& get_buffer() const {
    return buffer_;
  }

  bit_buffer_ptr& get_buffer() {
    return buffer_;
  }

  bit_buffer buffer_;

  friend class bit_accessor;

  CH_FOR_EACH(CH_BIT_FRIEND_OPS, CH_SEP_SPACE, CH_BIT_OP_TYPES)

  template <unsigned M>
  inline friend ch_bit<M> operator<<(const const_bit& lhs, const const_scalar<M>& rhs) {
    return lhs << const_bit<M>(rhs);
  }

  template <unsigned M>
  inline friend ch_bit<M> operator<<(const const_scalar<M>& rhs, const const_bit& lhs) {
    return const_bit<M>(rhs) << lhs;
  }

  template <unsigned M>
  inline friend ch_bit<M> operator>>(const const_bit& lhs, const const_scalar<M>& rhs) {
    return lhs >> const_bit<M>(rhs);
  }

  template <unsigned M>
  inline friend ch_bit<M> operator>>(const const_scalar<M>& rhs, const const_bit& lhs) {
    return const_bit<M>(rhs) >> lhs;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public const_bit<N> {
public:  
  using traits = logic_traits<N, ch_bit, const_bit<N>, ch_bit, ch_scalar<N>>;
  using base = const_bit<N>;
  using base::buffer_;
      
  ch_bit(const bit_buffer& buffer = bit_buffer(N, CH_SOURCE_LOCATION))
    : base(buffer)
  {}
  
  ch_bit(const ch_bit& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_bit(ch_bit&& rhs) : base(std::move(rhs)) {}

  ch_bit(const const_bit<N>& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_bit(const const_scalar<N>& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> == N)>
  explicit ch_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit ch_bit(const U& rhs, const source_location& sloc = CH_SOURCE_LOCATION)
    : base(rhs, sloc)
  {}

  ch_bit& operator=(const ch_bit& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(N == width_v<U>)>
  ch_bit& operator=(const U& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(N == width_v<U>)>
  ch_bit& operator=(const U& rhs) {
    buffer_->write(scalar_accessor::get_data(rhs));
    return *this;
  }

  template <typename U, CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_bit& operator=(U rhs) {
    buffer_->write(bitvector(N, rhs));
    return *this;
  }

  auto operator[](size_t index) const {
    assert(index < N);
    return const_bit<1>(bit_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    assert(index < N);
    return ch_bit<1>(bit_buffer(1, buffer_, index));
  }

  template <unsigned M>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    static_assert(M <= N, "invalid size");
    assert((start + M) <= N);
    return const_bit<M>(bit_buffer(M, buffer_, start, sloc));
  }

  template <unsigned M>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    return this->slice<M>(start * M, sloc);
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return const_type_t<R>(bit_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) const {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  template <unsigned M>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
    static_assert(M <= N, "invalid size");
    return ch_bit<M>(bit_buffer(M, buffer_, start, sloc));
  }

  template <unsigned M>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
    return this->slice<M>(start * M, sloc);
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto slice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
    static_assert(width_v<R> <= N, "invalid size");
    return R(bit_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_compatible<R>::value)>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  CH_LOGIC_READONLY_INTERFACE(ch_bit)
  CH_LOGIC_WRITABLE_INTERFACE(ch_bit)
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <unsigned N>
inline auto ch_eq(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs == rhs);
}

template <unsigned N>
inline auto ch_ne(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs != rhs);
}

template <unsigned N>
inline auto ch_lt(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs < rhs);
}

template <unsigned N>
inline auto ch_le(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs <= rhs);
}

template <unsigned N>
inline auto ch_gt(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs > rhs);
}

template <unsigned N>
inline auto ch_ge(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs >= rhs);
}

// bitwise operators

template <unsigned N>
inline auto ch_and(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs & rhs);
}

template <unsigned N>
inline auto ch_or(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs | rhs);
}

template <unsigned N>
inline auto ch_xor(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs ^ rhs);
}

// arithmetic operators

template <unsigned N>
inline auto ch_add(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs + rhs);
}

template <unsigned N>
inline auto ch_sub(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs - rhs);
}

template <unsigned N>
inline auto ch_mult(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs * rhs);
}

template <unsigned N>
inline auto ch_div(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs / rhs);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return (lhs >> rhs);
}

// unary operators

template <unsigned N>
auto ch_inv(const const_bit<N>& in) {
  return ~in;
}

template <unsigned N>
auto ch_neg(const const_bit<N>& in) {
  return -in;
}

// reduce operators

template <unsigned N>
auto ch_andr(const const_bit<N>& in) {
  return OpReduce<alu_andr>(in);
}

template <unsigned N>
auto ch_orr(const const_bit<N>& in) {
  return OpReduce<alu_orr>(in);
}

template <unsigned N>
auto ch_xorr(const const_bit<N>& in) {
  return OpReduce<alu_xorr>(in);
}

// shift operators

template <unsigned N, unsigned M>
auto ch_sra(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_sra, N, M>(lhs, rhs);
}

template <unsigned N, unsigned M>
auto ch_rotl(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_rotl, N, M>(lhs, rhs);
}

template <unsigned N, unsigned M>
auto ch_rotr(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_rotr, N, M>(lhs, rhs);
}

// multiplexers

template <typename I, typename S,
          CH_REQUIRE_0(has_bitwidth<I>::value),
          CH_REQUIRE_0(has_bitwidth<S>::value),
          CH_REQUIRE_0(ispow2(width_v<I>)),
          CH_REQUIRE_0(ispow2(width_v<S>)),
          CH_REQUIRE_0((width_v<I> >> width_v<S>) != 0)>
auto ch_mux(const I& in, const S& sel) {
  return make_type<ch_bit<(width_v<I> >> width_v<S>)>>(
        createAluNode(alu_mux, get_lnode(in), get_lnode(sel)));
}

// cloning

template <typename T,
          CH_REQUIRE_0(is_logic_type<T>::value)>
auto ch_clone(const T& obj, const source_location& sloc = CH_SOURCE_LOCATION) {
  return bit_accessor::clone(obj, sloc);
}

// slicing

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_compatible<R>::value),
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
R ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
  static_assert(width_v<R> <= width_v<T>, "invalid size");
  assert((start + width_v<R>) <= width_v<T>);
  if constexpr(width_v<R> == width_v<T>) {    
    if constexpr(std::is_same<R, T>::value) {
      return obj;
    } else {
      return R(obj, sloc);
    }
  } else {
    ch_bit<width_v<R>> ret(bit_buffer(width_v<R>, sloc));
    bit_accessor::write(ret, 0, obj, start, width_v<R>);
    return ret.template as<R>();
  }
}

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_compatible<R>::value),
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
R ch_aslice(const T& obj, size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
  return ch_slice<R>(obj, start * width_v<R>, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
auto ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {  
  return ch_slice<ch_bit<N>>(obj, start, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
auto ch_aslice(const T& obj, size_t start = 0, const source_location& sloc = CH_SOURCE_LOCATION) {
  return ch_slice<ch_bit<N>>(obj, start * N, sloc);
}

// tie

template <typename... Ts>
class tie_impl {
public:
  tie_impl(const source_location& sloc, Ts&... args)
    : sloc_(sloc)
    , args_(args...)
  {}

  template <typename T>
  void operator=(const T& rhs) {
    this->assign(static_cast<logic_cast_t<T, ch_bit<width_v<Ts...>>>>(rhs),
                 std::index_sequence_for<Ts...>());
  }

protected:

  template <typename T, typename U>
  void assign_impl(unsigned src_offset, const T& src, U& dst) {
    dst = ch_slice<U>(src, src_offset, sloc_);
  }

  template <typename T, typename U0, typename... Us>
  void assign_impl(unsigned src_offset, const T& src, U0& dst0, Us&... dsts) {
    this->assign_impl(src_offset, src, dst0);
    this->assign_impl(src_offset + width_v<U0>, src, dsts...);
  }

  template <typename T, size_t... I>
  void assign(const T& src, std::index_sequence<I...>) {
    this->assign_impl(0, src, std::get<sizeof...(Ts) - 1 - I>(args_)...);
  }

  source_location sloc_;
  std::tuple<Ts&...> args_;
};

#define CH_TIE_TMPL(i, x) typename __T##i
#define CH_TIE_REQUIRE(i, x) CH_REQUIRE_0(is_logic_compatible<__T##i>::value)
#define CH_TIE_DECL(i, x) __T##i& arg##i
#define CH_TIE_ARG(i, x) arg##i
#define CH_TIE(...) \
  template <CH_FOR_EACH(CH_TIE_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_TIE_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_tie(CH_FOR_EACH(CH_TIE_DECL, CH_SEP_COMMA, __VA_ARGS__), \
         const source_location& sloc = CH_SOURCE_LOCATION) { \
    return tie_impl(sloc, CH_FOR_EACH(CH_TIE_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
  }
CH_VA_ARGS_MAP(CH_TIE)
#undef CH_TIE_TMPL
#undef CH_TIE_REQUIRE
#undef CH_TIE_DECL
#undef CH_TIE_ARG
#undef CH_TIE

// concatenation

template <typename U, typename T>
void cat_impl(U& inout, unsigned dst_offset, const T& arg) {
  bit_accessor::write(inout, dst_offset - width_v<T>, arg, 0, width_v<T>);
}

template <typename U, typename T0, typename... Ts>
void cat_impl(U& inout, unsigned dst_offset, const T0& arg0, const Ts&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - width_v<T0>, args...);
}

#define CH_CAT_TYPE(i, x) __T##i
#define CH_CAT_TMPL(i, x) typename __T##i
#define CH_CAT_REQUIRE(i, x) CH_REQUIRE_0(is_logic_compatible<__T##i>::value || is_bit_convertible<__T##i>::value)
#define CH_CAT_DECL(i, x) const __T##i& arg##i
#define CH_CAT_ARG(i, x) static_cast<logic_cast_t<__T##i>>(arg##i)
#define CH_CAT(...) \
  template <typename R, \
            CH_FOR_EACH(CH_CAT_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_CAT_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), \
         const source_location& sloc = CH_SOURCE_LOCATION) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    static_assert(width_v<R> == N, "size mismatch"); \
    R ret(bit_buffer(N, sloc)); \
    cat_impl(ret, N, CH_FOR_EACH(CH_CAT_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  } \
  template <CH_FOR_EACH(CH_CAT_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_CAT_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), \
         const source_location& sloc = CH_SOURCE_LOCATION) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    ch_bit<N> ret(bit_buffer(N, sloc)); \
    cat_impl(ret, N, CH_FOR_EACH(CH_CAT_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  }
CH_VA_ARGS_MAP(CH_CAT)
#undef CH_CAT_TYPE
#undef CH_CAT_TMPL
#undef CH_CAT_REQUIRE
#undef CH_CAT_DECL
#undef CH_CAT_ARG
#undef CH_CAT

// zero-extend

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_compatible<R>::value),
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
R ch_zext(const T& obj, const source_location& sloc = CH_SOURCE_LOCATION) {
  static_assert(width_v<R> >= width_v<T>, "invalid extend size");
  if constexpr(width_v<T> < width_v<R>) {
    auto pad = ch_bit<(width_v<R> - width_v<T>)>(0x0, sloc);
    return ch_cat(pad, obj, sloc).template as<R>();
  } else {    
    return R(obj, sloc);
  }
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
auto ch_zext(const T& obj, const source_location& sloc = CH_SOURCE_LOCATION) {
  return ch_zext<ch_bit<N>>(obj, sloc);
}

// sign-extend

template <typename R, typename T,
          CH_REQUIRE_0(is_bit_compatible<R>::value),
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
R ch_sext(const T& obj, const source_location& sloc = CH_SOURCE_LOCATION) {
  static_assert(width_v<R> >= width_v<T>, "invalid extend size");
  if constexpr(width_v<T> < width_v<R>) {
    static constexpr unsigned D = width_v<R> - width_v<T>;
    auto pad = ch_bit<D>(0x0) - ch_zext<D>(obj[width_v<T> - 1], sloc);
    return ch_cat(pad, obj, sloc).template as<R>();
  } else {
    return R(obj, sloc);
  }
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
ch_bit<N> ch_sext(const T& obj, const source_location& sloc = CH_SOURCE_LOCATION) {
  return ch_sext<ch_bit<N>>(obj, sloc);
}

// shuffle

template <unsigned N, typename T,
          CH_REQUIRE_0(is_bit_compatible<T>::value)>
auto ch_shuffle(const T& obj,
                const std::array<unsigned, N>& indices,
                const source_location& sloc = CH_SOURCE_LOCATION) {
  static_assert(0 == (width_v<T> % N), "invalid indices size");
  static constexpr unsigned M = (width_v<T> / N);
  ch_bit<width_v<T>> ret(bit_buffer(width_v<T>, sloc));
  for (unsigned i = 0; i < N; ++i) {
    unsigned j = indices[N - 1 - i];
    assert(j < N);
    ret. template slice<M>(i * M) = ch_slice<M>(obj, j * M);
  }
  return ret;
}

// tap

template <typename T,
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
void ch_tap(const std::string& name, const T& value) {
  registerTap(name, get_lnode(value));
}

// print

const ch_bit<64> ch_getTick();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRE_0(are_all_logic_compatible<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

// global operators

CH_GLOBAL_OP_AND_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_OR_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_XOR_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_ADD_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_SUB_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_MULT_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_DIV_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)
CH_GLOBAL_OP_MOD_SZ((template<unsigned N, unsigned M, CH_REQUIRE_0(M != N)>), const const_bit<N>&, const const_bit<M>&)

#define CH_BIT_GLOBAL_OPS(i, x) \
  CH_GLOBAL_OP_EQ((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_NE((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_LT((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_LE((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_GT((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_GE((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_AND((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_OR((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_XOR((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_NAND((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_NOR((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_XNOR((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_ADD((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_SUB((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_MULT((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_DIV((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_MOD((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_SLL((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_SRL((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_SRA((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_ROTL((template <unsigned N>), const const_bit<N>&, x) \
  CH_GLOBAL_OP_ROTR((template <unsigned N>), const const_bit<N>&, x)

CH_FOR_EACH(CH_BIT_GLOBAL_OPS, CH_SEP_SPACE, CH_BIT_OP_TYPES)

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
