#pragma once

#include "lnode.h"

namespace chdl_internal {

template <unsigned N> class ch_bitv;

template <unsigned N>
class typebase<N, lnode::bitstream_type> {
public:   
  static const unsigned bit_count = N;
  typedef lnode::bitstream_type bitstream_type;
  
  typebase() {}
  virtual ~typebase() {}
  
  template <unsigned M>
  const_slice_ref<typebase, M> slice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M>
  slice_ref<typebase, M> slice(size_t index) {
    return slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M>
  const_slice_ref<typebase, M> aslice(size_t index) const {
    return const_slice_ref<typebase, M>(*this, index * M);
  }
  
  template <unsigned M>
  slice_ref<typebase, M> aslice(size_t index) {
    return slice_ref<typebase, M>(*this, index * M);
  }
  
  const_subscript_ref<typebase> operator[](size_t index) const {
    return const_subscript_ref<typebase>(*this, index); 
  }
  
  subscript_ref<typebase> operator[](size_t index) {
    return subscript_ref<typebase>(*this, index); 
  }
  
  typebase& operator=(const typebase& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
 
#define CHDL_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =(ch_bitv<N>(value)); \
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
  
  virtual lnode get_node() const {
    bitstream_type data(N);
    this->read(data, 0, N);
    return lnode(data);
  }
  
protected:

  virtual void read(bitstream_type& inout, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, typename T_::bitstream_type& inout, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const typename T_::bitstream_type& in, size_t src_offset, size_t src_length); 
};

template <unsigned N> using ch_bitbase = typebase<N, lnode::bitstream_type>;
using ch_logicbase = ch_bitbase<1>;

}
