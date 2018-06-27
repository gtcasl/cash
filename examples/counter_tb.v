`timescale 1ns/1ns
`include "counter.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg       clk = 0;
    reg       reset = 0;
    wire[3:0] out;

    Counter counter(clk, reset, out);
	
    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tout");
        $monitor("%3d\t%b\t%b\t%h", $time, clk, reset, out);

        #0 reset = 0;
        #1 reset = 1;
        #1 reset = 0;

        #20 `check(out == 12);
            $finish;
    end

endmodule
