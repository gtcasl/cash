#include <cash.h>
#include <htl/decoupled.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::htl;

template <unsigned N>
struct GCD {
  __io (
    (ch_deq_io<ch_vec<ch_bit<N>,2>>) in,
    (ch_valid_io<ch_bit<N>>) out
  );
  void describe() {
    ch_seq<ch_bit<N>> x, y;
    ch_seq<ch_bool> p(false);

    io.in.ready = !p;

    __if (io.in.valid && io.in.ready) {
      x.next = io.in.data[0];
      y.next = io.in.data[1];
      p.next = true;
    };

    __if (p) {
      __if (x > y) {
        x.next = y;
        y.next = x;
      } __else {
        y.next = y - x;
      };
    };

    __if (io.out.valid) {
      p.next = false;
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
  auto ticks = tracer.run([&](ch_tick)->bool {
    return !gcd.io.out.valid;
  });

  std::cout << "completed after " << (ticks/2) << " cycles" << std::endl;
  std::cout << "result:" << std::endl;
  std::cout << "input[0] = " << gcd.io.in.data[0] << std::endl;
  std::cout << "input[1] = " << gcd.io.in.data[1] << std::endl;
  std::cout << "out = "  << gcd.io.out.data << std::endl;

  assert(gcd.io.out.data == 16);

  ch_toVerilog("gcd.v", gcd);

  return 0;
}
