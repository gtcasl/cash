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
  wire proxy37; // v14 - fifo.cpp(22)
  wire ne69;
  wire eq71;
  reg[1:0] reg27; // v7 - fifo.cpp(19)
  reg[1:0] reg33; // v10 - fifo.cpp(19)
  wire proxy35; // v13 - fifo.cpp(21)
  reg[1:0] mem60[0:1];
  wire and73;
  wire eq65;

  assign eq40 = eq65 == 1'h0;
  assign add51 = reg27 + 2'h1;
  assign and42 = io_pop & eq40;
  assign add56 = reg33 + 2'h1;
  assign eq45 = and73 == 1'h0;
  assign sel53 = and42 ? add51 : reg27;
  assign sel58 = and47 ? add56 : reg33;
  assign and47 = io_push & eq45;
  assign proxy37 = reg33[0];
  assign ne69 = reg33[1] != reg27[1];
  assign eq71 = proxy37 == proxy35;
  always @ (posedge clk) begin
    reg27 <= reset ? 2'h0 : sel53;
  end
  always @ (posedge clk) begin
    reg33 <= reset ? 2'h0 : sel58;
  end
  assign proxy35 = reg27[0];
  always @(posedge clk) begin
    if (and47) begin
      mem60[proxy37] = io_din;
    end
  end
  assign and73 = eq71 & ne69;
  assign eq65 = reg33 == reg27;

  assign io_dout = mem60[proxy35];
  assign io_empty = eq65;
  assign io_full = and73;

endmodule
