#pragma once

#include "lnode.h"

namespace cash {
namespace detail {

template <unsigned N> class ch_bit;

template <unsigned N> using const_bitref = const_typeref<N, lnode::data_type>;
template <unsigned N> using bitref = typeref<N, lnode::data_type>;
template <unsigned N> using ch_bitbase = typebase<N, lnode::data_type>;

template <unsigned N>
class typebase<N, lnode::data_type> : public typebase_itf<lnode::data_type> {
public:   
  static const unsigned bit_count = N;
  using data_type = lnode::data_type;
  
  const_sliceref<typebase, 1> operator[](size_t index) const {
    static_assert(N > 1, "invalid call");
    return const_sliceref<typebase, 1>(*this, index);
  }

  sliceref<typebase, 1> operator[](size_t index) {
    static_assert(N > 1, "invalid call");
    return sliceref<typebase, 1>(*this, index);
  }

  template <unsigned M>
  const_sliceref<typebase, M> slice(size_t index = 0) const {
    static_assert(N > 1, "invalid call");
    return const_sliceref<typebase, M>(*this, index);
  }

  template <unsigned M>
  sliceref<typebase, M> slice(size_t index = 0) {
    static_assert(N > 1, "invalid call");
    return sliceref<typebase, M>(*this, index);
  }

  template <unsigned M>
  const_sliceref<typebase, M> aslice(size_t index = 0) const {
    static_assert(N > 1, "invalid call");
    return const_sliceref<typebase, M>(*this, index * M);
  }

  template <unsigned M>
  sliceref<typebase, M> aslice(size_t index = 0) {
    static_assert(N > 1, "invalid call");
    return sliceref<typebase, M>(*this, index * M);
  }

  template <unsigned M>
  const_concatref<typebase, ch_bitbase<M>> concat(const ch_bitbase<M>& rhs) const {
    return const_concatref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  const_concatref<typebase, ch_bitbase<M>> concat(const ch_bitbase<M>& rhs) {
    return const_concatref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  concatref<typebase, ch_bitbase<M>> concat(ch_bitbase<M>& rhs) {
    return concatref<typebase, ch_bitbase<M>>(*this, rhs);
  }

  template <unsigned M>
  concatref<typebase, ch_bitbase<M>> concat(const bitref<M>& rhs) {
    return concatref<typebase, ch_bitbase<M>>(*this, rhs);
  }
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }
 
#define CH_DEF_AOP(type) \
  typebase& operator=(type rhs) { \
    ch_bit<N> b(rhs); \
    data_type data(N, true); \
    detail::read_data(b, data, 0, N); \
    this->write_data(0, data, 0, N); \
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
};

template <unsigned N>
lnode get_node(const ch_bitbase<N>& b) {
  lnode::data_type data(N, true);
  b.read_data(data, 0, N);
  return lnode(data);
}


}
}
