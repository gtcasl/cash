#pragma once

#include "../core.h"
#include "decoupled.h"
#include "counter.h"

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
    __out (ch_uint<size_width>) size
  );

  void describe() {
    ch_reg<ch_uint<size_width>> size(0);

    auto reading = io.deq.valid && io.deq.ready;
    auto writing = io.enq.ready && io.enq.valid;

    if constexpr (N == 1) {
      __if (writing && !reading) {
        size->next = 1;
      }__elif (reading && !writing) {
        size->next = 0;
      };

      io.deq.data  = ch_nextEn(io.enq.data, writing);
      io.deq.valid = size;
      io.enq.ready = !size || io.deq.ready;
      io.size      = size;
    } else {
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
      ch_mem<T, N, SyncRead> mem;
      mem.write(wr_ctr.value(), io.enq.data, writing);

      T data_out;
      if constexpr (SyncRead) {
        ch_counter<N> rd_ctr(reading);
        data_out = mem.read(rd_ctr.value());
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
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
struct ch_llqueue {
  using value_type = T;
  static constexpr uint32_t max_size   = N;
  static constexpr uint32_t size_width = log2ceil(N+1);

  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out (ch_uint<size_width>) size
  );

  void describe() {
    ch_reg<ch_uint<size_width>> size(0);

    auto reading = io.deq.valid && io.deq.ready;
    auto writing = io.enq.ready && io.enq.valid;

    if constexpr (N == 1) {
      __if (writing && !reading) {
        size->next = 1;
      }__elif (reading && !writing) {
        size->next = 0;
      };

      io.deq.data  = ch_nextEn(io.enq.data, writing);
      io.deq.valid = size;
      io.enq.ready = !size || io.deq.ready;
      io.size      = size;
    } else {
      ch_reg<ch_bit<N+1>> ptr(1);

      __if (writing && !reading) {
        ptr->next = ch_cat(ch_slice<N>(ptr, 0), 0_b);
        size->next = size + 1;
      }__elif (reading && !writing) {
        ptr->next = ch_cat(0_b, ch_slice<N>(ptr, 1));
        size->next = size - 1;
      };

      ch_bit<N> data_upd, data_new;
      for (unsigned i = 0; i < N; ++i) {
        data_upd[i] = reading | (writing & ptr[i]);
        data_new[i] = ~reading | ptr[i+1];
      }

      ch_vec<ch_reg<T>, N> data;
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

///////////////////////////////////////////////////////////////////////////////

template <typename T, unsigned N>
struct ch_pipequeue {
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
