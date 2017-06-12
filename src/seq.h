#pragma once

#include "reg.h"

namespace cash {
namespace detail {

template <typename T>
class ch_seq : public T {
public:
  using value_type = T;
  using base = ch_bitbase<T::bit_count>;
  using data_type = typename T::data_type;
  using bus_type = typename T::bus_type;

  T next;

  ch_seq() {
    T::operator=(ch_reg(next));
  }
  
  ch_seq(const T& init) {
    T::operator=(ch_reg(next, init));
  }

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
