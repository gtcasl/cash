#include <chdl.h>

using namespace chdl::core;
using namespace chdl::core_literals;
using namespace chdl::sim;

template <unsigned N>
ch_bitv<N> Counter() {
  ch_bitv<N> out;
  out = ch_reg(out + 1);
  return out;
}

int main(int argc, char **argv) {
  ch_bus<4> out;

  ch_device myDevice(Counter<4>, out);

  /*std::ofstream v_file("counter.v");
  myDevice.toVerilog("counter", v_file);
  v_file.close();*/

  ch_vcdtracer tracer("counter.vcd", myDevice);
  __ch_trace(tracer, out);
  tracer.run();

  return 0;
}
