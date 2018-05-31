`timescale 1ns/1ns
`include "counter.v"

`define assert(condition) if (!(condition)) begin $display("assertion FAILED!"); $finish_and_return(1); end

module testbench();

    reg       clk = 0;
    reg       rst = 0;
    wire[3:0] out;

    Counter counter(clk, rst, out);
	
    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tout");
        $monitor("%3d\t%b\t%b\t%h", $time, clk, rst, out);

        #0 rst = 0;
        #1 rst = 1;
        #1 rst = 0;

        #20 `assert(out == 12);
            $finish;
    end

endmodule
