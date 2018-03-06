`timescale 1ns/1ns
`include "fastmult.v"

`define assert(condition) if (!(condition)) begin $display("assertion FAILED!"); $finish_and_return(1); end

module testbench();

    reg[3:0]  lhs = 2;
    reg[3:0]  rhs = 3;
    wire[7:0] out;

    FastMult fastmult(lhs, rhs, out);

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tlhs\trhs\tout");
        $monitor("%3d\t%h\t%h\t%h", $time, lhs, rhs, out);

        #1 `assert(out == 6);
           $finish;
    end

endmodule
