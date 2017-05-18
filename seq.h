#pragma once

#include "reg.h"

namespace cash {
namespace detail {

template <typename T>
class ch_seq : public T {
public:
  using value_type = T;
  using base = ch_bitbase<value_type::bit_count>;
  using data_type = typename value_type::data_type;
  using bus_type = typename value_type::bus_type;
  
  ch_seq() {
    T::operator =(ch_reg(next));
  }
  
  ch_seq(const value_type& init) {
    T::operator =(ch_reg(next, init));
  }
  
  value_type next;
  
  const_slice_ref<base, 1> operator[](size_t index) {
    return const_slice_ref<base, 1>(*this, index);
  }
  
  template <unsigned M> 
  const_slice_ref<base, M> slice(size_t index = 0) {
    return const_slice_ref<base, M>(*this, index);
  }
  
  template <unsigned M> 
  const_slice_ref<base, M> aslice(size_t index = 0) {
    return const_slice_ref<base, M>(*this, index * M);
  }
  
  template <unsigned M> 
  const_concat_ref<base, ch_bitbase<M>> concat(ch_bitbase<M>& rhs) {
    return const_concat_ref<base, ch_bitbase<M>>(*this, rhs);
  }
  
  template <unsigned M> 
  const_concat_ref<base, ch_bitbase<M>> concat(const bitref<M>& rhs) {
    return const_concat_ref<base, ch_bitbase<M>>(*this, rhs);
  }
  
protected:
  // disable assigment operator
  using T::operator=;    
};

}
}
