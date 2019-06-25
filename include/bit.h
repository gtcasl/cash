#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_sbit : public ch_sbit_base<ch_sbit<N>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = system_traits<N, false, ch_sbit, ch_bit<N>>;
  template <unsigned M> using size_cast = ch_sbit<M>;
  using base = ch_sbit_base<ch_sbit<N>>;
  using base::operator=;

  ch_sbit(const system_buffer_ptr& buffer
          = make_system_buffer(N, idname<ch_sbit>()))
    : buffer_(buffer) {
    assert(N == buffer->size());
  }

  template <typename U,
            CH_REQUIRE(std::is_integral_v<U>)>
  ch_sbit(const U& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(is_bitvector_extended_type_v<U>)>
  explicit ch_sbit(U&& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(make_system_buffer(sdata_type(N , std::forward<U>(other))));
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_sbit(const ch_sbit_base<U>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_sint<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_suint<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_sbit(const ch_sbit<M>& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    base::operator=(other);
  }

  ch_sbit(const ch_sbit& other)
    : ch_sbit(make_system_buffer(N, idname<ch_sbit>())) {
    this->operator=(other);
  }

  ch_sbit(ch_sbit&& other) : buffer_(std::move(other.buffer_)) {}

  ch_sbit& operator=(const ch_sbit& other) {
    system_accessor::assign(*this, other);
    return *this;
  }

  ch_sbit& operator=(ch_sbit&& other) {
    system_accessor::move(*this, std::move(other));
    return *this;
  }

protected:

  const system_buffer_ptr& __buffer() const {
    return buffer_;
  }

  system_buffer_ptr buffer_;

  friend class system_accessor;
  template <unsigned M> friend class ch_sbit;
};

///////////////////////////////////////////////////////////////////////////////

template <unsigned N>
class ch_bit : public ch_bit_base<ch_bit<N>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, false, ch_bit, ch_sbit<N>>;
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
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_bit(const ch_sbit_base<U>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_sbit<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_sint<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M <= N)>
  ch_bit(const ch_suint<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <typename U,
            CH_REQUIRE(ch_width_v<U> <= N)>
  explicit ch_bit(const ch_bit_base<U>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=((const U&)other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_uint<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_int<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  template <unsigned M,
            CH_REQUIRE(M < N)>
  ch_bit(const ch_bit<M>& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    base::operator=(other);
  }

  ch_bit(const ch_bit& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
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

// read/write functions

template <typename T, typename U>
void ch_read(const T& obj,
             uint32_t src_offset,
             U* out,
             uint32_t dst_offset = 0,
             uint32_t length = ch_width_v<T>) {
  static_assert(is_system_type_v<T>, "invalid type");
  system_accessor::buffer(obj)->read(src_offset, out, sizeof(U), dst_offset, length);
}

template <typename T, typename U>
void ch_write(T& obj,
              uint32_t dst_offset,
              U* in,
              uint32_t src_offset = 0,
              uint32_t length = ch_width_v<T>) {
  static_assert(is_system_type_v<T>, "invalid type");
  system_accessor::buffer(obj)->write(dst_offset, in, sizeof(U), src_offset, length);
}

// slicing functions

template <typename R, typename T>
auto ch_slice(const ch_sbit_base<T>& obj, size_t start = 0) {
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  return system_accessor::slice<R>((const T&)obj, start);
}

template <typename R, typename T>
auto ch_aslice(const ch_sbit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return ch_slice<R>(obj, start * ch_width_v<R>);
}

template <typename R, typename T>
auto ch_sliceref(ch_sbit_base<T>& obj, size_t start = 0) {
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  return system_accessor::sliceref<R>((T&)obj, start);
}

template <typename R, typename T>
auto ch_asliceref(ch_sbit_base<T>& obj, size_t start = 0) {
  return ch_sliceref<R>(obj, start * ch_width_v<R>);
}

template <unsigned N, typename T>
auto ch_slice(const ch_sbit_base<T>& obj, size_t start = 0) {
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_slice<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_aslice(const ch_sbit_base<T>& obj, size_t start = 0) {
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_aslice<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_sliceref(ch_sbit_base<T>& obj, size_t start = 0) {
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_sliceref<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_asliceref(ch_sbit_base<T>& obj, size_t start = 0) {
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_asliceref<ch_size_cast_t<T, N>>(obj, start);
  }
}

///////////////////////////////////////////////////////////////////////////////

template <typename R, typename T>
auto ch_slice(const ch_bit_base<T>& obj, size_t start = 0) {
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  CH_SOURCE_LOCATION(1);            
  return logic_accessor::slice<R>((const T&)obj, start);
} 

template <typename R, typename T>
auto ch_aslice(const ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return ch_slice<R>(obj, start * ch_width_v<R>);
}

template <typename R, typename T>
auto ch_sliceref(ch_bit_base<T>& obj, size_t start = 0) {
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  CH_SOURCE_LOCATION(1);
  return logic_accessor::sliceref<R>((T&)obj, start);
}

template <typename R, typename T>
auto ch_asliceref(ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  return ch_sliceref<R>(obj, start * ch_width_v<R>);
}

template <unsigned N, typename T>
auto ch_slice(const ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_slice<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_aslice(const ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return (const T&)obj;
  } else {
    return ch_aslice<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_sliceref(ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return ((T&)obj).ref();
  } else {
    return ch_sliceref<ch_size_cast_t<T, N>>(obj, start);
  }
}

template <unsigned N, typename T>
auto ch_asliceref(ch_bit_base<T>& obj, size_t start = 0) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    assert(0 == start);
    return ((T&)obj).ref();
  } else {
    return ch_asliceref<ch_size_cast_t<T, N>>(obj, start);
  }
}

// rotate functions

template <typename T>
inline auto ch_rotl(const ch_bit_base<T>& lhs, uint32_t rhs) {
  CH_SOURCE_LOCATION(1);
  return make_logic_type<T>(createRotateNode(get_lnode((const T&)lhs), rhs, false));
}

template <typename T>
inline auto ch_rotr(const ch_bit_base<T>& lhs, uint32_t rhs) {
  CH_SOURCE_LOCATION(1);
  return make_logic_type<T>(createRotateNode(get_lnode((const T&)lhs), rhs, true));
}

// padding function

template <unsigned N, typename T>
auto ch_pad(const ch_bit_base<T>& obj) {
  CH_SOURCE_LOCATION(1);
  if constexpr (0 == N || !is_resizable_v<T>) {
    static_assert(0 == N, "invalid size");
    return (const T&)obj;
  } else {
    return ch_size_cast_t<T, (ch_width_v<T> + N)>((const T&)obj);
  }
}

// resize function

template <typename R, typename T>
auto ch_resize(const ch_bit_base<T>& obj) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> <= ch_width_v<R>) {
    return ch_pad<ch_width_v<R>-ch_width_v<T>>(obj).template as<R>();
  } else {
    return ch_slice<R>(obj, 0);
  }
}

template <unsigned M, typename T>
auto ch_resize(const ch_bit_base<T>& obj) {
  CH_SOURCE_LOCATION(1);
  if constexpr (ch_width_v<T> <= M) {
    return ch_pad<M-ch_width_v<T>>(obj);
  } else {
    return ch_slice<M>(obj, 0);
  }
}

// shuffle function

template <unsigned M, typename T>
auto ch_shuffle(const ch_bit_base<T>& obj, const std::array<unsigned, M>& indices) {
  static_assert(0 == (ch_width_v<T> % M), "invalid indices size");
  CH_SOURCE_LOCATION(1);
  auto node = createShuffleNode(get_lnode((const T&)obj),
                                std::vector<unsigned>(indices.begin(), indices.end()));
  return make_logic_type<T>(node);
}

// tie function

template <typename... Args>
class tie_impl {
public:
  tie_impl(Args&... args) : args_(args...) {}

  template <typename U>
  void operator=(const U& other) {
    static_assert(is_bit_convertible_v<U, ch_width_v<Args...>>, "invalid type");
    this->assign(to_logic<ch_width_v<Args...>>(other), std::index_sequence_for<Args...>());
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
  static_assert((is_data_type_v<Args> && ...), "invalid argument type");
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
  static_assert(is_data_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.template as<R>();
}

// reference function

template <typename T>
auto ch_ref(T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.ref();
}

// clone function

template <typename T>
auto ch_clone(const T& obj) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  return obj.clone();
}

// abs function

template <unsigned N>
auto ch_abs(const ch_int<N>& obj) {
  CH_SOURCE_LOCATION(1);
  return ch_sel(obj[N-1], -obj, obj);
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
