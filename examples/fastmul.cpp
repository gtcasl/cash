#include <iostream>
#include <fstream>
#include <chdl.h>

using namespace chdl::core;
using namespace chdl::sim;

ch_bit8 FastMul(const ch_bit4& lhs, const ch_bit4& rhs) {
  std::vector<uint32_t> tbl_mult(16 * 16);
  for (int j = 0; j < 16; ++j)
    for (int i = 0; i < 16; ++i)
      tbl_mult[j * 16 + i] = i * j;
  ch_rom<8, 8> mem(tbl_mult);
  return mem.read((ch_zext<8>(lhs) << 4) | rhs);
}

int main(int argc, char **argv) {
  ch_bus<8> out;
  ch_bus<4> lhs(2), rhs(3);

  ch_device myDevice(FastMul, lhs, rhs, out);

  /*std::ofstream v_file("fastmul.v");
  myDevice.toVerilog("fastmul", v_file);
  v_file.close();*/

  ch_vcdtracer tracer("fastmul.vcd", myDevice);
  __ch_trace(tracer, lhs, rhs, out);
  tracer.run();

  return 0;
}
