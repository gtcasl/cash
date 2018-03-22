module GCD(
  input wire clk,
  input wire reset,
  input wire io_in_valid,
  input wire[31:0] io_in_data,
  output wire io_in_ready,
  output wire io_out_valid,
  output wire[15:0] io_out_data
);
  wire[15:0] sub51;
  wire[15:0] sel48; // gcd.cpp(21)
  wire[15:0] sel53; // gcd.cpp(28)
  wire[15:0] sel54; // gcd.cpp(27)
  wire and43;
  wire gt49;
  wire sel46; // gcd.cpp(21)
  reg[15:0] reg32; // v11 - gcd.cpp(16)
  wire sel57; // gcd.cpp(36)
  wire[15:0] sel47; // gcd.cpp(21)
  wire and56;
  wire[15:0] sel55; // gcd.cpp(28)
  wire eq59;
  reg reg39; // v14 - gcd.cpp(17)
  reg[15:0] reg26; // v8 - gcd.cpp(16)
  wire and61;
  wire eq41;

  assign sub51 = reg32 - reg26;
  assign sel48 = and43 ? io_in_data[31:16] : reg32;
  assign sel53 = gt49 ? reg26 : sub51;
  assign sel54 = reg39 ? sel53 : sel48;
  assign and43 = io_in_valid & eq41;
  assign gt49 = reg26 > reg32;
  assign sel46 = and43 ? 1'h1 : reg39;
  always @ (posedge clk) begin
    reg32 <= reset ? 16'h0 : sel54;
  end
  assign sel57 = and61 ? 1'h0 : sel46;
  assign sel47 = and43 ? io_in_data[15:0] : reg26;
  assign and56 = reg39 & gt49;
  assign sel55 = and56 ? reg32 : sel47;
  assign eq59 = 16'h0 == reg32;
  always @ (posedge clk) begin
    reg39 <= reset ? 1'h0 : sel57;
  end
  always @ (posedge clk) begin
    reg26 <= reset ? 16'h0 : sel55;
  end
  assign and61 = eq59 & reg39;
  assign eq41 = reg39 == 1'h0;

  assign io_in_ready = eq41;
  assign io_out_valid = and61;
  assign io_out_data = reg26;

endmodule
