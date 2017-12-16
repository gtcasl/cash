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
    wire[1:0] io_dout11; // fifo.cpp(8) #4
    wire[1:0] proxy20; // fifo.cpp(19) #7
    reg[1:0] reg26; // fifo.cpp(19) #7
    wire[1:0] proxy28; // fifo.cpp(19) #10
    reg[1:0] reg31; // fifo.cpp(19) #10
    wire proxy33; // fifo.cpp(21) #13
    wire proxy35; // fifo.cpp(22) #14
    wire inv36;
    wire and37;
    wire inv38;
    wire and39;
    wire[1:0] add41;
    wire[1:0] sel42;
    wire[1:0] add43;
    wire[1:0] sel44;
    reg[1:0] mem45[0:1];
    wire[1:0] proxy47;
    wire[1:0] sel48;
    wire eq50;
    wire proxy51; // fifo.cpp(19) #28
    wire proxy52; // fifo.cpp(19) #29
    wire ne53;
    wire eq54;
    wire and55;

    assign io_dout11 = mem45[proxy33];
    assign proxy20 = reg26;
    always @ (posedge clk) reg26 <= reset ? 2'b0 : sel42;
    assign proxy28 = reg31;
    always @ (posedge clk) reg31 <= reset ? 2'b0 : sel44;
    assign proxy33 = proxy20[0];
    assign proxy35 = proxy28[0];
    assign inv36 = ~eq50;
    assign and37 = io_pop & inv36;
    assign inv38 = ~and55;
    assign and39 = io_push & inv38;
    assign add41 = proxy20 + 2'b1;
    assign sel42 = and37 ? add41 : proxy20;
    assign add43 = proxy28 + 2'b1;
    assign sel44 = and39 ? add43 : proxy28;
    always @(posedge clk) mem45[proxy35] = proxy47;
    assign proxy47 = sel48;
    assign sel48 = and39 ? io_din : mem45[proxy35];
    assign eq50 = proxy28 == proxy20;
    assign proxy51 = proxy20[1];
    assign proxy52 = proxy28[1];
    assign ne53 = proxy52 != proxy51;
    assign eq54 = proxy35 == proxy33;
    assign and55 = eq54 & ne53;

    assign io_dout = io_dout11;
    assign io_empty = eq50;
    assign io_full = and55;

endmodule
