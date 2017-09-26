`include "fifo.v"
`timescale 1ns/1ns

module testbench();

    reg       clk   = 0;
    reg       reset = 0;
    reg[1:0]  din   = 0;
    reg       push  = 0;
    reg       pop   = 0;
    wire[1:0] dout;
    wire      empty;
    wire      full;

    fifo m1(clk, reset, din, push, pop, dout, empty, full);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0,testbench);

        $display ("time\tclk\treset\tdin\tpush\tpop\tdout\tempty\tfull");
        $monitor("%3d\t%b\t%b\t%h\t%b\t%b\t%h\t%b\t%b", $time, clk, reset, din, push, pop, dout, empty, full);

        #0 reset  = 1;
        #1 reset  = 1;
        #1 reset  = 0;

        #0 din    = 1;
           push   = 1;
        #2 din    = 2;
           push   = 1;
        #2 din    = 0;
           push   = 0;
	#2 pop    = 1;
	#2 pop    = 1;
	#2 pop    = 0;
        #20 $finish;
    end

endmodule
