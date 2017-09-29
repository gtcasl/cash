`timescale 1ns/1ns
`include "counter.v"

module testbench();

    reg       clk   = 0;
    reg       reset = 0;
    wire[3:0] out;

    counter m1(clk, reset, out);
	
    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0,testbench);

        $display ("time\tclk\treset\tout");
        $monitor("%3d\t%b\t%b\t%h", $time, clk, reset, out);

        #0 reset  = 1;
        #1 reset  = 1;
        #1 reset  = 0;

        #20 $finish;
    end

endmodule
