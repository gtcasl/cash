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
    wire a35, a36, a37, s43, a44, a45, a48, a50, s52, a53, a54;
    wire[15:0] s39, s41, s46, s47, a49, s51;

    always @ (posedge clk)
    r21 <= reset ? 16'h0 : s46;
    always @ (posedge clk)
    r26 <= reset ? 16'h0 : s51;
    always @ (posedge clk)
    r32 <= reset ? 1'b0 : s52;
    assign a35 = ~r32;
    assign a36 = ~r32;
    assign a37 = io_in_valid & a36;
    assign s39 = a37 ? io_in_data[15:0] : r21;
    assign s41 = a37 ? io_in_data[31:16] : r26;
    assign s43 = a37 ? 1'b1 : r32;
    assign a44 = r21 > r26;
    assign a45 = r32 & a44;
    assign s46 = a45 ? r26 : s39;
    assign s47 = a45 ? r21 : s41;
    assign a48 = ~a44;
    assign a49 = r26 - r21;
    assign a50 = r32 & a48;
    assign s51 = a50 ? a49 : s47;
    assign s52 = a54 ? 1'b0 : s43;
    assign a53 = 16'h0 == r26;
    assign a54 = a53 & r32;

    assign io_in_ready = a35;
    assign io_out_valid = a54;
    assign io_out_data = r21;

endmodule
