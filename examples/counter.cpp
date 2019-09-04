#include <cash.h>
#include "common.h"

using namespace ch::core;

template <unsigned N>
struct Counter {
  __io (
    __out (ch_uint<N>) out
  );

  void describe() {    
    ch_reg<ch_uint<N>> out(2);
    out->next = out + 1;
    io.out = out;
  }
};

int main() {
  ch_device<Counter<4>> counter;

  ch_tracer tracer(counter);
  tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": out="  << counter.io.out << std::endl;
    return (t != 2*10);
  }, 2);

  CHECK(counter.io.out == 12);

  ch_toVerilog("counter.v", counter);
  ch_toFIRRTL("counter.fir", counter);

  tracer.toText("counter.log");
  tracer.toVCD("counter.vcd");  
  tracer.toVerilog("counter_tb.v", "counter.v");
  int ret = !system("iverilog counter_tb.v -o counter_tb.iv")
          & !system("! vvp counter_tb.iv | grep 'ERROR' || false");
  return (0 == ret);
}
