module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] zext22;
  wire[2:0] zext25;
  wire[2:0] add27;
  wire[2:0] zext30;
  wire[2:0] add32;

  assign zext22 = {{2{1'b0}}, io_cin};
  assign zext25 = {{1{1'b0}}, io_lhs};
  assign add27 = zext22 + zext25;
  assign zext30 = {{1{1'b0}}, io_rhs};
  assign add32 = add27 + zext30;

  assign io_out = add32[1:0];
  assign io_cout = add32[2];

endmodule
