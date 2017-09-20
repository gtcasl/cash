#pragma once

#include "busbase.h"

namespace cash {
namespace internal {

#define CH_BUS_INTERFACE(type) \
  type& operator=(const ch_busbase<type::bitcount>& rhs) { \
    this->assign(rhs); \
    return *this; \
  } \
  template <typename U, CH_REQUIRES(cash::internal::is_bit_scalar<U>::value)> \
  type& operator=(U rhs) { \
    this->assign(rhs); \
    return *this; \
  } \

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:
  using base = ch_busbase<N>;
  using data_t = snode;

  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : node_(rhs.node_, N) {}

  ch_bus(ch_bus&& rhs) : node_(std::move(rhs.node_)) {}
  
  ch_bus(const ch_busbase<N>& rhs) : node_(get_snode(rhs), N) {}

  template <typename U,
            CH_REQUIRES(is_bit_scalar<U>::value)>
  explicit ch_bus(U rhs) : node_(bitvector(N, rhs)) {}
   
  ch_bus& operator=(const ch_bus& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bus& operator=(ch_bus&& rhs) {
    node_ = std::move(rhs.node_);
    return *this;
  }

  CH_BUS_INTERFACE(ch_bus)
  
  template <typename U,
            CH_REQUIRES(is_bit_scalar<U>::value)>
  operator U() const {
    return static_cast<U>(node_.get_value()); \
  }

  void write(uint32_t dst_offset, const void* in, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) {
    assert(dst_offset + length <= N);
    assert(src_offset + length <= sizeInBytes * 8);
    node_.write(dst_offset, in, sizeInBytes, src_offset, length, N);
  }

protected:

  ch_bus(const snode& node) : node_(node) {
    assert(N == node_.get_size());
  }
  
  void read_data(nodelist<snode>& inout, size_t offset, size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const nodelist<snode>& in, size_t src_offset, size_t length) override {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }
  
  snode node_;

  template <unsigned M> friend const ch_bus<M> make_bus(const snode& node);
};

template <unsigned N>
const ch_bus<N> make_bus(const snode& node) {
  return ch_bus<N>(node);
}

template <typename T, unsigned N = std::decay<T>::type::bitcount>
struct is_bus_convertible {
  static constexpr bool value = is_cast_convertible<T, ch_bus<N>>::value;
};

template <typename... Ts>
struct are_bus_convertible;

template <typename T>
struct are_bus_convertible<T> {
  static constexpr bool value = is_cast_convertible<T, ch_bus<std::decay<T>::type::bitcount>>::value;
};

template <typename T0, typename... Ts>
struct are_bus_convertible<T0, Ts...> {
  static constexpr bool value = is_cast_convertible<T0, ch_bus<std::decay<T0>::type::bitcount>>::value && are_bus_convertible<Ts...>::value;
};

template <typename T, unsigned N = T::bitcount>
using bus_cast = std::conditional<
  std::is_base_of<ch_busbase<N>, T>::value,
  const ch_busbase<N>&,
  ch_bus<N>>;

template <typename T, unsigned N = T::bitcount,
          CH_REQUIRES(is_bus_convertible<T, N>::value)>
snode get_snode(const T& rhs) {
  nodelist<snode> data(N);
  typename bus_cast<T, N>::type x(rhs);
  read_data(x, data, 0, N);
  return snode(data);
}

template <unsigned N>
std::ostream& operator<<(std::ostream& os, const ch_busbase<N>& bus) {
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
