`include "cash.v"

module Counter(
    input wire clk,
    input wire reset,
    output wire[3:0] io_out
);
    wire[3:0] io_out2, proxy5, proxy7, add15, proxy16;
    reg[3:0] reg12;

    assign io_out2 = proxy5;
    assign proxy5 = reg12;
    assign proxy7 = proxy16;
    always @ (posedge clk)
    reg12 <= reset ? 4'h0 : proxy7;
    assign add15 = proxy5 + 4'h1;
    assign proxy16 = add15;

    assign io_out = io_out2;

endmodule
