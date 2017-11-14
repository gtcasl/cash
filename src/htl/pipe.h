#pragma once

#include <cash.h>

namespace ch {
namespace htl {
 
template <typename T, unsigned Delay>
struct ch_pipe {
  using value_type = T;
  __io (
    (ch_flip_t<ch_valid_io<T>>) enq,
    (ch_valid_io<T>) deq
  );

  void describe() {
    T data(io.enq.data);
    ch_bool valid(io.enq.valid);
    for (unsigned i = 0; i < Delay; ++i) {
      auto c_data  = ch_clone(data);
      auto c_valid = ch_clone(valid);
      data  = ch_reg(ch_select(c_valid, c_data, data));
      valid = ch_reg(c_valid);
    }
    io.deq.data  = data;
    io.deq.valid = valid;
  }
};
  
}
}
