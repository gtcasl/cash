module FiFo(
  input wire clk,
  input wire reset,
  input wire[1:0] io_din,
  input wire io_push,
  input wire io_pop,
  output wire[1:0] io_dout,
  output wire io_empty,
  output wire io_full
);
  wire eq38;
  wire[1:0] add49;
  wire and40;
  wire[1:0] add54;
  wire eq43;
  wire[1:0] sel51;
  wire[1:0] sel56;
  wire and45;
  wire proxy35; // v12 - fifo.cpp(22)
  wire ne67;
  wire eq69;
  reg[1:0] reg23; // v7 - fifo.cpp(19)
  reg[1:0] reg31; // v9 - fifo.cpp(19)
  wire proxy33; // v11 - fifo.cpp(21)
  reg[1:0] mem58[0:1];
  wire and71;
  wire eq63;

  assign eq38 = eq63 == 1'h0;
  assign add49 = reg23 + 2'h1;
  assign and40 = io_pop & eq38;
  assign add54 = reg31 + 2'h1;
  assign eq43 = and71 == 1'h0;
  assign sel51 = and40 ? add49 : reg23;
  assign sel56 = and45 ? add54 : reg31;
  assign and45 = io_push & eq43;
  assign proxy35 = reg31[0];
  assign ne67 = reg31[1] != reg23[1];
  assign eq69 = proxy35 == proxy33;
  always @ (posedge clk) begin
    reg23 <= sel51;
  end
  always @ (posedge clk) begin
    reg31 <= sel56;
  end
  assign proxy33 = reg23[0];
  always @(posedge clk) begin
    if (and45) begin
      mem58[proxy35] = io_din;
    end
  end
  assign and71 = eq69 & ne67;
  assign eq63 = reg31 == reg23;

  assign io_dout = mem58[proxy33];
  assign io_empty = eq63;
  assign io_full = and71;

endmodule
