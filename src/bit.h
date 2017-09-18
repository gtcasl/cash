#pragma once

#include "bitbase.h"
#include "vec.h"

namespace cash {
namespace internal {

void createPrintNode(const std::string& format,
                     const std::initializer_list<lnode>& args);

template <unsigned N> class ch_bus;

template <unsigned N> class ch_bit;

template <unsigned N> class const_bit;

template <unsigned N>
struct traits < ch_bit<N> > {
  static constexpr unsigned bitcount = N;
  static constexpr bool readonly = false;
  using data_type  = lnode;
  using value_type = ch_bit<N>;
  using const_type = const_bit<N>;
  using bus_type   = ch_bus<N>;
};

template <unsigned N>
struct traits < const_bit<N> > {
  static constexpr unsigned bitcount = N;
  static constexpr bool readonly = true;
  using data_type  = lnode;
  using value_type = const_bit<N>;
  using const_type = const_bit<N>;
  using bus_type   = ch_bus<N>;
};

template <unsigned N>
class ch_bit : public ch_bitbase< ch_bit<N> > {
public:
  using base = ch_bitbase< ch_bit<N> >;
  using base::operator=;
      
  ch_bit() : node_(N) {}
  
  ch_bit(const ch_bit& rhs) : node_(rhs.node_, N) {}

  ch_bit(ch_bit&& rhs) : node_(std::move(rhs.node_), N) {}

  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == N)>
  ch_bit(const ch_bitbase<OtherDerived>& rhs) : node_(get_lnode(rhs), N) {}

  ch_bit(const ch_boolean& rhs) : node_(bitvector(N, (int)rhs)) {}
    
  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  explicit ch_bit(T rhs) : node_(bitvector(N, rhs)) {}

  ch_bit& operator=(const ch_bit& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bit& operator=(ch_bit&& rhs) {
    node_.move(rhs.node_, N);
    return *this;
  }

  const auto clone() const {
    return make_bit<N>(node_.clone(N));
  }
  
protected:

  ch_bit(const lnode& node) : node_(node) {
    assert(N == node_.get_size());
  }

  void read_data(nodelist<lnode>& inout, size_t offset, size_t length) const {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const nodelist<lnode>& in, size_t src_offset, size_t length) {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }

  lnode node_;

  template <typename T> friend class typebase;

  template <unsigned M> friend const ch_bit<M> make_bit(const lnode& node);
};

template <unsigned N>
class const_bit : public ch_bitbase< const_bit<N> > {
public:

  const_bit() : node_(N) {}

  const_bit(const const_bit& rhs) : node_(rhs.node_, N) {}

  const_bit(const_bit&& rhs) : node_(std::move(rhs.node_), N) {}

  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == N)>
  const_bit(const ch_bitbase<OtherDerived>& rhs) : node_(get_lnode(rhs), N) {}

  const_bit(const ch_boolean& rhs) : node_(bitvector(N, (int)rhs)) {}

  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  explicit const_bit(T rhs) : node_(bitvector(N, rhs)) {}

  const auto clone() const {
    return make_bit<N>(node_.clone(N));
  }

protected:

  const_bit& operator=(const const_bit& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  const_bit& operator=(const_bit&& rhs) {
    node_.move(rhs.node_, N);
    return *this;
  }

  void read_data(nodelist<lnode>& inout, size_t offset, size_t length) const {
    node_.read_data(inout, offset, length, N);
  }

  void write_data(size_t dst_offset, const nodelist<lnode>& in, size_t src_offset, size_t length) {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }

  lnode node_;

  template <typename T> friend class typebase;
};

template <unsigned N>
const ch_bit<N> make_bit(const lnode& node) {
  return ch_bit<N>(node);
}

template <typename T, unsigned N = traits<typename std::decay<T>::type>::bitcount>
struct is_bit_convertible {
  static constexpr bool value = is_cast_convertible<T, ch_bit<N>>::value;
};

template <typename... Ts>
struct are_bit_convertible;

template <typename T>
struct are_bit_convertible<T> {
  static constexpr bool value = is_cast_convertible<T, ch_bit<traits<typename std::decay<T>::type>::bitcount>>::value;
};

template <typename T0, typename... Ts>
struct are_bit_convertible<T0, Ts...> {
  static constexpr bool value = is_cast_convertible<T0, ch_bit<traits<typename std::decay<T0>::type>::bitcount>>::value && are_bit_convertible<Ts...>::value;
};

template <typename T, unsigned N = traits<T>::bitcount>
struct ch_bit_cast {
  using type = const ch_bit<N>;
};

template <typename T>
struct ch_bit_cast< ch_bitbase<T>, 0 > {
  using type = const ch_bitbase<T>&;
};

template <unsigned N>
struct ch_bit_cast< ch_bit<N>, 0 > {
  using type = const ch_bit<N>&;
};

template <typename T, unsigned N = traits<T>::bitcount,
          CH_REQUIRES(is_bit_convertible<T, N>::value)>
lnode get_lnode(const T& rhs) {
  nodelist<lnode> data(N);
  typename ch_bit_cast<T, N>::type x(rhs);
  read_data(x, data, 0, N);
  return lnode(data);
}

// concatenation functions

template <typename T>
void ch_cat_helper(nodelist<lnode>& data, const T& arg) {
  read_data(arg, data, 0, traits<T>::bitcount);
}

template <typename T0, typename... Ts>
void ch_cat_helper(nodelist<lnode>& data, const T0& arg0, const Ts&... args) {
  ch_cat_helper(data, args...);
  read_data(arg0, data, 0, traits<T0>::bitcount);
}

template <typename... Ts>
const auto cat_impl(const Ts&... args) {
  nodelist<lnode> data(concat_info<Ts...>::bitcount);
  ch_cat_helper(data, args...);
  return make_bit<concat_info<Ts...>::bitcount>(lnode(data));
}

template <typename... Ts,
         CH_REQUIRES(are_bit_convertible<Ts...>::value)>
const auto ch_cat(const Ts&... args) {
  return cat_impl(static_cast<typename ch_bit_cast<Ts>::type>(args)...);
}

template <typename B, typename A>
const auto operator,(const ch_bitbase<B>& b, const ch_bitbase<A>& a) {
  return ch_cat(b, a);
}

template <typename... Ts,
         CH_REQUIRES(are_bit_convertible<Ts...>::value)>
concatref<Ts...> ch_tie(Ts&... args) {
  return concatref<Ts...>(args...);
}

// slice functions

template <unsigned N, unsigned M>
const auto ch_slice(const ch_bit<M>&& in, size_t index = 0) {
  return std::move(in).template slice<N>(index);
}

template <unsigned N, unsigned M>
const auto ch_aslice(const ch_bit<M>&& in, size_t index = 0) {
  return std::move(in).template aslice<N>(index);
}

template <unsigned N, typename T>
const auto ch_slice(const ch_bitbase<T>& in, size_t index = 0) {
  return in.template slice<N>(index);
}

template <unsigned N, typename T>
const auto ch_aslice(const ch_bitbase<T>& in, size_t index = 0) {
  return in.template aslice<N>(index);
}

// extend functions

template <unsigned D>
class zext_select {
public:
    template <typename T>
    const auto operator() (const ch_bitbase<T>& in) {
      return ch_cat(ch_bit<D>(0x0), in);
    }
};

template <>
class zext_select<0> {
public:
    template <typename T>
    const auto operator() (const ch_bitbase<T>& in) {
      return ch_bit<traits<T>::bitcount>(in);
    }
};

template <unsigned M, unsigned D>
class sext_pad {
public:
  template <typename T>
  const auto operator() (const ch_bitbase<T>& in) {
    return ch_cat(in[M-1], ch_bit<D>(0x0), ch_slice<M-1>(in, 1));
  }
};

template <unsigned D>
class sext_pad<1, D> {
public:
  template <typename T>
  const auto operator() (const ch_bitbase<T>& in) {
    return ch_cat(in, ch_bit<D>(0x0));
  }
};

template <unsigned D>
class sext_select {
public:
  template <typename T>
  const auto operator() (const ch_bitbase<T>& in) {
    return sext_pad<traits<T>::bitcount, D>()(in);
  }
};

template <>
class sext_select<0> {
public:
  template <typename T>
  const auto operator() (const ch_bitbase<T>& in) {
    return ch_bit<traits<T>::bitcount>(in);
  }
};

template <unsigned N, typename T>
const auto ch_zext(const ch_bitbase<T>& in) {
  static_assert(N >= traits<T>::bitcount, "invalid extend size");
  return zext_select<(N-traits<T>::bitcount)>()(in);
}

template <unsigned N, typename T>
const auto ch_sext(const ch_bitbase<T>& in) {
  static_assert(N >= traits<T>::bitcount, "invalid extend size");
  return sext_select<(N-traits<T>::bitcount)>()(in);
}

// shuffle functions

template <typename T, unsigned I>
const auto ch_shuffle(const ch_bitbase<T>& in,
                     const std::array<uint32_t, I>& indices) {  
  static_assert((I % traits<T>::bitcount) == 0, "invalid indices size");
  ch_bit< traits<T>::bitcount > ret;
  for (unsigned i = 0; i < I; ++i) {
    ret.template aslice<<(traits<T>::bitcount / I)>(i) = in.template aslice<(traits<T>::bitcount / I)>(indices[i]);
  }
  return ret;
}

// print functions

const ch_bit<64> ch_getTick();

inline void ch_print(const std::string& format) {
  createPrintNode(format, {});
}

template <typename...Args,
          CH_REQUIRES(are_bit_convertible<Args...>::value)>
void ch_print(const std::string& format, const Args& ...args) {
  createPrintNode(format, {get_lnode(args)...});
}

// utils functions

template <typename... Ts>
struct return_type {
  using type = std::tuple<ch_bitbase<Ts>...>;
};

template <typename T>
struct return_type< ch_bitbase<T> > {
  using type = T;
};

template <typename T>
const auto make_return(const ch_bitbase<T>& x) {
  return x;
}

template <typename... Ts>
const auto make_return(const ch_bitbase<Ts>&... args) {
  return typename return_type<Ts...>::type(args...);
}

}
}

#define CH_OUT(...) typename cash::internal::return_type<__VA_ARGS__>::type
#define CH_RET(...) return cash::internal::make_return(__VA_ARGS__)
