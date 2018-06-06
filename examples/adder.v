module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] zext13; // adder.cpp(18)
  wire[2:0] zext16; // adder.cpp(18)
  wire[2:0] add18; // adder.cpp(18)
  wire[2:0] zext21; // adder.cpp(18)
  wire[2:0] add23; // adder.cpp(18)

  assign zext13 = {{2{1'b0}}, io_cin};
  assign zext16 = {{1{1'b0}}, io_lhs};
  assign add18 = zext13 + zext16;
  assign zext21 = {{1{1'b0}}, io_rhs};
  assign add23 = add18 + zext21;

  assign io_out = add23[1:0];
  assign io_cout = add23[2];

endmodule
