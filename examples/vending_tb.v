`timescale 1ns/1ns
`include "vending.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg clk = 0;
    reg reset = 0;
    reg coin = 1;
    wire valid;

    VendingMachine device(clk, reset, coin, valid);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tcoin\tvalid");
        $monitor("%3d\t%b\t%b\t%h\t%h", $time, clk, reset, coin, valid);

        #0 reset = 1;
        #1 reset = 1;
        #1 reset = 0;

        #8 `check(valid == 1);
            $finish;
    end

endmodule
