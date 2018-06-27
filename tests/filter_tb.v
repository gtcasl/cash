`timescale 1ns/1ns
`include "filter.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg         clk      = 0;
    reg[15:0]   x_data   = 0;
    reg         x_valid  = 0;
    reg         x_parity = 0;
    wire[15:0]  y_data;
    wire        y_valid;
    wire        y_parity;

    FilterBlock filter(clk, x_data, x_valid, x_parity, y_data, y_valid, y_parity);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\txdat\txval\txpar\tydat\tyval\typar");
        $monitor("%3d\t%b\t%h\t%b\t%b\t%h\t%b\t%b", $time, clk, x_data, x_valid, x_parity, y_data, y_valid, y_parity);

        #4 `check(y_data   == 12);
           `check(y_valid  == 1);
           `check(y_parity == 0);

        #2 $finish;
    end

endmodule
