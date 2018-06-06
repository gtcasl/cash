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
  reg[1:0] reg23; // fifo.cpp(19)
  reg[1:0] reg29; // fifo.cpp(19)
  wire proxy32; // v12 - fifo.cpp(21)
  wire proxy34; // v13 - fifo.cpp(22)
  wire eq37;
  wire and39;
  wire eq42;
  wire and44;
  wire[1:0] add48;
  wire[1:0] sel50;
  wire[1:0] add53;
  wire[1:0] sel55;
  reg[1:0] mem57[0:1]; // fifo.cpp(30)
  wire eq61;
  wire ne65;
  wire eq67;
  wire and69;

  always @ (posedge clk) begin
    reg23 <= sel50;
  end
  always @ (posedge clk) begin
    reg29 <= sel55;
  end
  assign proxy32 = reg23[0];
  assign proxy34 = reg29[0];
  assign eq37 = 1'h0 == eq61;
  assign and39 = io_pop & eq37;
  assign eq42 = 1'h0 == and69;
  assign and44 = io_push & eq42;
  assign add48 = reg23 + 2'h1;
  assign sel50 = and39 ? add48 : reg23;
  assign add53 = reg29 + 2'h1;
  assign sel55 = and44 ? add53 : reg29;
  always @(posedge clk) begin
    if (and44) begin
      mem57[proxy34] = io_din;
    end
  end
  assign eq61 = reg29 == reg23;
  assign ne65 = reg29[1] != reg23[1];
  assign eq67 = proxy34 == proxy32;
  assign and69 = eq67 & ne65;

  assign io_dout = mem57[proxy32];
  assign io_empty = eq61;
  assign io_full = and69;

endmodule
