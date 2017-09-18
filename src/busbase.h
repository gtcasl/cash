#pragma once

#include "snode.h"

namespace cash {
namespace internal {

template <typename Derived>
class ch_busbase;

template <unsigned N>
class ch_bus;

template <unsigned N> const ch_bus<N> make_bus(const snode& node);

template <>
struct data_traits <snode> {
  template <typename T> using base_type = ch_busbase<T>;

  template <typename T> static const T make_type(const snode& node) {
    return T(std::move(make_bus<traits<T>::bitcount>(node)));
  }
};

template <typename Derived>
struct traits < ch_busbase<Derived> > {
  static constexpr unsigned bitcount = traits<Derived>::bitcount;
};

template <typename Derived>
class ch_busbase : public typebase<Derived> {
public:
  static_assert(std::is_same<typename traits<Derived>::data_type, snode>::value, "data type mismatch");

  template <typename OtherDerived,
            CH_REQUIRES(traits<OtherDerived>::bitcount == traits<Derived>::bitcount),
            CH_REQUIRES(!traits<Derived>::readonly)>
  Derived& operator=(const ch_busbase<OtherDerived>& rhs) {
    return this->assign(rhs);
  }

  template <typename T,
            CH_REQUIRES(is_scalar<T>::value),
            CH_REQUIRES(!traits<Derived>::readonly)>
  Derived& operator=(const T& rhs) { \
    return this->assign(rhs);
  }

  /*void read(uint32_t dst_offset, void* out, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) const {
    assert(src_offset + length <= N);
    assert(dst_offset + length <= sizeInBytes * 8);
    data_type data(length);
    this->read_data(data, src_offset, length);
    for (auto& slice : data) {
      slice.src.read(dst_offset, out, sizeInBytes, slice.offset, slice.length, slice.src.get_size());
      dst_offset += slice.length;
    }
  }

  void write(uint32_t dst_offset, const void* in, uint32_t sizeInBytes, uint32_t src_offset = 0, uint32_t length = N) {
    assert(dst_offset + length <= N);
    assert(src_offset + length <= sizeInBytes * 8);
    data_type data(length);
    this->read_data(data, dst_offset, length);
    for (auto& slice : data) {
      const_cast<snode&>(slice.src).write(slice.offset, in, sizeInBytes, src_offset, slice.length, slice.src.get_size());
      src_offset += slice.length;
    }
  }*/
};

}
}
