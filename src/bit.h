#pragma once

#include "bitbase.h"

namespace ch {
namespace internal {

void registerTap(const std::string& name, const lnode& node);

void createPrintNode(const std::string& format, const std::initializer_list<lnode>& args);

#define CH_BIT_READONLY_INTERFACE(type)

#define CH_BIT_WRITABLE_INTERFACE(type)

template <unsigned N>
class const_bit : public bitbase<N> {
public:
  using base = bitbase<N>;
  using traits = logic_traits<const_bit, const_bit, ch_bit<N>, ch_scalar<N>>;

  const_bit() : node_(N) {}

  const_bit(const const_bit& rhs) : node_(rhs.node_, N) {}

  const_bit(const_bit&& rhs) : node_(std::move(rhs.node_), N) {}

  const_bit(const bitbase<N>& rhs) : node_(get_lnode(rhs), N) {}

  const_bit(const ch_scalar<N>& rhs) : node_(rhs.get_value()) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<ch_bit<U::bitsize>, U>::value)>
  const_bit(const const_vec<U, (N / U::bitsize)>& rhs) : node_(N) {
    this->assign(rhs);
  }

  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit const_bit(const U& rhs) : node_(bitvector(N, rhs)) {}

  const auto clone() const {
    return make_type<ch_bit<N>>(node_.clone(N));
  }

  CH_BIT_READONLY_INTERFACE(const_bit)

  const auto operator[](size_t index) const {
    return const_sliceref<refproxy<const_bit>, 1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return const_sliceref<refproxy<const_bit>, M>(*this, index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return const_sliceref<refproxy<const_bit>, M>(*this, index * M);
  }

protected:

  const_bit(const lnode& node) : node_(node) {
    assert(N == node_.get_size());
  }

  void read_lnode(nodelist& inout, size_t offset, size_t length) const override {
    node_.read_lnode(inout, offset, length, N);
  }

  void write_lnode(size_t dst_offset, const nodelist& in, size_t src_offset, size_t length) override {
    node_.write_lnode(dst_offset, in, src_offset, length, N);
  }

  void read_bytes(uint32_t dst_offset, void* out, uint32_t out_cbsize, uint32_t src_offset, uint32_t length) const override {
    node_.read_bytes(dst_offset, out, out_cbsize, src_offset, length, N);
  }

  void write_bytes(uint32_t dst_offset, const void* in, uint32_t in_cbsize, uint32_t src_offset, uint32_t length) override {
    node_.write_bytes(dst_offset, in, in_cbsize, src_offset, length, N);
  }

  lnode node_;
};

template <unsigned N>
class ch_bit : public const_bit<N> {
public:
  using base = const_bit<N>;
  using traits = logic_traits<ch_bit, const_bit<N>, ch_bit, ch_scalar<N>>;

  using base::node_;
      
  ch_bit() {}
  
  ch_bit(const ch_bit& rhs) : base(rhs) {}

  ch_bit(ch_bit&& rhs) : base(rhs) {}

  ch_bit(const const_bit<N>& rhs) : base(rhs) {}

  ch_bit(const bitbase<N>& rhs) : base(rhs) {}

  ch_bit(const ch_scalar<N>& rhs) : base(rhs) {}

  template <typename U,
            CH_REQUIRES(is_cast_convertible<ch_bit<U::bitsize>, U>::value)>
  ch_bit(const const_vec<U, (N / U::bitsize)>& rhs) : base(rhs) {}
    
  template <typename U,
            CH_REQUIRES(is_bitvector_value<U>::value || std::is_enum<U>::value)>
  explicit ch_bit(const U& rhs) : base(rhs) {}

  ch_bit& operator=(const ch_bit& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    node_.move(rhs.node_, N);
    return *this;
  }

  ch_bit& operator=(const const_bit<N>& rhs) {
    base::assign(rhs);
    return *this;
  }

  ch_bit& operator=(const bitbase<N>& rhs) {
    base::assign(rhs);
    return *this;
  }

  ch_bit& operator=(const ch_scalar<N>& rhs) {
    base::assign(rhs);
    return *this;
  }

  template <typename U, CH_REQUIRES(is_integral_or_enum<U>::value)>
  ch_bit& operator=(const U& rhs) {
    base::assign(rhs);
    return *this;
  }

  auto operator[](size_t index) & { \
    return ch::internal::sliceref<ch_bit, 1>(*this, index); \
  }

  const auto operator[](size_t index) const & {
    return ch::internal::const_sliceref<ch::internal::refproxy<ch_bit>, 1>(*this, index);
  }

  const auto operator[](size_t index) const && {
    return ch::internal::const_sliceref<ch_bit, 1>(std::move(*this), index);
  }

  template <unsigned M>
  auto slice(size_t index = 0) & {
    return ch::internal::sliceref<ch_bit, M>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const & {
   return ch::internal::const_sliceref<ch::internal::refproxy<ch_bit>, M>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const && {
   return ch::internal::const_sliceref<ch_bit, M>(std::move(*this), index);
  }

  template <unsigned M>
  auto aslice(size_t index = 0) & {
   return ch::internal::sliceref<ch_bit, M>(*this, index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const & {
   return ch::internal::const_sliceref<ch::internal::refproxy<ch_bit>, M>(*this, index * M);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const && {
   return ch::internal::const_sliceref<ch_bit, M>(std::move(*this), index * M);
  }

  CH_BIT_WRITABLE_INTERFACE(ch_bit)
};

static_assert(has_bitsize<ch_bit<1>>::value, ":-(");
static_assert(deduce_ch_bit_t<int, int>::bitsize == 0, ":-(");
static_assert(deduce_ch_bit_t<int, ch_bit<2>>::bitsize == 2, ":-(");

template <typename T, unsigned N = std::decay_t<T>::bitsize>
struct is_ch_bit_convertible {
  static constexpr bool value = is_cast_convertible<ch_bit<N>, T>::value;
};

template <typename... Ts>
struct are_ch_bit_convertible;

template <typename T>
struct are_ch_bit_convertible<T> {
  static constexpr bool value = is_cast_convertible<ch_bit<std::decay_t<T>::bitsize>, T>::value;
};

template <typename T0, typename... Ts>
struct are_ch_bit_convertible<T0, Ts...> {
  static constexpr bool value = is_cast_convertible<ch_bit<std::decay_t<T0>::bitsize>, T0>::value && are_ch_bit_convertible<Ts...>::value;
};

template <typename T, unsigned N = T::bitsize>
using bitbase_cast_t = std::conditional_t<
  std::is_base_of<bitbase<N>, T>::value, const bitbase<N>&, ch_bit<N>>;

template <typename T, unsigned N = T::bitsize,
          CH_REQUIRES(is_ch_bit_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  nodelist data(N, true);
  bitbase_cast_t<T, N> x(rhs);
  read_lnode(x, data, 0, N);
  return lnode(data);
}

// concatenation functions

template <typename T>
void ch_cat_helper(nodelist& data, const T& arg) {
  read_lnode(arg, data, 0, T::bitsize);
}

template <typename T0, typename... Ts>
void ch_cat_helper(nodelist& data, const T0& arg0, const Ts&... args) {
  ch_cat_helper(data, args...);
  read_lnode(arg0, data, 0, T0::bitsize);
}

template <typename... Ts>
const auto cat_impl(const Ts&... args) {
  nodelist data(concat_traits<Ts...>::bitsize, true);
  ch_cat_helper(data, args...);
  return make_type<ch_bit<concat_traits<Ts...>::bitsize>>(data);
}

template <typename... Ts,
         CH_REQUIRES(are_ch_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  return cat_impl(static_cast<bitbase_cast_t<Ts>>(args)...);
}

template <typename B, typename A,
          CH_REQUIRES(is_ch_bit_convertible<B>::value),
          CH_REQUIRES(is_ch_bit_convertible<A>::value)>
const auto operator,(const B& b, const A& a) {
  return ch_cat(b, a);
}

template <typename... Ts,
         CH_REQUIRES(are_ch_bit_convertible<Ts...>::value)>
concatref<Ts...> ch_tie(Ts&... args) {
  return concatref<Ts...>(args...);
}

// slice functions

template <unsigned N, typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_slice(const T&& in, size_t index = 0) {
  return ch::internal::const_sliceref<T, N>(std::move(in), index);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_aslice(const T&& in, size_t index = 0) {
  return ch::internal::const_sliceref<T, N>(std::move(in), index * N);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_slice(const T& in, size_t index = 0) {
  return const_sliceref<refproxy<T>, N>(in, index);
}

template <unsigned N, typename T,
          CH_REQUIRES(is_ch_bit_convertible<T>::value)>
const auto ch_aslice(const T& in, size_t index = 0) {
  return const_sliceref<refproxy<T>, N>(in, index * N);
}

// extend functions

template <unsigned D>
class zext_select {
public:
    template <unsigned N>
    const auto operator() (const bitbase<N>& in) {
      return ch_cat(ch_bit<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <unsigned N>
    const auto operator() (const bitbase<N>& in) {
      return ch_bit<N>(in);
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
  template <unsigned N>
  const auto operator() (const bitbase<N>& in) {
    return ch_cat(in[M-1], ch_bit<D>(0x0), ch_slice<M-1>(in, 1));
  }
};

template <unsigned D>
class sext_pad<1, D> {
public:
  template <unsigned N>
  const auto operator() (const bitbase<N>& in) {
    return ch_cat(in, ch_bit<D>(0x0));
  }
};

template <unsigned D>
class sext_select {
public:
  template <unsigned N>
  const auto operator() (const bitbase<N>& in) {
    return sext_pad<N, D>()(in);
  }
};

template <>
class sext_select<0> {
public:
  template <unsigned N>
  const auto operator() (const bitbase<N>& in) {
    return ch_bit<N>(in);
  }
};

template <unsigned N, unsigned M>
const auto ch_zext(const bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return zext_select<(N-M)>()(in);
}

template <unsigned N, unsigned M>
const auto ch_sext(const bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return sext_select<(N-M)>()(in);
}

// shuffle functions

template <unsigned N, unsigned I>
const auto ch_shuffle(const bitbase<N>& in,
                     const std::array<uint32_t, I>& indices) {  
  static_assert((I % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < I; ++i) {
    ret.template aslice<<(N / I)>(i) = in.template aslice<(N / I)>(indices[i]);
  }
  return ret;
}

// utils functions

template <unsigned N>
void ch_tap(const std::string& name, const bitbase<N>& value) {
  registerTap(name, get_lnode(value));
}

const ch_bit<64> ch_getTick();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRES(are_ch_bit_convertible<Args...>::value)>
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
