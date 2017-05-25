#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

template <unsigned N>
__out(ch_bit<N>, ch_logic) Adder(
           const ch_bit<N>& lhs,
           const ch_bit<N>& rhs,
           const ch_logic& cin) {
  ch_bit<N> out;
  ch_logic cout;
  ch_logic x(1_b);
  ch_bit<N+1> sum((0_b, lhs) + rhs + cin);
  cout = sum[N];
  out  = ch_slice<N>(sum);  
  __ret(out, cout);
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("adder.vcd");
  ch_signal cout, cin(1);
  ch_bus<2> out, lhs(1), rhs(3);
  
  ch_device myDevice(Adder<2>, lhs, rhs, cin, out, cout);

  /*std::ofstream v_file("adder.v");
  myDevice.to_verilog("adder", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, myDevice);
  __trace(tracer, lhs, rhs, cin, out, cout);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << cout << std::endl;
  std::cout << "out = " << out << std::endl;
  assert(cout == 1 && out == 1);

  return 0;
}
