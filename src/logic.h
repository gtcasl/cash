#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

void registerTap(const std::string& name, const lnode& node);

void createPrintNode(const std::string& format, const std::initializer_list<lnode>& args);

///////////////////////////////////////////////////////////////////////////////

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

template <unsigned M, unsigned N>
ch_logic<M> ch_pad(const ch_logic<N>& obj, const source_location& sloc);

template <unsigned Bitwidth, bool Signed, typename LogicType, typename ScalarType>
struct logic_traits {
  static constexpr traits_type type = traits_logic;
  static constexpr unsigned bitwidth = Bitwidth;
  static constexpr unsigned is_signed = Signed;
  using logic_type  = LogicType;
  using scalar_type = ScalarType;
};

template <typename T>
using logic_type_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
using is_logic_traits = is_true<(T::type & traits_logic)>;

CH_DEF_SFINAE_CHECK(is_logic_only, is_true<(std::decay_t<T>::traits::type == traits_logic)>::value);

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits<typename std::decay_t<T>::traits>::value);

CH_DEF_SFINAE_CHECK(is_logic_compatible, (std::is_base_of<ch_logic<width_v<T>>, T>::value));

#if defined(__clang__)
  #define CH_SRC_LOCATION source_location(__FILE__, __LINE__)
#else
  #define CH_SRC_LOCATION source_location(__builtin_FILE(), __builtin_LINE())
#endif

template <typename... Ts>
using deduce_logic_t = std::conditional_t<
  is_logic_compatible<deduce_type_t<false, Ts...>>::value,
  deduce_type_t<false, Ts...>,
  non_ch_type>;

template <typename T0, typename T1>
using deduce_first_logic_t = std::conditional_t<
  (is_logic_compatible<T0>::value || is_logic_compatible<T1>::value),
  deduce_first_type_t<T0, T1>,
  non_ch_type>;

template <typename T, unsigned N = T::traits::bitwidth>
using is_logic_convertible = is_cast_convertible<ch_logic<N>, T>;

template <typename... Ts>
using are_all_logic_type = conjunction<is_logic_type<Ts>::value...>;

///////////////////////////////////////////////////////////////////////////////

class logic_buffer;

using logic_buffer_ptr = std::shared_ptr<logic_buffer>;

class logic_buffer {
public:
  explicit logic_buffer(unsigned size,
                             const source_location& sloc = source_location(),
                             const std::string& name = "");

  logic_buffer(const logic_buffer& rhs,
                    const source_location& sloc = source_location(),
                    const std::string& name = "");

  logic_buffer(logic_buffer&& rhs);

  explicit logic_buffer(const lnode& data,
                             const source_location& sloc = source_location(),
                             const std::string& name = "");

  logic_buffer(unsigned size,
                    const logic_buffer_ptr& buffer,
                    unsigned offset,
                    const source_location& sloc = source_location(),
                    const std::string& name = "");

  virtual ~logic_buffer() {}

  logic_buffer& operator=(const logic_buffer& rhs);

  logic_buffer& operator=(logic_buffer&& rhs);

  const lnode& get_data() const;

  virtual void write(uint32_t dst_offset,
                     const lnode& data,
                     uint32_t src_offset,
                     uint32_t length);

  void write(const lnode& data) {
    this->write(0, data, 0, data.size());
  }

  void copy(const logic_buffer& rhs) {
    this->write(0, rhs.get_data(), 0, rhs.size());
  }

  uint32_t get_id() const {
    return id_;
  }

  unsigned size() const {
    return value_.size();
  }

  const logic_buffer_ptr& get_source() const {
    return source_;
  }

  logic_buffer_ptr& get_source() {
    return source_;
  }

  unsigned get_offset() const {
    return offset_;
  }

protected:

  logic_buffer(const lnode& value,
                    const logic_buffer_ptr& source,
                    unsigned offset);
  uint32_t id_;
  lnode value_;
  logic_buffer_ptr source_;
  unsigned offset_;
};

template <typename... Args>
auto make_logic_buffer(Args&&... args) {
  return std::make_shared<logic_buffer>(std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static const logic_buffer_ptr& get_buffer(const T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static logic_buffer_ptr& get_buffer(T& obj) {
    return obj.get_buffer();
  }

  template <typename T>
  static const lnode& get_data(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->size());
    return obj.get_buffer()->get_data();
  }

  template <typename T>
  static void set_data(const T& obj, const lnode& data) {
    assert(width_v<T> == obj.get_buffer()->size());
    auto& obj_data = obj.get_buffer()->get_data();
    const_cast<lnode&>(data).set_var_id(obj_data.get_var_id());
    const_cast<lnode&>(data).set_source_location(obj_data.get_source_location());
    obj.get_buffer()->write(data);
  }

  template <typename T>
  static auto copy_buffer(const T& obj,
                          const source_location& sloc = CH_SRC_LOCATION,
                          const std::string& name = "") {
    assert(width_v<T> == obj.get_buffer()->size());
    return make_logic_buffer(*obj.get_buffer(), sloc, name);
  }

  template <typename U, typename V,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(is_logic_type<V>::value),
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(width_v<U> == dst.get_buffer()->size());
    assert(width_v<V> == src.get_buffer()->size());
    *dst.get_buffer() = *src.get_buffer();
  }

  template <typename U, typename V,
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void move(U& dst, V&& src) {
    assert(width_v<U> == dst.get_buffer()->size());
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
    assert(width_v<T> == obj.get_buffer()->size());
    auto data = obj.get_buffer()->get_data().clone();
    return T(make_logic_buffer(data, sloc));
  }

  template <typename D, typename T>
  static auto cast(const T& obj) {
    assert(width_v<T> == obj.get_buffer()->size());
    return D(obj.get_buffer());
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = ch_logic<width_v<T>>>
using logic_cast_t = std::conditional_t<is_logic_type<T>::value, const T&, R>;

template <typename T, unsigned N = width_v<T>,
          CH_REQUIRE_0(is_logic_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  return logic_accessor::get_data(static_cast<logic_cast_t<T, ch_logic<N>>>(rhs));
}

template <typename T, typename R,
          CH_REQUIRE_0(is_cast_convertible<R, T>::value)>
lnode get_lnode(const T& rhs) {
  return logic_accessor::get_data(static_cast<logic_cast_t<T, R>>(rhs));
}

template <typename T>
auto make_type(const lnode& node) {
  return T(make_logic_buffer(node));
}

template <typename T>
using type_buffer_t = std::conditional_t<is_logic_traits<T>::value, logic_buffer, scalar_buffer>;

template <typename T>
using type_accessor_t = std::conditional_t<is_logic_traits<T>::value, logic_accessor, scalar_accessor>;

template <typename T,
          typename U,
          typename Q = typename T::traits,
          typename X = typename ch_type_t<U>::traits>
using aggregate_init_cast_t = std::conditional_t<X::bitwidth != 0,
      std::conditional_t<(Q::type == X::type),
                         const U&,
                         std::conditional_t<is_logic_traits<Q>::value,
                                            ch_logic<X::bitwidth>,
                                            ch_scalar<X::bitwidth>>>,
      std::conditional_t<is_logic_traits<Q>::value,
                         ch_logic<Q::bitwidth>,
                         ch_scalar<Q::bitwidth>>>;

///////////////////////////////////////////////////////////////////////////////

template <ch_op op, typename R, typename A>
auto LogicOp(const A& a) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a));
  return R(make_logic_buffer(node));
}

template <ch_op op, typename R, typename A, typename B>
auto LogicOp(const A& a, const B& b) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a), get_lnode(b));
  return R(make_logic_buffer(node));
}

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_FRIEND_OP1(i, x) \
  CH_FRIEND_OP1((), &&, const ch_logic&, x) \
  CH_FRIEND_OP1((), ||, const ch_logic&, x) \
  CH_FRIEND_OP1((), ==, const ch_logic&, x) \
  CH_FRIEND_OP1((), !=, const ch_logic&, x) \
  CH_FRIEND_OP1((), &, const ch_logic&, x) \
  CH_FRIEND_OP1((), |, const ch_logic&, x) \
  CH_FRIEND_OP1((), ^, const ch_logic&, x)

#define CH_LOGIC_GLOBAL_FUNC1(i, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_eq, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_ne, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_and, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_or, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_xor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_nand, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_nor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1((template <unsigned N>), ch_xnor, const ch_logic<N>&, x)

#define CH_LOGIC_OP1_TYPES \
  const ch_scalar<N>&, \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_FRIEND_OP2(i, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ==, const ch_logic&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), !=, const ch_logic&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_logic&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_logic&, x) \
  CH_FRIEND_OP2((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_logic&, x)

#define CH_LOGIC_GLOBAL_FUNC2(i, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_eq, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_ne, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_and, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_or, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_nand, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_nor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xnor, const ch_logic<N>&, x)

#define CH_LOGIC_OP2_TYPES \
  const ch_logic<M>&, const ch_scalar<M>&

#define CH_LOGIC_FRIEND_OP3(i, x) \
  CH_FRIEND_OP3((), <<, const ch_logic&, x, ch_logic<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3((), >>, const ch_logic&, x, ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_GLOBAL_FUNC3(i, x) \
  CH_GLOBAL_FUNC3((template <unsigned N>), ch_sll, const ch_logic<N>&, x, ch_logic<CH_WIDTH_OF(x)>&) \
  CH_GLOBAL_FUNC3((template <unsigned N>), ch_srl, const ch_logic<N>&, x, ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_FRIEND_OP4(i, x) \
  CH_FRIEND_OP3((template <unsigned M>), <<, const ch_logic&, x, ch_logic<M>&) \
  CH_FRIEND_OP3((template <unsigned M>), >>, const ch_logic&, x, ch_logic<M>&)

#define CH_LOGIC_GLOBAL_FUNC4(i, x) \
  CH_GLOBAL_FUNC3((template <unsigned N, unsigned M>), ch_sll, const ch_logic<N>&, x, ch_logic<M>&) \
  CH_GLOBAL_FUNC3((template <unsigned N, unsigned M>), ch_srl, const ch_logic<N>&, x, ch_logic<M>&)

#define CH_LOGIC_OP4_TYPES \
  const ch_scalar<M>&

#define CH_LOGIC_INTERFACE(type) \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type<R>::value)> \
  const auto as() const { \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type<R>::value)> \
  auto as() { \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  const auto as_bit() const { \
    return this->as<ch::internal::ch_logic<type::traits::bitwidth>>(); \
  } \
  auto as_bit() { \
    return this->as<ch::internal::ch_logic<type::traits::bitwidth>>(); \
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
  auto as_reg(const source_location& sloc = CH_SRC_LOCATION) { \
    ch_reg<type> s(sloc); \
    (*this) = s; \
    return s; \
  } \
  auto as_reg(const type& init, const source_location& sloc = CH_SRC_LOCATION) { \
    ch_reg<type> s(init, sloc); \
    (*this) = s; \
    return s; \
  }

template <unsigned N>
class ch_logic {
public:
  using traits = logic_traits<N, false, ch_logic, ch_scalar<N>>;

  ch_logic(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_SRC_LOCATION))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  ch_logic(const ch_logic& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(logic_accessor::copy_buffer(rhs, sloc))
  {}

  ch_logic(ch_logic&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  ch_logic(const ch_scalar<N>& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(make_logic_buffer(scalar_accessor::get_data(rhs), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_logic(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(logic_accessor::copy_buffer(rhs, sloc))
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> <= N)>
  explicit ch_logic(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(make_logic_buffer(scalar_accessor::get_data(ch_scalar<N>(rhs)), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible<U>::value)>
  explicit ch_logic(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(make_logic_buffer(bitvector(N, rhs), sloc))
  {}

  ch_logic& operator=(const ch_logic& rhs) {
    logic_accessor::copy(*this, rhs);
    return *this;
  }

  ch_logic& operator=(ch_logic&& rhs) {
    logic_accessor::move(*this, std::move(rhs));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_logic_type<U>::value),
            CH_REQUIRE_0(width_v<U> == N)>
  ch_logic& operator=(const U& rhs) {
    logic_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type<U>::value),
            CH_REQUIRE_1(width_v<U> <= N)>
  ch_logic& operator=(const U& rhs) {
    buffer_->write(scalar_accessor::get_data(ch_scalar<N>(rhs)));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_logic& operator=(U rhs) {
    buffer_->write(bitvector(N, rhs));
    return *this;
  }

  // slicing operators

  const auto operator[](size_t index) const {
    assert(index < N);
    return ch_logic<1>(make_logic_buffer(1, buffer_, index));
  }

  auto operator[](size_t index) {
    assert(index < N);
    return ch_logic<1>(make_logic_buffer(1, buffer_, index));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type<R>::value)>
  const auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) const {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type<R>::value)>
  const auto aslice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) const {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  template <unsigned M>
  const auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) const {
    return this->slice<ch_logic<M>>(start, sloc);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) const {
    return this->slice<ch_logic<M>>(start * M, sloc);
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type<R>::value)>
  auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type<R>::value)>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  template <unsigned M>
  auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
    return this->slice<ch_logic<M>>(start, sloc);
  }

  template <unsigned M>
  auto aslice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
    return this->slice<ch_logic<M>>(start * M, sloc);
  }

  // compare operators

  auto operator==(const ch_logic& rhs) const {
    return LogicOp<op_eq, ch_logic<1>>(*this, rhs);
  }

  auto operator!=(const ch_logic& rhs) const {
    return LogicOp<op_ne, ch_logic<1>>(*this, rhs);
  }

  // logical operators

  auto operator&&(const ch_logic& rhs) const {
    static_assert(1 == N, "invalid size");
    return LogicOp<op_and, ch_logic>(*this, rhs);
  }

  auto operator||(const ch_logic& rhs) const {
    static_assert(1 == N, "invalid size");
    return LogicOp<op_or, ch_logic>(*this, rhs);
  }

  auto operator!() const {
    return (0x0 == *this);
  }

  // bitwise operators

  auto operator~() const {
    return LogicOp<op_inv, ch_logic>(*this);
  }

  auto operator&(const ch_logic& rhs) const {
    return LogicOp<op_and, ch_logic>(*this, rhs);
  }

  auto operator|(const ch_logic& rhs) const {
    return LogicOp<op_or, ch_logic>(*this, rhs);
  }

  auto operator^(const ch_logic& rhs) const {
    return LogicOp<op_xor, ch_logic>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_logic<M>& rhs) const {
    return LogicOp<op_sll, ch_logic>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_logic<M>& rhs) const {
    return LogicOp<op_srl, ch_logic>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_logic)

protected:

  const logic_buffer_ptr& get_buffer() const {
    return buffer_;
  }

  logic_buffer_ptr& get_buffer() {
    return buffer_;
  }

  logic_buffer_ptr buffer_;

  friend class logic_accessor;

  // friend operators

  CH_FOR_EACH(CH_LOGIC_FRIEND_OP1, CH_SEP_SPACE, CH_LOGIC_OP1_TYPES)
  CH_FOR_EACH(CH_LOGIC_FRIEND_OP2, CH_SEP_SPACE, CH_LOGIC_OP2_TYPES)
  CH_FOR_EACH(CH_LOGIC_FRIEND_OP3, CH_SEP_SPACE, CH_LOGIC_OP3_TYPES)
  CH_FOR_EACH(CH_LOGIC_FRIEND_OP4, CH_SEP_SPACE, CH_LOGIC_OP4_TYPES)
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <unsigned N>
inline auto ch_eq(const ch_logic<N>& lhs, const ch_logic<N>& rhs) {
  return (lhs == rhs);
}

template <unsigned N>
inline auto ch_ne(const ch_logic<N>& lhs, const ch_logic<N>& rhs) {
  return (lhs != rhs);
}

// bitwise operators

template <unsigned N>
auto ch_inv(const ch_logic<N>& in) {
  return ~in;
}

template <unsigned N>
inline auto ch_and(const ch_logic<N>& lhs, const ch_logic<N>& rhs) {
  return (lhs & rhs);
}

template <unsigned N>
inline auto ch_or(const ch_logic<N>& lhs, const ch_logic<N>& rhs) {
  return (lhs | rhs);
}

template <unsigned N>
inline auto ch_xor(const ch_logic<N>& lhs, const ch_logic<N>& rhs) {
  return (lhs ^ rhs);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const ch_logic<N>& lhs, const ch_logic<M>& rhs) {
  return (lhs << rhs);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_logic<N>& lhs, const ch_logic<M>& rhs) {
  return (lhs >> rhs);
}

// reduce operators

template <unsigned N>
auto ch_andr(const ch_logic<N>& in) {
  return LogicOp<op_andr, ch_logic<1>>(in);
}

template <unsigned N>
auto ch_orr(const ch_logic<N>& in) {
  return LogicOp<op_orr, ch_logic<1>>(in);
}

template <unsigned N>
auto ch_xorr(const ch_logic<N>& in) {
  return LogicOp<op_xorr, ch_logic<1>>(in);
}

// rotate operators

template <unsigned N>
auto ch_rotl(const ch_logic<N>& lhs, unsigned rhs) {
  auto node = createRotateNode(get_lnode(lhs), rhs, false);
  return make_type<ch_logic<N>>(node);
}

template <unsigned N>
auto ch_rotr(const ch_logic<N>& lhs, unsigned rhs) {
  auto node = createRotateNode(get_lnode(lhs), rhs, true);
  return make_type<ch_logic<N>>(node);
}

// cloning

template <typename T,
          CH_REQUIRE_0(is_logic_type<T>::value)>
auto ch_clone(const T& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return logic_accessor::clone(obj, sloc);
}

// slicing

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_type<R>::value),
          CH_REQUIRE_0(is_logic_type<T>::value)>
R ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> <= width_v<T>, "invalid size");
  assert((start + width_v<R>) <= width_v<T>);
  if constexpr(width_v<R> == width_v<T>) {
    if constexpr(std::is_same<R, T>::value) {
      return obj;
    } else {
      return R(obj, sloc);
    }
  } else {
    ch_logic<width_v<R>> ret(make_logic_buffer(width_v<R>, sloc));
    logic_accessor::write(ret, 0, obj, start, width_v<R>);
    return ret.template as<R>();
  }
}

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_type<R>::value),
          CH_REQUIRE_0(is_logic_type<T>::value)>
R ch_aslice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_slice<R>(obj, start * width_v<R>, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type<T>::value)>
auto ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_slice<ch_logic<N>>(obj, start, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type<T>::value)>
auto ch_aslice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_slice<ch_logic<N>>(obj, start * N, sloc);
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
    this->assign(static_cast<logic_cast_t<T, ch_logic<width_v<Ts...>>>>(rhs),
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
#define CH_TIE_REQUIRE(i, x) CH_REQUIRE_0(is_logic_type<__T##i>::value)
#define CH_TIE_DECL(i, x) __T##i& arg##i
#define CH_TIE_ARG(i, x) arg##i
#define CH_TIE(...) \
  template <CH_FOR_EACH(CH_TIE_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_TIE_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_tie(CH_FOR_EACH(CH_TIE_DECL, CH_SEP_COMMA, __VA_ARGS__), \
         const source_location& sloc = CH_SRC_LOCATION) { \
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
  logic_accessor::write(inout, dst_offset - width_v<T>, arg, 0, width_v<T>);
}

template <typename U, typename T0, typename... Ts>
void cat_impl(U& inout, unsigned dst_offset, const T0& arg0, const Ts&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - width_v<T0>, args...);
}

#define CH_CAT_TYPE(i, x) __T##i
#define CH_CAT_TMPL(i, x) typename __T##i
#define CH_CAT_REQUIRE(i, x) CH_REQUIRE_0(is_logic_convertible<__T##i>::value)
#define CH_CAT_DECL(i, x) const __T##i& arg##i
#define CH_CAT_ARG(i, x) static_cast<logic_cast_t<__T##i>>(arg##i)
#define CH_CAT(...) \
  template <typename R, \
            CH_FOR_EACH(CH_CAT_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_CAT_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), \
              const source_location& sloc = CH_SRC_LOCATION) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    static_assert(width_v<R> == N, "size mismatch"); \
    R ret(make_logic_buffer(N, sloc)); \
    cat_impl(ret, N, CH_FOR_EACH(CH_CAT_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  } \
  template <CH_FOR_EACH(CH_CAT_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_CAT_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), \
              const source_location& sloc = CH_SRC_LOCATION) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    ch_logic<N> ret(make_logic_buffer(N, sloc)); \
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

// padding

template <typename R, unsigned N>
auto ch_pad(const ch_logic<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> >= N, "invalid pad size");
  if constexpr(width_v<R> > N) {
    return LogicOp<op_zext, R>(obj);
  } else {
    return R(obj, sloc);
  }
}

template <unsigned M, unsigned N>
auto ch_pad(const ch_logic<N>& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_pad<ch_logic<M>>(obj, sloc);
}

// shuffle

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_compatible<T>::value)>
auto ch_shuffle(const T& obj,
                const std::array<unsigned, N>& indices,
                const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(0 == (width_v<T> % N), "invalid indices size");
  static constexpr unsigned M = (width_v<T> / N);
  ch_logic<width_v<T>> ret(make_logic_buffer(width_v<T>, sloc));
  for (unsigned i = 0; i < N; ++i) {
    auto j = indices[N - 1 - i];
    assert(j < N);
    ret. template slice<M>(i * M) = ch_slice<M>(obj, j * M);
  }
  return ret;
}

// tap

template <typename T,
          CH_REQUIRE_0(is_logic_type<T>::value)>
void ch_tap(const std::string& name, const T& value) {
  registerTap(name, get_lnode(value));
}

// print

ch_logic<64> ch_time();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRE_0(are_all_logic_type<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

// global functions

CH_FOR_EACH(CH_LOGIC_GLOBAL_FUNC1, CH_SEP_SPACE, CH_LOGIC_OP1_TYPES)
CH_FOR_EACH(CH_LOGIC_GLOBAL_FUNC2, CH_SEP_SPACE, CH_LOGIC_OP2_TYPES)
CH_FOR_EACH(CH_LOGIC_GLOBAL_FUNC3, CH_SEP_SPACE, CH_LOGIC_OP3_TYPES)

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
