#pragma once

#include "snode.h"

namespace cash {
namespace internal {

template <unsigned N>
class ch_bus;

template <unsigned N> const ch_bus<N> make_bus(const snode& node);

template <typename T> const auto make_type(const snode& node) {
  T ret;
  write_data(ret, 0, {node, 0 , T::bitcount}, 0, T::bitcount);
  return ret;
}

template <unsigned N> using ch_busbase = typebase<N, snode>;

template <>
struct data_traits<snode> {
  template <unsigned N> using device_type = ch_bus<N>;
  template <typename T> using bus_type = T;
};

template <unsigned N>
class typebase<N, snode> : public typebase_itf<snode> {
public:  
  static constexpr unsigned bitcount = N;
  static_assert(N > 0, "invalid size");
  using base = typebase_itf<snode>;
  using data_type = snode;

  void read(uint32_t dst_offset, void* out, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) const {
    assert(src_offset + length <= N);
    assert(dst_offset + length <= sizeInBytes * 8);
    nodelist<data_type> data(length);
    this->read_data(data, src_offset, length);
    for (auto& slice : data) {
      slice.src.read(dst_offset, out, sizeInBytes, slice.offset, slice.length, slice.src.get_size());
      dst_offset += slice.length;
    }
  }

protected:

  void assign(const typebase& rhs) {
    nodelist<snode> data(N);
    cash::internal::read_data(rhs, data, 0, N);
    this->write_data(0, data, 0, N);
  }

  template <typename U,
            CH_REQUIRES(is_bit_scalar<U>::value)>
  void assign(U rhs) {
    snode node(bitvector(N, rhs));
    this->write_data(0, {node, 0 , N}, 0, N);
  }
};

}
}
