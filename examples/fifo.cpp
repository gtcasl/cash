#include <cash.h>

using namespace ch::core;
using namespace ch::sim;

template <typename T, unsigned N>
struct FiFo {
  static constexpr unsigned addr_width = log2ceil(N);
  __io(
    __in(T)        din,
    __in(ch_bool)  push,
    __in(ch_bool)  pop,
    __out(T)       dout,
    __out(ch_bool) empty,
    __out(ch_bool) full
  );
  void describe() {
    ch_reg<ch_uint<addr_width+1>> rd_ptr(0), wr_ptr(0);

    auto rd_A = ch_slice<addr_width>(rd_ptr);
    auto wr_A = ch_slice<addr_width>(wr_ptr);

    auto reading = io.pop && !io.empty;
    auto writing = io.push && !io.full;

    rd_ptr->next = ch_sel(reading, rd_ptr + 1, rd_ptr);
    wr_ptr->next = ch_sel(writing, wr_ptr + 1, wr_ptr);

    ch_mem<T, N> mem;
    mem.write(wr_A, io.din, writing);

    io.dout  = mem.read(rd_A);
    io.empty = (wr_ptr == rd_ptr);
    io.full  = (wr_A == rd_A) && (wr_ptr[addr_width] != rd_ptr[addr_width]);    
  }
};

int main() {
  ch_device<FiFo<ch_bit<2>, 2>> fifo;

  ch_tracer tracer(fifo);
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
      assert(fifo.io.empty == true);
      assert(fifo.io.full == false);
      fifo.io.din = 1;
      fifo.io.push = 1;
      break;      
    case 2:
      assert(fifo.io.empty == false);
      assert(fifo.io.full == false);
      assert(fifo.io.dout == 1);
      fifo.io.din = 2;
      fifo.io.push = 1;
      break;
    case 4:
      assert(fifo.io.empty == false);
      assert(fifo.io.full == true);
      assert(fifo.io.dout == 1);
      fifo.io.din = 0;
      fifo.io.push = 0;
      break;
    case 6:
      assert(fifo.io.empty == false);
      assert(fifo.io.full == true);
      assert(fifo.io.dout == 1);
      fifo.io.pop = 1;
      break;
    case 8:
      assert(fifo.io.empty == false);
      assert(fifo.io.full == false);
      assert(fifo.io.dout == 2);
      fifo.io.pop = 1;
      break;
    case 10:
      assert(fifo.io.empty == true);
      assert(fifo.io.full == false);
      assert(fifo.io.dout == 1);
      fifo.io.pop = 0;
      break;
    }
    return (t <= 10);
  });

  tracer.toVCD("fifo.vcd");

  ch_toVerilog("fifo.v", fifo);
  ch_toFirrtl("fifo.fir", fifo);

  int ret = system("iverilog fifo_tb.v -o fifo_tb.iv")
          | system("vvp fifo_tb.iv");
  return ret != 0;
}
