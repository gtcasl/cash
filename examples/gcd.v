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
    wire[31:0] io_in_data5; // #2 gcd.cpp(10)
    wire[15:0] proxy6; // #3 unknown(0)
    wire[15:0] proxy7; // #4 unknown(0)
    wire io_in_ready10; // #5 gcd.cpp(10)
    wire io_out_valid13; // #6 gcd.cpp(10)
    wire[15:0] io_out_data16; // #7 gcd.cpp(10)
    wire[15:0] proxy19; // #8 gcd.cpp(16)
    reg[15:0] reg26; // #8 gcd.cpp(16)
    reg[15:0] reg32; // #11 gcd.cpp(16)
    reg reg39; // #14 gcd.cpp(17)
    wire eq41;
    wire proxy42; // #18 unknown(0)
    wire and43;
    wire[15:0] sel45;
    wire[15:0] sel46;
    wire sel48;
    wire gt49;
    wire and51;
    wire[15:0] sel52;
    wire[15:0] sel53;
    wire[15:0] sub54;
    wire inv56;
    wire and57;
    wire[15:0] sel58;
    wire sel59;
    wire eq61;
    wire and63;
    wire proxy64; // #24 unknown(0)

    assign io_in_data5 = io_in_data;
    assign proxy6 = io_in_data5[31:16];
    assign proxy7 = io_in_data5[15:0];
    assign io_in_ready10 = proxy42;
    assign io_out_valid13 = proxy64;
    assign io_out_data16 = proxy19;
    assign proxy19 = reg26;
    always @ (posedge clk) reg26 <= reset ? 16'h0 : sel52;
    always @ (posedge clk) reg32 <= reset ? 16'h0 : sel58;
    always @ (posedge clk) reg39 <= reset ? 1'b0 : sel59;
    assign eq41 = reg39 == 1'b0;
    assign proxy42 = eq41;
    assign and43 = io_in_valid & io_in_ready10;
    assign sel45 = and43 ? proxy7 : proxy19;
    assign sel46 = and43 ? proxy6 : reg32;
    assign sel48 = and43 ? 1'b1 : reg39;
    assign gt49 = proxy19 > reg32;
    assign and51 = reg39 & gt49;
    assign sel52 = and51 ? reg32 : sel45;
    assign sel53 = and51 ? proxy19 : sel46;
    assign sub54 = reg32 - proxy19;
    assign inv56 = ~gt49;
    assign and57 = reg39 & inv56;
    assign sel58 = and57 ? sub54 : sel53;
    assign sel59 = io_out_valid13 ? 1'b0 : sel48;
    assign eq61 = 16'h0 == reg32;
    assign and63 = eq61 & reg39;
    assign proxy64 = and63;

    assign io_in_ready = io_in_ready10;
    assign io_out_valid = io_out_valid13;
    assign io_out_data = io_out_data16;

endmodule
