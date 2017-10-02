#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

#define CHECK(x, v) if (ch_peek<decltype(v)>(x) != v) { assert(false); exit(1); }

struct FastMult {
  __io (
    (ch_in<ch_bit4>) lhs,
    (ch_in<ch_bit4>) rhs,
    (ch_out<ch_bit8>) out
  );
  void describe() {
    std::vector<uint8_t> tbl_mult(256);
    for (int j = 0; j < 16; ++j) {
      for (int i = 0; i < 16; ++i) {
        tbl_mult[j * 16 + i] = i * j;
      }
    }
    ch_rom<8, 8> mem(tbl_mult);
    auto addr = (ch_zext<8>(io.lhs) << 4) | ch_zext<8>(io.rhs);
    io.out = mem[addr];
  }
};

int main(int argc, char **argv) {
  ch_module<FastMult> fastmult;

  ch_poke(fastmult->io.lhs, 2);
  ch_poke(fastmult->io.rhs, 3);

  ch_vcdtracer tracer("fastmult.vcd", fastmult);
  tracer.run();

  std::cout << "result:" << std::endl;
  std::cout << "lhs = " << fastmult->io.lhs << std::endl;
  std::cout << "rhs = " << fastmult->io.rhs << std::endl;
  std::cout << "out = " << fastmult->io.out << std::endl;

  CHECK(fastmult->io.out, 6);

  ch_toVerilog("fastmult.v", fastmult);
}
