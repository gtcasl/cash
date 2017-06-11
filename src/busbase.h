#pragma once

#include "snode.h"

namespace cash {
namespace detail {

template <unsigned N> class ch_bus;
template <unsigned N> using ch_busbase = typebase<N, snode::data_type>;
using ch_signalbase = ch_busbase<1>;

template <unsigned N>
class typebase<N, snode::data_type> {
public:   
  static const unsigned bit_count = N;
  using data_type = snode::data_type;
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
  
  typebase& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    return this->operator =(ch_bus<N>(value ? 0x1 : 0x0));
  } 
  
#define CH_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =(ch_bus<N>(value)); \
  } 
  CH_DEF_AOP(const std::initializer_list<uint32_t>&)
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
  
  bool operator==(const typebase& rhs) const {
    return get_node(*this).is_equal(get_node(rhs), N);
  }
  
  bool operator<(const typebase& rhs) const {
    return get_node(*this).is_less(get_node(rhs), N);
  }
  
  bool operator!=(const typebase& rhs) const {
    return !(*this == rhs);
  }
  
  bool operator>(const typebase& rhs) const {
    return (rhs < *this);
  }
  
  bool operator<=(const typebase& rhs) const {
    return !(*this > rhs);
  }
  
  bool operator>=(const typebase& rhs) const {
    return !(*this < rhs);
  }
  
  virtual void read(void* out, uint32_t offset, uint32_t length) const {
    get_node(*this).read(reinterpret_cast<uint8_t*>(out), offset, length, N);
  }
  
  virtual void write(const void* in, uint32_t offset, uint32_t length) {
    ch_bus<N> tmp;
    tmp.write(reinterpret_cast<const uint8_t*>(in), offset, length), N;
    this->operator =(tmp);
  }

protected:

  virtual void read_data(data_type& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) = 0;

  template <unsigned N_> friend snode get_node(const ch_busbase<N_>& b);
  template <typename T_> friend void read_data(const T_& b, typename T_::data_type& inout, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& b, size_t dst_offset, const typename T_::data_type& in, size_t src_offset, size_t src_length);
};

template <unsigned N>
snode get_node(const ch_busbase<N>& b) {
  snode::data_type data(N);
  b.read_data(data, 0, N);
  return snode(data);
}

template <unsigned N> 
std::ostream& operator<<(std::ostream& os, const ch_busbase<N>& b) {
  return os << get_node(b);
}

#define CH_DEF_COMP_IMPL(op, type) \
  template <unsigned N> bool op(const ch_busbase<N>& lhs, type rhs) { return lhs.op(ch_bus<N>(rhs)); } \
  template <unsigned N> bool op(type lhs, const ch_busbase<N>& rhs) { return ch_bus<N>(lhs).op(rhs); }

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
