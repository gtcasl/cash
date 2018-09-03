#pragma once

#include <cash.h>
#include <htl/decoupled.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T, unsigned N, bool SyncRead = false, bool ShowAhead = true>
struct ch_queue {
  using value_type = T;
  static constexpr uint32_t max_size   = N;
  static constexpr uint32_t size_width = log2ceil(N+1);
  static_assert(N > 1, "invalid size");

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out(ch_uint<size_width>) size
  );

  void describe() {    
    static constexpr uint32_t addr_width = log2ceil(N);
    ch_reg<ch_uint<addr_width>> rd_ptr(0), wr_ptr(0);
    ch_reg<ch_uint<size_width>> counter(0);
    ch_reg<ch_bool> full(false), empty(true);

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    rd_ptr->next = ch_sel(reading, rd_ptr + 1, rd_ptr);
    wr_ptr->next = ch_sel(writing, wr_ptr + 1, wr_ptr);

    __if (writing && !reading) {
      counter->next = counter + 1;
    }__elif (reading && !writing) {
      counter->next = counter - 1;
    };

    ch_mem<T, N, SyncRead && !ShowAhead> mem;
    mem.write(wr_ptr, io.enq.data, writing);

    T data_out;
    if constexpr (SyncRead && ShowAhead) {
      ch_reg<T> r_data_out;
      __if (writing && (empty || (1 == counter && reading))) {
        r_data_out->next = io.enq.data;
      }__elif (reading) {
        r_data_out->next = mem.read(rd_ptr + 1);
      }__else {
        r_data_out->next = mem.read(rd_ptr);
      };
      data_out = r_data_out;
    } else {
      data_out = mem.read(rd_ptr);
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
