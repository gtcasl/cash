module VendingMachine(
  input wire clk,
  input wire reset,
  input wire io_coin,
  output wire io_valid
);
  reg[2:0] reg9; // vending.cpp(16)
  wire eq16;
  wire eq22;
  wire[2:0] sel53; // vending.cpp(19)
  wire[2:0] sel54; // vending.cpp(20)
  wire[2:0] sel55; // vending.cpp(23)
  wire[2:0] sel56; // vending.cpp(24)
  wire[2:0] sel57; // vending.cpp(27)
  wire[2:0] sel58; // vending.cpp(28)
  wire[2:0] sel59; // vending.cpp(31)
  wire[2:0] sel60; // vending.cpp(32)
  reg[2:0] sel61; // vending.cpp(17)
  wire eq63;

  always @ (posedge clk) begin
    reg9 <= reset ? 3'h0 : sel61;
  end
  assign eq16 = io_coin == 1'h1;
  assign eq22 = io_coin == 1'h0;
  assign sel53 = eq16 ? 3'h1 : reg9;
  assign sel54 = eq22 ? 3'h2 : sel53;
  assign sel55 = eq16 ? 3'h2 : reg9;
  assign sel56 = eq22 ? 3'h3 : sel55;
  assign sel57 = eq16 ? 3'h3 : reg9;
  assign sel58 = eq22 ? 3'h4 : sel57;
  assign sel59 = eq16 ? 3'h4 : reg9;
  assign sel60 = eq22 ? 3'h4 : sel59;
  always @(*) begin
    case (reg9)
      3'h0: sel61 = sel54;
      3'h1: sel61 = sel56;
      3'h2: sel61 = sel58;
      3'h3: sel61 = sel60;
      3'h4: sel61 = 3'h0;
      default: sel61 = reg9;
    endcase
  end
  assign eq63 = reg9 == 3'h4;

  assign io_valid = eq63;

endmodule
