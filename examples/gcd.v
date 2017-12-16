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
    wire[31:0] io_in_data5; // gcd.cpp(10) #2
    wire[15:0] proxy6; // gcd.cpp(10) #3
    wire[15:0] proxy7; // gcd.cpp(10) #4
    wire[15:0] io_out_data16; // gcd.cpp(10) #7
    wire[15:0] proxy19; // gcd.cpp(16) #8
    reg[15:0] reg25; // gcd.cpp(16) #8
    reg[15:0] reg30; // gcd.cpp(16) #11
    reg reg36; // gcd.cpp(17) #14
    wire inv37;
    wire and38;
    wire[15:0] sel39;
    wire[15:0] sel40;
    wire sel42;
    wire gt43;
    wire and44;
    wire[15:0] sel45;
    wire[15:0] sel46;
    wire[15:0] sub47;
    wire inv48;
    wire and49;
    wire[15:0] sel50;
    wire sel51;
    wire eq52;
    wire and53;

    assign io_in_data5 = io_in_data;
    assign proxy6 = io_in_data5[31:16];
    assign proxy7 = io_in_data5[15:0];
    assign io_out_data16 = proxy19;
    assign proxy19 = reg25;
    always @ (posedge clk) reg25 <= reset ? 16'h0 : sel45;
    always @ (posedge clk) reg30 <= reset ? 16'h0 : sel50;
    always @ (posedge clk) reg36 <= reset ? 1'b0 : sel51;
    assign inv37 = ~reg36;
    assign and38 = io_in_valid & inv37;
    assign sel39 = and38 ? proxy7 : proxy19;
    assign sel40 = and38 ? proxy6 : reg30;
    assign sel42 = and38 ? 1'b1 : reg36;
    assign gt43 = proxy19 > reg30;
    assign and44 = reg36 & gt43;
    assign sel45 = and44 ? reg30 : sel39;
    assign sel46 = and44 ? proxy19 : sel40;
    assign sub47 = reg30 - proxy19;
    assign inv48 = ~gt43;
    assign and49 = reg36 & inv48;
    assign sel50 = and49 ? sub47 : sel46;
    assign sel51 = and53 ? 1'b0 : sel42;
    assign eq52 = 16'h0 == reg30;
    assign and53 = eq52 & reg36;

    assign io_in_ready = inv37;
    assign io_out_valid = and53;
    assign io_out_data = io_out_data16;

endmodule
