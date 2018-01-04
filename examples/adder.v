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
    wire[1:0] proxy17; // #6 /home/blaise/dev/cash/src/bit.h(1004)
    wire[2:0] proxy19; // #7 adder.cpp(18)
    wire[2:0] proxy20; // #8 /home/blaise/dev/cash/src/bit.h(1008)
    wire proxy22; // #9 /home/blaise/dev/cash/src/bit.h(1004)
    wire[2:0] proxy24; // #10 /home/blaise/dev/cash/src/bit.h(1090)
    wire[2:0] add25;
    wire[2:0] proxy26; // #11 unknown(0)
    wire[2:0] proxy27; // #12 /home/blaise/dev/cash/src/bit.h(1008)
    wire proxy28; // #13 /home/blaise/dev/cash/src/bit.h(1004)
    wire[2:0] proxy30; // #14 /home/blaise/dev/cash/src/bit.h(1090)
    wire[2:0] add31;
    wire[2:0] proxy32; // #15 unknown(0)
    wire[1:0] proxy34; // #16 adder.cpp(19)
    wire[1:0] proxy35; // #17 /home/blaise/dev/cash/src/bit.h(599)
    wire proxy36; // #18 unknown(0)

    assign io_cin2 = io_cin;
    assign io_lhs5 = io_lhs;
    assign io_rhs8 = io_rhs;
    assign io_out11 = proxy35;
    assign io_cout14 = proxy36;
    assign proxy17 = 2'b0;
    assign proxy19 = {proxy17, io_cin2};
    assign proxy20 = proxy19;
    assign proxy22 = 1'b0;
    assign proxy24 = {proxy22, io_lhs5};
    assign add25 = proxy20 + proxy24;
    assign proxy26 = add25;
    assign proxy27 = proxy26;
    assign proxy28 = 1'b0;
    assign proxy30 = {proxy28, io_rhs8};
    assign add31 = proxy27 + proxy30;
    assign proxy32 = add31;
    assign proxy34 = proxy32[1:0];
    assign proxy35 = proxy34;
    assign proxy36 = proxy32[2];

    assign io_out = io_out11;
    assign io_cout = io_cout14;

endmodule
