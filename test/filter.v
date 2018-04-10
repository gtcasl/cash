module Filter(
  input wire clk,
  input wire reset,
  input wire[15:0] io_x_data,
  input wire io_x_valid,
  input wire io_x_parity,
  output wire[15:0] io_y_data,
  output wire io_y_valid,
  output wire io_y_parity
);
  wire[16:0] proxy32; // v2155 - module.cpp(71)
  wire[16:0] sll35;
  wire[16:0] proxy28; // v2153 - module.cpp(72)
  wire[16:0] or37;
  reg reg52;
  reg[15:0] reg43;

  assign proxy32 = {1'h0, io_x_data};
  assign sll35 = proxy32 << 17'h1;
  assign proxy28 = {16'h0, io_x_parity};
  assign or37 = sll35 | proxy28;
  always @ (posedge clk) begin
    reg52 <= io_x_valid;
  end
  always @ (posedge clk) begin
    reg43 <= or37[15:0];
  end

  assign io_y_data = reg43;
  assign io_y_valid = reg52;
  assign io_y_parity = or37[16];

endmodule


module FilterBlock(
  input wire clk,
  input wire reset,
  input wire[15:0] io_x_data,
  input wire io_x_valid,
  input wire io_x_parity,
  output wire[15:0] io_y_data,
  output wire io_y_valid,
  output wire io_y_parity
);
  wire bindin39;
  wire bindin36;
  wire[15:0] bindin33;
  wire bindin32;
  wire bindin31;
  wire bindout54;
  wire bindout49;
  wire[15:0] bindout44;
  wire bindin66;
  wire bindin63;
  wire[15:0] bindin60;
  wire bindin59;
  wire bindin58;
  wire bindout81;
  wire bindout76;
  wire[15:0] bindout71;

  assign bindin39 = io_x_parity;
  assign bindin36 = io_x_valid;
  assign bindin33 = io_x_data;
  assign bindin32 = reset;
  assign bindin31 = clk;
  Filter __module215__(.clk(bindin31), .reset(bindin32), .io_x_data(bindin33), .io_x_valid(bindin36), .io_x_parity(bindin39), .io_y_data(bindout44), .io_y_valid(bindout49), .io_y_parity(bindout54));
  assign bindin66 = bindout54;
  assign bindin63 = bindout49;
  assign bindin60 = bindout44;
  assign bindin59 = reset;
  assign bindin58 = clk;
  Filter __module216__(.clk(bindin58), .reset(bindin59), .io_x_data(bindin60), .io_x_valid(bindin63), .io_x_parity(bindin66), .io_y_data(bindout71), .io_y_valid(bindout76), .io_y_parity(bindout81));

  assign io_y_data = bindout71;
  assign io_y_valid = bindout76;
  assign io_y_parity = bindout81;

endmodule
