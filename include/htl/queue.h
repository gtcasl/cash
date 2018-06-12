#pragma once

#include <cash.h>
#include <htl/decoupled.h>

namespace ch {
namespace htl {

using namespace ch::core;

template <typename T, unsigned N>
struct ch_queue {
  using value_type = T;
  static constexpr uint32_t max_size = N;
  static constexpr uint32_t addr_width = log2ceil(N);
  static_assert(N > 1, "invalid size");

  __io (
    (ch_deq_io<T>) enq,
    (ch_enq_io<T>) deq,
    __out(ch_uint<addr_width+1>) size
  );

  void describe() {
    ch_reg<ch_uint<addr_width+1>> rd_ptr, wr_ptr;

    auto rd_A = ch_slice<addr_width>(rd_ptr);
    auto wr_A = ch_slice<addr_width>(wr_ptr);

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    rd_ptr <<= ch_sel(reading, rd_ptr + 1, rd_ptr);
    wr_ptr <<= ch_sel(writing, wr_ptr + 1, wr_ptr);

    ch_mem<T, N> mem;
    mem.write(wr_A, io.enq.data, writing);

    io.deq.data  = mem.read(rd_A);
    io.deq.valid = (wr_ptr != rd_ptr);
    io.enq.ready = (wr_A != rd_A) || (wr_ptr[addr_width] == rd_ptr[addr_width]);
    io.size      = (wr_ptr - rd_ptr);
  }
};

}
}
