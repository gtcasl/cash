#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

#define CHECK(x, v) if (ch_peek<decltype(v)>(x) != v) { assert(false); exit(1); }

template <unsigned N>
struct GCD {
  __io (
    (ch_deqIO<ch_vec<ch_bit<N>,2>>) in,
    (ch_validIO<ch_bit<N>>) out
  );
  void describe() {
    ch_seq<ch_bit<N>> x, y;
    ch_seq<ch_bool> p(false);

    io.in.ready = !p;

    __if (io.in.valid && !p) (
      x.next = io.in.data[0];
      y.next = io.in.data[1];
      p.next = true;
    );

    __if (p) (
      __if (x > y) (
        x.next = y;
        y.next = x;
      )__else(
        y.next = y - x;
      );
    );

    __if (io.out.valid) (
      p.next = false;
    );

    io.out.data  = x;
    io.out.valid = (0 == y) && p;
  }
};

int main(int argc, char **argv) {
  ch_device<GCD<16>> gcd;

  ch_poke(gcd.io.in.data, 0x00300020_h);
  ch_poke(gcd.io.in.valid, true);

  ch_vcdtracer tracer("gcd.vcd", gcd);
  auto ticks = tracer.run([&](ch_tick t)->bool {
    return !ch_peek<bool>(gcd.io.out.valid);
  });

  std::cout << "completed after " << (ticks/2) << " cycles" << std::endl;
  std::cout << "result:" << std::endl;
  std::cout << "inputs = " << gcd.io.in.data << std::endl;
  std::cout << "out = "  << gcd.io.out.data << std::endl;

  CHECK(gcd.io.out.data, 16);

  ch_toVerilog("gcd.v", gcd);

  return 0;
}
