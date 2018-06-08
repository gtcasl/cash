module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] zext13;
  wire[2:0] zext15;
  wire[2:0] add19;
  wire[2:0] zext21;
  wire[2:0] add25;

  assign zext13 = {{2{1'b0}}, io_cin};
  assign zext15 = {{1{1'b0}}, io_lhs};
  assign add19 = zext13 + zext15;
  assign zext21 = {{1{1'b0}}, io_rhs};
  assign add25 = add19 + zext21;

  assign io_out = add25[1:0];
  assign io_cout = add25[2];

endmodule
