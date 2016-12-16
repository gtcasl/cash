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
  
  typebase& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    return this->operator =(ch_bus<N>(value ? 0x1 : 0x0));
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
  
  virtual void readBytes(void* out, uint32_t sizeInBytes) const {  
    assert(sizeInBytes * 8 >= N);
    this->get_node().readBytes(reinterpret_cast<uint8_t*>(out), sizeInBytes);
  }
  
  virtual void writeBytes(const void* in, uint32_t sizeInBytes) {
    assert(sizeInBytes * 8 >= N);
    ch_bus<N> tmp;
    tmp.writeBytes(reinterpret_cast<const uint8_t*>(in), sizeInBytes);
    this->operator =(tmp);
  }
  
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

#define CHDL_DEF_COMP_IMPL(op, type) \
  template <unsigned N> bool op(const ch_busbase<N>& lhs, type rhs) { return lhs.op(ch_bus<N>(rhs)); } \
  template <unsigned N> bool op(type rhs, const ch_busbase<N>& lhs) { return ch_bus<N>(lhs).op(rhs); }
#define CHDL_DEF_COMP(type) \
  CHDL_DEF_COMP_IMPL(operator==, type) \
  CHDL_DEF_COMP_IMPL(operator!=, type) \
  CHDL_DEF_COMP_IMPL(operator< , type) \
  CHDL_DEF_COMP_IMPL(operator> , type) \
  CHDL_DEF_COMP_IMPL(operator<=, type) \
  CHDL_DEF_COMP_IMPL(operator>=, type) 
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
#undef CHDL_DEF_COMP_IMPL

}
