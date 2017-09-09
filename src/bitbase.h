#pragma once

#include "lnode.h"

namespace cash {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N> const ch_bit<N> make_bit(const lnode& node);

template <unsigned N> using ch_bitbase = typebase<N, lnode::data_type>;

template <unsigned N>
class typebase<N, lnode::data_type> : public typebase_itf<lnode::data_type> {
public:   
  static const unsigned bitcount = N;
  using data_type = lnode::data_type;
  
  const auto operator[](size_t index) const {
    lnode::data_type data(1);
    this->read_data(data, index, 1);
    return make_bit<1>(lnode(data));
  }

  auto operator[](size_t index) {
    return sliceref<typebase, 1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    lnode::data_type data(M);
    this->read_data(data, index, M);
    return make_bit<M>(lnode(data));
  }

  template <unsigned M>
  auto slice(size_t index = 0) {
    return sliceref<typebase, M>(*this, index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    lnode::data_type data(M);
    this->read_data(data, index * M, M);
    return make_bit<M>(lnode(data));
  }

  template <unsigned M>
  auto aslice(size_t index = 0) {
    return sliceref<typebase, M>(*this, index * M);
  }
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }

#define CH_DEF_AOP(type) \
  typebase& operator=(type rhs) { \
    const lnode node(bitvector(N, rhs)); \
    this->write_data(0, {N, node, 0 , N}, 0, N); \
    return *this; \
  }
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

}
}
