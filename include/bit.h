#pragma once

#include "logic.h"

namespace ch {
namespace internal {

template <typename T>
class ch_bit_base {
public:

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  T& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    auto self = reinterpret_cast<T*>(this);
    logic_accessor::assign(*self, sdata_type(ch_width_v<T>, other));
    return *self;
  }

  template <typename U,
            CH_REQUIRE(is_scbit_base_v<U>)>
  T& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_scbit<ch_width_v<T>> tmp(other);
      logic_accessor::assign(*self, system_accessor::data(tmp));
    } else {
      logic_accessor::assign(*self, system_accessor::data(other));
    }
    return *self;
  }

  template <typename U,
            CH_REQUIRE(is_bit_base_v<U>)>
  T& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    static_assert(ch_width_v<U> <= ch_width_v<T>, "invalid size");
    auto self = reinterpret_cast<T*>(this);
    if constexpr (ch_width_v<U> < ch_width_v<T>) {
      ch_bit<ch_width_v<T>> tmp(logic_buffer(
          createOpNode(ch_op::pad, ch_width_v<T>, ch_signed_v<U>, get_lnode(other))));
      logic_accessor::assign(*self, tmp);
    } else {
      logic_accessor::assign(*self, other);
    }
    return *self;
  }

  // subscript operators

  auto operator[](size_t index) const {
    assert(index < ch_width_v<T>);
    CH_SOURCE_LOCATION(1);
    return this->template slice<ch_bit<1>>(index);
  }

  auto operator[](size_t index) {
    assert(index < ch_width_v<T>);
    CH_SOURCE_LOCATION(1);
    return this->template sliceref<ch_bit<1>>(index);
  }

  CH_LOGIC_INTERFACE(T)
  CH_LOGIC_OP_SLICE(T)

  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::eq, operator==, do_eq)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::ne, operator!=, do_ne)

  CH_LOGIC_OPERATOR1_IMPL(T, ch_op::notl, operator!, do_not)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::andl, operator&&, do_andl)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::orl, operator||, do_orl)

  CH_LOGIC_OPERATOR1_IMPL(T, ch_op::inv, operator~, do_inv)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::andb, operator&, do_and)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::orb, operator|, do_or)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::xorb, operator^, do_xor)

  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::shl, operator<<, do_shl)
  CH_LOGIC_OPERATOR2_IMPL(T, ch_op::shr, operator>>, do_shr)

  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::eq, ch_eq, do_eq)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::ne, ch_ne, do_ne)

  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::notl, ch_not, do_not)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::andl, ch_andl, do_andl)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::orl, ch_orl, do_orl)

  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::inv, ch_inv, do_inv)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::andb, ch_and, do_and)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::orb, ch_or, do_or)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::xorb, ch_xor, do_xor)

  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::shl, ch_shl, do_shl)
  CH_LOGIC_FUNCTION2_IMPL(T, ch_op::shr, ch_shr, do_shr)

  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::andr, ch_andr, do_andr)
  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::orr, ch_orr, do_orr)
  CH_LOGIC_FUNCTION1_IMPL(T, ch_op::xorr, ch_xorr, do_xorr)

protected:

  template <typename U>
  auto do_eq(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::eq, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_ne(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::ne, ch_signed_v<T>, ch_bool>(*self, other);
  }

  auto do_not() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::notl, false, ch_bool>(*self);
  }

  template <typename U>
  auto do_andl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andl, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename U>
  auto do_orl(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orl, ch_signed_v<T>, ch_bool>(*self, other);
  }

  template <typename R>
  auto do_inv() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::inv, false, R>(*self);
  }

  template <typename R, typename U>
  auto do_and(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_or(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_xor(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::xorb, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_shl(const U& other) const {    
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<ch_op::shl, ch_signed_v<R>, R>(*self, other);
  }

  template <typename R, typename U>
  auto do_shr(const U& other) const {
    auto self = reinterpret_cast<const T*>(this);
    static_assert(ch_width_v<U> <= 32, "invalid size");
    return make_logic_op<ch_op::shr, ch_signed_v<R>, R>(*self, other);
  }

  auto do_andr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::andr, false, ch_bool>(*self);
  }

  auto do_orr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::orr, false, ch_bool>(*self);
  }

  auto do_xorr() const {
    auto self = reinterpret_cast<const T*>(this);
    return make_logic_op<ch_op::xorr, false, ch_bool>(*self);
  }

  template <typename U> friend class ch_bit_base;
};


CH_LOGIC_FUNCTION2_DECL(ch_eq)
CH_LOGIC_FUNCTION2_DECL(ch_ne)

CH_LOGIC_FUNCTION1_DECL(ch_not)
CH_LOGIC_FUNCTION2_DECL(ch_andl)
CH_LOGIC_FUNCTION2_DECL(ch_orl)

CH_LOGIC_FUNCTION1_DECL(ch_inv)
CH_LOGIC_FUNCTION2_DECL(ch_and)
CH_LOGIC_FUNCTION2_DECL(ch_or)
CH_LOGIC_FUNCTION2_DECL(ch_xor)

CH_LOGIC_FUNCTION2_DECL(ch_andr)
CH_LOGIC_FUNCTION2_DECL(ch_orr)
CH_LOGIC_FUNCTION2_DECL(ch_xorr)

CH_LOGIC_FUNCTION2_DECL(ch_shl)
CH_LOGIC_FUNCTION2_DECL(ch_shr)

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public ch_bit_base<ch_bit<N>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, false, ch_bit, ch_scbit<N>>;
  template <unsigned M> using size_cast = ch_bit<M>;
  using base = ch_bit_base<ch_bit<N>>;
  using base::operator=;

  ch_bit(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_bit>()))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_scbit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_bit_base_v<U>),
            CH_REQUIRE(ch_width_v<U> <= N)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_bit(const ch_bit& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_bit(ch_bit&& other) : buffer_(std::move(other.buffer_)) {}  

  ch_bit& operator=(const ch_bit& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, other);
    return *this;
  }

  ch_bit& operator=(ch_bit&& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
  template <unsigned M> friend class ch_bit;
};

///////////////////////////////////////////////////////////////////////////////

// slicing functions

template <typename R, typename T>
auto ch_slice(const T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template slice<ch_width_v<R>>(start).template as<R>();
}

template <unsigned N, typename T>
auto ch_slice(const T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template slice<N>(start);
}

template <typename R, typename T>
auto ch_aslice(const T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template aslice<ch_width_v<R>>(start).template as<R>();
}

template <unsigned N, typename T>
auto ch_aslice(const T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template aslice<N>(start);
}

template <typename R, typename T>
auto ch_sliceref(T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template sliceref<ch_width_v<R>>(start).template as<R>();
}

template <unsigned N, typename T>
auto ch_sliceref(T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template sliceref<N>(start);
}

template <typename R, typename T>
auto ch_asliceref(T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template asliceref<ch_width_v<R>>(start).template as<R>();
}

template <unsigned N, typename T>
auto ch_asliceref(T& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return obj.template asliceref<N>(start);
}

// rotate functions

template <unsigned N>
inline auto ch_rotl(const ch_bit<N>& lhs, uint32_t rhs) {
  CH_SOURCE_LOCATION(1);
  auto node = createRotateNode(get_lnode(lhs), rhs, false);
  return make_type<ch_bit<N>>(node);
}

template <unsigned N>
inline auto ch_rotr(const ch_bit<N>& lhs, uint32_t rhs) {
  CH_SOURCE_LOCATION(1);
  auto node = createRotateNode(get_lnode(lhs), rhs, true);
  return make_type<ch_bit<N>>(node);
}

// padding function

template <unsigned M, unsigned N>
auto ch_pad(const ch_bit<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_bit<M+N>(obj);
}

// resize function

template <typename R, typename T>
auto ch_resize(const T& obj) {  
  static_assert(is_bit_base_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> <= ch_width_v<R>) {
    return ch_pad<ch_width_v<R>-ch_width_v<T>>(obj).template as<R>();
  } else {
    return ch_slice<R>(obj, 0);
  }
}

template <unsigned M, typename T>
auto ch_resize(const T& obj) {
  static_assert(is_bit_base_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> <= M) {
    return ch_pad<M-ch_width_v<T>>(obj);
  } else {
    return ch_slice<M>(obj, 0);
  }
}

// shuffle function

template <unsigned M, unsigned N>
auto ch_shuffle(const ch_bit<N>& obj, const std::array<unsigned, M>& indices) {
  static_assert(0 == (N % M), "invalid indices size");
  CH_SOURCE_LOCATION(1);
  auto node = createShuffleNode(
        get_lnode(obj),
        std::vector<unsigned>(indices.begin(), indices.end()));
  return make_type<ch_bit<N>>(node);
}

// tie function

template <typename... Args>
class tie_impl {
public:
  tie_impl(Args&... args) : args_(args...) {}

  template <typename U>
  void operator=(const U& other) {
    static_assert(is_bit_convertible_v<U, ch_width_v<Args...>>, "invalid type");
    this->assign(to_logic<ch_width_v<Args...>>(other),
                 std::index_sequence_for<Args...>());
  }

protected:

  template <typename U, typename V>
  void assign_impl(uint32_t src_offset, const U& src, V& dst) {
    dst = ch_slice<V>(src, src_offset);
  }

  template <typename U, typename V0, typename... Vs>
  void assign_impl(uint32_t src_offset, const U& src, V0& dst0, Vs&... dsts) {
    this->assign_impl(src_offset, src, dst0);
    this->assign_impl(src_offset + ch_width_v<V0>, src, dsts...);
  }

  template <typename U, size_t... I>
  void assign(const U& src, std::index_sequence<I...>) {
    this->assign_impl(0, src, std::get<sizeof...(Args) - 1 - I>(args_)...);
  }

  std::tuple<Args&...> args_;
};

template <typename... Args>
  auto ch_tie(Args&... args) {
  static_assert((is_logic_type_v<Args> && ...), "invalid type for argument");
  CH_SOURCE_LOCATION(1);
  return tie_impl(args...);
}

// concatenation function

template <typename O, typename I>
void cat_impl(O& inout, uint32_t dst_offset, const I& arg) {
  logic_accessor::write(inout, dst_offset - ch_width_v<I>, arg, 0, ch_width_v<I>);
}

template <typename O, typename I0, typename... Is>
void cat_impl(O& inout, uint32_t dst_offset, const I0& arg0, const Is&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - ch_width_v<I0>, args...);
}

template <typename R, typename... Args>
auto ch_cat(const Args&... args) {
  static_assert((is_object_type_v<Args> && ...), "invalid argument type");
  static constexpr unsigned N = (ch_width_v<Args> + ...);
  static_assert(ch_width_v<R> == N, "size mismatch");
  CH_SOURCE_LOCATION(1);
  R ret(logic_buffer(N, "cat"));
  cat_impl(ret, N, to_logic<ch_width_v<Args>>(args)...);
  return ret;
}

template <typename... Args>
auto ch_cat(const Args&... args) {
  static constexpr unsigned N = (ch_width_v<Args> + ...);
  CH_SOURCE_LOCATION(1);
  return ch_cat<ch_bit<N>>(args...);
}

// duplicate function

template <unsigned N, typename T>
auto ch_dup(const T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  ch_bit<ch_width_v<T> * N> out(logic_buffer(ch_width_v<T> * N, "dup"));
  for (unsigned i = 0; i < N; ++i) {
    ch_asliceref<ch_width_v<T>>(out, i) = obj;
  }
  return out;
}

// cast function

template <typename R, typename T>
auto ch_as(const T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.template as<R>();
}

// reference function

template <typename T>
auto ch_ref(T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.template ref();
}

// clone function

template <typename T>
auto ch_clone(const T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.template clone();
}

}
}                           

#ifndef NDEBUG
  #define CH_TAP(x) ch_tap(x, #x)
#else
  #define CH_TAP(x)
#endif

#ifndef NDEBUG
  #define CH_ASSERT(x) \
    ch_assert(x, stringf("Failed assertion in %s: %d", __FILE__, __LINE__))
#else
  #define CH_ASSERT(x)
#endif
