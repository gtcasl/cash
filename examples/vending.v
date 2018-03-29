module VendingMachine(
  input wire clk,
  input wire reset,
  input wire io_nickel,
  input wire io_dime,
  output wire io_valid
);
  wire[2:0] sel30; // vending.cpp(32)
  wire[2:0] sel28; // vending.cpp(28)
  wire[2:0] sel26; // vending.cpp(24)
  wire[2:0] sel24; // vending.cpp(20)
  wire[2:0] sel31; // vending.cpp(33)
  wire[2:0] sel29; // vending.cpp(29)
  wire[2:0] sel27; // vending.cpp(25)
  wire[2:0] sel25; // vending.cpp(21)
  reg[2:0] sel32; // vending.cpp(18)
  reg[2:0] reg16; // v4 - vending.cpp(17)
  wire eq34;

  assign sel30 = io_nickel ? 3'h4 : reg16;
  assign sel28 = io_nickel ? 3'h3 : reg16;
  assign sel26 = io_nickel ? 3'h2 : reg16;
  assign sel24 = io_nickel ? 3'h1 : reg16;
  assign sel31 = io_dime ? 3'h4 : sel30;
  assign sel29 = io_dime ? 3'h4 : sel28;
  assign sel27 = io_dime ? 3'h3 : sel26;
  assign sel25 = io_dime ? 3'h2 : sel24;
  always @(*) begin
    case (reg16)
      3'h0: sel32 = sel25;
      3'h1: sel32 = sel27;
      3'h2: sel32 = sel29;
      3'h3: sel32 = sel31;
      3'h4: sel32 = 3'h0;
      default: sel32 = reg16;
    endcase
  end
  always @ (posedge clk) begin
    reg16 <= reset ? 3'h0 : sel32;
  end
  assign eq34 = reg16 == 3'h4;

  assign io_valid = eq34;

endmodule
