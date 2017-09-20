#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }

template <unsigned N>
auto Counter = []() {
  ch_seq<ch_bit<N>> out;
  out.next = out + 1;
  __ret(out);
};

int main(int argc, char **argv) {
  std::ofstream vcd_file("counter.vcd");
  ch_bus4 out;

  auto counter = ch_function(Counter<4>);
  out = counter();

  //std::ofstream v_file("counter.v");
  //counter.to_verilog("counter", v_file);
  //v_file.close();

  ch_vcdtracer tracer(vcd_file, counter);
  __trace(tracer, out);
  tracer.run(22);

  std::cout << "result:" << std::endl;
  std::cout << "out = " << out << std::endl;

  CHECK(out == 10);

  return 0;
}
