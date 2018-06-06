module VendingMachine(
  input wire clk,
  input wire reset,
  input wire io_coin,
  output wire io_valid
);
  reg[2:0] reg11; // vending.cpp(16)
  wire eq18;
  wire eq24;
  wire[2:0] sel55; // vending.cpp(19)
  wire[2:0] sel56; // vending.cpp(20)
  wire[2:0] sel57; // vending.cpp(23)
  wire[2:0] sel58; // vending.cpp(24)
  wire[2:0] sel59; // vending.cpp(27)
  wire[2:0] sel60; // vending.cpp(28)
  wire[2:0] sel61; // vending.cpp(31)
  wire[2:0] sel62; // vending.cpp(32)
  reg[2:0] sel63; // vending.cpp(17)
  wire eq65;

  always @ (posedge clk) begin
    reg11 <= reset ? 3'h0 : sel63;
  end
  assign eq18 = io_coin == 1'h1;
  assign eq24 = io_coin == 1'h0;
  assign sel55 = eq18 ? 3'h1 : reg11;
  assign sel56 = eq24 ? 3'h2 : sel55;
  assign sel57 = eq18 ? 3'h2 : reg11;
  assign sel58 = eq24 ? 3'h3 : sel57;
  assign sel59 = eq18 ? 3'h3 : reg11;
  assign sel60 = eq24 ? 3'h4 : sel59;
  assign sel61 = eq18 ? 3'h4 : reg11;
  assign sel62 = eq24 ? 3'h4 : sel61;
  always @(*) begin
    case (reg11)
      3'h0: sel63 = sel56;
      3'h1: sel63 = sel58;
      3'h2: sel63 = sel60;
      3'h3: sel63 = sel62;
      3'h4: sel63 = 3'h0;
      default: sel63 = reg11;
    endcase
  end
  assign eq65 = reg11 == 3'h4;

  assign io_valid = eq65;

endmodule
