`timescale 1ns/1ns
`include "fastmult.v"

`define check(condition) if (!(condition)) $display("FAILED!")

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

        #1 `check(out == 6);
           $finish;
    end

endmodule
