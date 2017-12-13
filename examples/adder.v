`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire io_cin2, io_cout14, proxy21, proxy27, proxy35;
    wire[1:0] io_lhs5, io_rhs8, io_out11, proxy17, proxy34;
    wire[2:0] proxy19, proxy23, proxy24, add25, proxy29, proxy30, add31, proxy32;

    assign io_cin2 = io_cin;
    assign io_lhs5 = io_lhs;
    assign io_rhs8 = io_rhs;
    assign io_out11 = proxy34;
    assign io_cout14 = proxy35;
    assign proxy17 = 2'b0;
    assign proxy19 = {proxy17, io_cin2};
    assign proxy21 = 1'b0;
    assign proxy23 = {proxy21, io_lhs5};
    assign proxy24 = proxy23;
    assign add25 = proxy19 + proxy24;
    assign proxy27 = 1'b0;
    assign proxy29 = {proxy27, io_rhs8};
    assign proxy30 = proxy29;
    assign add31 = add25 + proxy30;
    assign proxy32 = add31;
    assign proxy34 = proxy32[1:0];
    assign proxy35 = proxy32[2];

    assign io_out = io_out11;
    assign io_cout = io_cout14;

endmodule
