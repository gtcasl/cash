`include "cash.v"

module Adder(
    input wire io_cin,
    input wire[1:0] io_lhs,
    input wire[1:0] io_rhs,
    output wire[1:0] io_out,
    output wire io_cout
);
    wire io_cin2; // adder.cpp(8) @var1
    wire[1:0] io_lhs5; // adder.cpp(8) @var2
    wire[1:0] io_rhs8; // adder.cpp(8) @var3
    wire[1:0] io_out11; // adder.cpp(8) @var4
    wire io_cout14; // adder.cpp(8) @var5
    wire[1:0] proxy17; // adder.cpp(18) @var6
    wire[2:0] proxy19; // adder.cpp(18) @var7
    wire[2:0] proxy20; // /home/blaise/dev/cash/src/bit.h(1086) @var8
    wire proxy22; // /home/blaise/dev/cash/src/bit.h(1086) @var9
    wire[2:0] proxy24; // /home/blaise/dev/cash/src/bit.h(1086) @var10
    wire[2:0] add25;
    wire[2:0] proxy26; // @var11
    wire[2:0] proxy27; // /home/blaise/dev/cash/src/bit.h(1086) @var12
    wire proxy28; // /home/blaise/dev/cash/src/bit.h(1086) @var13
    wire[2:0] proxy30; // /home/blaise/dev/cash/src/bit.h(1086) @var14
    wire[2:0] add31;
    wire[2:0] proxy32; // @var15
    wire[1:0] proxy34; // adder.cpp(19) @var16
    wire proxy35; // @var17

    assign io_cin2 = io_cin;
    assign io_lhs5 = io_lhs;
    assign io_rhs8 = io_rhs;
    assign io_out11 = proxy34;
    assign io_cout14 = proxy35;
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
    assign proxy35 = proxy32[2];

    assign io_out = io_out11;
    assign io_cout = io_cout14;

endmodule
