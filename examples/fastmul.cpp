#include <iostream>
#include <fstream>
#include <chdl.h>

using namespace chdl;
using namespace chdl::sim;

ch_bit8 FastMul(const ch_bit4& lhs, const ch_bit4& rhs) {

  std::vector<uint32_t> muls(16 * 16);

  for (int j = 0; j < 16; ++j)
    for (int i = 0; i < 16; ++i)
      muls[j * 16 + i] = i * j;

  ch_rom<8, 8> mem(muls);
  return mem.read((ch_zext<8>(lhs) << 4) | rhs);
}

int main(int argc, char **argv) {
  ch_bus<8> out;
  ch_bus<4> lhs(1), rhs(2);

  ch_device myDevice(FastMul);
  myDevice.bind(out, lhs, rhs);

  std::ofstream v_file("fastmul.v");
  myDevice.toVerilog("fastmul", v_file);
  v_file.close();

  ch_vcdtracer tracer("fastmul.vcd");
  __ch_trace(tracer, out, lhs, rhs);
  tracer.run();
  tracer.close();

  return 0;
}
