#include <cash.h>

namespace ch {
namespace stl {

using namespace  ch::core;

template <typename T, unsigned A>
struct ch_fifo {
  __inout(link_t, (
    (ch_in<ch_bit1>)  ready,
    (ch_out<ch_bit1>) valid,
    (ch_out<T>)       data
  ));
  __io (
    (ch_flip_t<link_t>) enq,
    (link_t) deq
  );
  void describe() {
    ch_seq<ch_bit<A+1>> rd_ptr, wr_ptr;

    auto rd_A = ch_slice<A>(rd_ptr);
    auto wr_A = ch_slice<A>(wr_ptr);

    auto reading = io.deq.ready && io.deq.valid;
    auto writing = io.enq.ready && io.enq.valid;

    rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
    wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);

    ch_ram<T::bitwidth, A> mem;
    __if (writing) (
      mem[wr_A] = io.end.data;
    );

    io.deq.data  = mem[rd_A];
    io.deq.valid = (wr_ptr != rd_ptr);
    io.enq.ready = (wr_A != rd_A) || (wr_ptr[A] == rd_ptr[A]);
  }
};

}
}
