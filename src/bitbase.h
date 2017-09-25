#pragma once

#include "lnode.h"

namespace cash {
namespace internal {

template <unsigned N> class ch_bit;

template <unsigned N> const ch_bit<N> make_bit(const lnode& node);

template <typename T> const auto make_type(const lnode& node) {
  typename T::value_type ret;
  write_data(ret, 0, {node, 0 , T::bitcount}, 0, T::bitcount);
  return ret;
};

template <unsigned N> using ch_bitbase = typebase<N, lnode>;

template <>
struct data_traits<lnode> {
  template <unsigned N> using device_type = ch_bit<N>;
  template <typename T> using bus_type = typename T::bus_type;
};

template <unsigned N>
class typebase<N, lnode> : public typebase_itf<lnode> {
public:
  static constexpr unsigned bitcount = N;
  static_assert(N > 0, "invalid size");
  using base = typebase_itf<lnode>;
  using data_type = lnode;

  const auto operator[](size_t index) const {
    return const_sliceref<refproxy<typebase>, 1>(*this, index);
  }

  template <unsigned M>
  const auto slice(size_t index = 0) const {
    return const_sliceref<refproxy<typebase>, M>(*this, index);
  }

  template <unsigned M>
  const auto aslice(size_t index = 0) const {
    return const_sliceref<refproxy<typebase>, M>(*this, index * M);
  }

protected:

  void assign(const typebase& rhs) {
    nodelist<lnode> data(N);
    cash::internal::read_data(rhs, data, 0, N);
    this->write_data(0, data, 0, N);
  }

  template <typename U,
            CH_REQUIRES(is_bit_scalar<U>::value)>
  void assign(U rhs) {
    lnode node(bitvector(N, rhs));
    this->write_data(0, {node, 0 , N}, 0, N);
  }
};

}
}
