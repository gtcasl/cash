#include <iostream>
#include <fstream>
#include <cash.h>

using namespace cash::core;
using namespace cash::sim;

#define CHECK(x) if (!(x)) { assert(false); exit(1); }

ch_bit8 FastMul(const ch_bit4& lhs, const ch_bit4& rhs) {
  std::vector<uint8_t> tbl_mult(256);
  for (int j = 0; j < 16; ++j) {
    for (int i = 0; i < 16; ++i) {
      tbl_mult[j * 16 + i] = i * j;
    }
  }
  ch_rom<8, 8> mem(tbl_mult);
  return mem[(ch_zext<8>(lhs) << 4) | ch_zext<8>(rhs)];
}

int main(int argc, char **argv) {
  std::ofstream vcd_file("fastmul.vcd");
  ch_bus8 out;
  ch_bus4 lhs(2), rhs(3);

  ch_device myDevice(FastMul, lhs, rhs, out);

  /*std::ofstream v_file("fastmul.v");
  myDevice.to_verilog("fastmul", v_file);
  v_file.close();*/

  ch_vcdtracer tracer(vcd_file, myDevice);
  __trace(tracer, lhs, rhs, out);
  tracer.run();
  
  std::cout << "result:" << std::endl;
  std::cout << "lhs = " << lhs << std::endl;
  std::cout << "rhs = " << rhs << std::endl;
  std::cout << "out = " << out << std::endl;

  CHECK(out == 6);

  return 0;
}
