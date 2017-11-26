`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire[2:0] w18, w21, w23, a24, a25;

    assign w18 = {2'b0, io_cin};
    assign w21 = {1'b0, io_rhs};
    assign w23 = {1'b0, io_lhs};
    assign a24 = w23 + w21;
    assign a25 = a24 + w18;

    assign io_out = a25[1:0];
    assign io_cout = a25[2];

endmodule
