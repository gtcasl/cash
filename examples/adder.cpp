#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }

template <unsigned N>
__out(ch_bit<N>, ch_bit1) Adder(
    const ch_bit<N>& lhs,
    const ch_bit<N>& rhs,
    const ch_bit1& cin) {
  auto sum = (0_b, lhs) + ch_zext<N+1>(rhs) + ch_zext<N+1>(cin);
  ch_bit<N> out = sum.template slice<N>();
  ch_bit1 cout = sum[N];
  __ret(out, cout);
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

  CHECK(cout == 1 && out == 1);

  return 0;
}
