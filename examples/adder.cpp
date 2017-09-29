#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }

template <unsigned N>
auto Adder = [](
    const ch_bit<N>& lhs,
    const ch_bit<N>& rhs,
    const ch_bit1& cin) {
  auto sum  = (0_b, lhs) + ch_zext<N+1>(rhs) + ch_zext<N+1>(cin);
  auto out  = ch_slice<N>(sum);
  auto cout = sum[N];
  __ret(out, cout);
};

int main(int argc, char **argv) {
  std::ofstream vcd_file("adder.vcd");
  ch_bus1 cout, cin(1);
  ch_bus2 out, lhs(1), rhs(3);
  
  auto adder = ch_function(Adder<2>);
  __tie(out, cout) = adder(lhs, rhs, cin);
  //auto adder = ch_call(Adder<2>)(lhs, rhs, cin, out, cout);
  //auto adder = __call(Adder<2>, lhs, rhs, cin, out, cout);


  std::ofstream v_file("adder.v");
  adder.to_verilog(v_file, "adder", "lhs", "rhs", "cin", "out", "cout");
  v_file.close();

  ch_vcdtracer tracer(vcd_file, adder);
  __trace(tracer, lhs, rhs, cin, out, cout);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << cout << std::endl;
  std::cout << "out = " << out << std::endl;

  CHECK(cout == 1 && out == 1);

  return 0;
}
