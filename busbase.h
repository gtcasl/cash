#pragma once

#include "snode.h"

namespace chdl_internal {

template <unsigned N> class ch_bus;

template <unsigned N>
class typebase<N, snode::bitstream_type> {
public:   
  static const unsigned bit_count = N;
  using bitstream_type = snode::bitstream_type;
  
  typebase& operator=(const typebase& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
#define CHDL_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =(ch_bus<N>(value)); \
  } 
  CHDL_DEF_AOP(const std::initializer_list<uint32_t>&)
  CHDL_DEF_AOP(char)
  CHDL_DEF_AOP(int8_t)
  CHDL_DEF_AOP(uint8_t)
  CHDL_DEF_AOP(int16_t)
  CHDL_DEF_AOP(uint16_t)
  CHDL_DEF_AOP(int32_t)
  CHDL_DEF_AOP(uint32_t)
  CHDL_DEF_AOP(int64_t)
  CHDL_DEF_AOP(uint64_t)
#undef CHDL_DEF_AOP
  
  bool operator==(const typebase& rhs) const {
    return (this->get_node() == rhs.get_node());
  }
  
  bool operator<(const typebase& rhs) const {
    return (this->get_node() < rhs.get_node());
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
  
#define CHDL_DEF_COMP(type) \
  bool operator==(type value) const { return this->operator==(ch_bus<N>(value)); } \
  bool operator!=(type value) const { return this->operator!=(ch_bus<N>(value)); } \
  bool operator< (type value) const { return this->operator< (ch_bus<N>(value)); } \
  bool operator> (type value) const { return this->operator> (ch_bus<N>(value)); } \
  bool operator<=(type value) const { return this->operator<=(ch_bus<N>(value)); } \
  bool operator>=(type value) const { return this->operator>=(ch_bus<N>(value)); }  
  CHDL_DEF_COMP(const std::initializer_list<uint32_t>&)
  CHDL_DEF_COMP(char)
  CHDL_DEF_COMP(int8_t)
  CHDL_DEF_COMP(uint8_t)
  CHDL_DEF_COMP(int16_t)
  CHDL_DEF_COMP(uint16_t)
  CHDL_DEF_COMP(int32_t)
  CHDL_DEF_COMP(uint32_t)
  CHDL_DEF_COMP(int64_t)
  CHDL_DEF_COMP(uint64_t)
#undef CHDL_DEF_COMP  
  
  virtual snode get_node() const {
    bitstream_type data(N);
    this->read(data, 0, N);
    return snode(data);
  }
  
protected:

  virtual void read(bitstream_type& inout, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, typename T_::bitstream_type& inout, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const typename T_::bitstream_type& in, size_t src_offset, size_t src_length); 
  template <unsigned N_> friend std::ostream& operator<<(std::ostream& os, const typebase<N_, snode::bitstream_type>& b);
};

template <unsigned N> using ch_busbase = typebase<N, snode::bitstream_type>;
using ch_signalbase = ch_busbase<1>;

template <unsigned N> 
std::ostream& operator<<(std::ostream& os, const ch_busbase<N>& b) {
  return os << b.get_node();
}

}
