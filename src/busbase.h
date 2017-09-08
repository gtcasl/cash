#pragma once

#include "snode.h"

namespace cash {
namespace internal {

template <unsigned N> using ch_busbase = typebase<N, snode::data_type>;

template <unsigned N>
class typebase<N, snode::data_type> : public typebase_itf<snode::data_type> {
public:   
  static const unsigned bitcount = N;
  using data_type = snode::data_type;
  
  typebase& operator=(const typebase& rhs) {
    data_type data(N);
    rhs.read_data(data, 0, N);
    this->write_data(0, data, 0, N);
    return *this;
  }

  typebase& operator=(const ch_literal<N>& rhs) {
    const snode node(rhs);
    this->write_data(0, {N, node.get_impl(), 0 , N}, 0, N);
    return *this;
  }
  
#define CH_DEF_AOP(type) \
  typebase& operator=(type rhs) { \
    snode node(bitvector(N, rhs)); \
    this->write_data(0, {N, node.get_impl(), 0 , N}, 0, N); \
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

  void read(uint32_t dst_offset, void* out, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) const {
    assert(src_offset + length <= N);
    assert(dst_offset + length <= sizeInBytes * 8);
    data_type data(length);
    this->read_data(data, src_offset, length);
    for (auto& slice : data) {
      snode node(slice.src);
      node.read(dst_offset, out, sizeInBytes, slice.offset, slice.length, node.get_size());
      dst_offset += slice.length;
    }
  }

  void write(uint32_t dst_offset, const void* in, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) {
    assert(dst_offset + length <= N);
    assert(src_offset + length <= sizeInBytes * 8);
    data_type data(length);
    this->read_data(data, dst_offset, length);
    for (auto& slice : data) {
      snode node(slice.src);
      node.write(slice.offset, in, sizeInBytes, src_offset, slice.length, node.get_size());
      src_offset += slice.length;
    }
  }
};

}
}
