#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

template <unsigned N>
struct Counter {
  __io (
    __out(ch_bit<N>) out
  );

  void describe() {
    ch_reg<ch_bit<N>> out(0);
    out.next = out + 1;
    io.out = out;
  }
};

int main() {
  ch_device<Counter<4>> counter;

  ch_vcdtracer tracer("counter.vcd", counter);
  tracer.run(2*(1+10));

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << counter.io.out << std::endl;

  assert(counter.io.out == 10);

  ch_toVerilog("counter.v", counter);
  ch_toFIRRTL("counter.fir", counter);

  return 0;
}
