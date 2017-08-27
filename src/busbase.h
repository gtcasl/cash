#pragma once

#include "snode.h"

namespace cash {
namespace detail {

template <unsigned N> using ch_busbase = typebase<N, snode::data_type>;

template <unsigned N>
class typebase<N, snode::data_type> : public typebase_itf<snode::data_type> {
public:   
  static const unsigned bit_count = N;
  using data_type = snode::data_type;
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
  
#define CH_DEF_AOP(type) \
  typebase& operator=(type rhs) { \
    snode node(bitvector(N, rhs)); \
    this->write_data(0, {node, 0 , N}, 0, N); \
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
  
  void read(void* out, uint32_t offset, uint32_t length) const {
    assert(offset + length <= N);
    get_node(*this).read(reinterpret_cast<uint8_t*>(out), offset, length, N);
  }
  
  void write(const void* in, uint32_t offset, uint32_t length) {
    assert(offset + length <= N);
    get_node(*this).write(reinterpret_cast<const uint8_t*>(in), offset, length, N);
  }
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

template <unsigned N>
bool operator==(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return get_node(lhs).is_equal(get_node(rhs), N);
}

template <unsigned N>
bool operator<(const ch_busbase<N>& lhs, const ch_busbase<N>& rhs) {
  return get_node(lhs).is_less(get_node(rhs), N);
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

}
}
