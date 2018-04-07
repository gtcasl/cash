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
  wire eq40;
  wire[1:0] add51;
  wire and42;
  wire[1:0] add56;
  wire eq45;
  wire[1:0] sel53;
  wire[1:0] sel58;
  wire and47;
  wire proxy37; // v13 - fifo.cpp(22)
  wire ne68;
  wire eq70;
  reg[1:0] reg26;
  reg[1:0] reg32;
  wire proxy35; // v12 - fifo.cpp(21)
  reg[1:0] mem60[0:1];
  wire and72;
  wire eq64;

  assign eq40 = 1'h0 == eq64;
  assign add51 = reg26 + 2'h1;
  assign and42 = io_pop & eq40;
  assign add56 = reg32 + 2'h1;
  assign eq45 = 1'h0 == and72;
  assign sel53 = and42 ? add51 : reg26;
  assign sel58 = and47 ? add56 : reg32;
  assign and47 = io_push & eq45;
  assign proxy37 = reg32[0];
  assign ne68 = reg32[1] != reg26[1];
  assign eq70 = proxy37 == proxy35;
  always @ (posedge clk) begin
    reg26 <= sel53;
  end
  always @ (posedge clk) begin
    reg32 <= sel58;
  end
  assign proxy35 = reg26[0];
  always @(posedge clk) begin
    if (and47) begin
      mem60[proxy37] = io_din;
    end
  end
  assign and72 = eq70 & ne68;
  assign eq64 = reg32 == reg26;

  assign io_dout = mem60[proxy35];
  assign io_empty = eq64;
  assign io_full = and72;

endmodule
