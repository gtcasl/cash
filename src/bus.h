#pragma once

#include "busbase.h"

namespace cash {
namespace internal {

template <unsigned N>
class ch_bus;

template <unsigned N>
struct traits < ch_bus<N> > {
  static constexpr unsigned bitcount = N;
  static constexpr bool readonly = false;
  using data_type  = snode;
  using value_type = ch_bus<N>;
  using bus_type   = ch_bus<N>;
};

template <unsigned N> 
class ch_bus : public ch_busbase< ch_bus<N> > {
public:
  using base = ch_busbase< ch_bus<N> >;
  using base::operator=;

  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : node_(rhs.node_, N) {}

  ch_bus(ch_bus&& rhs) : node_(std::move(rhs.node_)) {}
  
  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == N)>
  ch_bus(const ch_busbase<OtherDerived>& rhs) : node_(get_snode(rhs), N) {}

  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  explicit ch_bus(T rhs) : node_(bitvector(N, rhs)) {}
   
  ch_bus& operator=(const ch_bus& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bus& operator=(ch_bus&& rhs) {
    node_ = std::move(rhs.node_);
    return *this;
  }
  
  template <typename T,
            CH_REQUIRES(is_scalar<T>::value)>
  operator T() const { \
    return static_cast<T>(node_.get_value()); \
  }

protected:

  ch_bus(const snode& node) : node_(node) {
    assert(N == node_.get_size());
  }
  
  void read_data(nodelist<snode>& inout, size_t offset, size_t length) const {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const nodelist<snode>& in, size_t src_offset, size_t length) {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }
  
  snode node_;

  template <typename T> friend class typebase;

  template <unsigned M> friend const ch_bus<M> make_bus(const snode& node);
};

template <unsigned N>
const ch_bus<N> make_bus(const snode& node) {
  return ch_bus<N>(node);
}

template <typename T, unsigned N = traits<typename std::decay<T>::type>::bitcount>
struct is_bus_convertible {
  static constexpr bool value = is_cast_convertible<T, ch_bus<N>>::value;
};

template <typename... Ts>
struct are_bus_convertible;

template <typename T>
struct are_bus_convertible<T> {
  static constexpr bool value = is_cast_convertible<T, ch_bus<traits<typename std::decay<T>::type>::bitcount>>::value;
};

template <typename T0, typename... Ts>
struct are_bus_convertible<T0, Ts...> {
  static constexpr bool value = is_cast_convertible<T0, ch_bus<traits<typename std::decay<T0>::type>::bitcount>>::value && are_bus_convertible<Ts...>::value;
};

template <typename T, unsigned N = traits<T>::bitcount>
struct ch_bus_cast {
  using type = ch_bus<N>;
};

template <typename T>
struct ch_bus_cast<ch_busbase<T>, 0> {
  using type = const ch_busbase<T>&;
};

template <unsigned N>
struct ch_bus_cast<ch_bus<N>, 0> {
  using type = const ch_bus<N>&;
};

template <typename T, unsigned N = traits<T>::bitcount,
          CH_REQUIRES(is_bus_convertible<T, N>::value)>
snode get_snode(const T& rhs) {
  nodelist<snode> data(N);
  typename ch_bus_cast<T, N>::type x(rhs);
  read_data(x, data, 0, N);
  return snode(data);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const ch_busbase<T>& bus) {
  return os << get_snode(bus);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator==(const A& a, const B& b) {
  return get_snode<A, deduce_type<A, B>::bitcount>(a).is_equal(
        get_snode<B, deduce_type<A, B>::bitcount>(b), deduce_type<A, B>::bitcount);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator<(const A& a, const B& b) {
  return get_snode<A, deduce_type<A, B>::bitcount>(a).is_less(
        get_snode<B, deduce_type<A, B>::bitcount>(b), deduce_type<A, B>::bitcount);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator!=(const A& a, const B& b) {
  return !(a == b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator>(const A& a, const B& b) {
  return (b < a);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator<=(const A& a, const B& b) {
  return !(a > b);
}

template <typename A, typename B,
          CH_REQUIRES(deduce_type<A, B>::bitcount != 0),
          CH_REQUIRES(is_bus_convertible<A, deduce_type<A, B>::bitcount>::value),
          CH_REQUIRES(is_bus_convertible<B, deduce_type<A, B>::bitcount>::value)>
bool operator>=(const A& a, const B& b) {
  return !(a < b);
}

}
}
