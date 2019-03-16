#include <cash.h>

#define CHECK(x) do { if (!(x)) { std::cout << "FAILED: " << #x << std::endl; std::abort(); } } while (false)

using namespace ch::logic;
using namespace ch::system;

struct FastMul {
  __io (
    __in (ch_uint4)  lhs,
    __in (ch_uint4)  rhs,
    __out (ch_uint8) out
  );
  void describe() {
    std::array<uint8_t, 256> tbl_mul;
    for (int j = 0; j < 16; ++j) {
      for (int i = 0; i < 16; ++i) {
        tbl_mul[j * 16 + i] = i * j;
      }
    }
    ch_rom<ch_uint8, 256> rom(tbl_mul);
    auto addr = (ch_pad<4>(io.lhs) << 4) | ch_pad<4>(io.rhs);
    io.out = rom.read(addr);
  }
};

int main() {
  ch_device<FastMul> fastmul;

  fastmul.io.lhs = 2;
  fastmul.io.rhs = 3;

  ch_tracer tracer(fastmul);
  tracer.run();

  std::cout << "result:" << std::endl;
  std::cout << "lhs = "  << fastmul.io.lhs << std::endl;
  std::cout << "rhs = "  << fastmul.io.rhs << std::endl;
  std::cout << "out = "  << fastmul.io.out << std::endl;

  CHECK(fastmul.io.out == 6);

  ch_toVerilog("fastmul.v", fastmul);
  ch_toFIRRTL("fastmul.fir", fastmul);

  tracer.toText("fastmul.log");
  tracer.toVCD("fastmul.vcd");
  tracer.toTestBench("fastmul_tb.v", "fastmul.v");
  int ret = system("iverilog fastmul_tb.v -o fastmul_tb.iv")
          | system("! vvp fastmul_tb.iv | grep 'ERROR' || false");
  return ret != 0;
}
