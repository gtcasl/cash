`timescale 1ns/1ns
`include "gcd.v"

`define check(condition) if (!(condition)) $display("FAILED!")

module testbench();

    reg        clk = 0;
    reg        rst = 0;
    reg        in_valid;
    reg[31:0]  in_data;
    wire       in_ready;
    wire       out_valid;
    wire[15:0] out_data;

    GCD gcd(clk, rst, in_valid, in_data, in_ready, out_valid, out_data);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tin_val\tin_data\t\tin_rdy\tout_val\tout_data");
        $monitor("%3d\t%b\t%b\t%b\t%h\t%b\t%b\t%h", $time, clk, rst, in_valid, in_data, in_ready, out_valid, out_data);

        #0 rst = 1;
        #1 rst = 1;
        #1 rst = 0;

        #0 in_data  = 32'h0030_0020;
           in_valid = 1;

        #11 `check(out_valid == 1);
            `check(out_data == 16);
            $finish;
    end

endmodule
