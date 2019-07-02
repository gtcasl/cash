#pragma once

#include <cash.h>

namespace ch {
namespace htl {

template <typename T, unsigned N>
struct ch_pipe {
  using value_type = T;
  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq
  );

  struct state_t {
    T       data;
    ch_bool valid;
    ch_bool ready;
  };

  void describe() {
    state_t states[N+1];
    ch_reg<ch_bit<N>> r_valid(false);
    ch_reg<T> r_data[N];

    states[0].data  = io.enq.data;
    states[0].valid = io.enq.valid;
    states[N].ready = io.deq.ready;

    for (unsigned i = N; i >= 1; --i) {
      states[i].data  = r_data[i - 1];
      states[i].valid = r_valid[i - 1];
      states[i - 1].ready = ~states[i].valid | states[i].ready;
    }

    for (unsigned i = 0; i < N; ++i) {
      __if (states[i].ready) {
        r_valid->next[i] = states[i].valid;
        __if (states[i].valid) {
          r_data[i]->next = states[i].data;
        };
      };
    }

    io.deq.data  = states[N].data;
    io.deq.valid = states[N].valid;
    io.enq.ready = states[0].ready;
  }
};
  
}
}
