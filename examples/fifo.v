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
  reg[1:0] reg17; // fifo.cpp(19)
  reg[1:0] reg23; // fifo.cpp(19)
  wire proxy26; // fifo.cpp(21)
  wire proxy28; // fifo.cpp(22)
  wire eq31;
  wire and33;
  wire eq36;
  wire and38;
  wire[1:0] add42;
  wire[1:0] sel44;
  wire[1:0] add47;
  wire[1:0] sel49;
  reg[1:0] mem51[0:1]; // fifo.cpp(30)
  wire eq55;
  wire ne59;
  wire eq61;
  wire and63;

  always @ (posedge clk) begin
    reg17 <= sel44;
  end
  always @ (posedge clk) begin
    reg23 <= sel49;
  end
  assign proxy26 = reg17[0];
  assign proxy28 = reg23[0];
  assign eq31 = 1'h0 == eq55;
  assign and33 = io_pop & eq31;
  assign eq36 = 1'h0 == and63;
  assign and38 = io_push & eq36;
  assign add42 = reg17 + 2'h1;
  assign sel44 = and33 ? add42 : reg17;
  assign add47 = reg23 + 2'h1;
  assign sel49 = and38 ? add47 : reg23;
  always @(posedge clk) begin
    if (and38) begin
      mem51[proxy28] = io_din;
    end
  end
  assign eq55 = reg23 == reg17;
  assign ne59 = reg23[1] != reg17[1];
  assign eq61 = proxy28 == proxy26;
  assign and63 = eq61 & ne59;

  assign io_dout = mem51[proxy26];
  assign io_empty = eq55;
  assign io_full = and63;

endmodule
