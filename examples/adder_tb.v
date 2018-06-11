`timescale 1ns/1ns
`include "adder.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg cin       = 1;
    reg[1:0]  lhs = 1;
    reg[1:0]  rhs = 3;    
    wire[1:0] out;
    wire      cout;

    Adder adder(cin, lhs, rhs, out, cout);

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tlhs\trhs\tcin\tout\tcout");
        $monitor("%3d\t%h\t%h\t%b\t%h\t%b", $time, lhs, rhs, cin, out, cout);

        #1 `check(out == 1);
           `check(cout == 1);
           $finish;
    end

endmodule
