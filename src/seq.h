#pragma once

#include "reg.h"

namespace cash {
namespace internal {

template <typename T>
class ch_seq : public T {
public:
  using value_type = T;
  using base = ch_bitbase<T::bitcount>;
  using data_type = typename T::data_type;
  using bus_type = typename T::bus_type;

  T next;

  ch_seq() {
    T::operator=(ch_reg(next));
    next = *this;
  }
  
  ch_seq(const T& init) {
    T::operator=(ch_reg(next, init));
    next = *this;
  }

protected:

  // disable assigment operator
  using T::operator=;
};

}
}
