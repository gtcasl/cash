#include <cash.h>

using namespace ch::core;
using namespace ch::sim;

template <unsigned N>
struct Counter {
  __io (
    __out(ch_uint<N>) out
  );

  void describe() {    
    ch_reg<ch_uint<N>> out(2);
    out <<= out + 1;
    io.out = out;
    //ch_print("{0}: clk={1}, rst={2}, out={3}", ch_time(), ch_clock(), ch_reset(), out);
  }
};

int main() {
  ch_device<Counter<4>> counter;

  ch_vcdtracer tracer("counter.vcd", counter);
  tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": out="  << counter.io.out << std::endl;
    return (t != 2*10);
  });

  assert(counter.io.out == 12);

  ch_toVerilog("counter.v", counter);
  ch_toFIRRTL("counter.fir", counter);

  int ret = system("iverilog counter_tb.v -o counter_tb.iv")
          | system("vvp counter_tb.iv");
  return ret != 0;
}
