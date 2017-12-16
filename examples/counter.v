`include "cash.v"

module Counter(
    input wire clk,
    input wire reset,
    output wire[3:0] io_out
);
    wire[3:0] io_out2; // counter.cpp(8) #1
    wire[3:0] proxy5; // counter.cpp(14) #2
    reg[3:0] reg11; // counter.cpp(14) #2
    wire[3:0] add13;

    assign io_out2 = proxy5;
    assign proxy5 = reg11;
    always @ (posedge clk) reg11 <= reset ? 4'h0 : add13;
    assign add13 = proxy5 + 4'h1;

    assign io_out = io_out2;

endmodule
