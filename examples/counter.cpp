#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

#define CHECK(x, v) if (ch_peek<decltype(v)>(x) != v) { assert(false); exit(1); }

template <unsigned N>
struct Counter {
  __io (
    (ch_out<ch_bit<N>>) out
  );
  void describe() {
    ch_seq<ch_bit<N>> out;
    out.next = out + 1;
    io.out = out;
  }
};

int main(int argc, char **argv) {
  ch_module<Counter<4>> counter("Counter");

  ch_vcdtracer tracer("counter.vcd", counter);
  tracer.run(22);

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << counter.io.out << std::endl;

  CHECK(counter.io.out, 10);

  ch_toVerilog("counter.v", counter);

  return 0;
}
