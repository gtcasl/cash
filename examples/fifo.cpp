#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

#define CHECK(x, v) if (ch_peek<decltype(v)>(x) != v) { assert(false); exit(1); }

template <unsigned A, unsigned W>
struct FiFo {
  __io(
    (ch_in<ch_bit<W>>)  din,
    (ch_in<ch_bit1>)    push,
    (ch_in<ch_bit1>)    pop,
    (ch_out<ch_bit<W>>) dout,
    (ch_out<ch_bit1>)   empty,
    (ch_out<ch_bit1>)   full
  );
  void describe() {
    ch_seq<ch_bit<A+1>> rd_ptr, wr_ptr;

    auto rd_A = ch_slice<A>(rd_ptr);
    auto wr_A = ch_slice<A>(wr_ptr);

    auto reading = io.pop && !io.empty;
    auto writing = io.push && !io.full;

    rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
    wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);

    ch_ram<W, A> mem;
    __if (writing) (
      mem[wr_A] = io.din;
    );

    io.dout  = mem[rd_A];
    io.empty = (wr_ptr == rd_ptr);
    io.full  = (wr_A == rd_A) && (wr_ptr[A] != rd_ptr[A]);
  }
};

int main(int argc, char **argv) {
  ch_module<FiFo<1, 2>> fifo("FiFo");

  ch_vcdtracer tracer("fifo.vcd", fifo);
  tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t
              << ": din=" << fifo.io.din
              << ", push=" << fifo.io.push
              << ", pop=" << fifo.io.pop
              << ", dout=" << fifo.io.dout
              << ", empty=" << fifo.io.empty
              << ", full=" << fifo.io.full << std::endl;
    switch (t) {
    case 0:
      CHECK(fifo.io.empty, true);
      CHECK(fifo.io.full, false);
      ch_poke(fifo.io.din, 1);
      ch_poke(fifo.io.push, 1);
      break;      
    case 2:
      CHECK(fifo.io.empty, false);
      CHECK(fifo.io.full, false);
      CHECK(fifo.io.dout, 1);
      ch_poke(fifo.io.din, 2);
      ch_poke(fifo.io.push, 1);
      break;
    case 4:
      CHECK(fifo.io.empty, false);
      CHECK(fifo.io.full, true);
      CHECK(fifo.io.dout, 1);
      ch_poke(fifo.io.din, 0);
      ch_poke(fifo.io.push, 0);
      break;
    case 6:
      CHECK(fifo.io.empty, false);
      CHECK(fifo.io.full, true);
      CHECK(fifo.io.dout, 1);
      ch_poke(fifo.io.pop, 1);
      break;
    case 8:
      CHECK(fifo.io.empty, false);
      CHECK(fifo.io.full, false);
      CHECK(fifo.io.dout, 2);
      ch_poke(fifo.io.pop, 1);
      break;
    case 10:
      CHECK(fifo.io.empty, true);
      CHECK(fifo.io.full, false);
      CHECK(fifo.io.dout, 1);
      ch_poke(fifo.io.pop, 0);
      break;
    }
    return (t <= 10);
  });

  ch_toVerilog("fifo.v", fifo);

  return 0;
}
