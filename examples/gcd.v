module GCD(
  input wire clk,
  input wire reset,
  input wire io_in_valid,
  input wire[31:0] io_in_data,
  output wire io_in_ready,
  output wire io_out_valid,
  output wire[15:0] io_out_data
);
  reg[15:0] reg17; // gcd.cpp(16)
  reg[15:0] reg23; // gcd.cpp(16)
  reg reg28; // gcd.cpp(17)
  wire eq31;
  wire and33;
  wire sel37; // gcd.cpp(21)
  wire[15:0] sel38; // gcd.cpp(21)
  wire[15:0] sel39; // gcd.cpp(21)
  wire gt40;
  wire[15:0] sub42;
  wire[15:0] sel44; // gcd.cpp(28)
  wire[15:0] sel45; // gcd.cpp(27)
  wire[15:0] sel46; // gcd.cpp(28)
  wire and47;
  wire sel49; // gcd.cpp(36)
  wire eq52;
  wire and54;

  always @ (posedge clk) begin
    reg17 <= sel46;
  end
  always @ (posedge clk) begin
    reg23 <= sel45;
  end
  always @ (posedge clk) begin
    reg28 <= reset ? 1'h0 : sel49;
  end
  assign eq31 = 1'h0 == reg28;
  assign and33 = io_in_valid & eq31;
  assign sel37 = and33 ? 1'h1 : reg28;
  assign sel38 = and33 ? io_in_data[15:0] : reg17;
  assign sel39 = and33 ? io_in_data[31:16] : reg23;
  assign gt40 = reg17 > reg23;
  assign sub42 = reg23 - reg17;
  assign sel44 = gt40 ? reg17 : sub42;
  assign sel45 = reg28 ? sel44 : sel39;
  assign sel46 = and47 ? reg23 : sel38;
  assign and47 = reg28 & gt40;
  assign sel49 = and54 ? 1'h0 : sel37;
  assign eq52 = 16'h0 == reg23;
  assign and54 = eq52 & reg28;

  assign io_in_ready = eq31;
  assign io_out_valid = and54;
  assign io_out_data = reg17;

endmodule
