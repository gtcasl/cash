`timescale 1ns/1ns
`include "queue.v"

`define check(condition) if (!(condition === 1'b1)) $display("FAILED!")

module testbench();

    reg       clk = 0;
    reg       reset = 0;
    reg[3:0]  din = 0;
    reg       enq = 0;
    reg       deq = 0;
    wire[3:0] dout;
    wire      enq_ready;
    wire      deq_valid;

    QueueWrapper queue(clk, reset, enq, din, deq, enq_ready, deq_valid, dout);

    always begin
        #1 clk = !clk;
    end

    initial begin
        $dumpfile("testbench.vcd");
        $dumpvars(0, testbench);

        $display ("time\tclk\trst\tdin\tenq\tdeq\tdout\tenq_rdy\tdeq_val");
        $monitor("%3d\t%b\t%b\t%h\t%b\t%b\t%h\t%b\t%b", $time, clk, reset, din, enq, deq, dout, enq_ready, deq_valid);

        #0 reset = 1;
        #1 reset = 1;
        #1 reset = 0;

        #0 din = 1;
           enq = 1;
           `check(deq_valid == 0);
           `check(enq_ready == 1);

        #2 din = 2;
           enq = 1;
           `check(deq_valid == 1);
           `check(enq_ready == 1);
           `check(dout == 1);

        #2 din = 0;
           enq = 0;
           `check(deq_valid == 1);
           `check(enq_ready == 0);
           `check(dout == 1);

        #2 deq = 1;
          `check(deq_valid == 1);
          `check(enq_ready == 0);
          `check(dout == 1);

        #2 deq = 1;
           `check(deq_valid == 1);
           `check(enq_ready == 1);
           `check(dout == 2);

        #2 deq = 0;
           `check(deq_valid == 0);
           `check(enq_ready == 1);
           `check(dout == 1);

        #2 $finish;
    end

endmodule
