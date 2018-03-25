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
  wire[16:0] proxy26; // v2189 - module.cpp(71)
  wire[16:0] sll29;
  wire[16:0] proxy22; // v2187 - module.cpp(72)
  wire[16:0] or31;
  reg reg42;
  reg[15:0] reg38;

  assign proxy26 = {1'h0, io_x_data};
  assign sll29 = proxy26 << 17'h1;
  assign proxy22 = {16'h0, io_x_parity};
  assign or31 = sll29 | proxy22;
  always @ (posedge clk) begin
    reg42 <= reset ? 1'h0 : io_x_valid;
  end
  always @ (posedge clk) begin
    reg38 <= reset ? 16'h0 : or31[15:0];
  end

  assign io_y_data = reg38;
  assign io_y_valid = reg42;
  assign io_y_parity = or31[16];

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
  wire bindin32;
  wire bindin29;
  wire[15:0] bindin26;
  wire bindin25;
  wire bindin23;
  wire bindout41;
  wire bindout38;
  wire[15:0] bindout35;
  wire bindin53;
  wire bindin50;
  wire[15:0] bindin47;
  wire bindin46;
  wire bindin45;
  wire bindout62;
  wire bindout59;
  wire[15:0] bindout56;

  assign bindin32 = io_x_parity;
  assign bindin29 = io_x_valid;
  assign bindin26 = io_x_data;
  assign bindin25 = reset;
  assign bindin23 = clk;
  Filter __module212__(.clk(bindin23), .reset(bindin25), .io_x_data(bindin26), .io_x_valid(bindin29), .io_x_parity(bindin32), .io_y_data(bindout35), .io_y_valid(bindout38), .io_y_parity(bindout41));
  assign bindin53 = bindout41;
  assign bindin50 = bindout38;
  assign bindin47 = bindout35;
  assign bindin46 = reset;
  assign bindin45 = clk;
  Filter __module213__(.clk(bindin45), .reset(bindin46), .io_x_data(bindin47), .io_x_valid(bindin50), .io_x_parity(bindin53), .io_y_data(bindout56), .io_y_valid(bindout59), .io_y_parity(bindout62));

  assign io_y_data = bindout56;
  assign io_y_valid = bindout59;
  assign io_y_parity = bindout62;

endmodule
