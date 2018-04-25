module Adder(
  input wire io_cin,
  input wire[1:0] io_lhs,
  input wire[1:0] io_rhs,
  output wire[1:0] io_out,
  output wire io_cout
);
  wire[2:0] zext19;
  wire[2:0] zext22;
  wire[2:0] add24;
  wire[2:0] zext27;
  wire[2:0] add29;

  assign zext19 = {{2{1'b0}}, io_cin};
  assign zext22 = {{1{1'b0}}, io_lhs};
  assign add24 = zext19 + zext22;
  assign zext27 = {{1{1'b0}}, io_rhs};
  assign add29 = add24 + zext27;

  assign io_out = add29[1:0];
  assign io_cout = add29[2];

endmodule
