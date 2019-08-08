#pragma once

#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>

namespace ch {
namespace htl {

template <typename T, unsigned N>
struct ch_pipe {
  using value_type = T;
  static constexpr uint32_t max_size   = N;
  static constexpr uint32_t size_width = log2ceil(N+1);

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out (ch_uint<size_width>) size
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

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    ch_reg<ch_uint<size_width>> size(0);
    __if (writing && !reading) {
      size->next = size + 1;
    }__elif (reading && !writing) {
      size->next = size - 1;
    };

    for (unsigned i = N; i >= 1; --i) {
      states[i].data  = r_data[i - 1];
      states[i].valid = r_valid[i - 1];
      states[i - 1].ready = states[i].ready | ~states[i].valid;
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
    io.size      = size;
  }
};
  
}
}
