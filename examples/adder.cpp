#include <iostream>
#include <fstream>
#include <chdl.h>

using namespace chdl::core;
using namespace chdl::sim;

template <unsigned N>
__ch_out(ch_bitv<N>, ch_logic) Adder(
           const ch_bitv<N>& lhs,
           const ch_bitv<N>& rhs,
           const ch_logic& cin) {
  ch_bitv<N> out;
  ch_logic cout;
  ch_bitv<N+1> sum((0_b, lhs) + rhs + cin);
  cout = sum[N];
  out  = ch_slice<N>(sum);
  return __ch_ret(out, cout);
}

int main(int argc, char **argv) {
  ch_signal cout, cin(1_b);
  ch_bus<2> out, lhs(1), rhs(3);
  
  int a, b;
  
  std::tuple<int, int, int> x{a, a, b};

  ch_device myDevice(Adder<2>, lhs, rhs, cin, out, cout);

  /*std::ofstream v_file("adder.v");
  myDevice.toVerilog("adder", v_file);
  v_file.close();*/

  ch_vcdtracer tracer("adder.vcd");
  __ch_trace(tracer, lhs, rhs, cin, out, cout);
  tracer.run();
  tracer.close();

  return 0;
}
