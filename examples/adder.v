`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire io_cin2, io_cout14, proxy28;
    wire[1:0] io_lhs5, io_rhs8, io_out11, proxy27;
    wire[2:0] proxy18, proxy21, add22, proxy24, add25;

    assign io_cin2 = io_cin;
    assign io_lhs5 = io_lhs;
    assign io_rhs8 = io_rhs;
    assign io_out11 = proxy27;
    assign io_cout14 = proxy28;
    assign proxy18 = {2'b0, io_cin2};
    assign proxy21 = {1'b0, io_lhs5};
    assign add22 = proxy18 + proxy21;
    assign proxy24 = {1'b0, io_rhs8};
    assign add25 = add22 + proxy24;
    assign proxy27 = add25[1:0];
    assign proxy28 = add25[2];

    assign io_out = io_out11;
    assign io_cout = io_cout14;

endmodule
