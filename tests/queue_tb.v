`timescale 1ns/1ns
`include "queue.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg       clk = 0;
    reg       reset = 0;
    reg[3:0]  din = 0;
    reg       enq_val = 0;
    wire      enq_rdy;
    wire[3:0] dout;
    wire      deq_val;
    reg       deq_rdy = 0;

    QueueWrapper queue(clk, reset, din, enq_val, enq_rdy, dout, deq_val, deq_rdy);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tdin\tenq\tdeq\tdout\tenq_rdy\tdeq_val");
        $monitor("%3d\t%b\t%b\t%h\t%b\t%b\t%h\t%b\t%b", $time, clk, reset, din, enq_val, deq_rdy, dout, enq_rdy, deq_val);

        #0 reset = 1;
        #1 reset = 1;
        #1 reset = 0;

        #0 din = 1;
           enq_val = 1;
           `check(deq_val == 0);
           `check(enq_rdy == 1);

        #2 din = 2;
           enq_val = 1;
           `check(deq_val == 1);
           `check(enq_rdy == 1);
           `check(dout == 1);

        #2 din = 0;
           enq_val = 0;
           `check(deq_val == 1);
           `check(enq_rdy == 0);
           `check(dout == 1);

        #2 deq_rdy = 1;
          `check(deq_val == 1);
          `check(enq_rdy == 0);
          `check(dout == 1);

        #2 deq_rdy = 1;
           `check(deq_val == 1);
           `check(enq_rdy == 1);
           `check(dout == 2);

        #2 deq_rdy = 0;
           `check(deq_val == 0);
           `check(enq_rdy == 1);
           `check(dout == 1);

        #2 $finish;
    end

endmodule
