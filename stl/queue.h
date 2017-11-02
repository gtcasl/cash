#include <cash.h>

namespace ch {
namespace stl {

using namespace ch::core;

template <typename T, unsigned N>
struct ch_queue {
  using value_type = T;
  static constexpr unsigned max_size = N;
  static constexpr unsigned addr_width = log2ceil(N);

  __io (
    (ch_deqIO<T>) enq,
    (ch_enqIO<T>) deq,
    __out(ch_bit<addr_width+1>) size
  );

  void describe() {
    ch_seq<ch_bit<addr_width+1>> rd_ptr, wr_ptr;

    auto rd_A = ch_slice<addr_width>(rd_ptr);
    auto wr_A = ch_slice<addr_width>(wr_ptr);

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.valid && io.enq.ready;

    rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
    wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);

    ch_ram<T, N> mem;
    __if (writing) (
      mem[wr_A] = io.enq.data;
    );

    io.deq.data  = mem[rd_A];
    io.deq.valid = (wr_ptr != rd_ptr);
    io.enq.ready = (wr_A != rd_A) || (wr_ptr[addr_width] == rd_ptr[addr_width]);
    io.size      = (wr_ptr - rd_ptr);
  }
};

}
}