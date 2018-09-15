#pragma once

#include "logic.h"

namespace ch {
namespace internal {

template <unsigned N>
class ch_bit : public logic_op_equality<ch_bit, N,
                        logic_op_logical<ch_bit, N,
                          logic_op_bitwise<ch_bit, N,
                            logic_op_shift<ch_bit, N,
                              logic_op_slice<ch_bit, N>>>>> {
public:
  using traits = logic_traits<N, false, ch_bit, ch_scbit<N>>;
  using base = logic_op_equality<ch_bit, N,
                 logic_op_logical<ch_bit, N,
                   logic_op_bitwise<ch_bit, N,
                     logic_op_shift<ch_bit, N,
                       logic_op_slice<ch_bit, N>>>>>;

  explicit ch_bit(const logic_buffer& buffer = logic_buffer(N, CH_CUR_SLOC))
    : buffer_(buffer) {
    assert(N == buffer.size());
  }

  template <typename U,
            CH_REQUIRE_0(std::is_integral_v<U>)>
  ch_bit(const U& other, CH_SLOC)
    : buffer_(logic_buffer(bitvector(N, other), sloc))
  {}

  ch_bit(const ch_scbit<N>& other, CH_SLOC)
    : buffer_(logic_buffer(system_accessor::data(other), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bitvector_extended_type_v<U>)>
  explicit ch_bit(const U& other, CH_SLOC)
    : buffer_(logic_buffer(bitvector(N, other), sloc))
  {}

  template <typename U,
            CH_REQUIRE_0(is_bit_base_v<U>),
            CH_REQUIRE_0(ch_width_v<U> < N)>
  explicit ch_bit(const U& other, CH_SLOC)
    : buffer_(createAluNode(ch_op::pad, N, ch_signed_v<U>, get_lnode(other), sloc))
  {}

  ch_bit(const ch_bit& other, CH_SLOC)
    : base()
    , buffer_(logic_accessor::copy(other, sloc))
  {}

  ch_bit(ch_bit&& other) : buffer_(std::move(other.buffer_)) {}

  ch_bit& operator=(const ch_bit& other) {
    logic_accessor::copy(*this, other);
    return *this;
  }

  ch_bit& operator=(ch_bit&& other) {
    logic_accessor::move(*this, std::move(other));
    return *this;
  }

  // subscript operators

  const auto operator[](const sloc_arg<size_t>& index) const {
    assert(index.value < N);
    return ch_bit<1>(logic_buffer(1, buffer_, index.value, index.sloc));
  }

  auto operator[](const sloc_arg<size_t>& index) {
    assert(index.value < N);
    return ch_bit<1>(logic_buffer(1, buffer_, index.value, index.sloc));
  }

  CH_LOGIC_INTERFACE(ch_bit)

protected:

  logic_buffer buffer() const {
    return buffer_;
  }

  logic_buffer buffer_;

  friend class logic_accessor;
};

///////////////////////////////////////////////////////////////////////////////

// equality functions

CH_LOGIC_FUNCTION_EQUALITY(ch_eq, ch_op::eq, ch_bit)
CH_LOGIC_FUNCTION_EQUALITY(ch_ne, ch_op::ne, ch_bit)

// binary functions

CH_LOGIC_FUNCTION_BINARY1(ch_inv, ch_op::inv, ch_bit)
CH_LOGIC_FUNCTION_BINARY2(ch_and, ch_op::andb, ch_bit)
CH_LOGIC_FUNCTION_BINARY2(ch_or, ch_op::orb, ch_bit)
CH_LOGIC_FUNCTION_BINARY2(ch_xor, ch_op::xorb, ch_bit)

// shift functions

CH_LOGIC_FUNCTION_SHIFT(ch_shl, ch_op::shl, ch_bit)
CH_LOGIC_FUNCTION_SHIFT(ch_shr, ch_op::shr, ch_bit)

// reduce functions

template <unsigned N>
inline auto ch_andr(const ch_bit<N>& in, CH_SLOC) {
  return make_logic_op<ch_op::andr, false, ch_bit<1>>(in, sloc);
}

template <unsigned N>
inline auto ch_orr(const ch_bit<N>& in, CH_SLOC) {
  return make_logic_op<ch_op::orr, false, ch_bit<1>>(in, sloc);
}

template <unsigned N>
inline auto ch_xorr(const ch_bit<N>& in, CH_SLOC) {
  return make_logic_op<ch_op::xorr, false, ch_bit<1>>(in, sloc);
}

// rotate functions

template <unsigned N>
inline auto ch_rotl(const ch_bit<N>& lhs, unsigned rhs, CH_SLOC) {
  auto node = createRotateNode(get_lnode(lhs), rhs, false, sloc);
  return make_type<ch_bit<N>>(node, sloc);
}

template <unsigned N>
inline auto ch_rotr(const ch_bit<N>& lhs, unsigned rhs, CH_SLOC) {
  auto node = createRotateNode(get_lnode(lhs), rhs, true, sloc);
  return make_type<ch_bit<N>>(node, sloc);
}

// slicing functions

template <typename R, typename T>
auto ch_slice(const T& obj, size_t start = 0, CH_SLOC) {
  return obj.template slice<ch_width_v<R>>(start, sloc).template as<R>();
}

template <unsigned N, typename T>
auto ch_slice(const T& obj, size_t start = 0, CH_SLOC) {
  return obj.template slice<N>(start, sloc);
}

template <typename R, typename T>
auto ch_aslice(const T& obj, size_t start = 0, CH_SLOC) {
  return obj.template aslice<ch_width_v<R>>(start, sloc).template as<R>();
}

template <unsigned N, typename T>
auto ch_aslice(const T& obj, size_t start = 0, CH_SLOC) {
  return obj.template aslice<N>(start, sloc);
}

template <typename R, typename T>
auto ch_sliceref(T& obj, size_t start = 0, CH_SLOC) {
  return obj.template sliceref<ch_width_v<R>>(start, sloc).template as<R>();
}

template <unsigned N, typename T>
auto ch_sliceref(T& obj, size_t start = 0, CH_SLOC) {
  return obj.template sliceref<N>(start, sloc);
}

template <typename R, typename T>
auto ch_asliceref(T& obj, size_t start = 0, CH_SLOC) {
  return obj.template asliceref<ch_width_v<R>>(start, sloc).template as<R>();
}

template <unsigned N, typename T>
auto ch_asliceref(T& obj, size_t start = 0, CH_SLOC) {
  return obj.template asliceref<N>(start, sloc);
}

// padding function

template <unsigned M, unsigned N>
auto ch_pad(const ch_bit<N>& obj, CH_SLOC) {
  return ch_bit<M+N>(obj, sloc);
}

// resize function

template <typename R, typename T>
auto ch_resize(const T& obj, CH_SLOC) {
  static_assert(is_bit_base_v<T>, "invalid type");
  if constexpr (ch_width_v<T> <= ch_width_v<R>) {
    return ch_pad<ch_width_v<R>-ch_width_v<T>>(obj, sloc).template as<R>();
  } else {
    return ch_slice<R>(obj, 0, sloc);
  }
}

template <unsigned M, typename T>
auto ch_resize(const T& obj, CH_SLOC) {
  if constexpr (ch_width_v<T> <= M) {
    return ch_pad<M-ch_width_v<T>>(obj, sloc);
  } else {
    return ch_slice<M>(obj, 0, sloc);
  }
}

// shuffle function

template <unsigned M, unsigned N>
auto ch_shuffle(const ch_bit<N>& obj,
               const std::array<unsigned, M>& indices, CH_SLOC) {
  static_assert(0 == (N % M), "invalid indices size");
  auto node = createShuffleNode(
        get_lnode(obj),
        std::vector<unsigned>(indices.begin(), indices.end()),
        sloc);
  return make_type<ch_bit<N>>(node, sloc);
}

// tie function

template <typename... Ts>
class bind_impl {
public:
  bind_impl(const source_location& sloc, Ts&... args) : sloc_(sloc), args_(args...) {}

  template <typename T>
  void operator=(const T& other) {
    static_assert(is_bit_convertible_v<T, ch_width_v<Ts...>>, "invalid type");
    this->assign(to_logic<ch_width_v<Ts...>>(other, sloc_),
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
    this->assign_impl(src_offset + ch_width_v<U0>, src, dsts...);
  }

  template <typename T, size_t... I>
  void assign(const T& src, std::index_sequence<I...>) {
    this->assign_impl(0, src, std::get<sizeof...(Ts) - 1 - I>(args_)...);
  }

  source_location sloc_;
  std::tuple<Ts&...> args_;
};

#define CH_BIND_TMPL(a, i, x) typename __T##i
#define CH_BIND_ASSERT(a, i, x) static_assert(is_logic_type_v<__T##i>, "invalid type for argument"#i)
#define CH_BIND_DECL(a, i, x) __T##i& arg##i
#define CH_BIND_ARG(a, i, x) arg##i
#define CH_BIND(...) \
  template <CH_FOR_EACH(CH_BIND_TMPL, , CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_bind(CH_FOR_EACH(CH_BIND_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    CH_FOR_EACH(CH_BIND_ASSERT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    return bind_impl(sloc, CH_FOR_EACH(CH_BIND_ARG, , CH_SEP_COMMA, __VA_ARGS__)); \
  }
CH_VA_ARGS_MAP(CH_BIND)
#undef CH_BIND_TMPL
#undef CH_BIND_ASSERT
#undef CH_BIND_DECL
#undef CH_BIND_ARG
#undef CH_BIND

// concatenation function

template <typename U, typename T>
void cat_impl(U& inout, uint32_t dst_offset, const source_location& sloc, const T& arg) {
  logic_accessor::write(inout, dst_offset - ch_width_v<T>, arg, 0, ch_width_v<T>, sloc);
}

template <typename U, typename T0, typename... Ts>
void cat_impl(U& inout, uint32_t dst_offset, const source_location& sloc,
              const T0& arg0, const Ts&... args) {
  cat_impl(inout, dst_offset, sloc, arg0);
  cat_impl(inout, dst_offset - ch_width_v<T0>, sloc, args...);
}

#define CH_CAT_TYPE(a, i, x) __T##i
#define CH_CAT_TMPL(a, i, x) typename __T##i
#define CH_CAT_ASSERT(a, i, x) static_assert(is_object_type_v<__T##i>, "invalid type for argument"#i)
#define CH_CAT_DECL(a, i, x) const __T##i& arg##i
#define CH_CAT_ARG(a, i, x) to_logic<ch_width_v<__T##i>>(arg##i, sloc)
#define CH_CAT(...) \
  template <typename R, \
            CH_FOR_EACH(CH_CAT_TMPL, , CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    CH_FOR_EACH(CH_CAT_ASSERT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    static constexpr unsigned N = ch_width_v<CH_FOR_EACH(CH_CAT_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>; \
    static_assert(ch_width_v<R> == N, "size mismatch"); \
    R ret(logic_buffer(N, sloc)); \
    cat_impl(ret, N, sloc, CH_FOR_EACH(CH_CAT_ARG, , CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  } \
  template <CH_FOR_EACH(CH_CAT_TMPL, , CH_SEP_COMMA, __VA_ARGS__)> \
  auto ch_cat(CH_FOR_EACH(CH_CAT_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    CH_FOR_EACH(CH_CAT_ASSERT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    static constexpr unsigned N = ch_width_v<CH_FOR_EACH(CH_CAT_TYPE, , CH_SEP_COMMA, __VA_ARGS__)>; \
    ch_bit<N> ret(logic_buffer(N, sloc)); \
    cat_impl(ret, N, sloc, CH_FOR_EACH(CH_CAT_ARG, , CH_SEP_COMMA, __VA_ARGS__)); \
    return ret; \
  }
CH_VA_ARGS_MAP(CH_CAT)
#undef CH_CAT_TYPE
#undef CH_CAT_TMPL
#undef CH_CAT_ASSERT
#undef CH_CAT_DECL
#undef CH_CAT_ARG
#undef CH_CAT                         

// reference function

template <typename R, typename T>
auto ch_as(const T& obj, CH_SLOC) {
  static_assert(is_logic_type_v<T>, "invalid type");
  return obj.template as<R>(sloc);
}

// reference function

template <typename T>
auto ch_ref(T& obj, CH_SLOC) {
  static_assert(is_logic_type_v<T>, "invalid type");
  return obj.template ref(sloc);
}

// clone function

template <typename T>
auto ch_clone(const T& obj, CH_SLOC) {
  static_assert(is_logic_type_v<T>, "invalid type");
  return obj.template clone(sloc);
}

// tap function

template <typename T>
void ch_tap(const T& value, const std::string& name, CH_SLOC) {
  static_assert(is_logic_type_v<T>, "invalid type");
  registerTap(get_lnode(value), name, sloc);
}

// print function

ch_bit<64> ch_now(CH_SLOC);

inline void ch_print(const std::string& format, CH_SLOC) {
  createPrintNode(format, {}, sloc);
}

#define CH_PRINT_TMPL(a, i, x) typename __T##i
#define CH_PRINT_ASSERT(a, i, x) static_assert(is_logic_type_v<__T##i>, "invalid type for argument"#i)
#define CH_PRINT_DECL(a, i, x) const __T##i& arg##i
#define CH_PRINT_ARG(a, i, x) get_lnode(arg##i)
#define CH_PRINT(...) \
  template <CH_FOR_EACH(CH_PRINT_TMPL, , CH_SEP_COMMA, __VA_ARGS__)> \
  void ch_print(const std::string& format, CH_FOR_EACH(CH_PRINT_DECL, , CH_SEP_COMMA, __VA_ARGS__), CH_SLOC) { \
    CH_FOR_EACH(CH_PRINT_ASSERT, , CH_SEP_SEMICOLON, __VA_ARGS__); \
    createPrintNode(format, {CH_FOR_EACH(CH_PRINT_ARG, , CH_SEP_COMMA, __VA_ARGS__)}, sloc); \
  }
CH_VA_ARGS_MAP(CH_PRINT)
#undef CH_PRINT_TMPL
#undef CH_PRINT_ASSERT
#undef CH_PRINT_DECL
#undef CH_PRINT_ARG
#undef CH_PRINT
}
}
