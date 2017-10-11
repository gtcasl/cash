`timescale 1ns/1ns
`include "counter.v"

`define assert(condition) if (!(condition)) begin $display("assertion FAILED!"); $finish_and_return(1); end

module testbench();

    reg       clk   = 0;
    reg       reset = 0;
    wire[3:0] out;

    //AES_ExpandKey x(clk, reset, out);
    //AES_Encrypt e1(clk, reset, out);
    //AES_Decrypt d1(clk, reset, out);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        //$display ("time\tclk\treset\tout");
        //$monitor("%3d\t%b\t%b\t%h", $time, clk, reset, out);

        #0 reset  = 1;
        #1 reset  = 1;
        #1 reset  = 0;

        #20 $finish;
    end

endmodule
