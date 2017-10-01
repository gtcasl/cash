#include <cash.h>

using namespace cash::core;
using namespace cash::literals;
using namespace cash::sim;

#define CHECK(x, v) if (ch_peek<decltype(v)>(x) != v) { assert(false); exit(1); }

template <unsigned N>
struct Adder {
  __io (
    (ch_in<ch_bit1>)    cin,
    (ch_in<ch_bit<N>>)  lhs,
    (ch_in<ch_bit<N>>)  rhs,
    (ch_out<ch_bit<N>>) out,
    (ch_out<ch_bit1>)   cout
  );
  Adder() {
    auto sum = (0_b, io.lhs) + (0_b, io.rhs) + ch_zext<N+1>(io.cin);
    io.out  = ch_slice<N>(sum);
    io.cout = sum[N];
  }
};

int main(int argc, char **argv) {
  ch_module<Adder<2>> adder;

  ch_poke(adder->io.cin, 1);
  ch_poke(adder->io.lhs, 1);
  ch_poke(adder->io.rhs, 3);

  ch_vcdtracer tracer("adder.vcd", adder);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "cout = " << adder->io.cout << std::endl;
  std::cout << "out = " << adder->io.out << std::endl;

  CHECK(adder->io.out, 1);
  CHECK(adder->io.cout, true);

  ch_toVerilog("adder.v", adder);

  return 0;
}
