#include <cash.h>

using namespace ch::core;
using namespace ch::sim;
using namespace ch::literals;

template <unsigned N>
struct Adder {
  __io (
    __in(ch_uint1)    cin,
    __in(ch_uint<N>)  lhs,
    __in(ch_uint<N>)  rhs,
    __out(ch_uint<N>) out,
    __out(ch_uint1)   cout
  );

  void describe() {
    auto sum = ch_pad<N+1>(io.lhs) + io.rhs + io.cin;
    io.out  = ch_slice<N>(sum).as_uint();
    io.cout = sum[N].as_uint();
  }
};

int main() {
  ch_device<Adder<2>> adder;

  adder.io.cin = 1;
  adder.io.lhs = 1;
  adder.io.rhs = 3;

  ch_tracer tracer(adder);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << adder.io.cout << std::endl;
  std::cout << "out = "  << adder.io.out << std::endl;

  assert(adder.io.out == 1);
  assert(adder.io.cout == 1);

  ch_toVerilog("adder.v", adder);
  ch_toFirrtl("adder.fir", adder);

  tracer.toText("adder.log");
  tracer.toVCD("adder.vcd");
  tracer.toTestBench("adder_tb.v", "adder.v");
  int ret = system("iverilog adder_tb.v -o adder_tb.iv")
          | system("! vvp -n adder_tb.iv | grep 'ERROR' || false");
  return ret != 0;
}
