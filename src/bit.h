#pragma once

#include "bitbase.h"
#include "vec.h"

namespace cash {
namespace internal {

void createPrintNode(const std::string& format,
                     const std::initializer_list<lnode>& args);

void createPrintNode(const lnode& pred,
                     const std::string& format,
                     const std::initializer_list<lnode>& args);

template <unsigned N> class ch_bus;

template <unsigned N>
class ch_bit : public ch_bitbase<N> {
public:
  using base = ch_bitbase<N>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus<N>;
      
  ch_bit() : node_(N) {}
  
  ch_bit(const ch_bit& rhs) : node_(rhs.node_, N) {}

  ch_bit(ch_bit&& rhs) : node_(std::move(rhs.node_), N) {}

  ch_bit(const ch_bitbase<N>& rhs) : node_(get_lnode(rhs), N) {}

  ch_bit(const ch_literal<N>& rhs) : node_(rhs) {}
    
#define CH_DEF_CTOR(type) \
  explicit ch_bit(type value) : node_(bitvector(N, value)) {}
  CH_DEF_CTOR(const std::initializer_list<uint32_t>&)
  CH_DEF_CTOR(bool)
  CH_DEF_CTOR(char)
  CH_DEF_CTOR(int8_t)
  CH_DEF_CTOR(uint8_t)
  CH_DEF_CTOR(int16_t)
  CH_DEF_CTOR(uint16_t)
  CH_DEF_CTOR(int32_t)
  CH_DEF_CTOR(uint32_t)
  CH_DEF_CTOR(int64_t)
  CH_DEF_CTOR(uint64_t)
#undef CH_DEF_CTOR
  
  ch_bit& operator=(const ch_bit& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    node_.move(rhs.node_, N);
    return *this;
  }
  
  ch_bit& operator=(const ch_literal<N>& rhs) {
    node_.assign(rhs);
    return *this;
  }

  ch_bit& operator=(const ch_bitbase<N>& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
  
#define CH_DEF_AOP(type) \
  ch_bit& operator=(type value) { \
    node_.assign(bitvector(N, value)); \
    return *this; \
  } 
  CH_DEF_AOP(bool)
  CH_DEF_AOP(char)
  CH_DEF_AOP(int8_t)
  CH_DEF_AOP(uint8_t)
  CH_DEF_AOP(int16_t)
  CH_DEF_AOP(uint16_t)
  CH_DEF_AOP(int32_t)
  CH_DEF_AOP(uint32_t)
  CH_DEF_AOP(int64_t)
  CH_DEF_AOP(uint64_t)
#undef CH_DEF_AOP

  const auto clone() const {
    return make_bit<N>(node_.clone(N));
  }
  
protected:

  ch_bit(lnodeimpl* node) : node_(node) {
    assert(N == node_.get_size());
  }

  void read_data(data_type& inout,
                 size_t offset,
                 size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset,
                  const data_type& in,
                  size_t src_offset,
                  size_t length) override {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }

  lnode node_;

  template <unsigned M> friend const ch_bit<M> make_bit(lnodeimpl* node);
};

template <unsigned N>
const ch_bit<N> make_bit(lnodeimpl* node) {
  return ch_bit<N>(node);
}

template<typename... Ts>
struct is_bit_convertible;

template<typename T>
struct is_bit_convertible<T> {
  static const bool value = is_weak_convertible<T, ch_bit<T::bitcount>>::value;
};

template<typename T0, typename... Ts>
struct is_bit_convertible<T0, Ts...> {
  static const bool value = is_weak_convertible<T0, ch_bit<T0::bitcount>>::value && is_bit_convertible<Ts...>::value;
};

template <typename T, unsigned N = T::bitcount>
struct ch_bit_cast {
  using type = ch_bit<N>;
};

template <unsigned N>
struct ch_bit_cast<ch_bitbase<N>, N> {
  using type = const ch_bitbase<N>&;
};

template <unsigned N>
struct ch_bit_cast<ch_bit<N>, N> {
  using type = const ch_bit<N>&;
};

template <typename T, unsigned N = T::bitcount,
          CH_REQUIRES(is_weak_convertible<T, ch_bit<N>>::value)>
lnode get_lnode(const T& rhs) {
  lnode::data_type data(N);
  typename ch_bit_cast<T, N>::type x(rhs);
  read_data(x, data, 0, N);
  return lnode(data);
}

// concatenation functions

template<typename T>
void ch_cat_helper(lnode::data_type& data, const T& arg) {
  typename ch_bit_cast<T>::type x(arg);
  read_data(x, data, 0, T::bitcount);
}

template<typename T0, typename... Ts>
void ch_cat_helper(lnode::data_type& data, const T0& arg0, const Ts&... args) {
  ch_cat_helper(data, args...);
  typename ch_bit_cast<T0>::type x(arg0);
  read_data(x, data, 0, T0::bitcount);
}

template<typename... Ts,
         CH_REQUIRES(is_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  lnode::data_type data(concat_size<Ts...>::value);
  ch_cat_helper(data, args...);
  lnode node(data);
  return make_bit<concat_size<Ts...>::value>(node.get_impl());
}

template <typename U, typename V,
          CH_REQUIRES(is_weak_convertible<U, ch_bit<U::bitcount>>::value),
          CH_REQUIRES(is_weak_convertible<V, ch_bit<V::bitcount>>::value)>
const auto operator,(const U& b, const V& a) {
  return ch_cat(b, a);
}

template<typename... Ts,
         CH_REQUIRES(is_bit_convertible<Ts...>::value)>
concatref<Ts...> ch_tie(Ts&... args) {
  return concatref<Ts...>(args...);
}

// slice functions

template <unsigned N, unsigned M>
const auto ch_slice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, unsigned M>
const auto ch_aslice(const ch_bitbase<M>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

// extend functions

template <unsigned D>
class zext_select {
public:
    template <unsigned M>
    const auto operator() (const ch_bitbase<M>& in) {
      return (ch_bit<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <unsigned M>
    const ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
   const auto operator() (const ch_bitbase<M>& in) {
      return (in[M-1], ch_bit<D>(0x0), ch_slice<M-1>(in, 1));
    }    
};

template <unsigned D>
class sext_pad<1, D> {
public:
    const auto operator() (const ch_bitbase<1>& in) {
      return (in, ch_bit<D>(0x0));
    }
};

template <unsigned D>
class sext_select {
public:
    template <unsigned M>
    const auto operator() (const ch_bitbase<M>& in) {
      return sext_pad<M, D>()(in);
    }
};

template <>
class sext_select<0> {
public:
    template <unsigned M>
   const ch_bit<M> operator() (const ch_bitbase<M>& in) {
      return in;
    }
};

template <unsigned N, unsigned M>
const auto ch_zext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return zext_select<(N-M)>()(in);
}

template <unsigned N, unsigned M>
const auto ch_sext(const ch_bitbase<M>& in) {
  static_assert(N >= M, "invalid extend size");
  return sext_select<(N-M)>()(in);
}

// shuffle functions

template <unsigned N, unsigned I>
const auto ch_shuffle(const ch_bitbase<N>& in,
                     const std::array<uint32_t, I>& indices) {
  static_assert((I % N) == 0, "invalid indices size");
  ch_bit<N> ret;
  for (unsigned i = 0; i < I; ++i) {
    ret.template aslice<<(N / I)>(i) = in.template aslice<(N / I)>(indices[i]);
  }
  return ret;
}

// print functions

const ch_bit<64> ch_getTick();

template <typename...Args,
          CH_REQUIRES(is_bit_convertible<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

}
}
