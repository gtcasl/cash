#pragma once

#include "lnode.h"

namespace chdl_internal {

template <unsigned N> class ch_bit;

template <unsigned N>
class typebase<N, lnode::bitstream_type> { // LCOV_EXCL_LINE
public:   
  static const unsigned bit_count = N;
  using bitstream_type = lnode::bitstream_type;
  
  const_slice_ref<typebase, 1> operator[](size_t index) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, 1>(*this, index); 
  }
  
  slice_ref<typebase, 1> operator[](size_t index) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, 1>(*this, index); 
  }
  
  template <unsigned M>
  const_slice_ref<typebase, M> slice(size_t index) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M>
  slice_ref<typebase, M> slice(size_t index) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, M>(*this, index);
  }
  
  template <unsigned M>
  const_slice_ref<typebase, M> aslice(size_t index) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, M>(*this, index * M);
  }
  
  template <unsigned M>
  slice_ref<typebase, M> aslice(size_t index) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, M>(*this, index * M);
  }
  
  typebase& operator=(const typebase& rhs) {
    bitstream_type data(N);
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
 
#define CHDL_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =(ch_bit<N>(value)); \
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
  
 // LCOV_EXCL_START
  virtual lnode get_node() const {
    bitstream_type data(N);
    this->read(data, 0, N);
    return lnode(data);
  }
// LCOV_EXCL_END
  
protected:

  virtual void read(bitstream_type& inout, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const bitstream_type& in, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, typename T_::bitstream_type& inout, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const typename T_::bitstream_type& in, size_t src_offset, size_t src_length); 
};

template <unsigned N> using ch_bitbase = typebase<N, lnode::bitstream_type>;
using ch_logicbase = ch_bitbase<1>;

}
