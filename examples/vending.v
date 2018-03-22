module VendingMachine(
  input wire clk,
  input wire reset,
  input wire io_nickel,
  input wire io_dime,
  output wire io_valid
);
  wire[2:0] sel29; // vending.cpp(32)
  wire[2:0] sel27; // vending.cpp(28)
  wire[2:0] sel25; // vending.cpp(24)
  wire[2:0] sel23; // vending.cpp(20)
  wire[2:0] sel30; // vending.cpp(33)
  wire[2:0] sel28; // vending.cpp(29)
  wire[2:0] sel26; // vending.cpp(25)
  wire[2:0] sel24; // vending.cpp(21)
  reg[2:0] sel31; // vending.cpp(18)
  reg[2:0] reg18; // v4 - vending.cpp(17)
  wire eq33;

  assign sel29 = io_nickel ? 3'h4 : reg18;
  assign sel27 = io_nickel ? 3'h3 : reg18;
  assign sel25 = io_nickel ? 3'h2 : reg18;
  assign sel23 = io_nickel ? 3'h1 : reg18;
  assign sel30 = io_dime ? 3'h4 : sel29;
  assign sel28 = io_dime ? 3'h4 : sel27;
  assign sel26 = io_dime ? 3'h3 : sel25;
  assign sel24 = io_dime ? 3'h2 : sel23;
  always @(*) begin
    case (reg18)
      3'h0: sel31 = sel24;
      3'h1: sel31 = sel26;
      3'h2: sel31 = sel28;
      3'h3: sel31 = sel30;
      3'h4: sel31 = 3'h0;
      default: sel31 = reg18;
    endcase
  end
  always @ (posedge clk) begin
    reg18 <= reset ? 3'h0 : sel31;
  end
  assign eq33 = reg18 == 3'h4;

  assign io_valid = eq33;

endmodule
