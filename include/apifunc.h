#pragma once

#include "bit.h"
#include "int.h"
#include "uint.h"

namespace ch {
namespace internal {

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

template <typename R, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_slice(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  if constexpr (ch_width_v<T> == ch_width_v<R>) {
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return obj.template as<R>();
  } else
  if constexpr (is_logic_type_v<T>) {
    return logic_accessor::slice<R>(std::forward<T>(obj), start);
  } else {
    return system_accessor::slice<R>(std::forward<T>(obj), start);
  }
}

template <typename R, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_sliceref(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  static_assert(ch_width_v<R> <= ch_width_v<T>, "invalid size");
  assert(start + ch_width_v<R> <= ch_width_v<T>);
  if constexpr (ch_width_v<T> == ch_width_v<R>) {
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return obj.template as<R>();
  } else
  if constexpr (is_logic_type_v<T>) {
    return logic_accessor::sliceref<R>(std::forward<T>(obj), start);
  } else {
    return system_accessor::sliceref<R>(std::forward<T>(obj), start);
  }
}

template <typename R, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_aslice(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  return ch_slice<R>(std::forward<T>(obj), start * ch_width_v<R>);
}

template <typename R, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_asliceref(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  return ch_sliceref<R>(std::forward<T>(obj), start * ch_width_v<R>);
}

template <unsigned N, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_slice(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return std::move(obj);
  } else {
    return ch_slice<ch_size_cast_t<T, N>>(std::forward<T>(obj), start);
  }
}

template <unsigned N, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_aslice(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return std::move(obj);
  } else {
    return ch_aslice<ch_size_cast_t<T, N>>(std::forward<T>(obj), start);
  }
}

template <unsigned N, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_sliceref(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return std::move(obj);
  } else {
    return ch_sliceref<ch_size_cast_t<T, N>>(std::forward<T>(obj), start);
  }
}

template <unsigned N, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_asliceref(T&& obj, size_t start = 0) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> == N || !is_resizable_v<T>) {
    static_assert(ch_width_v<T> == N, "invalid size");
    CH_DBGCHECK(0 == start, "invalid offset");
    CH_UNUSED(start);
    return std::move(obj);
  } else {
    return ch_asliceref<ch_size_cast_t<T, N>>(std::forward<T>(obj), start);
  }
}

// padding function

template <unsigned N, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_pad(T&& obj) {
  CH_API_ENTRY(1);
  if constexpr (0 == N || !is_resizable_v<T>) {
    static_assert(0 == N, "invalid size");
    return std::move(obj);
  } else {
    return ch_size_cast_t<T, (ch_width_v<T> + N)>(std::forward<T>(obj));
  }
}

// resize function

template <typename R, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_resize(T&& obj) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> <= ch_width_v<R>) {
    return ch_pad<ch_width_v<R>-ch_width_v<T>>(std::forward<T>(obj)).template as<R>();
  } else {
    return ch_slice<R>(std::forward<T>(obj), 0);
  }
}

template <unsigned M, typename T,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_resize(T&& obj) {
  CH_API_ENTRY(1);
  if constexpr (ch_width_v<T> <= M) {
    return ch_pad<M-ch_width_v<T>>(std::forward<T>(obj));
  } else {
    return ch_slice<M>(std::forward<T>(obj), 0);
  }
}

// rotate functions

template <typename T>
inline auto ch_rotl(const T& obj, uint32_t dist) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");  
  auto mod = dist % ch_width_v<T>;
  if constexpr (is_logic_type_v<T>) {
    ch_bit<ch_width_v<T>> out(make_logic_buffer(ch_width_v<T>, "rotl"));
    logic_accessor::write(out, 0, obj, ch_width_v<T> - mod, mod);
    logic_accessor::write(out, mod, obj, 0, ch_width_v<T> - mod);
    return out;
  } else {
    ch_sbit<ch_width_v<T>> out(make_system_buffer(ch_width_v<T>, "rotr"));
    system_accessor::write(out, 0, obj, ch_width_v<T> - mod, mod);
    system_accessor::write(out, mod, obj, 0, ch_width_v<T> - mod);
    return out;
  }
}

template <typename T>
inline auto ch_rotr(const T& obj, uint32_t dist) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");  
  auto mod = dist % ch_width_v<T>;
  if constexpr (is_logic_type_v<T>) {
    ch_bit<ch_width_v<T>> out(make_logic_buffer(ch_width_v<T>, "rotl"));
    logic_accessor::write(out, 0, obj, mod, ch_width_v<T> - mod);
    logic_accessor::write(out, ch_width_v<T> - mod, obj, 0, mod);
    return out;
  } else {
    ch_sbit<ch_width_v<T>> out(make_system_buffer(ch_width_v<T>, "rotr"));
    system_accessor::write(out, 0, obj, mod, ch_width_v<T> - mod);
    system_accessor::write(out, ch_width_v<T> - mod, obj, 0, mod);
    return out;
  }
}

// shuffle function

template <unsigned N, typename T>
auto ch_shuffle(const T& obj, const std::array<size_t, N>& indices) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");
  static_assert(0 == (ch_width_v<T> % N), "invalid indices size");  
  auto stride = ch_width_v<T> / N;
  CH_CHECK(stride * N == ch_width_v<T>, "invalid size");
  if constexpr (is_logic_type_v<T>) {
    ch_bit<ch_width_v<T>> out(make_logic_buffer(ch_width_v<T>, "shuffle"));
    for (unsigned i = 0; i < N; ++i) {
      auto j = indices[N - 1 - i];
      CH_CHECK(j < N, "invalid index");
      logic_accessor::write(out, i * stride, obj, j * stride, stride);
    }
    return out;
  } else {
    ch_sbit<ch_width_v<T>> out(make_system_buffer(ch_width_v<T>, "shuffle"));
    for (unsigned i = 0; i < N; ++i) {
      auto j = indices[N - 1 - i];
      CH_CHECK(j < N, "invalid index");
      system_accessor::write(out, i * stride, obj, j * stride, stride);
    }
    return out;
  }
}

// tie function

template <typename... Args>
class tie_impl {
public:
  tie_impl(Args&... args) : args_(args...) {}

  template <typename U>
  void operator=(const U& other) {
    static_assert(std::is_integral_v<U> || is_data_type_v<U>, "invalid type");
    if constexpr (std::is_integral_v<U>) {
      this->assign(ch_logic_t<U>(other), std::index_sequence_for<Args...>());
    } else
    if constexpr (is_data_type_v<U>) {
      if constexpr (ch_width_v<U> == ch_width_v<Args...>) {
        this->assign(other, std::index_sequence_for<Args...>());
      } else {
        static_assert(is_resizable_v<U>, "invalid type");
        this->assign(ch_size_cast_t<U, ch_width_v<Args...>>(other), std::index_sequence_for<Args...>());
      }
    }
  }

protected:

  template <typename U, typename V>
  void assign_impl(uint32_t src_offset, const U& src, V& dst) {
    dst.as_bit() = ch_slice<ch_width_v<V>>(src.as_bit(), src_offset);
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
  CH_API_ENTRY(1);
  static_assert((is_data_type_v<Args> && ...), "invalid type for argument");  
  return tie_impl(args...);
}

// concatenation function

template <typename O, typename I>
void cat_impl(O& inout, uint32_t dst_offset, const I& arg) {
  if constexpr (is_logic_type_v<O>) {
    if constexpr (is_logic_type_v<I>) {
      logic_accessor::write(inout, dst_offset - ch_width_v<I>, arg, 0, ch_width_v<I>);
    } else {
      logic_accessor::write(inout, dst_offset - ch_width_v<I>, ch_logic_t<I>(arg), 0, ch_width_v<I>);
    }
  } else {
    system_accessor::write(inout, dst_offset - ch_width_v<I>, arg, 0, ch_width_v<I>);
  }
}

template <typename O, typename I0, typename... Is>
void cat_impl(O& inout, uint32_t dst_offset, const I0& arg0, const Is&... args) {
  cat_impl(inout, dst_offset, arg0);
  cat_impl(inout, dst_offset - ch_width_v<I0>, args...);
}

template <typename R, typename... Args>
auto ch_cat(const Args&... args) {
  CH_API_ENTRY(1);
  static_assert((is_data_type_v<Args> && ...), "invalid argument type");
  static constexpr unsigned N = (ch_width_v<Args> + ...);
  static_assert(ch_width_v<R> == N, "size mismatch");  
  if constexpr (is_logic_type_v<R>) {
    R ret(make_logic_buffer(N, "cat"));
    cat_impl(ret, N, args...);
    return ret;
  } else {
    R ret(make_system_buffer(N, "cat"));
    cat_impl(ret, N, args...);
    return ret;
  }
}

template <typename... Args>
auto ch_cat(const Args&... args) {
  CH_API_ENTRY(1);
  static_assert((is_data_type_v<Args> && ...), "invalid argument type");
  static constexpr unsigned N = (ch_width_v<Args> + ...);  
  if constexpr ((is_logic_type_v<Args> || ...)) {
    return ch_cat<ch_bit<N>>(args...);
  } else {
    return ch_cat<ch_sbit<N>>(args...);
  }
}

// duplicate function

template <unsigned N, typename T>
auto ch_dup(T&& obj) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");
  static_assert(N > 0, "invalid size");
  if constexpr (1 == N) {
    return std::move(obj);
  } else
  if constexpr (is_logic_type_v<T>) {
    ch_bit<ch_width_v<T> * N> out(make_logic_buffer(ch_width_v<T> * N, "dup"));
    for (unsigned i = 0; i < N; ++i) {
      logic_accessor::write(out, i * ch_width_v<T>, obj, 0, ch_width_v<T>);
    }
    return out;
  } else {
    ch_sbit<ch_width_v<T> * N> out(make_system_buffer(ch_width_v<T> * N, "dup"));
    for (unsigned i = 0; i < N; ++i) {
      system_accessor::write(out, i * ch_width_v<T>, obj, 0, ch_width_v<T>);
    }
    return out;
  }
}

// cast function

template <typename R, typename T>
auto ch_as(const T& obj) {
  CH_API_ENTRY(1);
  static_assert(is_data_type_v<T>, "invalid type");
  return obj.template as<R>();
}

// reference function

template <typename T>
auto ch_ref(T& obj) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<T>, "invalid type");
  return obj.ref();
}

// clone function

template <typename T>
auto ch_clone(const T& obj) {
  CH_API_ENTRY(1);
  static_assert(is_logic_type_v<T>, "invalid type");
  return obj.clone();
}

// map function

template <typename T, typename F,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_map(const T& obj, const F& f) {
  using ret_t = std::result_of_t<F(decltype(obj[0]))>;
  static const unsigned N = ch_width_v<T> / ch_width_v<ret_t>;
  ch_vec<ret_t, N> ret;
  for (unsigned i = 0; i < N; ++i) {
    ret[i] = f(obj[i]);
  }
  return ret;
}

template <typename T, unsigned N, typename F>
auto ch_map(const std::array<T, N>& obj, const F& f) {
  using ret_t = std::result_of_t<F(T)>;
  std::array<ret_t, N> ret;
  for (unsigned i = 0; i < N; ++i) {
    ret[i] = f(obj[i]);
  }
  return ret;
}

// fold function

template <typename T, typename F, typename I,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_fold(const T& obj, const F& f, const I& init) {
  using ret_t = std::result_of_t<F(I, decltype(obj[0]))>;
  static const unsigned N = ch_width_v<T> / ch_width_v<ret_t>;
  ret_t ret(init);
  for (unsigned i = 0; i < N; ++i) {
    if constexpr (is_logic_type_v<ret_t>) {
      ret = f(ch_clone(ret), obj[i]);
    } else {
      ret = f(ret, obj[i]);
    }
  }
  return ret;
}

template <typename T, unsigned N, typename F, typename I>
auto ch_fold(const std::array<T, N>& obj, const F& f, const I& init) {
  using ret_t = std::result_of_t<F(I, T)>;
  ret_t ret(init);
  for (unsigned i = 0; i < N; ++i) {
    if constexpr (is_logic_type_v<ret_t>) {
      ret = f(ch_clone(ret), obj[i]);
    } else {
      ret = f(ret, obj[i]);
    }
  }
  return ret;
}

// zip function

template <typename T, typename U, typename F,
          CH_REQUIRE(is_data_type_v<T> && is_data_type_v<U> && ch_width_v<T> == ch_width_v<U>)>
auto ch_zip(const T& obj1, const U& obj2, const F& f) {
  using ret_t = std::result_of_t<F(decltype(obj1[0]), decltype(obj2[0]))>;
  static const unsigned N = ch_width_v<T> / ch_width_v<ret_t>;
  ch_vec<ret_t, N> ret;
  for (unsigned i = 0; i < N; ++i) {
    ret[i] = f(obj1[i], obj2[i]);
  }
  return ret;
}

template <typename T, typename U, unsigned N, typename F>
auto ch_zip(const std::array<T, N>& obj1, const std::array<U, N>& obj2, const F& f) {
  using ret_t = std::result_of_t<F(T, U)>;
  std::array<ret_t, N> ret;
  for (unsigned i = 0; i < N; ++i) {
    ret[i] = f(obj1[i], obj2[i]);
  }
  return ret;
}

// scan function

template <typename T, typename F, typename I,
          CH_REQUIRE(is_data_type_v<T>)>
auto ch_scan(const T& obj, const F& f, const I& init) {
  using ret_t = std::result_of_t<F(I, decltype(obj[0]))>;
  static const unsigned N = ch_width_v<T> / ch_width_v<ret_t>;
  ch_vec<ret_t, N> ret;
  ret_t tmp(init);
  for (unsigned i = 0; i < N; ++i) {
    if constexpr (is_logic_type_v<ret_t>) {
      tmp = f(ch_clone(tmp), obj[i]);
    } else {
      tmp = f(tmp, obj[i]);
    }
    ret[i] = ch_clone(tmp);
  }
  return ret;
}

template <typename T, unsigned N, typename F, typename I>
auto ch_scan(const std::array<T, N>& obj, const F& f, const I& init) {
  using ret_t = std::result_of_t<F(I, T)>;
  std::array<ret_t, N> ret;
  ret_t tmp(init);
  for (unsigned i = 0; i < N; ++i) {
    if constexpr (is_logic_type_v<ret_t>) {
      tmp = f(ch_clone(tmp), obj[i]);
    } else {
      tmp = f(tmp, obj[i]);
    }
    ret[i] = tmp;
  }
  return ret;
}

}
}
