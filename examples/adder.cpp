#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

template <unsigned N>
struct Adder {
  __io (
    __in(ch_bit1)    cin,
    __in(ch_bit<N>)  lhs,
    __in(ch_bit<N>)  rhs,
    __out(ch_bit<N>) out,
    __out(ch_bit1)   cout
  );

  void describe() {
    auto sum = ch_zext<N+1>(io.cin) + io.lhs + io.rhs;
    io.out  = ch_slice<N>(sum);
    io.cout = sum[N];
  }
};

int main() {
  ch_device<Adder<2>> adder;

  adder.io.cin = 1;
  adder.io.lhs = 1;
  adder.io.rhs = 3;

  ch_vcdtracer tracer("adder.vcd", adder);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << adder.io.cout << std::endl;
  std::cout << "out = "  << adder.io.out << std::endl;

  assert(adder.io.out == 1);
  assert(adder.io.cout == 1);

  ch_toVerilog("adder.v", adder);
  ch_toFIRRTL("adder.fir", adder);

  return 0;
}
