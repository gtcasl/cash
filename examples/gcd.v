module GCD(
  input wire clk,
  input wire reset,
  input wire io_in_valid,
  input wire[31:0] io_in_data,
  output wire io_in_ready,
  output wire io_out_valid,
  output wire[15:0] io_out_data
);
  wire[15:0] sub50;
  wire[15:0] sel47; // gcd.cpp(21)
  wire[15:0] sel52; // gcd.cpp(28)
  wire[15:0] sel53; // gcd.cpp(27)
  wire and41;
  wire gt48;
  wire sel45; // gcd.cpp(21)
  reg[15:0] reg31;
  wire sel57; // gcd.cpp(36)
  wire[15:0] sel46; // gcd.cpp(21)
  wire and55;
  wire[15:0] sel54; // gcd.cpp(28)
  wire eq60;
  reg reg36;
  reg[15:0] reg25;
  wire and62;
  wire eq39;

  assign sub50 = reg31 - reg25;
  assign sel47 = and41 ? io_in_data[31:16] : reg31;
  assign sel52 = gt48 ? reg25 : sub50;
  assign sel53 = reg36 ? sel52 : sel47;
  assign and41 = io_in_valid & eq39;
  assign gt48 = reg25 > reg31;
  assign sel45 = and41 ? 1'h1 : reg36;
  always @ (posedge clk) begin
    reg31 <= sel53;
  end
  assign sel57 = and62 ? 1'h0 : sel45;
  assign sel46 = and41 ? io_in_data[15:0] : reg25;
  assign and55 = reg36 & gt48;
  assign sel54 = and55 ? reg31 : sel46;
  assign eq60 = 16'h0 == reg31;
  always @ (posedge clk) begin
    reg36 <= reset ? 1'h0 : sel57;
  end
  always @ (posedge clk) begin
    reg25 <= sel54;
  end
  assign and62 = eq60 & reg36;
  assign eq39 = 1'h0 == reg36;

  assign io_in_ready = eq39;
  assign io_out_valid = and62;
  assign io_out_data = reg25;

endmodule
