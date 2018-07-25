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
  });

  assert(counter.io.out == 12);

  tracer.toText("counter.log");
  tracer.toVCD("counter.vcd");

  ch_toVerilog("counter.v", counter);
  ch_toFirrtl("counter.fir", counter);

  int ret = system("iverilog counter_tb.v -o counter_tb.iv")
          | system("vvp counter_tb.iv");
  return ret != 0;
}
