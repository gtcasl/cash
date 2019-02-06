#pragma once

#include <cash.h>
#include <htl/decoupled.h>
#include <htl/counter.h>

namespace ch {
namespace htl {

using namespace ch::logic;

template <typename T, unsigned N, bool SyncRead = false>
struct ch_queue {
  using value_type = T;
  static constexpr uint32_t max_size   = N;
  static constexpr uint32_t size_width = log2ceil(N+1);

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out(ch_uint<size_width>) size
  );

  void describe() {    
    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    ch_reg<ch_uint<size_width>> size(0);
    __if (writing && !reading) {
      size->next = size + 1;
    }__elif (reading && !writing) {
      size->next = size - 1;
    };

    ch_reg<ch_bool> empty(true);
    __if (size == 1 && reading && !writing) {
      empty->next = true;
    }__elif (writing && !reading) {
      empty->next = false;
    };

    ch_reg<ch_bool> full(false);
    __if (size == (N-1) && writing && !reading) {
      full->next = true;
    }__elif (reading && !writing) {
      full->next = false;
    };

    ch_counter<N> wr_ctr(writing);
    ch_mem<T, N> mem;
    mem.write(wr_ctr.value, io.enq.data, writing);

    T data_out;
    if constexpr (SyncRead) {
      ch_counter<N> rd_ctr(reading);
      data_out = mem.read(rd_ctr.value);
    } else {
      ch_uint<log2up(N)> rd_ptr, rd_next_ptr;
      if constexpr (N > 2) {
        rd_ptr = ch_nextEn(rd_next_ptr, reading, 0);
        if constexpr (ispow2(N)) {
          rd_next_ptr = ch_nextEn(rd_ptr + 2, reading, 1);
        } else {
          auto next = ch_sel(rd_ptr >= (N-2), rd_ptr - (N-2), rd_ptr + 2);
          rd_next_ptr = ch_nextEn(next, reading, 1);
        }
      } else
      if constexpr (N == 2) {
        rd_ptr = ch_nextEn(rd_next_ptr, reading, 0);
        rd_next_ptr = ch_nextEn(~rd_next_ptr, reading, 1);
      } else {
        rd_ptr = 0;
        rd_next_ptr = 0;
      }

      auto bypass = ch_delay(writing && (empty || (1 == size && reading)), 1, false);
      auto curr   = ch_delay(io.enq.data);
      auto head   = ch_delay(mem.read(ch_sel(reading, rd_next_ptr, rd_ptr)));
      data_out    = ch_sel(bypass, curr, head);
    }

    io.deq.data  = data_out;
    io.deq.valid = !empty;
    io.enq.ready = !full;
    io.size      = size;
  }
};

template <typename T, unsigned N>
struct ch_llqueue {
  using value_type = T;
  static constexpr uint32_t max_size   = N;
  static constexpr uint32_t size_width = log2ceil(N+1);

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out(ch_uint<size_width>) size
  );

  void describe() {
    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    if constexpr (N == 1) {      
      ch_reg<ch_uint1> size(0);

      __if (writing && !reading) {
        size->next = 1;
      }__elif (reading && !writing) {
        size->next = 0;
      };

      auto data = ch_nextEn(io.enq.data, writing);

      io.deq.data  = data;
      io.deq.valid = size;
      io.enq.ready = !size;
      io.size      = size;
    } else {
      ch_reg<ch_uint<size_width>> size(0);
      ch_reg<ch_bit<N+1>> ptr(1);

      __if (writing && !reading) {
        size->next = size + 1;
        ptr->next = ch_cat(ch_slice<N>(ptr, 0), 0_b);
      }__elif (reading && !writing) {
        size->next = size - 1;
        ptr->next = ch_cat(0_b, ch_slice<N>(ptr, 1));
      };

      ch_bit<N> data_upd, data_new;
      for (unsigned i = 0; i < N; ++i) {
        data_upd[i] = reading | (writing & ptr[i]);
        data_new[i] = (!reading) | ptr[i+1];
      }

      std::array<ch_reg<T>, N> data;
      for (unsigned i = 0; i < N-1; ++i) {
        data[i]->next = ch_sel(data_upd[i], ch_sel(data_new[i], io.enq.data, data[i+1]), data[i]);
      }
      data[N-1]->next = ch_sel(data_upd[N-1], io.enq.data, data[N-1]);

      io.deq.data  = data[0];
      io.deq.valid = !ptr[0];
      io.enq.ready = !ptr[N];
      io.size      = size;
    }
  }
};

}
}
