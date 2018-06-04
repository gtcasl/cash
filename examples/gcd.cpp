#include <cash.h>
#include <htl/decoupled.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::htl;

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
      x <<= io.in.data[0];
      y <<= io.in.data[1];
      p <<= true;
    };

    __if (p) {
      __if (x > y) {
        x <<= y;
        y <<= x;
      } __else {
        y <<= y - x;
      };
    };

    __if (io.out.valid) {
      p <<= false;
    };

    io.out.data  = x;
    io.out.valid = (0 == y) && p;

    ch_print("{0}: clk={1}, rst={2}, x={3}, y={4}, p={5}", ch_time(), ch_clock(), ch_reset(), x, y, p);
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

  ch_toVerilog("gcd.v", gcd);
  ch_toFIRRTL("gcd.fir", gcd);

  return 0;
}
