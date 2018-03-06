`timescale 1ns/1ns
`include "adder.v"

`define assert(condition) if (!(condition)) begin $display("assertion FAILED!"); $finish_and_return(1); end

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

        #1 `assert(out == 1);
           `assert(cout == 1);
           $finish;
    end

endmodule
