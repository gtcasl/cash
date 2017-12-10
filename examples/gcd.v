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
    wire[31:0] io_in_data5;
    wire[15:0] proxy6, proxy7, io_out_data16, proxy19, sel44, sel45, sel51, sel52, sub53, sel57;
    wire io_in_ready10, io_out_valid13, inv40, proxy41, and42, sel47, gt48, and50, inv55, and56, sel58, eq60, and62, proxy63;
    reg[15:0] reg26, reg32;
    reg reg39;

    assign io_in_data5 = io_in_data;
    assign proxy6 = io_in_data5[31:16];
    assign proxy7 = io_in_data5[15:0];
    assign io_in_ready10 = proxy41;
    assign io_out_valid13 = proxy63;
    assign io_out_data16 = proxy19;
    assign proxy19 = reg26;
    always @ (posedge clk)
    reg26 <= reset ? 16'h0 : sel51;
    always @ (posedge clk)
    reg32 <= reset ? 16'h0 : sel57;
    always @ (posedge clk)
    reg39 <= reset ? 1'b0 : sel58;
    assign inv40 = ~reg39;
    assign proxy41 = inv40;
    assign and42 = io_in_valid & io_in_ready10;
    assign sel44 = and42 ? proxy7 : proxy19;
    assign sel45 = and42 ? proxy6 : reg32;
    assign sel47 = and42 ? 1'b1 : reg39;
    assign gt48 = proxy19 > reg32;
    assign and50 = reg39 & gt48;
    assign sel51 = and50 ? reg32 : sel44;
    assign sel52 = and50 ? proxy19 : sel45;
    assign sub53 = reg32 - proxy19;
    assign inv55 = ~gt48;
    assign and56 = reg39 & inv55;
    assign sel57 = and56 ? sub53 : sel52;
    assign sel58 = io_out_valid13 ? 1'b0 : sel47;
    assign eq60 = 16'h0 == reg32;
    assign and62 = eq60 & reg39;
    assign proxy63 = and62;

    assign io_in_ready = io_in_ready10;
    assign io_out_valid = io_out_valid13;
    assign io_out_data = io_out_data16;

endmodule
