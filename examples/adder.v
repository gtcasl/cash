`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire io_cin2; // #1 adder.cpp(8)
    wire[1:0] io_lhs5; // #2 adder.cpp(8)
    wire[1:0] io_rhs8; // #3 adder.cpp(8)
    wire[1:0] io_out11; // #4 adder.cpp(8)
    wire io_cout14; // #5 adder.cpp(8)
    wire[1:0] proxy17; // #6 /home/blaise/dev/cash/src/bit.h(1020)
    wire[2:0] proxy19; // #7 adder.cpp(18)
    wire proxy21; // #8 /home/blaise/dev/cash/src/bit.h(1020)
    wire[2:0] proxy23; // #9 /home/blaise/dev/cash/src/bit.h(417)
    wire[2:0] proxy24; // #10 /home/blaise/dev/cash/src/bit.h(547)
    wire[2:0] add25;
    wire proxy27; // #12 /home/blaise/dev/cash/src/bit.h(1020)
    wire[2:0] proxy29; // #13 /home/blaise/dev/cash/src/bit.h(417)
    wire[2:0] proxy30; // #14 /home/blaise/dev/cash/src/bit.h(547)
    wire[2:0] add31;
    wire[2:0] proxy32; // #15 unknown(0)
    wire[1:0] proxy34; // #16 adder.cpp(19)
    wire proxy35; // #17 unknown(0)

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
