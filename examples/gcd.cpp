#include <cash.h>
#include <htl/decoupled.h>

using namespace ch::core;
using namespace ch::sim;
using namespace ch::htl;
using namespace ch::literals;

template <unsigned N>
struct GCD {
  __io (
    (ch_deq_io<ch_vec<ch_uint<N>,2>>) in,
    (ch_valid_io<ch_uint<N>>) out
  );
  void describe() {
    ch_reg<ch_uint<N>> x, y;
    ch_reg<ch_bool> p(false);

    io.in.ready = !p;

    __if (io.in.valid && io.in.ready) {
      x->next = io.in.data[0];
      y->next = io.in.data[1];
      p->next = true;
    };

    __if (p) {
      __if (x > y) {
        x->next = y;
        y->next = x;
      } __else {
        y->next = y - x;
      };
    };

    __if (io.out.valid) {
      p->next = false;
    };

    io.out.data  = x;
    io.out.valid = (0 == y) && p;
  }
};

int main() {
  ch_device<GCD<16>> gcd;

  gcd.io.in.data[0] = 0x0020_h;
  gcd.io.in.data[1] = 0x0030_h;
  gcd.io.in.valid = true;

  ch_vcdtracer tracer("gcd.vcd", gcd);
  auto ticks = tracer.run([&](ch_tick t)->bool {
    std::cout << "t" << t << ": in="  << gcd.io.in.ready
              << ", out="  << gcd.io.out.data << std::endl;
    return !gcd.io.out.valid && t < 20;
  });

  std::cout << "completed after " << (ticks/2) << " cycles" << std::endl;

  assert(gcd.io.out.data == 16);

  ch_verilog("gcd.v", gcd);
  ch_firrtl("gcd.fir", gcd);

  int ret = system("iverilog gcd_tb.v -o gcd_tb.iv")
          | system("vvp gcd_tb.iv");
  return ret != 0;
}
