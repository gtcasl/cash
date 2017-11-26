`include "cash.v"

module Counter(
    input wire clk,
    input wire reset,
    output wire[3:0] io_out
);
    reg[3:0] r9;
    wire[3:0] a13;

    always @ (posedge clk)
    r9 <= reset ? 4'h0 : a13;
    assign a13 = r9 + 4'h1;

    assign io_out = r9;

endmodule
