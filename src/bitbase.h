#pragma once

#include "lnode.h"

namespace cash {
namespace detail {

template <unsigned N> class ch_bit;

template <unsigned N> using const_bitref = const_typeref<N, lnode::data_type>;
template <unsigned N> using bitref = typeref<N, lnode::data_type>;
template <unsigned N> using ch_bitbase = typebase<N, lnode::data_type>;

template <unsigned N>
class typebase<N, lnode::data_type> {
public:   
  static const unsigned bit_count = N;
  using data_type = lnode::data_type;
  
  const_slice_ref<typebase, 1> operator[](size_t index) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, 1>(*this, index);
  }

  slice_ref<typebase, 1> operator[](size_t index) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, 1>(*this, index);
  }

  template <unsigned M>
  const_slice_ref<typebase, M> slice(size_t index = 0) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, M>(*this, index);
  }

  template <unsigned M>
  slice_ref<typebase, M> slice(size_t index = 0) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, M>(*this, index);
  }

  template <unsigned M>
  const_slice_ref<typebase, M> aslice(size_t index = 0) const {
    static_assert(N > 1, "invalid call");
    return const_slice_ref<typebase, M>(*this, index * M);
  }

  template <unsigned M>
  slice_ref<typebase, M> aslice(size_t index = 0) {
    static_assert(N > 1, "invalid call");
    return slice_ref<typebase, M>(*this, index * M);
  }

  template <unsigned M>
  const_concat_ref<typebase, ch_bitbase<M>> concat(const ch_bitbase<M>& rhs) const {
    return const_concat_ref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  const_concat_ref<typebase, ch_bitbase<M>> concat(const ch_bitbase<M>& rhs) {
    return const_concat_ref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  concat_ref<typebase, ch_bitbase<M>> concat(ch_bitbase<M>& rhs) {
    return concat_ref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  concat_ref<typebase, ch_bitbase<M>> concat(const bitref<M>& rhs) {
    return concat_ref<typebase, ch_bitbase<M>>(*this, rhs);
  }
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
  
  typebase& operator=(bool value) {
    static_assert(N == 1, "bool assignents only allowed on single-bit objects");
    return this->operator =(ch_bit<N>(value ? 0x1 : 0x0));
  } 
 
#define CH_DEF_AOP(type) \
  typebase& operator=(type value) { \
    return this->operator =(ch_bit<N>(value)); \
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

protected:
  
  virtual void read_data(data_type& inout, size_t offset, size_t length) const = 0;
  virtual void write_data(size_t dst_offset, const data_type& in, size_t src_offset, size_t src_length) = 0;
  
  template <unsigned N_> friend lnode get_node(const ch_bitbase<N_>& b);
  template <typename T_> friend void read_data(const T_& b, typename T_::data_type& inout, size_t offset, size_t length);
  template <typename T_> friend void write_data(T_& b, size_t dst_offset, const typename T_::data_type& in, size_t src_offset, size_t src_length);
};

template <unsigned N>
lnode get_node(const ch_bitbase<N>& b) {
  lnode::data_type data(N);
  b.read_data(data, 0, N);
  return lnode(data);
}


}
}
