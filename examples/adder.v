module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] proxy19; // v7 - adder.cpp(18)
  wire[2:0] proxy24; // v10 - /home/blaise/dev/cash/src/bit.h(1114)
  wire[2:0] add25;
  wire[2:0] proxy30; // v14 - /home/blaise/dev/cash/src/bit.h(1114)
  wire[2:0] add31;

  assign proxy19 = {2'h0, io_cin};
  assign proxy24 = {1'h0, io_lhs};
  assign add25 = proxy19 + proxy24;
  assign proxy30 = {1'h0, io_rhs};
  assign add31 = add25 + proxy30;

  assign io_out = add31[1:0];
  assign io_cout = add31[2];

endmodule
