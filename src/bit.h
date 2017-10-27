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

template <unsigned Bitwidth, typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct logic_traits {
  static constexpr unsigned bitwidth = Bitwidth;
  using logic_type  = LogicType;
  using const_type  = ConstType;
  using value_type  = ValueType;
  using scalar_type = ScalarType;
};

template <typename T>
using logic_type_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
using value_type_t = typename logic_type_t<std::decay_t<T>>::traits::value_type;

template <typename T>
using const_type_t = typename logic_type_t<std::decay_t<T>>::traits::const_type;

template <typename T>
using is_const_type = is_true<std::is_same<T, const_type_t<T>>::value>;

template <typename T>
struct is_logic_traits : std::false_type {};

template <unsigned Bitwidth, typename LogicType, typename ConstType, typename ValueType, typename ScalarType>
struct is_logic_traits<logic_traits<Bitwidth, LogicType, ConstType, ValueType, ScalarType>> : std::true_type {};

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits<typename std::decay_t<T>::traits>::value);

CH_DEF_SFINAE_CHECK(is_bit_compatible, (!is_scalar_type<T>::value
                                     && std::is_same<ch_bit<bitwidth_v<T>>, value_type_t<T>>::value));

template <typename... Ts>
using deduce_ch_bit_t = std::conditional_t<
  is_bit_compatible<deduce_type_t<Ts...>>::value,
  deduce_type_t<Ts...>,
  non_bitsize_type>;

template <typename T0, typename T1>
using deduce_first_ch_bit_t = std::conditional_t<
  (is_bit_compatible<T0>::value || is_bit_compatible<T1>::value),
  deduce_first_type_t<T0, T1>,
  non_bitsize_type>;

template <typename T, unsigned N = T::traits::bitwidth>
using is_bit_convertible = is_cast_convertible<ch_bit<N>, T>;

template <typename... Ts>
using are_all_bit_convertible = conjunction<is_bit_convertible<Ts>::value...>;

template <typename... Ts>
using are_all_logic_type = conjunction<is_logic_type<Ts>::value...>;

///////////////////////////////////////////////////////////////////////////////

class bit_buffer_impl;

using bit_buffer_ptr = std::shared_ptr<bit_buffer_impl>;

class bit_buffer_impl {
public:
  bit_buffer_impl(unsigned size);

  bit_buffer_impl(const bit_buffer_impl& rhs);

  bit_buffer_impl(bit_buffer_impl&& rhs);

  bit_buffer_impl(const lnode& data);

  bit_buffer_impl(lnode&& data);

  bit_buffer_impl(unsigned size, const bit_buffer_ptr& buffer, unsigned offset);

  bit_buffer_impl& operator=(const bit_buffer_impl& rhs);

  bit_buffer_impl& operator=(bit_buffer_impl&& rhs);

  void write(uint32_t dst_offset,
             const bit_buffer_impl& src,
             uint32_t src_offset,
             uint32_t length);

  void set_data(const lnode& data);

  const lnode& get_data() const;

  const auto& get_source() const {
    return source_;
  }

  auto& get_source() {
    return source_;
  }

  auto get_offset() const {
    return offset_;
  }

  auto get_size() const {
    return size_;
  }

  virtual void write(uint32_t dst_offset,
                     const lnode& data,
                     uint32_t src_offset,
                     uint32_t length);
protected:

  bit_buffer_ptr source_;
  mutable lnode value_;
  unsigned offset_;
  unsigned size_;  
};

class bit_buffer : public bit_buffer_ptr {
public:
  using base = bit_buffer_ptr;
  using base::operator*;
  using base::operator->;

  template <typename... Args>
  explicit bit_buffer(Args&&... args)
    : base(new bit_buffer_impl(std::forward<Args>(args)...))
  {}

  bit_buffer(bit_buffer_impl* rhs) : base(rhs) {}

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

struct bit_accessor {
  template <typename T>
  static const auto& get_buffer(const T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    return obj.get_buffer();
  }

  template <typename T>
  static auto& get_buffer(T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    return obj.get_buffer();
  }

  template <typename T>
  static const auto& get_data(const T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    return obj.get_buffer()->get_data();
  }

  template <typename T>
  static void set_data(const T& obj, const lnode& data) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    obj.get_buffer()->set_data(data);
  }

  template <typename T>
  static auto cloneBuffer(const T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    return bit_buffer(obj.get_buffer()->get_data());
  }

  template <typename U, typename V,
            CH_REQUIRES(bitwidth_v<U> == bitwidth_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(bitwidth_v<U> == dst.get_buffer()->get_size());
    assert(bitwidth_v<V> == src.get_buffer()->get_size());
    dst.get_buffer()->write(0, *src.get_buffer(), 0, bitwidth_v<V>);
  }

  template <typename U, typename V,
            CH_REQUIRES(bitwidth_v<U> == bitwidth_v<V>)>
  static void move(U& dst, V&& src) {
    assert(bitwidth_v<U> == dst.get_buffer()->get_size());
    *dst.get_buffer() = std::move(*src.get_buffer());
  }

  template <typename U, typename V>
  static void write(U& dst,
                    unsigned dst_offset,
                    const V& src,
                    unsigned src_offset,
                    unsigned length) {
    dst.get_buffer()->write(dst_offset, *src.get_buffer(), src_offset, length);
  }

  template <typename T>
  static const auto clone(const T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    return value_type_t<T>(bit_buffer(obj.get_buffer()->get_data().clone()));
  }

  template <typename D, typename T>
  static auto cast(const T& obj) {
    assert(bitwidth_v<T> == obj.get_buffer()->get_size());
    using return_type = std::conditional_t<is_const_type<T>::value, const_type_t<D>, D>;
    return return_type(bit_buffer(bitwidth_v<T>, obj.get_buffer(), 0));
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N = bitwidth_v<T>>
using bit_cast_t = std::conditional_t<is_logic_type<T>::value, const T&, ch_bit<N>>;

template <typename T, unsigned N = bitwidth_v<T>,
          CH_REQUIRES(is_bit_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  return bit_accessor::get_data(static_cast<bit_cast_t<T, N>>(rhs));
}

template <typename T>
const auto make_type(const lnode& node) {
  return T(bit_buffer(node));
};

///////////////////////////////////////////////////////////////////////////////

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpBinary(const A& a, const B& b) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N, unsigned M, typename A, typename B>
const auto OpShiftOp(const A& a, const B& b) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, M>(b)));
}

template <ch_alu_op op, unsigned N, typename A, typename B>
const auto OpCompare(const A& a, const B& b) {
  return make_type<ch_bit<1>>(createAluNode(op, get_lnode<A, N>(a), get_lnode<B, N>(b)));
}

template <ch_alu_op op, unsigned N>
const auto OpUnary(const const_bit<N>& a) {
  return make_type<ch_bit<N>>(createAluNode(op, get_lnode(a)));
}

template <ch_alu_op op, unsigned N>
const auto OpReduce(const const_bit<N>& a) {
  return make_type<ch_bit<1>>(createAluNode(op, get_lnode(a)));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_BIT_FRIEND_OPS(i, x) \
  CH_FRIEND_OP_EQ(, const const_bit&, x) \
  CH_FRIEND_OP_NE(, const const_bit&, x) \
  CH_FRIEND_OP_LT(, const const_bit&, x) \
  CH_FRIEND_OP_LE(, const const_bit&, x) \
  CH_FRIEND_OP_GT(, const const_bit&, x) \
  CH_FRIEND_OP_GE(, const const_bit&, x) \
  CH_FRIEND_OP_AND(, const const_bit&, x) \
  CH_FRIEND_OP_OR(, const const_bit&, x) \
  CH_FRIEND_OP_XOR(, const const_bit&, x) \
  CH_FRIEND_OP_ADD(, const const_bit&, x) \
  CH_FRIEND_OP_SUB(, const const_bit&, x) \
  CH_FRIEND_OP_MULT(, const const_bit&, x) \
  CH_FRIEND_OP_DIV(, const const_bit&, x) \
  CH_FRIEND_OP_MOD(, const const_bit&, x) \
  CH_FRIEND_OP_SLL(, const const_bit&, x) \
  CH_FRIEND_OP_SRL(, const const_bit&, x) \

#define CH_BIT_OP_TYPES \
  ch_scalar<N>, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_BIT_READONLY_INTERFACE(type) \
  template <typename R> \
  auto as() const { \
    return ch::internal::bit_accessor::cast<R>(*this); \
  } \
  auto asBits() const { \
    return this->as<ch_bit<type::traits::bitwidth>>(); \
  }

#define CH_BIT_WRITABLE_INTERFACE(type)

template <unsigned N>
class const_bit {
public:  
  using traits = logic_traits<N, const_bit, const_bit, ch_bit<N>, ch_scalar<N>>;

  const_bit(const bit_buffer& buffer = bit_buffer(N)) : buffer_(buffer) {}

  const_bit(const const_bit& rhs) : buffer_(bit_accessor::cloneBuffer(rhs)) {}

  const_bit(const_bit&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  const_bit(const ch_scalar<N>& rhs) : buffer_(scalar_accessor::get_data(rhs)) {}

  template <typename U,
            CH_REQUIRES(is_logic_type<U>::value),
            CH_REQUIRES(N == bitwidth_v<U>)>
  explicit const_bit(const U& rhs) : buffer_(bit_accessor::cloneBuffer(rhs)) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_convertible<U>::value)>
  explicit const_bit(const U& rhs) : buffer_(bitvector(N, rhs)) {}

  // slicing operators

  const auto operator[](size_t index) const {
    return const_bit<1>(bit_buffer(1, buffer_, index));
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_bit<M>(bit_buffer(M, buffer_, start));
  }

  // compare operators

  const auto operator==(const const_bit& rhs) const {
    return OpCompare<alu_eq, N>(*this, rhs);
  }

  const auto operator!=(const const_bit& rhs) const {
    return OpCompare<alu_ne, N>(*this, rhs);
  }

  const auto operator<(const const_bit& rhs) const {
    return OpCompare<alu_lt, N>(*this, rhs);
  }

  const auto operator<=(const const_bit& rhs) const {
    return OpCompare<alu_le, N>(*this, rhs);
  }

  const auto operator>(const const_bit& rhs) const {
    return OpCompare<alu_gt, N>(*this, rhs);
  }

  const auto operator>=(const const_bit& rhs) const {
    return OpCompare<alu_ge, N>(*this, rhs);
  }

  // bitwise operators

  const auto operator~() const {
    return OpUnary<alu_inv>(*this);
  }

  const auto operator&(const const_bit& rhs) const {
    return OpBinary<alu_and, N>(*this, rhs);
  }

  const auto operator|(const const_bit& rhs) const {
    return OpBinary<alu_or, N>(*this, rhs);
  }

  const auto operator^(const const_bit& rhs) const {
    return OpBinary<alu_xor, N>(*this, rhs);
  }

  // arithmetic operators

  const auto operator-() const {
    return OpUnary<alu_neg>(*this);
  }

  const auto operator+(const const_bit& rhs) const {
    return OpBinary<alu_add, N>(*this, rhs);
  }

  const auto operator-(const const_bit& rhs) const {
    return OpBinary<alu_sub, N>(*this, rhs);
  }

  const auto operator*(const const_bit& rhs) const {
    return OpBinary<alu_mult, N>(*this, rhs);
  }

  const auto operator/(const const_bit& rhs) const {
    return OpBinary<alu_div, N>(*this, rhs);
  }

  const auto operator%(const const_bit& rhs) const {
    return OpBinary<alu_mod, N>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  const auto operator<<(const const_bit<M>& rhs) const {
    return OpShiftOp<alu_sll, N, M>(*this, rhs);
  }

  template <unsigned M>
  const auto operator>>(const const_bit<M>& rhs) const {
    return OpShiftOp<alu_srl, N, M>(*this, rhs);
  }

  CH_BIT_READONLY_INTERFACE(const_bit)

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
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public const_bit<N> {
public:  
  using traits = logic_traits<N, ch_bit, const_bit<N>, ch_bit, ch_scalar<N>>;
  using base = const_bit<N>;
  using base::buffer_;
      
  ch_bit(const bit_buffer& buffer = bit_buffer(N)) : base(buffer) {}
  
  ch_bit(const ch_bit& rhs) : base(rhs) {}

  ch_bit(ch_bit&& rhs) : base(std::move(rhs)) {}

  ch_bit(const const_bit<N>& rhs) : base(rhs) {}

  ch_bit(const ch_scalar<N>& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_logic_type<U>::value),
            CH_REQUIRES(N == bitwidth_v<U>)>
  explicit ch_bit(const U& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_bitvector_convertible<U>::value || std::is_enum<U>::value)>
  explicit ch_bit(const U& rhs) : base(rhs) {}

  ch_bit& operator=(const ch_bit& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    bit_accessor::move(*this, std::move(rhs));
    return *this;
  }

  ch_bit& operator=(const const_bit<N>& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename T,
            CH_REQUIRES(is_logic_type<T>::value),
            CH_REQUIRES(N == bitwidth_v<T>)>
  ch_bit& operator=(const T& rhs) {
    bit_accessor::copy(*this, rhs);
    return *this;
  }

  ch_bit& operator=(const ch_scalar<N>& rhs) {
    buffer_->set_data(scalar_accessor::get_data(rhs));
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum_v<U>)>
  ch_bit& operator=(U rhs) {
    buffer_->set_data(bitvector(N, rhs));
    return *this;
  }

  const auto operator[](size_t index) const {
    return const_bit<1>(bit_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    return ch_bit<1>(bit_buffer(1, buffer_, index)); \
  }

  template <unsigned M>
  const auto slice(size_t start = 0) const {
    return const_bit<M>(bit_buffer(M, buffer_, start));
  }

  template <unsigned M>
  auto slice(size_t start = 0) {
    return ch_bit<M>(bit_buffer(M, buffer_, start));
  }

  CH_BIT_WRITABLE_INTERFACE(ch_bit)
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <unsigned N>
inline const auto ch_eq(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs == rhs);
}

template <unsigned N>
inline const auto ch_ne(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs != rhs);
}

template <unsigned N>
inline const auto ch_lt(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs < rhs);
}

template <unsigned N>
inline const auto ch_le(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs <= rhs);
}

template <unsigned N>
inline const auto ch_gt(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs > rhs);
}

template <unsigned N>
inline const auto ch_ge(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs >= rhs);
}

// bitwise operators

template <unsigned N>
inline const auto ch_and(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs & rhs);
}

template <unsigned N>
inline const auto ch_or(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs | rhs);
}

template <unsigned N>
inline const auto ch_xor(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs ^ rhs);
}

// arithmetic operators

template <unsigned N>
inline const auto ch_add(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs + rhs);
}

template <unsigned N>
inline const auto ch_sub(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs - rhs);
}

template <unsigned N>
inline const auto ch_mult(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs * rhs);
}

template <unsigned N>
inline const auto ch_div(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return (lhs / rhs);
}

// shift operators

template <unsigned N, unsigned M>
inline const auto ch_sll(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline const auto ch_srl(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return (lhs >> rhs);
}

// unary operators

template <unsigned N>
const auto ch_inv(const const_bit<N>& in) {
  return ~in;
}

template <unsigned N>
const auto ch_neg(const const_bit<N>& in) {
  return -in;
}

// bitwise operators

template <unsigned N>
const auto ch_nand(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return OpBinary<alu_nand, N>(lhs, rhs);
}

template <unsigned N>
const auto ch_nor(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return OpBinary<alu_nor, N>(lhs, rhs);
}

template <unsigned N>
const auto ch_xnor(const const_bit<N>& lhs, const const_bit<N>& rhs) {
  return OpBinary<alu_xnor, N>(lhs, rhs);
}

// reduce operators

template <unsigned N>
const auto ch_andr(const const_bit<N>& in) {
  return OpReduce<alu_andr>(in);
}

template <unsigned N>
const auto ch_orr(const const_bit<N>& in) {
  return OpReduce<alu_orr>(in);
}

template <unsigned N>
const auto ch_xorr(const const_bit<N>& in) {
  return OpReduce<alu_xorr>(in);
}

template <unsigned N>
const auto ch_nandr(const const_bit<N>& in) {
  return OpReduce<alu_nandr>(in);
}

template <unsigned N>
const auto ch_norr(const const_bit<N>& in) {
  return OpReduce<alu_norr>(in);
}

template <unsigned N>
const auto ch_xnorr(const const_bit<N>& in) {
  return OpReduce<alu_xnorr>(in);
}

// shift operators

template <unsigned N, unsigned M>
const auto ch_sra(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_sra, N, M>(lhs, rhs);
}

template <unsigned N, unsigned M>
const auto ch_rotl(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_rotl, N, M>(lhs, rhs);
}

template <unsigned N, unsigned M>
const auto ch_rotr(const const_bit<N>& lhs, const const_bit<M>& rhs) {
  return OpShiftOp<alu_rotr, N, M>(lhs, rhs);
}

// logic operators

inline const auto operator! (const const_bit<1>& in) {
  return ~in;
}

inline const auto operator&& (const const_bit<1>& lhs, const const_bit<1>& rhs) {
  return lhs & rhs;
}

inline const auto operator|| (const const_bit<1>& lhs, const const_bit<1>& rhs) {
  return lhs | rhs;
}

// generate global operators for convertible types

#define CH_BIT_GLOBAL_OPS(i, x) \
  CH_GLOBAL_OP_EQ(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_NE(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_LT(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_LE(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_GT(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_GE(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_AND(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_OR(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_XOR(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_NAND(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_NOR(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_XNOR(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_ADD(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_SUB(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_MULT(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_DIV(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_MOD(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_SLL(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_SRL(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_SRA(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_ROTL(template <unsigned N>, const const_bit<N>&, x) \
  CH_GLOBAL_OP_ROTR(template <unsigned N>, const const_bit<N>&, x)

CH_FOR_EACH(CH_BIT_GLOBAL_OPS, CH_SEP_SPACE, CH_BIT_OP_TYPES)

///////////////////////////////////////////////////////////////////////////////

// multiplexers

template <typename I, typename S,
          CH_REQUIRES(is_logic_type<I>::value),
          CH_REQUIRES(is_logic_type<S>::value),
          CH_REQUIRES(ispow2(bitwidth_v<I>)),
          CH_REQUIRES(ispow2(bitwidth_v<S>)),
          CH_REQUIRES((bitwidth_v<I> >> bitwidth_v<S>) != 0)>
const auto ch_mux(const I& in, const S& sel) {
  return make_type<ch_bit<(bitwidth_v<I> >> bitwidth_v<S>)>>(
        createAluNode(alu_mux, get_lnode(in), get_lnode(sel)));
}

// clone function

template <typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
const auto ch_clone(const T& obj) {
  return bit_accessor::clone(obj);
}

// slice functions

template <unsigned N, typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
const auto ch_slice(const T& obj, size_t start = 0) {
  ch_bit<N> ret;
  bit_accessor::write(ret, 0, obj, start, N);
  return ret;
}

// concatenation function

template <unsigned N, typename T>
void cat_impl(ch_bit<N>& inout, unsigned dst_offset, const T& arg) {
  bit_accessor::write(inout, dst_offset - bitwidth_v<T>, arg, 0, bitwidth_v<T>);
}

template <unsigned N, typename T0, typename... Ts>
void cat_impl(ch_bit<N>& inout, unsigned dst_offset, const T0& arg0, const Ts&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - bitwidth_v<T0>, args...);
}

template <typename... Ts,
         CH_REQUIRES(are_all_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  ch_bit<bitwidth_v<Ts...>> ret;
  cat_impl(ret, bitwidth_v<Ts...>, static_cast<bit_cast_t<Ts>>(args)...);
  return ret;
}

template <typename B, typename A,
          CH_REQUIRES(is_bit_convertible<B>::value),
          CH_REQUIRES(is_bit_convertible<A>::value)>
const auto operator,(const B& b, const A& a) {
  return ch_cat(b, a);
}

// tie function

template <typename... Ts>
class tie_impl {
public:
  tie_impl(Ts&... args) : args_(args...) {}

  template <typename T>
  void operator=(const T& rhs) {
    this->assign(static_cast<bit_cast_t<T, bitwidth_v<Ts...>>>(rhs), std::index_sequence_for<Ts...>());
  }

protected:

  template <typename T, size_t... I>
  void assign(const T& src, std::index_sequence<I...>) {
    this->assign(0, src, std::get<sizeof...(Ts) - 1 - I>(args_)...);
  }

  template <typename T, typename U>
  void assign(unsigned src_offset, const T& src, U& dst) {
    dst = ch_slice<bitwidth_v<U>>(src, src_offset). template as<U>();
  }

  template <typename T, typename U0, typename... Us>
  void assign(unsigned src_offset, const T& src, U0& dst0, Us&... dsts) {
    this->assign(src_offset, src, dst0);
    this->assign(src_offset + bitwidth_v<U0>, src, dsts...);
  }

  std::tuple<Ts&...> args_;
};

template <typename... Ts,
         CH_REQUIRES(are_all_logic_type<Ts...>::value)>
auto ch_tie(Ts&... args) {
  return tie_impl<Ts...>(args...);
}

// zero-extend function

template <unsigned D>
class zext_impl {
public:
    template <typename T>
    const auto operator() (const T& obj) {
      return ch_cat(ch_bit<D>(0x0), obj);
    }
};

template <>
struct zext_impl<0> {
    template <typename T>
    const auto operator() (const T& obj) {
      return ch_bit<bitwidth_v<T>>(obj);
    }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_zext(const T& obj) {
  static_assert(N >= bitwidth_v<T>, "invalid extend size");
  return zext_impl<(N-bitwidth_v<T>)>()(obj);
}

// sign-extend function

template <unsigned D>
struct sext_impl {
  template <typename T>
  const auto operator() (const T& obj) {
    auto pad = ch_bit<D>(0x0) - ch_zext<D>(obj[bitwidth_v<T> - 1]);
    return ch_cat(pad, obj);
  }
};

template <>
struct sext_impl<0> {
  template <typename T>
  const auto operator() (const T& obj) {
    return ch_bit<bitwidth_v<T>>(obj);
  }
};

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_sext(const T& obj) {
  static_assert(N >= bitwidth_v<T>, "invalid extend size");
  return sext_impl<(N-bitwidth_v<T>)>()(obj);
}

// shuffle functions

template <unsigned N, typename T,
          CH_REQUIRES(is_bit_convertible<T>::value)>
const auto ch_shuffle(const T& obj,
                      const std::array<uint32_t, bitwidth_v<T>>& indices) {
  static_assert((bitwidth_v<T> % N) == 0, "invalid indices size");
  static const unsigned M = (N / bitwidth_v<T>);
  ch_bit<N> ret;
  for (unsigned i = 0; i < bitwidth_v<T>; ++i) {
    ch_slice<M>(ret, i * M) = ch_slice<M>(obj, indices[i] * M);
  }
  return ret;
}

// tap functions

template <typename T,
          CH_REQUIRES(is_logic_type<T>::value)>
void ch_tap(const std::string& name, const T& value) {
  registerTap(name, get_lnode(value));
}

// print functions

const ch_bit<64> ch_getTick();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRES(are_all_bit_convertible<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

}
}

#define CH_TIE(...) std::forward_as_tuple(__VA_ARGS__)

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
