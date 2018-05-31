`timescale 1ns/1ns
`include "vending.v"

`define assert(condition) if (!(condition)) begin $display("assertion FAILED!"); $finish_and_return(1); end

module testbench();

    reg clk = 0;
    reg rst = 0;
    reg[1:0] coin = 1;
    wire valid;

    VendingMachine device(clk, reset, coin, valid);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tnickel\tdime\tvalid");
        $monitor("%3d\t%b\t%b\t%h\t%b", $time, clk, rst, coin, valid);

        #0 rst = 1;
        #1 rst = 1;
        #1 rst = 0;

        #8 `assert(valid == 1);
            $finish;
    end

endmodule
