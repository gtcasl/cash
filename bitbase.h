#pragma once

#include "node.h"
#include "typebase.h"

namespace chdl_internal {

template <unsigned N> class ch_bus;
template <unsigned N> class ch_bitv;

template <unsigned N>
ch_bitv<N> ch_lit(uint32_t value);

template <unsigned N>
ch_bitv<N> ch_lit(const std::initializer_list<uint32_t>& values);

template <unsigned N>
class typebase<N, ch_node> {
public: 
  static const unsigned bit_count = N;
  typedef ch_node   data_type;
  typedef typebase  logic_type;
  typedef ch_bus<N> bus_type;
  
  typebase() {}
  virtual ~typebase() {}

  template <unsigned M>
  const_slice_ref<M, typebase> slice(size_t index) const {
    return const_slice_ref<M, typebase>(*this, index);
  }
  
  template <unsigned M>
  slice_ref<M, typebase> slice(size_t index) {
    return slice_ref<M, typebase>(*this, index);
  }
  
  template <unsigned M>
  const_slice_ref<M, typebase> aslice(size_t index) const {
    return const_slice_ref<M, typebase>(*this, index * M);
  }
  
  template <unsigned M>
  slice_ref<M, typebase> aslice(size_t index) {
    return slice_ref<M, typebase>(*this, index * M);
  }
  
  const_subscript_ref<typebase> operator[](size_t index) const {
    return const_subscript_ref<typebase>(*this, index); 
  }
  
  subscript_ref<typebase> operator[](size_t index) {
    return subscript_ref<typebase>(*this, index); 
  }
  
  typebase& operator=(const typebase& rhs) {
    std::vector< partition<data_type> > data;
    rhs.read(data, 0, N);
    this->write(0, data, 0, N);
    return *this;
  }
  
  typebase& operator=(uint32_t value) {
    *this = ch_lit<N>(value);
    return *this;
  }
  
  typebase& operator=(const std::initializer_list<uint32_t>& values) {
    *this = ch_lit<N>(values);
    return *this;
  }
  
  virtual operator ch_node() const  = 0;
  
protected:
  
  template <typename T_> 
  friend void read_data(const T_& t, std::vector< partition<typename T_::data_type> >& out, size_t offset, size_t length);
  
  template <typename T_>
  friend void write_data(T_& t, size_t dst_offset, const std::vector< partition<typename T_::data_type> >& src, size_t src_offset, size_t src_length);
  
  virtual void read(std::vector< partition<data_type> >& out, size_t offset, size_t length) const = 0;
  virtual void write(size_t dst_offset, const std::vector< partition<data_type> >& src, size_t src_offset, size_t src_length) = 0;
};

template <unsigned N> using ch_bitbase = typebase<N, ch_node>;

}
