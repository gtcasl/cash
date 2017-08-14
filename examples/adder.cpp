#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

template <unsigned N>
__out(ch_bit<N>, ch_bit1) Adder(
           const ch_bit<N>& lhs,
           const ch_bit<N>& rhs,
           const ch_bit1& cin) {
  ch_bit<N> out;
  ch_bit1 cout;
  ch_bit<N+1> sum((0_b, lhs) + rhs + cin);
  cout = sum[N];
  out  = ch_slice<N>(sum);  

  auto x = std::make_tuple<ch_bit<N>, ch_bit1>(out, cout);

  auto y = std::tuple<ch_bit<N>, ch_bit1>(x);

  //__ret(out, cout);
  return x;
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("adder.vcd");
  ch_bus1 cout, cin(1);
  ch_bus2 out, lhs(1), rhs(3);
  
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
