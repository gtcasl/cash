#pragma once

#include "scalar.h"

namespace ch {
namespace internal {

void registerTap(const std::string& name,
                 const lnode& node,
                 const source_location& sloc);

void createPrintNode(const std::string& format,
                     const std::initializer_list<lnode>& args);

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
using logic_type_t = typename std::decay_t<T>::traits::logic_type;

template <typename T>
inline constexpr bool is_logic_traits_v = is_true_v<(T::type & traits_logic)>;

CH_DEF_SFINAE_CHECK(is_logic_only, is_true_v<(std::decay_t<T>::traits::type == traits_logic)>);

CH_DEF_SFINAE_CHECK(is_logic_type, is_logic_traits_v<typename std::decay_t<T>::traits>);

CH_DEF_SFINAE_CHECK(is_logic_compatible, (std::is_base_of_v<ch_logic<width_v<T>>, T>));

template <typename... Ts>
using deduce_logic_t = std::conditional_t<
  is_logic_compatible_v<deduce_type_t<false, Ts...>>,
  deduce_type_t<false, Ts...>,
  non_ch_type>;

template <typename T0, typename T1>
using deduce_first_logic_t = std::conditional_t<
  (is_logic_compatible_v<T0> || is_logic_compatible_v<T1>),
  deduce_first_type_t<T0, T1>,
  non_ch_type>;

template <typename T, unsigned N = T::traits::bitwidth>
inline constexpr bool is_logic_convertible_v = std::is_constructible_v<ch_logic<N>, T>;

template <typename... Ts>
inline constexpr bool are_all_logic_type_v = std::conjunction_v<is_logic_type<Ts>...>;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

template <unsigned M, unsigned N>
ch_logic<M> ch_pad(const ch_logic<N>& obj, const source_location& sloc = CH_SRC_LOCATION);

///////////////////////////////////////////////////////////////////////////////

class logic_buffer;

using logic_buffer_ptr = std::shared_ptr<logic_buffer>;

class logic_buffer {
public:
  explicit logic_buffer(uint32_t size,
                        const source_location& sloc = source_location(),
                        const std::string& name = "");

  logic_buffer(const logic_buffer& rhs,
               const source_location& sloc = source_location(),
               const std::string& name = "");

  logic_buffer(logic_buffer&& rhs);

  explicit logic_buffer(const lnode& data,
                        const source_location& sloc = source_location(),
                        const std::string& name = "");

  logic_buffer(uint32_t size,
               const logic_buffer_ptr& buffer,
               uint32_t offset,
               const source_location& sloc = source_location(),
               const std::string& name = "");

  virtual ~logic_buffer() {}

  logic_buffer& operator=(const logic_buffer& rhs);

  logic_buffer& operator=(logic_buffer&& rhs);

  uint32_t id() const {
    return id_;
  }

  const lnode& data() const {
    return value_;
  }

  uint32_t size() const {
    return value_.size();
  }

  bool has_source() const {
    return !!source_;
  }

  const logic_buffer_ptr& source() const {
    return source_;
  }

  logic_buffer_ptr& source() {
    return source_;
  }

  uint32_t offset() const {
    return offset_;
  }

  virtual void write(uint32_t dst_offset,
                     const lnode& data,
                     uint32_t src_offset,
                     uint32_t length);

  void write(const lnode& data) {
    this->write(0, data, 0, data.size());
  }

protected:

  logic_buffer(const lnode& value,
               const logic_buffer_ptr& source,
               uint32_t offset);

  void update_sloc(const source_location& sloc);

  uint32_t id_;
  lnode value_;
  logic_buffer_ptr source_;
  uint32_t offset_;
};

template <typename... Args>
auto make_logic_buffer(Args&&... args) {
  return std::make_shared<logic_buffer>(std::forward<Args>(args)...);
}

///////////////////////////////////////////////////////////////////////////////

class logic_accessor {
public:
  template <typename T>
  static const logic_buffer_ptr& buffer(const T& obj) {
    return obj.buffer();
  }

  template <typename T>
  static logic_buffer_ptr& buffer(T& obj) {
    return obj.buffer();
  }

  template <typename T>
  static const lnode& data(const T& obj) {
    assert(width_v<T> == obj.buffer()->size());
    return obj.buffer()->data();
  }

  template <typename T>
  static auto copy_buffer(const T& obj,
                          const source_location& sloc = CH_SRC_LOCATION,
                          const std::string& name = "") {
    assert(width_v<T> == obj.buffer()->size());
    return make_logic_buffer(*obj.buffer(), sloc, name);
  }

  template <typename U, typename V,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(is_logic_type_v<V>),
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void copy(U& dst, const V& src) {
    assert(width_v<U> == dst.buffer()->size());
    assert(width_v<V> == src.buffer()->size());
    *dst.buffer() = *src.buffer();
  }

  template <typename U, typename V,
            CH_REQUIRE_0(width_v<U> == width_v<V>)>
  static void move(U& dst, V&& src) {
    assert(width_v<U> == dst.buffer()->size());
    *dst.buffer() = std::move(*src.buffer());
  }

  template <typename U, typename V>
  static void write(U& dst,
                    uint32_t dst_offset,
                    const V& src,
                    uint32_t src_offset,
                    uint32_t length) {
    auto data = src.buffer()->data();
    dst.buffer()->write(dst_offset, data, src_offset, length);
  }

  template <typename T>
  static auto clone(const T& obj, const source_location& sloc) {
    assert(width_v<T> == obj.buffer()->size());
    auto data = obj.buffer()->data().clone();
    return T(make_logic_buffer(data, sloc));
  }

  template <typename D, typename T>
  static auto cast(const T& obj) {
    assert(width_v<T> == obj.buffer()->size());
    return D(obj.buffer());
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = ch_logic<width_v<T>>>
using logic_cast_t = std::conditional_t<is_logic_type_v<T>, const T&, R>;

template <typename T, unsigned N = width_v<T>,
          CH_REQUIRE_0(is_logic_convertible_v<T, N>)>
lnode get_lnode(const T& rhs) {
  if constexpr(is_scalar_convertible_v<T, N>) {
    return lnode(scalar_accessor::data(static_cast<scalar_cast_t<T, ch_scalar<N>>>(rhs)));
  } else {
    return logic_accessor::data(static_cast<logic_cast_t<T, ch_logic<N>>>(rhs));
  }
}

template <typename T, typename R,
          CH_REQUIRE_0(std::is_constructible_v<R, T>)>
lnode get_lnode(const T& rhs) {
  return logic_accessor::data(static_cast<logic_cast_t<T, R>>(rhs));
}

template <typename T>
auto make_type(const lnode& node, const source_location& sloc = CH_SRC_LOCATION) {
  return T(make_logic_buffer(node, sloc));
}

template <ch_op op, typename R, typename A>
auto make_logic_op(const A& a, const source_location& sloc = CH_SRC_LOCATION) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a));
  return make_type<R>(node, sloc);
}

template <ch_op op, typename R, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_location& sloc = CH_SRC_LOCATION) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a), get_lnode(b));
  return make_type<R>(node, sloc);
}

template <typename T>
using type_buffer_t = std::conditional_t<is_logic_traits_v<T>, logic_buffer, scalar_buffer>;

template <typename T>
using type_accessor_t = std::conditional_t<is_logic_traits_v<T>, logic_accessor, scalar_accessor>;

template <typename T,
          typename U,
          typename Q = typename T::traits,
          typename X = typename ch_type_t<U>::traits>
using aggregate_init_cast_t = std::conditional_t<X::bitwidth != 0,
      std::conditional_t<(Q::type == X::type),
                         const U&,
                         std::conditional_t<is_logic_traits_v<Q>,
                                            ch_logic<X::bitwidth>,
                                            ch_scalar<X::bitwidth>>>,
      std::conditional_t<is_logic_traits_v<Q>,
                         ch_logic<Q::bitwidth>,
                         ch_scalar<Q::bitwidth>>>;

template <typename T>
struct sloc_arg {
  const T& value;
  source_location sloc;

  sloc_arg(const T& p_value, const source_location& p_sloc = CH_SRC_LOCATION)
    : value(p_value), sloc(p_sloc)
  {}
};

template <typename U, typename V>
auto resize_args(const U& lhs, const V& rhs, const source_location& sloc) {
  if constexpr(width_v<U> < width_v<V>) {
    if constexpr(is_logic_type_v<U>) {
      auto _lhs = ch_pad<width_v<V>>(lhs, sloc);
      return std::make_tuple(_lhs, rhs);
    } else {
      auto _lhs = ch_pad<width_v<V>>(lhs);
      return std::make_tuple(_lhs, rhs);
    }
  } else
  if constexpr(width_v<U> > width_v<V>) {
    if constexpr(is_logic_type_v<V>) {
      auto _rhs = ch_pad<width_v<U>>(rhs, sloc);
      return std::make_tuple(lhs, _rhs);
    } else {
      auto _rhs = ch_pad<width_v<U>>(rhs);
      return std::make_tuple(lhs, _rhs);
    }
  } else {
    return std::forward_as_tuple(lhs, rhs);
  }
}

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_OP1(i, x) \
  CH_FRIEND_OP1_IMPL((), ==, const ch_logic&, x) \
  CH_FRIEND_OP1_IMPL((), !=, const ch_logic&, x) \
  CH_FRIEND_OP1_IMPL((), &, const ch_logic&, x) \
  CH_FRIEND_OP1_IMPL((), |, const ch_logic&, x) \
  CH_FRIEND_OP1_IMPL((), ^, const ch_logic&, x)

#define CH_LOGIC_FUNC1(i, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_eq, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_ne, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_and, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_or, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_xor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_nand, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_nor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC1_IMPL((template <unsigned N>), ch_xnor, const ch_logic<N>&, x)

#define CH_LOGIC_OP1_TYPES \
  const ch_scalar<N>&, int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_OP2(i, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), ==, const ch_logic&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), !=, const ch_logic&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), &, const ch_logic&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), |, const ch_logic&, x) \
  CH_FRIEND_OP2_IMPL((template <unsigned M, CH_REQUIRE_0(M < N)>), ^, const ch_logic&, x)

#define CH_LOGIC_FUNC2(i, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_eq, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_ne, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_and, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_or, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_nand, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_nor, const ch_logic<N>&, x) \
  CH_GLOBAL_FUNC2_IMPL((template <unsigned N, unsigned M, CH_REQUIRE_0(M < N)>), ch_xnor, const ch_logic<N>&, x)

#define CH_LOGIC_OP2_TYPES \
  const ch_logic<M>&, const ch_scalar<M>&

#define CH_LOGIC_OP3(i, x) \
  CH_FRIEND_OP3_IMPL((), <<, const ch_logic&, x, ch_logic<CH_WIDTH_OF(x)>&) \
  CH_FRIEND_OP3_IMPL((), >>, const ch_logic&, x, ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_FUNC3(i, x) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N>), ch_sll, const ch_logic<N>&, x, ch_logic<CH_WIDTH_OF(x)>&) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N>), ch_srl, const ch_logic<N>&, x, ch_logic<CH_WIDTH_OF(x)>&)

#define CH_LOGIC_OP3_TYPES \
  int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t

#define CH_LOGIC_OP4(i, x) \
  CH_FRIEND_OP3_IMPL((template <unsigned M>), <<, const ch_logic&, x, ch_logic<M>&) \
  CH_FRIEND_OP3_IMPL((template <unsigned M>), >>, const ch_logic&, x, ch_logic<M>&)

#define CH_LOGIC_FUNC4(i, x) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N, unsigned M>), ch_sll, const ch_logic<N>&, x, ch_logic<M>&) \
  CH_GLOBAL_FUNC3_IMPL((template <unsigned N, unsigned M>), ch_srl, const ch_logic<N>&, x, ch_logic<M>&)

#define CH_LOGIC_OP4_TYPES \
  const ch_scalar<M>&

///////////////////////////////////////////////////////////////////////////////

#define CH_LOGIC_INTERFACE(type) \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type_v<R>)> \
  const auto as() const { \
    return ch::internal::logic_accessor::cast<R>(*this); \
  } \
  template <typename R, CH_REQUIRE_0(ch::internal::is_logic_type_v<R>)> \
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
  auto as_reg(const ch::internal::source_location& sloc = CH_SRC_LOCATION) { \
    ch_reg<type> s(sloc); \
    (*this) = s; \
    return s; \
  } \
  auto as_reg(const type& init, const ch::internal::source_location& sloc = CH_SRC_LOCATION) { \
    ch_reg<type> s(init, sloc); \
    (*this) = s; \
    return s; \
  }

///////////////////////////////////////////////////////////////////////////////

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
    : buffer_(make_logic_buffer(scalar_accessor::data(rhs), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  explicit ch_logic(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(logic_accessor::copy_buffer(rhs, sloc))
  {}

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
  explicit ch_logic(const U& rhs, const source_location& sloc = CH_SRC_LOCATION)
    : buffer_(make_logic_buffer(scalar_accessor::data(ch_scalar<N>(rhs)), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_convertible_v<U>)>
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
            CH_REQUIRE_0(is_logic_type_v<U>),
            CH_REQUIRE_0(width_v<U> == N)>
  ch_logic& operator=(const U& rhs) {
    logic_accessor::copy(*this, rhs);
    return *this;
  }

  template <typename U,
            CH_REQUIRE_1(is_scalar_type_v<U>),
            CH_REQUIRE_1(width_v<U> <= N)>
  ch_logic& operator=(const U& rhs) {
    buffer_->write(scalar_accessor::data(ch_scalar<N>(rhs)));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_integral_or_enum_v<U>)>
  ch_logic& operator=(U rhs) {
    buffer_->write(bitvector(N, rhs));
    return *this;
  }

  // slicing operators

  const auto operator[](const sloc_arg<size_t>& index) const {
    assert(index.value < N);
    return ch_logic<1>(make_logic_buffer(1, buffer_, index.value, index.sloc));
  }

  auto operator[](const sloc_arg<size_t>& index) {
    assert(index.value < N);
    return ch_logic<1>(make_logic_buffer(1, buffer_, index.value, index.sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  const auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) const {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
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
            CH_REQUIRE_0(is_logic_type_v<R>)>
  auto slice(size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
    static_assert(width_v<R> <= N, "invalid size");
    assert((start + width_v<R>) <= N);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
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
    return make_logic_op<op_eq, ch_logic<1>>(*this, rhs);
  }

  auto operator!=(const ch_logic& rhs) const {
    return make_logic_op<op_ne, ch_logic<1>>(*this, rhs);
  }

  // logical operators

  auto operator&&(const ch_logic& rhs) const {
    static_assert(1 == N, "invalid size");
    return make_logic_op<op_and, ch_logic>(*this, rhs);
  }

  auto operator||(const ch_logic& rhs) const {
    static_assert(1 == N, "invalid size");
    return make_logic_op<op_or, ch_logic>(*this, rhs);
  }

  auto operator!() const {
    return (0x0 == *this);
  }

  // bitwise operators

  auto operator~() const {
    return make_logic_op<op_inv, ch_logic>(*this, source_location());
  }

  auto operator&(const ch_logic& rhs) const {
    return make_logic_op<op_and, ch_logic>(*this, rhs);
  }

  auto operator|(const ch_logic& rhs) const {
    return make_logic_op<op_or, ch_logic>(*this, rhs);
  }

  auto operator^(const ch_logic& rhs) const {
    return make_logic_op<op_xor, ch_logic>(*this, rhs);
  }

  // shift operators

  template <unsigned M>
  auto operator<<(const ch_logic<M>& rhs) const {
    return make_logic_op<op_sll, ch_logic>(*this, rhs);
  }

  template <unsigned M>
  auto operator>>(const ch_logic<M>& rhs) const {
    return make_logic_op<op_srl, ch_logic>(*this, rhs);
  }

  CH_LOGIC_INTERFACE(ch_logic)

protected:

  const logic_buffer_ptr& buffer() const {
    return buffer_;
  }

  logic_buffer_ptr& buffer() {
    return buffer_;
  }

  logic_buffer_ptr buffer_;

  friend class logic_accessor;

  // friend operators

  CH_FOR_EACH(CH_LOGIC_OP1, CH_SEP_SPACE, CH_LOGIC_OP1_TYPES)
  CH_FOR_EACH(CH_LOGIC_OP2, CH_SEP_SPACE, CH_LOGIC_OP2_TYPES)
  CH_FOR_EACH(CH_LOGIC_OP3, CH_SEP_SPACE, CH_LOGIC_OP3_TYPES)
  CH_FOR_EACH(CH_LOGIC_OP4, CH_SEP_SPACE, CH_LOGIC_OP4_TYPES)
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <unsigned N>
inline auto ch_eq(const ch_logic<N>& lhs,
                  const ch_logic<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_eq, ch_logic<1>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_ne(const ch_logic<N>& lhs,
                  const ch_logic<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_ne, ch_logic<1>>(lhs, rhs, sloc);
}

// bitwise operators

template <unsigned N>
auto ch_inv(const ch_logic<N>& in,
            const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_inv, ch_logic<N>>(in, sloc);
}

template <unsigned N>
inline auto ch_and(const ch_logic<N>& lhs,
                   const ch_logic<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_and, ch_logic<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_or(const ch_logic<N>& lhs,
                  const ch_logic<N>& rhs,
                  const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_or, ch_logic<N>>(lhs, rhs, sloc);
}

template <unsigned N>
inline auto ch_xor(const ch_logic<N>& lhs,
                   const ch_logic<N>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_xor, ch_logic<N>>(lhs, rhs, sloc);
}

// shift operators

template <unsigned N, unsigned M>
inline auto ch_sll(const ch_logic<N>& lhs,
                   const ch_logic<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_sll, ch_logic<N>>(lhs, rhs, sloc);
}

template <unsigned N, unsigned M>
inline auto ch_srl(const ch_logic<N>& lhs,
                   const ch_logic<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_srl, ch_logic<N>>(lhs, rhs, sloc);
}

template <unsigned N, unsigned M>
inline auto ch_sra(const ch_logic<N>& lhs,
                   const ch_logic<M>& rhs,
                   const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_sra, ch_logic<N>>(lhs, rhs, sloc);
}

// reduce operators

template <unsigned N>
auto ch_andr(const ch_logic<N>& in,
             const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_andr, ch_logic<1>>(in, sloc);
}

template <unsigned N>
auto ch_orr(const ch_logic<N>& in,
            const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_orr, ch_logic<1>>(in, sloc);
}

template <unsigned N>
auto ch_xorr(const ch_logic<N>& in,
             const source_location& sloc = CH_SRC_LOCATION) {
  return make_logic_op<op_xorr, ch_logic<1>>(in, sloc);
}

// rotate operators

template <unsigned N>
auto ch_rotl(const ch_logic<N>& lhs,
             unsigned rhs,
             const source_location& sloc = CH_SRC_LOCATION) {
  auto node = createRotateNode(get_lnode(lhs), rhs, false);
  return make_type<ch_logic<N>>(node, sloc);
}

template <unsigned N>
auto ch_rotr(const ch_logic<N>& lhs,
             unsigned rhs,
             const source_location& sloc = CH_SRC_LOCATION) {
  auto node = createRotateNode(get_lnode(lhs), rhs, true);
  return make_type<ch_logic<N>>(node, sloc);
}

// cloning

template <typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
auto ch_clone(const T& obj, const source_location& sloc = CH_SRC_LOCATION) {
  return logic_accessor::clone(obj, sloc);
}

// slicing

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_type_v<R>),
          CH_REQUIRE_0(is_logic_type_v<T>)>
R ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> <= width_v<T>, "invalid size");
  assert((start + width_v<R>) <= width_v<T>);
  if constexpr(width_v<R> == width_v<T>) {
    if constexpr(std::is_same_v<R, T>) {
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
          CH_REQUIRE_0(is_logic_type_v<R>),
          CH_REQUIRE_0(is_logic_type_v<T>)>
R ch_aslice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_slice<R>(obj, start * width_v<R>, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
auto ch_slice(const T& obj, size_t start = 0, const source_location& sloc = CH_SRC_LOCATION) {
  return ch_slice<ch_logic<N>>(obj, start, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
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
  void assign_impl(uint32_t src_offset, const T& src, U& dst) {
    dst = ch_slice<U>(src, src_offset, sloc_);
  }

  template <typename T, typename U0, typename... Us>
  void assign_impl(uint32_t src_offset, const T& src, U0& dst0, Us&... dsts) {
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
#define CH_TIE_REQUIRE(i, x) CH_REQUIRE_0(is_logic_type_v<__T##i>)
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
void cat_impl(U& inout, uint32_t dst_offset, const T& arg) {
  logic_accessor::write(inout, dst_offset - width_v<T>, arg, 0, width_v<T>);
}

template <typename U, typename T0, typename... Ts>
void cat_impl(U& inout, uint32_t dst_offset, const T0& arg0, const Ts&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - width_v<T0>, args...);
}

#define CH_CAT_TYPE(i, x) __T##i
#define CH_CAT_TMPL(i, x) typename __T##i
#define CH_CAT_REQUIRE(i, x) CH_REQUIRE_0(is_logic_convertible_v<__T##i>)
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
auto ch_pad(const ch_logic<N>& obj,
            const source_location& sloc = CH_SRC_LOCATION) {
  static_assert(width_v<R> >= N, "invalid pad size");
  if constexpr(width_v<R> > N) {
    return make_logic_op<op_zext, R>(obj, sloc);
  } else {
    return R(obj, sloc);
  }
}

template <unsigned M, unsigned N>
ch_logic<M> ch_pad(const ch_logic<N>& obj, const source_location& sloc) {
  return ch_pad<ch_logic<M>>(obj, sloc);
}

// shuffle

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_compatible_v<T>)>
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
          CH_REQUIRE_0(is_logic_type_v<T>)>
void ch_tap(const std::string& name,
            const T& value,
            const source_location& sloc = CH_SRC_LOCATION) {
  registerTap(name, get_lnode(value), sloc);
}

// print

ch_logic<64> ch_time(const source_location& sloc = CH_SRC_LOCATION);

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRE_0(are_all_logic_type_v<Args...>)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

// global functions

CH_FOR_EACH(CH_LOGIC_FUNC1, CH_SEP_SPACE, CH_LOGIC_OP1_TYPES)
CH_FOR_EACH(CH_LOGIC_FUNC2, CH_SEP_SPACE, CH_LOGIC_OP2_TYPES)
CH_FOR_EACH(CH_LOGIC_FUNC3, CH_SEP_SPACE, CH_LOGIC_OP3_TYPES)
CH_FOR_EACH(CH_LOGIC_FUNC4, CH_SEP_SPACE, CH_LOGIC_OP4_TYPES)

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
