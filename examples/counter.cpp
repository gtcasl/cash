#include <chdl.h>

using namespace chdl;
using namespace chdl::sim;

template <unsigned N>
void Counter(ch_bitv<N>& out) {
  out = ch_reg(out + 0x1);
}

int main(int argc, char **argv) {
  ch_bus<4> out;

  ch_device myDevice(Counter<4>);
  myDevice.bind(out);

  std::ofstream v_file("counter.v");
  myDevice.toVerilog("counter", v_file);
  v_file.close();

  ch_vcdtracer tracer("counter.vcd");
  __ch_trace(tracer, out);
  tracer.run();
  tracer.close();

  return 0;
}
