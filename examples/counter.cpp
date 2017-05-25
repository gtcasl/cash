#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

template <unsigned N>
ch_bit<N> Counter() {
  ch_seq<ch_bit<N>> out;
  out.next = out + 1;
  return out;
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("counter.vcd");
  ch_bus<4> out;

  ch_device myDevice(Counter<4>, out);

  /*std::ofstream v_file("counter.v");
  myDevice.to_verilog("counter", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, myDevice);
  __trace(tracer, out);
  tracer.run(11);
  
  std::cout << "result:" << std::endl;
  std::cout << "out = " << out << std::endl;
  assert(out == 10);

  return 0;
}
