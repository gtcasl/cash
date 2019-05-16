#pragma once

#include "logic.h"
#include "vec.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_bit : public logic_op_equality<ch_bit, N,
                        logic_op_logical<ch_bit, N,
                          logic_op_bitwise<ch_bit, N,
                            logic_op_shift<ch_bit, N,
                              logic_op_slice<ch_bit, N>>>>> {
public:
  static_assert(N != 0, "invalid size");
  using traits = logic_traits<N, false, ch_bit, ch_scbit<N>>;
  using base = logic_op_equality<ch_bit, N,
                 logic_op_logical<ch_bit, N,
                   logic_op_bitwise<ch_bit, N,
                     logic_op_shift<ch_bit, N,
                       logic_op_slice<ch_bit, N>>>>>;

  ch_bit(const logic_buffer& buffer =
      logic_buffer(N, idname<ch_bit>()))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> <= N)>
  ch_bit(const U& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_bit(const ch_bit& other)
    : ch_bit(logic_buffer(N, idname<ch_bit>())) {
    CH_SOURCE_LOCATION(1);
    this->operator=(other);
  }

  ch_bit(ch_bit&& other) : buffer_(std::move(other.buffer_)) {}

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_bit& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, sdata_type(N, other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_scbit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  ch_bit& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    ch_scbit<N> tmp(other);
    logic_accessor::assign(*this, system_accessor::data(tmp));
    return *this;
  }

  ch_bit& operator=(const ch_scbit<N>& other) {
    CH_SOURCE_LOCATION(1);
    logic_accessor::assign(*this, system_accessor::data(other));
    return *this;
  }

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  ch_bit& operator=(const U& other) {
    CH_SOURCE_LOCATION(1);
    ch_bit<N> tmp(logic_buffer(createOpNode(ch_op::pad, N, ch_signed_v<U>, get_lnode(other))));
    logic_accessor::assign(*this, tmp);
    return *this;
  }

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

  // subscript operators

  auto operator[](size_t index) const {
    assert(index < N);
    CH_SOURCE_LOCATION(1);
    return this->template slice<1>(index);
  }

  auto operator[](size_t index) {
    assert(index < N);
    CH_SOURCE_LOCATION(1);
    return this->template sliceref<1>(index);
  }

  CH_LOGIC_INTERFACE(ch_bit)

protected:

  const logic_buffer& __buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
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

// equality functions

CH_LOGIC_FUNCTION_EQUALITY(ch_eq, ch_op::eq, ch_bit)
CH_LOGIC_FUNCTION_EQUALITY(ch_ne, ch_op::ne, ch_bit)

// binary functions

CH_LOGIC_FUNCTION_BITWISE1(ch_inv, ch_op::inv, ch_bit)
CH_LOGIC_FUNCTION_BITWISE2(ch_and, ch_op::andb, ch_bit)
CH_LOGIC_FUNCTION_BITWISE2(ch_or, ch_op::orb, ch_bit)
CH_LOGIC_FUNCTION_BITWISE2(ch_xor, ch_op::xorb, ch_bit)

// shift functions

CH_LOGIC_FUNCTION_SHIFT(ch_shl, ch_op::shl, ch_bit)
CH_LOGIC_FUNCTION_SHIFT(ch_shr, ch_op::shr, ch_bit)

// reduce functions

template <unsigned N>
inline auto ch_andr(const ch_bit<N>& in) {
  CH_SOURCE_LOCATION(1);
  return make_logic_op<ch_op::andr, false, ch_bit<1>>(in);
}

template <unsigned N>
inline auto ch_orr(const ch_bit<N>& in) {
  CH_SOURCE_LOCATION(1);
  return make_logic_op<ch_op::orr, false, ch_bit<1>>(in);
}

template <unsigned N>
inline auto ch_xorr(const ch_bit<N>& in) {
  CH_SOURCE_LOCATION(1);
  return make_logic_op<ch_op::xorr, false, ch_bit<1>>(in);
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

// time function

ch_uint<64> ch_now();

// print function       

template <typename... Args>
void ch_print(const std::string& format, const Args&... args) {
  static_assert((is_logic_type_v<Args> && ...), "invalid argument type");
  CH_SOURCE_LOCATION(1);
  createPrintNode(format, {get_lnode(args)...});
}

template <typename... Args>
void ch_println(const std::string& format, const Args&... args) {
  CH_SOURCE_LOCATION(1);
  ch_print(format + '\n', args...);
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name) {
  static_assert(is_logic_type_v<T>, "invalid type");
  CH_SOURCE_LOCATION(1);
  registerTap(get_lnode(value), name);
}

//
// assert functions
//

inline void ch_assert(const ch_bit<1>& cond, const std::string& msg) {
  CH_SOURCE_LOCATION(1);
  createAssertNode(get_lnode(cond), msg);
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
