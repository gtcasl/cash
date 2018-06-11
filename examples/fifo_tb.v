`timescale 1ns/1ns
`include "fifo.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg       clk   = 0;
    reg       rst   = 0;
    reg[1:0]  din   = 0;
    reg       push  = 0;
    reg       pop   = 0;
    wire[1:0] dout;
    wire      empty;
    wire      full;

    FiFo fifo(clk, rst, din, push, pop, dout, empty, full);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tdin\tpush\tpop\tdout\tempty\tfull");
        $monitor("%3d\t%b\t%b\t%h\t%b\t%b\t%h\t%b\t%b", $time, clk, rst, din, push, pop, dout, empty, full);

        #0 rst = 1;
        #1 rst = 1;
        #1 rst = 0;

        #0 din    = 1;
           push   = 1;
           `check(empty == 1);
           `check(full == 0);

        #2 din    = 2;
           push   = 1;
           `check(empty == 0);
           `check(full == 0);
           `check(dout == 1);

        #2 din    = 0;
           push   = 0;
           `check(empty == 0);
           `check(full == 1);
           `check(dout == 1);

        #2 pop    = 1;
          `check(empty == 0);
          `check(full == 1);
          `check(dout == 1);

        #2 pop    = 1;
           `check(empty == 0);
           `check(full == 0);
           `check(dout == 2);

        #2 pop    = 0;
           `check(empty == 1);
           `check(full == 0);
           `check(dout == 1);

        #2 $finish;
    end

endmodule
