#pragma once

#include "reg.h"

namespace chdl_internal {

template <typename T>
class ch_seq : public T {
public:
  using base = T;
  using bitstream_type = typename base::bitstream_type;
  using bus_type = typename base::bus_type;
  
  ch_seq() {
    T::operator =(ch_reg(next));
  }
  
  ch_seq(const base& init) {
    T::operator =(ch_reg(next, init));
  }
  
  base next;
};

}
