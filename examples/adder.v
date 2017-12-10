`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire io_cin2, io_cout14, proxy19, proxy22, proxy33;
    wire[1:0] io_lhs5, io_rhs8, io_out11, proxy24, proxy32;
    wire[2:0] proxy17, proxy21, proxy26, add27, add29, proxy30;

    assign io_cin2 = io_cin;
    assign io_lhs5 = io_lhs;
    assign io_rhs8 = io_rhs;
    assign io_out11 = proxy32;
    assign io_cout14 = proxy33;
    assign proxy17 = {proxy19, io_rhs8};
    assign proxy19 = 1'b0;
    assign proxy21 = {proxy22, io_lhs5};
    assign proxy22 = 1'b0;
    assign proxy24 = 2'b0;
    assign proxy26 = {proxy24, io_cin2};
    assign add27 = proxy26 + proxy21;
    assign add29 = add27 + proxy17;
    assign proxy30 = add29;
    assign proxy32 = proxy30[1:0];
    assign proxy33 = proxy30[2];

    assign io_out = io_out11;
    assign io_cout = io_cout14;

endmodule
