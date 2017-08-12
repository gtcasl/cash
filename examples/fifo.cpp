#include <iostream>
#include <fstream>
#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

template <unsigned ADDR, unsigned WIDTH>
__out(ch_bit<WIDTH>, ch_bit1, ch_bit1) FiFo(
  const ch_bit<WIDTH>& din,
  const ch_bit1& push,
  const ch_bit1& pop) {
  
  ch_bit<WIDTH> dout;
  ch_bit1 empty;
  ch_bit1 full;
  
  ch_ram<WIDTH, ADDR> mem;
  ch_seq<ch_bit<ADDR+1>> rd_ptr, wr_ptr;
  ch_bit<ADDR> rd_addr(ch_slice<ADDR>(rd_ptr));
  ch_bit<ADDR> wr_addr(ch_slice<ADDR>(wr_ptr));

  ch_bit1 reading(pop && !empty);
  ch_bit1 writing(push && !full);
  
  rd_ptr.next = ch_select(reading, rd_ptr + 1, rd_ptr);
  wr_ptr.next = ch_select(writing, wr_ptr + 1, wr_ptr);
  
  empty = (wr_ptr == rd_ptr);
  full  = (wr_addr == rd_addr) && (wr_ptr[ADDR] != rd_ptr[ADDR]);
  
  dout = mem[rd_addr];
  __if (writing) (
    mem[wr_addr] = din;
  );
  
  __ret(dout, empty, full);
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("fifo.vcd");
  ch_bus2 din, dout;
  ch_bus1 push, pop, empty, full;

  ch_device myDevice(FiFo<1, 2>, din, push, pop, dout, empty, full);

  /*std::ofstream v_file("fifo.v");
  myDevice.to_verilog("fifo", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, myDevice);
  __trace(tracer, din, push, pop, dout, empty, full);
  tracer.run([&](ch_cycle time)->bool {
    switch (time) {
    case 0:
      assert(empty);
      assert(!full);
      din  = 1;
      push = 1;      
      break;      
    case 1:
      assert(!empty);
      assert(!full);
      assert(dout == 1);      
      din  = 2;
      push = 1;
      break;
    case 2:
      assert(!empty);
      assert(full);
      assert(dout == 1);
      din  = 0;
      push = 0;
      break;
    case 3:
      assert(!empty);
      assert(full);
      assert(dout == 1);
      pop = 1;
      break;
    case 4:
      assert(!empty);
      assert(!full);
      assert(dout == 2);
      pop = 1;
      break;
    case 5:
      assert(empty);
      assert(!full);
      assert(dout == 1);
      pop = 0;
      break;
    }
    std::cout << "t" << time << ": din=" << din << ", push=" << push << ", pop=" << pop << ", dout=" << dout << ", empty=" << empty << ", full=" << full << std::endl;
    return (time < 6);
  });

  return 0;
}
