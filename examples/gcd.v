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
    wire[31:0] io_in_data5; // gcd.cpp(10) @var2
    wire[15:0] proxy6; // @var3
    wire[15:0] proxy7; // @var4
    wire io_in_ready10; // gcd.cpp(10) @var5
    wire io_out_valid13; // gcd.cpp(10) @var6
    wire[15:0] io_out_data16; // gcd.cpp(10) @var7
    wire[15:0] proxy19; // gcd.cpp(16) @var8
    reg[15:0] reg26; // gcd.cpp(16) @var8
    reg[15:0] reg32; // gcd.cpp(16) @var11
    reg reg39; // gcd.cpp(17) @var14
    wire eq41;
    wire proxy42; // @var18
    wire and43;
    wire sel46; // gcd.cpp(21)
    wire[15:0] sel47; // gcd.cpp(21)
    wire[15:0] sel48; // gcd.cpp(21)
    wire gt49;
    wire[15:0] sub51;
    wire[15:0] sel53; // gcd.cpp(28)
    wire[15:0] sel54; // gcd.cpp(27)
    wire[15:0] sel55; // gcd.cpp(28)
    wire and56;
    wire sel57; // gcd.cpp(36)
    wire eq59;
    wire and61;
    wire proxy62; // @var24

    assign io_in_data5 = io_in_data;
    assign proxy6 = io_in_data5[31:16];
    assign proxy7 = io_in_data5[15:0];
    assign io_in_ready10 = proxy42;
    assign io_out_valid13 = proxy62;
    assign io_out_data16 = proxy19;
    assign proxy19 = reg26;
    always @ (posedge clk) reg26 <= reset ? 16'h0 : sel55;
    always @ (posedge clk) reg32 <= reset ? 16'h0 : sel54;
    always @ (posedge clk) reg39 <= reset ? 1'b0 : sel57;
    assign eq41 = reg39 == 1'b0;
    assign proxy42 = eq41;
    assign and43 = io_in_valid & io_in_ready10;
    assign sel46 = and43 ? 1'b1 : reg39;
    assign sel47 = and43 ? proxy7 : proxy19;
    assign sel48 = and43 ? proxy6 : reg32;
    assign gt49 = proxy19 > reg32;
    assign sub51 = reg32 - proxy19;
    assign sel53 = gt49 ? proxy19 : sub51;
    assign sel54 = reg39 ? sel53 : sel48;
    assign sel55 = and56 ? reg32 : sel47;
    assign and56 = reg39 & gt49;
    assign sel57 = io_out_valid13 ? 1'b0 : sel46;
    assign eq59 = 16'h0 == reg32;
    assign and61 = eq59 & reg39;
    assign proxy62 = and61;

    assign io_in_ready = io_in_ready10;
    assign io_out_valid = io_out_valid13;
    assign io_out_data = io_out_data16;

endmodule
