#include <chdl.h>

using namespace chdl::core;
using namespace chdl::core_literals;
using namespace chdl::sim;

template <unsigned N>
__ch_out(ch_bit<N>, ch_logic) Adder(
           const ch_bit<N>& lhs,
           const ch_bit<N>& rhs,
           const ch_logic& cin) {
  ch_bit<N> out;
  ch_logic cout;
  ch_logic x(1_b);
  ch_bit<N+1> sum((0_b, lhs) + rhs + cin);
  cout = sum[N];
  out  = ch_slice<N>(sum);    
  __ch_ret(out, cout);
}

int main(int argc, char **argv) {
  ch_signal cout, cin(1);
  ch_bus<2> out, lhs(1), rhs(3);
  
  ch_device myDevice(Adder<2>, lhs, rhs, cin, out, cout);

  /*std::ofstream v_file("adder.v");
  myDevice.toVerilog("adder", v_file);
  v_file.close();*/

  ch_vcdtracer tracer("adder.vcd", myDevice);
  __ch_trace(tracer, lhs, rhs, cin, out, cout);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << cout << std::endl;
  std::cout << "out = " << out << std::endl;
  assert(cout == 1 && out == 1);

  return 0;
}
