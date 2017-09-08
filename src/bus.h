#pragma once

#include "busbase.h"

namespace cash {
namespace internal {

template <unsigned N> 
class ch_bus : public ch_busbase<N> {
public:  
  using base = ch_busbase<N>;
  using data_type = typename base::data_type;
  using bus_type = ch_bus;
      
  ch_bus() {}
  
  ch_bus(const ch_bus& rhs) : node_(rhs.node_, N) {}

  ch_bus(ch_bus&& rhs) : node_(std::move(rhs.node_)) {}
  
  ch_bus(const ch_busbase<N>& rhs) : node_(get_snode(rhs)) {}
  
  ch_bus(const ch_literal<N>& rhs) : node_(rhs) {}
 
#define CH_DEF_CTOR(type) \
  explicit ch_bus(type value) : node_(bitvector(N, value)) {}
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
   
  ch_bus& operator=(const ch_bus& rhs) {
    node_.assign(rhs.node_, N);
    return *this;
  }

  ch_bus& operator=(ch_bus&& rhs) {
    node_ = std::move(rhs.node_);
    return *this;
  }

  ch_bus& operator=(const ch_literal<N>& rhs) {
    node_.assign(rhs);
    return *this;
  }
  
  ch_bus& operator=(const ch_busbase<N>& rhs) {
    node_.assign(get_snode(rhs), N);
    return *this;
  }

#define CH_DEF_AOP(type) \
  ch_bus& operator=(type value) { \
    node_.assign(bitvector(N, value)); \
    return *this; \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
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
  
#define CH_DEF_CAST(type) \
  operator type() const { \
    return static_cast<type>(node_.get_value()); \
  } 
  CH_DEF_CAST(bool)
  CH_DEF_CAST(char)
  CH_DEF_CAST(int8_t)
  CH_DEF_CAST(uint8_t)
  CH_DEF_CAST(int16_t)
  CH_DEF_CAST(uint16_t)
  CH_DEF_CAST(int32_t)
  CH_DEF_CAST(uint32_t)
  CH_DEF_CAST(int64_t)
  CH_DEF_CAST(uint64_t)
#undef CH_DEF_CAST

protected:

  ch_bus(snodeimpl* node) : node_(node) {
    assert(N == node_.get_size());
  }
  
  void read_data(data_type& inout, size_t offset, size_t length) const override {
    node_.read_data(inout, offset, length, N);
  }
  
  void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t length) override {
    node_.write_data(dst_offset, in, src_offset, length, N);
  }
  
  snode node_;

  template <unsigned M> friend const ch_bus<M> make_bus(snodeimpl* node);
};

template <unsigned N>
const ch_bus<N> make_bus(snodeimpl* node) {
  return ch_bus<N>(node);
}

template<typename... Ts>
struct is_bus_convertible;

template<typename T>
struct is_bus_convertible<T> {
  static const bool value = is_weak_convertible<T, ch_bus<T::bitcount>>::value;
};

template<typename T0, typename... Ts>
struct is_bus_convertible<T0, Ts...> {
  static const bool value = is_weak_convertible<T0, ch_bus<T0::bitcount>>::value && is_bus_convertible<Ts...>::value;
};

template <typename T, unsigned N = T::bitcount>
struct ch_bus_cast {
  using type = ch_bus<N>;
};

template <unsigned N>
struct ch_bus_cast<ch_busbase<N>, N> {
  using type = const ch_busbase<N>&;
};

template <unsigned N>
struct ch_bus_cast<ch_bus<N>, N> {
  using type = const ch_bus<N>&;
};

template <typename T, unsigned N = T::bitcount,
          CH_REQUIRES(is_weak_convertible<T, ch_bus<N>>::value)>
snode get_snode(const T& rhs) {
  snode::data_type data(N);
  typename ch_bus_cast<T, N>::type x(rhs);
  read_data(x, data, 0, N);
  return snode(data);
}

template <unsigned N>
std::ostream& operator<<(std::ostream& os, const ch_busbase<N>& bus) {
  return os << get_snode(bus);
}

template <unsigned N>
bool operator==(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return get_snode(lhs).is_equal(get_snode(rhs), N);
}

template <unsigned N>
bool operator<(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return get_snode(lhs).is_less(get_snode(rhs), N);
}

template <unsigned N>
bool operator!=(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return !(lhs == rhs);
}

template <unsigned N>
bool operator>(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return (rhs < lhs);
}

template <unsigned N>
bool operator<=(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return !(lhs > rhs);
}

template <unsigned N>
bool operator>=(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return !(lhs < rhs);
}

#define CH_DEF_COMP_IMPL(op, type) \
  template <unsigned N> \
  bool op(const ch_busbase<N>& lhs, type rhs) { \
    return op(lhs, ch_bus<N>(rhs)); \
  } \
  template <unsigned N> \
  bool op(type lhs, const ch_busbase<N>& rhs) { \
    return op(ch_bus<N>(lhs), rhs); \
  }
#define CH_DEF_COMP(type) \
  CH_DEF_COMP_IMPL(operator==, type) \
  CH_DEF_COMP_IMPL(operator!=, type) \
  CH_DEF_COMP_IMPL(operator< , type) \
  CH_DEF_COMP_IMPL(operator> , type) \
  CH_DEF_COMP_IMPL(operator<=, type) \
  CH_DEF_COMP_IMPL(operator>=, type)
  CH_DEF_COMP(const std::initializer_list<uint32_t>&)
  CH_DEF_COMP(char)
  CH_DEF_COMP(int8_t)
  CH_DEF_COMP(uint8_t)
  CH_DEF_COMP(int16_t)
  CH_DEF_COMP(uint16_t)
  CH_DEF_COMP(int32_t)
  CH_DEF_COMP(uint32_t)
  CH_DEF_COMP(int64_t)
  CH_DEF_COMP(uint64_t)
#undef CH_DEF_COMP
#undef CH_DEF_COMP_IMPL

}
}
