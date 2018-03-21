#pragma once

#include <cash.h>

namespace ch {
namespace htl {
 
template <typename T, unsigned Delay>
struct ch_pipe {
  using value_type = T;
  __io (
    (ch_deq_io<T>) enq,
    (ch_enq_io<T>) deq
  );

  void describe() {
    T data(io.enq.data);
    ch_bool valid(io.enq.valid);
    for (unsigned i = 0; i < Delay; ++i) {
      T new_data;
      ch_bool new_valid;
      new_data  = ch_regNext(ch_select(io.deq.ready, ch_clone(data), new_data));
      new_valid = ch_regNext(ch_select(io.deq.ready, ch_clone(valid), new_valid));
      data  = new_data;
      valid = new_valid;
    }
    io.enq.ready = io.deq.ready;
    io.deq.data  = data;
    io.deq.valid = valid;
  }
};
  
}
}
