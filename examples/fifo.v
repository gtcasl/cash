`include "cash.v"

module FiFo(
    input wire clk,
    input wire reset,
    input wire[1:0] io_din,
    input wire io_push,
    input wire io_pop,
    output wire[1:0] io_dout,
    output wire io_empty,
    output wire io_full
);
    reg[1:0] r24, r29;
    wire w33, w35, a36, a37, a38, a39, a50, a53, a54, a55;
    wire[1:0] a41, s42, a43, s44, s48;
    reg[1:0] m45[0:1];

    always @ (posedge clk)
    r24 <= reset ? 2'b0 : s42;
    always @ (posedge clk)
    r29 <= reset ? 2'b0 : s44;
    assign w33 = r24[0];
    assign w35 = r29[0];
    assign a36 = ~a50;
    assign a37 = io_pop & a36;
    assign a38 = ~a55;
    assign a39 = io_push & a38;
    assign a41 = r24 + 2'b1;
    assign s42 = a37 ? a41 : r24;
    assign a43 = r29 + 2'b1;
    assign s44 = a39 ? a43 : r29;
    always @(posedge clk)
    m45[w35] = s48;
    assign s48 = a39 ? io_din : m45[w35];
    assign a50 = r29 == r24;
    assign a53 = r29[1] != r24[1];
    assign a54 = w35 == w33;
    assign a55 = a54 & a53;

    assign io_dout = m45[w33];
    assign io_empty = a50;
    assign io_full = a55;

endmodule
