#include <iostream>
#include <fstream>
#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }

template <unsigned A, unsigned W>
__out(ch_bit<W>, ch_bit1, ch_bit1) FiFo(
      const ch_bit<W>& din,
      const ch_bit1& push,
      const ch_bit1& pop) {
  ch_ram<W, A> mem;
  ch_seq<ch_bit<A+1>> rd_ptr, wr_ptr;
  ch_bit1 empty, full;

  auto rd_A = ch_slice<A>(rd_ptr);
  auto wr_A = ch_slice<A>(wr_ptr);

  auto reading = pop && !empty;
  auto writing = push && !full;
  
  rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
  wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);
  
  empty = (wr_ptr == rd_ptr);
  full  = (wr_A == rd_A) && (wr_ptr[A] != rd_ptr[A]);
  
  ch_bit<W> dout = mem[rd_A];
  __if (writing) (
    mem[wr_A] = din;
  );
  
  __ret(dout, empty, full);
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("fifo.vcd");
  ch_bus2 din, dout;
  ch_bus1 push, pop, empty, full;

  auto fifo = ch_function(FiFo<1, 2>);
  std::tie(dout, empty, full) = fifo(din, push, pop);

  /*std::ofstream v_file("fifo.v");
  fifo.to_verilog("fifo", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, fifo);
  __trace(tracer, din, push, pop, dout, empty, full);
  tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": din=" << din << ", push=" << push << ", pop=" << pop << ", dout=" << dout << ", empty=" << empty << ", full=" << full << std::endl;
    switch (t) {
    case 0:
      CHECK(empty);
      CHECK(!full);
      din  = 1;
      push = 1;      
      break;      
    case 2:
      CHECK(!empty);
      CHECK(!full);
      CHECK(dout == 1);
      din  = 2;
      push = 1;
      break;
    case 4:
      CHECK(!empty);
      CHECK(full);
      CHECK(dout == 1);
      din  = 0;
      push = 0;
      break;
    case 6:
      CHECK(!empty);
      CHECK(full);
      CHECK(dout == 1);
      pop = 1;
      break;
    case 8:
      CHECK(!empty);
      CHECK(!full);
      CHECK(dout == 2);
      pop = 1;
      break;
    case 10:
      CHECK(empty);
      CHECK(!full);
      CHECK(dout == 1);
      pop = 0;
      break;
    }
    return (t <= 10);
  });

  return 0;
}
