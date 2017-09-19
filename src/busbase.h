#pragma once

#include "snode.h"

namespace cash {
namespace internal {

template <typename T, unsigned N>
class ch_busbase;

template <unsigned N>
class ch_bus;

template <unsigned N> const ch_bus<N> make_bus(const snode& node);

template <>
struct data_traits <snode> {
  template <typename T, unsigned N = T::bitcount> using base_t = ch_busbase<T, N>;

  template <typename T> static const T make_type(const snode& node) {
    return T(std::move(make_bus<T::bitcount>(node)));
  }
};

template <typename T, unsigned N = T::bitcount>
class ch_busbase : public typebase<T, snode, N, false> {
public:
  template <typename U>
  T& operator=(const ch_busbase<U>& rhs) {
    static_assert(U::bitcount == N, "size mismatch");
    return this->assign(rhs);
  }

  template <typename U,
            CH_REQUIRES(is_scalar<U>::value)>
  T& operator=(U rhs) { \
    return this->assign(rhs);
  }

  /*void read(uint32_t dst_offset, void* out, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) const {
    assert(src_offset + length <= N);
    assert(dst_offset + length <= sizeInBytes * 8);
    data_t data(length);
    this->read_data(data, src_offset, length);
    for (auto& slice : data) {
      slice.src.read(dst_offset, out, sizeInBytes, slice.offset, slice.length, slice.src.get_size());
      dst_offset += slice.length;
    }
  }

  void write(uint32_t dst_offset, const void* in, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) {
    assert(dst_offset + length <= N);
    assert(src_offset + length <= sizeInBytes * 8);
    data_t data(length);
    this->read_data(data, dst_offset, length);
    for (auto& slice : data) {
      const_cast<snode&>(slice.src).write(slice.offset, in, sizeInBytes, src_offset, slice.length, slice.src.get_size());
      src_offset += slice.length;
    }
  }*/
};

}
}
