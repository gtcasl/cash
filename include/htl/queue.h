#pragma once

#include <cash.h>
#include <htl/decoupled.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename T, unsigned N, bool SyncRead = false>
struct ch_queue {
  using value_type = T;
  static constexpr uint32_t max_size = N;
  static constexpr uint32_t addr_width = log2ceil(N);
  static constexpr uint32_t size_width = log2ceil(N+1);
  static_assert(N > 1, "invalid size");

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out(ch_uint<size_width>) size
  );

  void describe() {
    ch_reg<ch_uint<addr_width>> rd_ptr(0), wr_ptr(0);
    ch_reg<ch_uint<size_width>> counter(0);
    ch_reg<ch_bool> full(false), empty(true);
    ch_mem<T, N> mem;

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    rd_ptr->next = ch_sel(reading, rd_ptr + 1, rd_ptr);
    wr_ptr->next = ch_sel(writing, wr_ptr + 1, wr_ptr);

    __if (writing && !reading) {
      counter->next = counter + 1;
    }__elif (reading && !writing) {
      counter->next = counter - 1;
    };

    auto rd_a = ch_slice<addr_width>(rd_ptr);
    auto wr_a = ch_slice<addr_width>(wr_ptr);
    mem.write(wr_a, io.enq.data, writing);

    T data_out;

    if constexpr (SyncRead) {
      ch_reg<T> r_data_out;
      auto wr_bypass = writing && (0 == counter || (1 == counter && reading));
      auto addr = ch_slice<addr_width>(ch_sel(reading, rd_ptr + 1, rd_ptr));
      data_out = ch_delay(ch_sel(wr_bypass, io.enq.data, mem.read(addr)));
    } else {
      data_out = mem.read(rd_a);
    }

    __if (counter == (N-1) && writing && !reading) {
      full->next = true;
    }__elif (reading && !writing) {
      full->next = false;
    };

    __if (counter == 1 && reading && !writing) {
      empty->next = true;
    }__elif (writing && !reading) {
      empty->next = false;
    };

    io.deq.data  = data_out;
    io.deq.valid = !empty;
    io.enq.ready = !full;
    io.size      = counter;
  }
};


}
}
