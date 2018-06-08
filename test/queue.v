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
  reg[1:0] reg20; // /home/blaise/dev/cash/src/htl/queue.h(25)
  reg[1:0] reg26; // /home/blaise/dev/cash/src/htl/queue.h(25)
  wire proxy29; // /home/blaise/dev/cash/src/htl/queue.h(27)
  wire proxy31; // /home/blaise/dev/cash/src/htl/queue.h(28)
  wire and32;
  wire and34;
  wire[1:0] add38;
  wire[1:0] sel40;
  wire[1:0] add43;
  wire[1:0] sel45;
  reg[3:0] mem47[0:1]; // /home/blaise/dev/cash/src/htl/queue.h(36)
  wire ne51;
  wire eq55;
  wire ne57;
  wire or59;
  wire[1:0] sub61;

  always @ (posedge clk) begin
    reg20 <= sel40;
  end
  always @ (posedge clk) begin
    reg26 <= sel45;
  end
  assign proxy29 = reg20[0];
  assign proxy31 = reg26[0];
  assign and32 = io_deq_ready & ne51;
  assign and34 = io_enq_valid & or59;
  assign add38 = reg20 + 2'h1;
  assign sel40 = and32 ? add38 : reg20;
  assign add43 = reg26 + 2'h1;
  assign sel45 = and34 ? add43 : reg26;
  always @(posedge clk) begin
    if (and34) begin
      mem47[proxy31] = io_enq_data;
    end
  end
  assign ne51 = reg26 != reg20;
  assign eq55 = reg26[1] == reg20[1];
  assign ne57 = proxy31 != proxy29;
  assign or59 = ne57 | eq55;
  assign sub61 = reg26 - reg20;

  assign io_enq_ready = or59;
  assign io_deq_valid = ne51;
  assign io_deq_data = mem47[proxy29];
  assign io_size = sub61;

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
  wire bindin22; // /home/blaise/dev/cash/src/module.h(33)
  wire bindin23; // /home/blaise/dev/cash/src/module.h(33)
  wire bindin24; // /home/blaise/dev/cash/src/module.h(33)
  wire[3:0] bindin27; // /home/blaise/dev/cash/src/module.h(33)
  wire bindout30; // /home/blaise/dev/cash/src/module.h(33)
  wire bindout33; // /home/blaise/dev/cash/src/module.h(33)
  wire[3:0] bindout36; // /home/blaise/dev/cash/src/module.h(33)
  wire bindin39; // /home/blaise/dev/cash/src/module.h(33)

  assign bindin22 = clk;
  assign bindin23 = reset;
  ch_queue __module227__(.clk(bindin22), .reset(bindin23), .io_enq_valid(bindin24), .io_enq_data(bindin27), .io_deq_ready(bindin39), .io_enq_ready(bindout30), .io_deq_valid(bindout33), .io_deq_data(bindout36));
  assign bindin24 = io_enq_valid;
  assign bindin27 = io_enq_data;
  assign bindin39 = io_deq_ready;

  assign io_enq_ready = bindout30;
  assign io_deq_valid = bindout33;
  assign io_deq_data = bindout36;

endmodule
