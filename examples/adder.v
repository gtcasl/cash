module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] proxy25; // v10 - adder.cpp(18)
  wire[2:0] proxy30; // v13 - /home/blaise/dev/cash/src/uint.h(294)
  wire[2:0] add31;
  wire[2:0] proxy36; // v17 - /home/blaise/dev/cash/src/uint.h(294)
  wire[2:0] add37;

  assign proxy25 = {2'h0, io_cin};
  assign proxy30 = {1'h0, io_lhs};
  assign add31 = proxy25 + proxy30;
  assign proxy36 = {1'h0, io_rhs};
  assign add37 = add31 + proxy36;

  assign io_out = add37[1:0];
  assign io_cout = add37[2];

endmodule
