module ch_queue(
  input wire clk,
  input wire reset,
  input wire io_enq_valid,
  input wire[3:0] io_enq_data,
  input wire io_deq_ready,
  output wire io_enq_ready,
  output wire io_deq_valid,
  output wire[3:0] io_deq_data,
  output wire[1:0] io_size
);
  wire[1:0] add47;
  wire and41;
  wire[1:0] add52;
  wire[1:0] sel49;
  wire[1:0] sel54;
  wire and43;
  wire proxy40; // v2231 - /home/blaise/dev/cash/src/htl/queue.h(28)
  reg[1:0] reg29;
  reg[1:0] reg35;
  wire eq64;
  wire ne66;
  wire proxy38; // v2230 - /home/blaise/dev/cash/src/htl/queue.h(27)
  reg[3:0] mem56[0:1];
  wire[1:0] sub70;
  wire ne60;
  wire or68;

  assign add47 = reg29 + 2'h1;
  assign and41 = io_deq_ready & ne60;
  assign add52 = reg35 + 2'h1;
  assign sel49 = and41 ? add47 : reg29;
  assign sel54 = and43 ? add52 : reg35;
  assign and43 = io_enq_valid & or68;
  assign proxy40 = reg35[0];
  always @ (posedge clk) begin
    reg29 <= sel49;
  end
  always @ (posedge clk) begin
    reg35 <= sel54;
  end
  assign eq64 = reg35[1] == reg29[1];
  assign ne66 = proxy40 != proxy38;
  assign proxy38 = reg29[0];
  always @(posedge clk) begin
    if (and43) begin
      mem56[proxy40] = io_enq_data;
    end
  end
  assign sub70 = reg35 - reg29;
  assign ne60 = reg35 != reg29;
  assign or68 = ne66 | eq64;

  assign io_enq_ready = or68;
  assign io_deq_valid = ne60;
  assign io_deq_data = mem56[proxy38];
  assign io_size = sub70;

endmodule

module QueueWrapper(
  input wire clk,
  input wire reset,
  input wire io_enq_valid,
  input wire[3:0] io_enq_data,
  input wire io_deq_ready,
  output wire io_enq_ready,
  output wire io_deq_valid,
  output wire[3:0] io_deq_data
);
  wire bindin54;
  wire[3:0] bindin36;
  wire bindin33;
  wire bindin32;
  wire bindin31;
  wire[3:0] bindout51;
  wire bindout46;
  wire bindout41;

  assign bindin54 = io_deq_ready;
  assign bindin36 = io_enq_data;
  assign bindin33 = io_enq_valid;
  assign bindin32 = reset;
  assign bindin31 = clk;
  ch_queue __module218__(.clk(bindin31), .reset(bindin32), .io_enq_valid(bindin33), .io_enq_data(bindin36), .io_deq_ready(bindin54), .io_enq_ready(bindout41), .io_deq_valid(bindout46), .io_deq_data(bindout51));

  assign io_enq_ready = bindout41;
  assign io_deq_valid = bindout46;
  assign io_deq_data = bindout51;

endmodule
