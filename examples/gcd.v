module GCD(
  input wire clk,
  input wire reset,
  input wire io_in_valid,
  input wire[31:0] io_in_data,
  output wire io_in_ready,
  output wire io_out_valid,
  output wire[15:0] io_out_data
);
  wire[15:0] sub49;
  wire[15:0] sel46; // gcd.cpp(21)
  wire[15:0] sel51; // gcd.cpp(28)
  wire[15:0] sel52; // gcd.cpp(27)
  wire and41;
  wire gt47;
  wire sel44; // gcd.cpp(21)
  reg[15:0] reg30; // v10 - gcd.cpp(16)
  wire sel55; // gcd.cpp(36)
  wire[15:0] sel45; // gcd.cpp(21)
  wire and54;
  wire[15:0] sel53; // gcd.cpp(28)
  wire eq58;
  reg reg37; // v12 - gcd.cpp(17)
  reg[15:0] reg22; // v8 - gcd.cpp(16)
  wire and60;
  wire eq39;

  assign sub49 = reg30 - reg22;
  assign sel46 = and41 ? io_in_data[31:16] : reg30;
  assign sel51 = gt47 ? reg22 : sub49;
  assign sel52 = reg37 ? sel51 : sel46;
  assign and41 = io_in_valid & eq39;
  assign gt47 = reg22 > reg30;
  assign sel44 = and41 ? 1'h1 : reg37;
  always @ (posedge clk) begin
    reg30 <= sel52;
  end
  assign sel55 = and60 ? 1'h0 : sel44;
  assign sel45 = and41 ? io_in_data[15:0] : reg22;
  assign and54 = reg37 & gt47;
  assign sel53 = and54 ? reg30 : sel45;
  assign eq58 = 16'h0 == reg30;
  always @ (posedge clk) begin
    reg37 <= reset ? 1'h0 : sel55;
  end
  always @ (posedge clk) begin
    reg22 <= sel53;
  end
  assign and60 = eq58 & reg37;
  assign eq39 = reg37 == 1'h0;

  assign io_in_ready = eq39;
  assign io_out_valid = and60;
  assign io_out_data = reg22;

endmodule
