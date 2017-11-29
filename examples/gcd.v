`include "cash.v"

module GCD(
    input wire clk,
    input wire reset,
    input wire io_in_valid,
    input wire[31:0] io_in_data,
    output wire io_in_ready,
    output wire io_out_valid,
    output wire[15:0] io_out_data
);
    reg[15:0] r21, r26;
    reg r32;
    wire a35, a36, s42, a43, a44, a48, a49, s51, a52, a53;
    wire[15:0] s38, s40, s45, s46, a47, s50;

    always @ (posedge clk)
    r21 <= reset ? 16'h0 : s45;
    always @ (posedge clk)
    r26 <= reset ? 16'h0 : s50;
    always @ (posedge clk)
    r32 <= reset ? 1'b0 : s51;
    assign a35 = ~r32;
    assign a36 = io_in_valid & a35;
    assign s38 = a36 ? io_in_data[15:0] : r21;
    assign s40 = a36 ? io_in_data[31:16] : r26;
    assign s42 = a36 ? 1'b1 : r32;
    assign a43 = r21 > r26;
    assign a44 = r32 & a43;
    assign s45 = a44 ? r26 : s38;
    assign s46 = a44 ? r21 : s40;
    assign a47 = r26 - r21;
    assign a48 = ~a43;
    assign a49 = r32 & a48;
    assign s50 = a49 ? a47 : s46;
    assign s51 = a53 ? 1'b0 : s42;
    assign a52 = 16'h0 == r26;
    assign a53 = a52 & r32;

    assign io_in_ready = a35;
    assign io_out_valid = a53;
    assign io_out_data = r21;

endmodule
