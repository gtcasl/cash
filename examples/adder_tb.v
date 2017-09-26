`include "adder.v"
`timescale 1ns/1ns

module testbench();

    reg[1:0]  lhs = 1;
    reg[1:0]  rhs = 3;
    reg cin       = 1;
    wire[1:0] out;
    wire      cout;

    adder m1(lhs, rhs, cin, out, cout);

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0,testbench);

        $display ("time\tlhs\trhs\tcin\tout\tcout");
        $monitor("%3d\t%h\t%h\t%b\t%h\t%b", $time, lhs, rhs, cin, out, cout);

        #1 $finish;
    end

endmodule
