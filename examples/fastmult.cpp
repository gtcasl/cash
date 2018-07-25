#include <cash.h>

using namespace ch::core;
using namespace ch::sim;

struct FastMult {
  __io (
    __in(ch_uint4)  lhs,
    __in(ch_uint4)  rhs,
    __out(ch_uint8) out
  );
  void describe() {
    std::array<uint8_t, 256> tbl_mult;
    for (int j = 0; j < 16; ++j) {
      for (int i = 0; i < 16; ++i) {
        tbl_mult[j * 16 + i] = i * j;
      }
    }
    ch_rom<ch_uint8, 256> rom(tbl_mult);
    auto addr = (ch_pad<8>(io.lhs) << 4) | ch_pad<8>(io.rhs);
    io.out = rom.read(addr);
  }
};

int main() {
  ch_device<FastMult> fastmult;

  fastmult.io.lhs = 2;
  fastmult.io.rhs = 3;

  ch_tracer tracer(fastmult);
  tracer.run();

  std::cout << "result:" << std::endl;
  std::cout << "lhs = "  << fastmult.io.lhs << std::endl;
  std::cout << "rhs = "  << fastmult.io.rhs << std::endl;
  std::cout << "out = "  << fastmult.io.out << std::endl;

  assert(fastmult.io.out == 6);

  tracer.toVCD("fastmult.vcd");

  ch_toVerilog("fastmult.v", fastmult);
  ch_toFirrtl("fastmult.fir", fastmult);

  int ret = system("iverilog fastmult_tb.v -o fastmult_tb.iv")
          | system("vvp fastmult_tb.iv");
  return ret != 0;
}
