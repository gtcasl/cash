#pragma once

#include "typebase.h"
#include "snode.h"

namespace chdl_internal {

template <unsigned N> class ch_bus;

template <unsigned N>
class typebase<N, snode> {
public:   
  static const unsigned bit_count = N;
  typedef snode data_type;
  
  typebase() {}
  virtual ~typebase() {}
  
  typebase& operator=(const typebase& rhs) {
    std::vector< partition<data_type> > data;
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
  typebase& operator=(const std::initializer_list<uint32_t>& value) {
    return this->operator =(ch_bus<N>(value));
  } 
  
  typebase& operator=(uint32_t value) {
    return this->operator =({value});
  }

#define CHDL_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =({static_cast<uint32_t>(value)}); \
  } 
  CHDL_DEF_AOP(int8_t)
  CHDL_DEF_AOP(uint8_t)
  CHDL_DEF_AOP(int16_t)
  CHDL_DEF_AOP(uint16_t)
  CHDL_DEF_AOP(int32_t)
  CHDL_DEF_AOP(int64_t)
  CHDL_DEF_AOP(uint64_t)
#undef CHDL_DEF_AOP
  
  operator snode() const { 
    return ch_bus<N>(*this); 
  }
  
protected:

  virtual void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) = 0;
  
  template <typename T_> friend void read_data(const T_& t, std::vector< partition<typename T_::data_type> >& out, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& t, size_t dst_offset, const std::vector< partition<typename T_::data_type> >& src, size_t src_offset, size_t src_length);  
};

template <unsigned N> using ch_busbase = typebase<N, snode>;
using ch_signalbase = ch_busbase<1>;

}
