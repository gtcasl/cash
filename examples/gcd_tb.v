`timescale 1ns/1ns
`include "gcd.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg        clk = 0;
    reg        reset = 0;    
    reg[31:0]  in_data;
    reg        in_valid;
    wire       in_ready;    
    wire[15:0] out_data;
    wire       out_valid;

    GCD gcd(clk, reset, in_data, in_valid, in_ready, out_data, out_valid);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tin_val\tin_data\t\tin_rdy\tout_val\tout_data");
        $monitor("%3d\t%b\t%b\t%b\t%h\t%b\t%b\t%h", $time, clk, reset, in_valid, in_data, in_ready, out_valid, out_data);

        #0 reset = 1;
        #1 reset = 1;
        #1 reset = 0;

        #0 in_data  = 32'h0030_0020;
           in_valid = 1;

        #11 `check(out_valid == 1);
            `check(out_data == 16);
            $finish;
    end

endmodule
