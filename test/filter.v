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
  wire[16:0] zext24;
  wire[16:0] zext22;
  wire[16:0] sll28;
  wire[16:0] or31;
  reg reg46;
  reg[15:0] reg37;

  assign zext24 = {{1{1'b0}}, io_x_data};
  assign zext22 = {{16{1'b0}}, io_x_parity};
  assign sll28 = zext24 << 32'h1;
  assign or31 = sll28 | zext22;
  always @ (posedge clk) begin
    reg46 <= io_x_valid;
  end
  always @ (posedge clk) begin
    reg37 <= or31[15:0];
  end

  assign io_y_data = reg37;
  assign io_y_valid = reg46;
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
  wire bindin36;
  wire bindin33;
  wire[15:0] bindin30;
  wire bindin29;
  wire bindin28;
  wire bindout51;
  wire bindout46;
  wire[15:0] bindout41;
  wire bindin63;
  wire bindin60;
  wire[15:0] bindin57;
  wire bindin56;
  wire bindin55;
  wire bindout78;
  wire bindout73;
  wire[15:0] bindout68;

  assign bindin36 = io_x_parity;
  assign bindin33 = io_x_valid;
  assign bindin30 = io_x_data;
  assign bindin29 = reset;
  assign bindin28 = clk;
  Filter __module220__(.clk(bindin28), .reset(bindin29), .io_x_data(bindin30), .io_x_valid(bindin33), .io_x_parity(bindin36), .io_y_data(bindout41), .io_y_valid(bindout46), .io_y_parity(bindout51));
  assign bindin63 = bindout51;
  assign bindin60 = bindout46;
  assign bindin57 = bindout41;
  assign bindin56 = reset;
  assign bindin55 = clk;
  Filter __module221__(.clk(bindin55), .reset(bindin56), .io_x_data(bindin57), .io_x_valid(bindin60), .io_x_parity(bindin63), .io_y_data(bindout68), .io_y_valid(bindout73), .io_y_parity(bindout78));

  assign io_y_data = bindout68;
  assign io_y_valid = bindout73;
  assign io_y_parity = bindout78;

endmodule
