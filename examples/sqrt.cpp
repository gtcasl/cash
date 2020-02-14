#include <core.h>
#include <math.h>
#include "common.h"

using namespace ch::core;
using namespace ch::extension;

// reference: https://github.com/tchoi8/verilog/blob/master/examples/sqrt.vl
static const char* sqrt_v_source =
    "module sqrt32(\n"
    "  input  clk,\n"
    "  input  reset,\n"
    "  input [31:0] x,\n"
    "  output rdy,\n"
    "  output [15:0] y);\n"
    "  reg [15:0] y;\n"
    "  reg [31:0] acc2;\n"
    "  reg [4:0]  bitl;\n"
    "  wire [15:0] bit = 1 << bitl;\n"
    "  wire [31:0] bit2 = 1 << (bitl << 1);\n"
    "  wire rdy = bitl[4];\n"
    "  wire [15:0] guess  = y | bit;\n"
    "  wire [31:0] guess2 = acc2 + bit2 + ((y << bitl) << 1);\n"
    "  always @(posedge clk)\n"
    "    if (reset)begin\n"
    "      y    = 0;\n"
    "      acc2 = 0;\n"
    "      bitl = 15;\n"
    "    end else begin\n"
    "      if (guess2 <= x) begin\n"
    "        y    <= guess;\n"
    "        acc2 <= guess2;\n"
    "      end\n"
    "      bitl <= bitl - 1;\n"
    "    end\n"
    "endmodule";

__inout(sqrt_io, (
  __in  (ch_int32) in,
  __out (ch_int16) out,
  __out (ch_bool)  valid
));

struct SqrtUDF {
  ch_system_io<sqrt_io> io;

  void eval() {
    auto guess = y_ | (1 << bitl_);
    auto guess2 = acc2_ + (1 << (bitl_ << 1)) + ((y_ << bitl_) << 1);
    if (guess2 <= io.in) {
      y_ = guess;
      acc2_ = guess2;
    }
    io.out = y_;
    io.valid = (bitl_ >> 4) & 0x1;
    --bitl_;
  }

  void reset() {
    io.valid = false;
    y_    = 0;
    acc2_ = 0;
    bitl_ = 15;
  }

  bool to_verilog(udf_vostream& out, udf_verilog mode) {
    switch (mode) {
    case udf_verilog::header:
      out << sqrt_v_source;
      return true;
    case udf_verilog::body:
      out << "sqrt32 root($clk, $reset, " << io.in << ", " << io.valid << ", " << io.out << ");";
      return true;
    default:
      break;
    }
    return false;
  }

  int y_, acc2_, bitl_;
};

struct Sqrt {
  sqrt_io io;

  void describe() {
    ch_udf_seq<SqrtUDF> sqrt;
    sqrt.io(io);
  }
};

int main() {
  ch_device<Sqrt> device;

  ch_tracer tracer(device);
  device.io.in = 63;
  auto cycles = tracer.run([&](ch_tick)->bool { return !device.io.valid; });

  std::cout << "result:" << std::endl;
  std::cout << "out = "  << device.io.out << " after " << cycles << " cycles." << std::endl;
  CHECK(device.io.out == (int)sqrt((int)device.io.in));

  ch_toVerilog("sqrt.v", device);

  tracer.toText("sqrt.log");
  tracer.toVCD("sqrt.vcd");
  tracer.toVerilog("sqrt_tb.v", "sqrt.v", true);
  int ret = !system("iverilog sqrt_tb.v -o sqrt_tb.iv")
          & !system("! vvp sqrt_tb.iv | grep 'ERROR' || false");
  return (0 == ret);
}
