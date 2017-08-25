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
  
  void read(void* out, uint32_t offset, uint32_t length) const {
    assert(offset + length <= N);
    get_node(*this).read(reinterpret_cast<uint8_t*>(out), offset, length, N);
  }
  
  void write(const void* in, uint32_t offset, uint32_t length) {
    assert(offset + length <= N);
    get_node(*this).write(reinterpret_cast<const uint8_t*>(in), offset, length, N);
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

}
}
