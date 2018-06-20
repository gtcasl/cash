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

template <typename T, unsigned N = T::traits::bitwidth>
inline constexpr bool is_logic_convertible_v = std::is_constructible_v<ch_bit<N>, T>;

template <typename... Ts>
inline constexpr bool are_all_logic_type_v = std::conjunction_v<is_logic_type<Ts>...>;

template <typename T> class ch_reg_impl;
template <typename T> using ch_reg = std::add_const_t<ch_reg_impl<T>>;

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
  static const lnode& data(const T& obj) {
    assert(width_v<T> == obj.buffer()->size());
    return obj.buffer()->data();
  }

  template <typename T>
  static auto copy_buffer(const T& obj, CH_SLOC, const std::string& name = "") {
    assert(width_v<T> == obj.buffer()->size());
    return make_logic_buffer(*obj.buffer(), sloc, name);
  }

  template <typename U, typename V>
  static void copy(U& dst, const V& src) {
    static_assert(width_v<U> == width_v<V>, "invalid size");
    assert(width_v<U> == dst.buffer()->size());
    assert(width_v<V> == src.buffer()->size());
    *dst.buffer() = *src.buffer();
  }

  template <typename U, typename V>
  static void move(U& dst, V&& src) {
    static_assert(width_v<U> == width_v<V>, "invalid size");
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

  template <typename R, typename T>
  static auto cast(const T& obj) {
    static_assert(width_v<T> == width_v<R>, "invalid size");
    assert(width_v<T> == obj.buffer()->size());
    return R(obj.buffer());
  }

  template <typename T>
  static const source_location& sloc(const T& obj) {
    return obj.buffer()->data().sloc();
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, typename R = ch_bit<width_v<T>>>
using logic_cast_t = std::conditional_t<is_logic_type_v<T>, const T&, R>;

template <typename T, unsigned N = width_v<T>,
          CH_REQUIRE_0(is_logic_convertible_v<T, N>)>
lnode get_lnode(const T& rhs) {
  if constexpr(is_scalar_convertible_v<T, N>) {
    return lnode(scalar_accessor::data(
                   static_cast<scalar_cast_t<T, ch_scbit<N>>>(rhs)));
  } else {
    return logic_accessor::data(
          static_cast<logic_cast_t<T, ch_bit<N>>>(rhs));
  }
}

template <typename T, typename R,
          CH_REQUIRE_0(std::is_constructible_v<R, T>)>
lnode get_lnode(const T& rhs) {
  return logic_accessor::data(static_cast<logic_cast_t<T, R>>(rhs));
}

template <typename T>
auto make_type(const lnode& node, const source_location& sloc = source_location()) {
  return T(make_logic_buffer(node, sloc));
}

template <ch_op op, typename R, typename A>
auto make_logic_op(const A& a, const source_location& sloc = source_location()) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a));
  return make_type<R>(node, sloc);
}

template <ch_op op, typename R, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_location& sloc = source_location()) {
  auto node = createAluNode(op, width_v<R>, get_lnode(a), get_lnode(b));
  return make_type<R>(node, sloc);
}

template <ch_op op, typename A>
auto make_logic_op(const A& a, const source_location& sloc = source_location()) {
  return make_logic_op<op, A, A>(a, sloc);
}

template <ch_op op, typename A, typename B>
auto make_logic_op(const A& a, const B& b, const source_location& sloc = source_location()) {
  return make_logic_op<op, A, A, B>(a, b, sloc);
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
                                            ch_bit<X::bitwidth>,
                                            ch_scbit<X::bitwidth>>>,
      std::conditional_t<is_logic_traits_v<Q>,
                         ch_bit<Q::bitwidth>,
                         ch_scbit<Q::bitwidth>>>;

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
    return this->as<ch::internal::ch_bit<ch::internal::width_v<type>>>(); \
  } \
  auto as_bit() { \
    return this->as<ch::internal::ch_bit<ch::internal::width_v<type>>>(); \
  } \
  const auto as_int() const { \
    return this->as<ch::internal::ch_int<ch::internal::width_v<type>>>(); \
  } \
  auto as_int() { \
    return this->as<ch::internal::ch_int<ch::internal::width_v<type>>>(); \
  } \
  const auto as_uint() const { \
    return this->as<ch::internal::ch_uint<ch::internal::width_v<type>>>(); \
  } \
  auto as_uint() { \
    return this->as<ch::internal::ch_uint<ch::internal::width_v<type>>>(); \
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

///////////////////////////////////////////////////////////////////////////////

template <typename Derived>
class ch_logic_integer;

template <typename Derived>
class ch_logic_base {
public:
  using self = Derived;

  ch_logic_base(const logic_buffer_ptr& buffer) : buffer_(buffer) {
    assert(width_v<Derived> == buffer->size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_logic_base(const U& rhs, const ch::internal::source_location& sloc)
    : buffer_(make_logic_buffer(bitvector(width_v<Derived>, rhs), sloc))
  {}

  template <typename U>
  ch_logic_base(const ch_scalar_base<U>& rhs,
                const ch::internal::source_location& sloc)
    : buffer_(make_logic_buffer(
                scalar_accessor::data(
                  rhs.template pad<width_v<Derived>>()), sloc)) {
    static_assert(width_v<U> <= width_v<Derived>, "invalid size");
  }

  template <typename U>
  ch_logic_base(const ch_logic_base<U>& rhs,
                const ch::internal::source_location& sloc)
    : buffer_(logic_accessor::copy_buffer(rhs, sloc)) {
    static_assert(width_v<U> == width_v<Derived>, "invalid size");
  }

  ch_logic_base(const ch_logic_base& rhs,
                const ch::internal::source_location& sloc)
    : buffer_(logic_accessor::copy_buffer(rhs, sloc))
  {}

  ch_logic_base(ch_logic_base&& rhs) : buffer_(std::move(rhs.buffer_)) {}

  ch_logic_base& operator=(const ch_logic_base& rhs) {
    logic_accessor::copy(*this, rhs);
    return *this;
  }

  ch_logic_base& operator=(ch_logic_base&& rhs) {
    logic_accessor::move(*this, std::move(rhs));
    return *this;
  }

  // subscript operators

  const auto operator[](const sloc_arg<size_t>& index) const {
    assert(index.value < width_v<Derived>);
    return ch_bit<1>(make_logic_buffer(1, buffer_, index.value, index.sloc));
  }

  auto operator[](const sloc_arg<size_t>& index) {
    assert(index.value < width_v<Derived>);
    return ch_bit<1>(make_logic_buffer(1, buffer_, index.value, index.sloc));
  }

  // slicing operators

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  const auto slice(size_t start = 0, CH_SLOC) const {
    static_assert(width_v<R> <= width_v<Derived>, "invalid size");
    assert((start + width_v<R>) <= width_v<Derived>);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  const auto aslice(size_t start = 0, CH_SLOC) const {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  template <unsigned M>
  const auto slice(size_t start = 0, CH_SLOC) const {
    return this->slice<ch_bit<M>>(start, sloc);
  }

  template <unsigned M>
  const auto aslice(size_t start = 0, CH_SLOC) const {
    return this->slice<ch_bit<M>>(start * M, sloc);
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  auto slice(size_t start = 0, CH_SLOC) {
    static_assert(width_v<R> <= width_v<Derived>, "invalid size");
    assert((start + width_v<R>) <= width_v<Derived>);
    return R(make_logic_buffer(width_v<R>, buffer_, start, sloc));
  }

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  auto aslice(size_t start = 0, CH_SLOC) {
    return this->slice<R>(start * width_v<R>, sloc);
  }

  template <unsigned M>
  auto slice(size_t start = 0, CH_SLOC) {
    return this->slice<ch_bit<M>>(start, sloc);
  }

  template <unsigned M>
  auto aslice(size_t start = 0, CH_SLOC) {
    return this->slice<ch_bit<M>>(start * M, sloc);
  }

  // padding operators

  template <typename R,
            CH_REQUIRE_0(is_logic_type_v<R>)>
  R pad(CH_SLOC) const {
    static_assert(width_v<R> >= width_v<Derived>, "invalid size");
    if constexpr (width_v<R> > width_v<Derived>) {
      return make_logic_op<(signed_v<Derived> ? op_sext : op_zext), R>(*this, sloc);
    } else
    if constexpr (std::is_same_v<R, Derived>) {
      return *this;
    } else {
      return R(*this, sloc);
    }
  }

  template <unsigned M>
  auto pad(CH_SLOC) const {
    return this->pad<ch_bit<M>>(sloc);
  }

  // compare operators

  friend auto operator==(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_eq, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator!=(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_ne, ch_bit<1>>(lhs, rhs, sloc);
  }

  // logical operators

  friend auto operator&&(Derived lhs, const Derived& rhs) {
    static_assert(1 == width_v<Derived>, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_and, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator||(Derived lhs, const Derived& rhs) {
    static_assert(1 == width_v<Derived>, "invalid size");
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_or, ch_bit<1>>(lhs, rhs, sloc);
  }

  friend auto operator!(Derived _this) {
    return (0x0 == _this);
  }

  // bitwise operators

  friend auto operator~(Derived _this) {
    auto sloc = logic_accessor::sloc(_this);
    return make_logic_op<op_inv>(_this, sloc);
  }

  friend auto operator&(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_and>(lhs, rhs, sloc);
  }

  friend auto operator|(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_or>(lhs, rhs, sloc);
  }

  friend auto operator^(Derived lhs, const Derived& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_xor>(lhs, rhs, sloc);
  }

  // shift operators

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator<<(Derived lhs, const U& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<CH_WIDTH_OF(U)>(rhs);
    return make_logic_op<op_sll>(lhs, _rhs, sloc);
  }

  template <typename U>
  friend auto operator<<(Derived lhs, const ch_scalar_integer<U>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<width_v<U>>(rhs);
    return make_logic_op<op_sll>(lhs, _rhs, sloc);
  }

  template <typename U>
  friend auto operator<<(Derived lhs, const ch_logic_integer<U>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<op_sll>(lhs, rhs, sloc);
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  friend auto operator>>(Derived lhs, const U& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<CH_WIDTH_OF(U)>(rhs);
    return make_logic_op<(signed_v<Derived> ? op_sra : op_srl)>(lhs, _rhs, sloc);
  }

  template <typename U>
  friend auto operator>>(Derived lhs, const ch_scalar_integer<U>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    auto _rhs = ch_bit<width_v<U>>(rhs);
    return make_logic_op<(signed_v<Derived> ? op_sra : op_srl)>(lhs, _rhs, sloc);
  }

  template <typename U>
  friend auto operator>>(Derived lhs, const ch_logic_integer<U>& rhs) {
    auto sloc = logic_accessor::sloc(lhs);
    return make_logic_op<(signed_v<Derived> ? op_sra : op_srl)>(lhs, rhs, sloc);
  }

  CH_LOGIC_INTERFACE(Derived)

protected:

  const logic_buffer_ptr& buffer() const {
    return buffer_;
  }

  logic_buffer_ptr buffer_;

  friend class logic_accessor;
};

template <unsigned N>
class ch_bit : public ch_logic_base<ch_bit<N>> {
public:
  using traits = logic_traits<N, false, ch_bit, ch_scbit<N>>;
  using base = ch_logic_base<ch_bit>;

  ch_bit(const logic_buffer_ptr& buffer = make_logic_buffer(N, CH_CUR_SLOC))
    : base(buffer)
  {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_bit(const U& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <typename U>
  ch_bit(const ch_scalar_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  template <unsigned M,
            CH_REQUIRE_0(M < N)>
  ch_bit(const ch_bit<M>& rhs, CH_SLOC) : base(rhs.template pad<N>(), sloc) {}

  template <typename U>
  explicit ch_bit(const ch_logic_base<U>& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_bit(const ch_bit& rhs, CH_SLOC) : base(rhs, sloc) {}

  ch_bit(ch_bit&& rhs) : base(std::move(rhs)) {}

  ch_bit& operator=(const ch_bit& rhs) {
    base::operator=(rhs);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    base::operator=(std::move(rhs));
    return *this;
  }
};

///////////////////////////////////////////////////////////////////////////////

// compare operators

template <typename T>
inline auto ch_eq(const ch_logic_base<T>& lhs, const ch_logic_base<T>& rhs, CH_SLOC) {
  return make_logic_op<op_eq, ch_bit<1>>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_ne(const ch_logic_base<T>& lhs, const ch_logic_base<T>& rhs, CH_SLOC) {
  return make_logic_op<op_ne, ch_bit<1>>(lhs, rhs, sloc);
}

// bitwise operators

template <typename T>
auto ch_inv(const ch_logic_base<T>& in, CH_SLOC) {
  return make_logic_op<op_inv, T>(in, sloc);
}

template <typename T>
inline auto ch_and(const ch_logic_base<T>& lhs, const ch_logic_base<T>& rhs, CH_SLOC) {
  return make_logic_op<op_and, T>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_or(const ch_logic_base<T>& lhs, const ch_logic_base<T>& rhs, CH_SLOC) {
  return make_logic_op<op_or, T>(lhs, rhs, sloc);
}

template <typename T>
inline auto ch_xor(const ch_logic_base<T>& lhs, const ch_logic_base<T>& rhs, CH_SLOC) {
  return make_logic_op<op_xor, T>(lhs, rhs, sloc);
}

// shift operators

template <typename T, typename U>
inline auto ch_sll(const ch_logic_base<T>& lhs, const ch_logic_integer<U>& rhs, CH_SLOC) {
  return make_logic_op<op_sll, T>(lhs, rhs, sloc);
}

template <typename T, typename U>
inline auto ch_srl(const ch_logic_base<T>& lhs, const ch_logic_integer<U>& rhs, CH_SLOC) {
  return make_logic_op<op_srl, T>(lhs, rhs, sloc);
}

template <typename T, typename U>
inline auto ch_sra(const ch_logic_base<T>& lhs, const ch_logic_integer<U>& rhs, CH_SLOC) {
  return make_logic_op<op_sra, T>(lhs, rhs, sloc);
}

// reduce operators

template <typename T>
auto ch_andr(const ch_logic_base<T>& in, CH_SLOC) {
  return make_logic_op<op_andr, ch_bit<1>>(in, sloc);
}

template <typename T>
auto ch_orr(const ch_logic_base<T>& in, CH_SLOC) {
  return make_logic_op<op_orr, ch_bit<1>>(in, sloc);
}

template <typename T>
auto ch_xorr(const ch_logic_base<T>& in, CH_SLOC) {
  return make_logic_op<op_xorr, ch_bit<1>>(in, sloc);
}

// rotate operators

template <typename T>
auto ch_rotl(const ch_logic_base<T>& lhs, unsigned rhs, CH_SLOC) {
  auto node = createRotateNode(get_lnode(lhs), rhs, false);
  return make_type<T>(node, sloc);
}

template <typename T>
auto ch_rotr(const ch_logic_base<T>& lhs, unsigned rhs, CH_SLOC) {
  auto node = createRotateNode(get_lnode(lhs), rhs, true);
  return make_type<T>(node, sloc);
}

// cloning

template <typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
auto ch_clone(const T& obj, CH_SLOC) {
  return logic_accessor::clone(obj, sloc);
}

// slicing

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_type_v<R>),
          CH_REQUIRE_0(is_logic_type_v<T>)>
R ch_slice(const T& obj, size_t start = 0, CH_SLOC) {
  static_assert(width_v<R> <= width_v<T>, "invalid size");
  assert((start + width_v<R>) <= width_v<T>);
  if constexpr(width_v<R> == width_v<T>) {
    if constexpr(std::is_same_v<R, T>) {
      return obj;
    } else {
      return R(obj, sloc);
    }
  } else {
    ch_bit<width_v<R>> ret(make_logic_buffer(width_v<R>, sloc));
    logic_accessor::write(ret, 0, obj, start, width_v<R>);
    return ret.template as<R>();
  }
}

template <typename R, typename T,
          CH_REQUIRE_0(is_logic_type_v<R>),
          CH_REQUIRE_0(is_logic_type_v<T>)>
R ch_aslice(const T& obj, size_t start = 0, CH_SLOC) {
  return ch_slice<R>(obj, start * width_v<R>, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
auto ch_slice(const T& obj, size_t start = 0, CH_SLOC) {
  return ch_slice<ch_bit<N>>(obj, start, sloc);
}

template <unsigned N, typename T,
          CH_REQUIRE_0(is_logic_type_v<T>)>
auto ch_aslice(const T& obj, size_t start = 0, CH_SLOC) {
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
  auto ch_tie(CH_FOR_EACH(CH_TIE_DECL, CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
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
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    static_assert(width_v<R> == N, "size mismatch"); \
    R ret(make_logic_buffer(N, sloc)); \
    cat_impl(ret, N, CH_FOR_EACH(CH_CAT_ARG, CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  } \
  template <CH_FOR_EACH(CH_CAT_TMPL, CH_SEP_COMMA, __VA_ARGS__), \
            CH_FOR_EACH(CH_CAT_REQUIRE, CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    static constexpr unsigned N = width_v<CH_FOR_EACH(CH_CAT_TYPE, CH_SEP_COMMA, __VA_ARGS__)>; \
    ch_bit<N> ret(make_logic_buffer(N, sloc)); \
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

template <typename R, typename T>
auto ch_pad(const ch_logic_base<T>& obj, CH_SLOC) {
  return obj.template pad<R>(sloc);
}

template <unsigned M, typename T>
ch_bit<M> ch_pad(const ch_logic_base<T>& obj, const source_location& sloc) {
  return obj.template pad<M>(obj, sloc);
}

// shuffle

template <unsigned N, typename T>
auto ch_shuffle(const ch_logic_base<T>& obj,
                const std::array<unsigned, N>& indices, CH_SLOC) {
  static_assert(0 == (width_v<T> % N), "invalid indices size");
  static constexpr unsigned M = (width_v<T> / N);
  ch_bit<width_v<T>> ret(make_logic_buffer(width_v<T>, sloc));
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
void ch_tap(const std::string& name, const T& value, CH_SLOC) {
  registerTap(name, get_lnode(value), sloc);
}

// print

ch_bit<64> ch_time(CH_SLOC);

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRE_0(are_all_logic_type_v<Args...>)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

}
}

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(#x, x)
#else
  #define CH_TAP(x)
#endif
