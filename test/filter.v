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
  wire[16:0] proxy26; // v2185 - module.cpp(71)
  wire[16:0] sll29;
  wire[16:0] proxy22; // v2183 - module.cpp(72)
  wire[16:0] or31;
  reg reg45;
  reg[15:0] reg37;

  assign proxy26 = {1'h0, io_x_data};
  assign sll29 = proxy26 << 17'h1;
  assign proxy22 = {16'h0, io_x_parity};
  assign or31 = sll29 | proxy22;
  always @ (posedge clk) begin
    reg45 <= io_x_valid;
  end
  always @ (posedge clk) begin
    reg37 <= or31[15:0];
  end

  assign io_y_data = reg37;
  assign io_y_valid = reg45;
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
  wire bindin33;
  wire bindin30;
  wire[15:0] bindin27;
  wire bindin26;
  wire bindin25;
  wire bindout42;
  wire bindout39;
  wire[15:0] bindout36;
  wire bindin54;
  wire bindin51;
  wire[15:0] bindin48;
  wire bindin47;
  wire bindin46;
  wire bindout63;
  wire bindout60;
  wire[15:0] bindout57;

  assign bindin33 = io_x_parity;
  assign bindin30 = io_x_valid;
  assign bindin27 = io_x_data;
  assign bindin26 = reset;
  assign bindin25 = clk;
  Filter __module212__(.clk(bindin25), .reset(bindin26), .io_x_data(bindin27), .io_x_valid(bindin30), .io_x_parity(bindin33), .io_y_data(bindout36), .io_y_valid(bindout39), .io_y_parity(bindout42));
  assign bindin54 = bindout42;
  assign bindin51 = bindout39;
  assign bindin48 = bindout36;
  assign bindin47 = reset;
  assign bindin46 = clk;
  Filter __module213__(.clk(bindin46), .reset(bindin47), .io_x_data(bindin48), .io_x_valid(bindin51), .io_x_parity(bindin54), .io_y_data(bindout57), .io_y_valid(bindout60), .io_y_parity(bindout63));

  assign io_y_data = bindout57;
  assign io_y_valid = bindout60;
  assign io_y_parity = bindout63;

endmodule
