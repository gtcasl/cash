#include <iostream>
#include <fstream>
#include <chdl.h>

using namespace chdl;
using namespace chdl::sim;

template <unsigned N>
void Adder(ch_bitv<N>& out,
           ch_logic& cout,
           const ch_bitv<N>& lhs,
           const ch_bitv<N>& rhs,
           const ch_logic& cin) {
  ch_bitv<N+1> sum(('0', lhs) + rhs + cin);
  cout = sum[N];
  out  = ch_slice<N>(sum);
}

int main(int argc, char **argv) {
  ch_signal cout, cin('1');
  ch_bus<2> out, lhs(1), rhs(2);

  ch_device myDevice(Adder<2>);
  myDevice.bind(out, cout, lhs, rhs, cin);

  //std::ofstream v_file("adder.v");
  //myDevice.toVerilog("adder", v_file);
  //v_file.close();

  ch_vcdtracer tracer("adder.vcd");
  __ch_trace(tracer, out, cout, lhs, rhs, cin);
  tracer.run();
  tracer.close();

  return 0;
}
