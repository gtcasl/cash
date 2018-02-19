`include "cash.v"

module Counter(
    input wire clk,
    input wire reset,
    output wire[3:0] io_out
);
    wire[3:0] io_out2; // counter.cpp(8) @var1
    wire[3:0] proxy5; // counter.cpp(14) @var2
    wire[3:0] proxy7; // /home/blaise/dev/cash/src/seq.h(17) @var3
    reg[3:0] reg12; // counter.cpp(14) @var2
    wire[3:0] add15;
    wire[3:0] proxy16; // @var6

    assign io_out2 = proxy5;
    assign proxy5 = reg12;
    assign proxy7 = proxy16;
    always @ (posedge clk) reg12 <= reset ? 4'h0 : proxy7;
    assign add15 = proxy5 + 4'h1;
    assign proxy16 = add15;

    assign io_out = io_out2;

endmodule
