module VendingMachine(
  input wire clk,
  input wire reset,
  input wire io_coin,
  output wire io_valid
);
  wire eq48;
  wire eq39;
  wire eq30;
  wire eq19;
  wire eq52;
  wire eq43;
  wire eq34;
  wire eq25;
  wire[2:0] sel62; // vending.cpp(31)
  wire[2:0] sel60; // vending.cpp(27)
  wire[2:0] sel58; // vending.cpp(23)
  wire[2:0] sel56; // vending.cpp(19)
  wire[2:0] sel63; // vending.cpp(32)
  wire[2:0] sel61; // vending.cpp(28)
  wire[2:0] sel59; // vending.cpp(24)
  wire[2:0] sel57; // vending.cpp(20)
  reg[2:0] sel64; // vending.cpp(17)
  reg[2:0] reg12;
  wire eq66;

  assign eq48 = io_coin == 1'h1;
  assign eq39 = io_coin == 1'h1;
  assign eq30 = io_coin == 1'h1;
  assign eq19 = io_coin == 1'h1;
  assign eq52 = io_coin == 1'h0;
  assign eq43 = io_coin == 1'h0;
  assign eq34 = io_coin == 1'h0;
  assign eq25 = io_coin == 1'h0;
  assign sel62 = eq48 ? 3'h4 : reg12;
  assign sel60 = eq39 ? 3'h3 : reg12;
  assign sel58 = eq30 ? 3'h2 : reg12;
  assign sel56 = eq19 ? 3'h1 : reg12;
  assign sel63 = eq52 ? 3'h4 : sel62;
  assign sel61 = eq43 ? 3'h4 : sel60;
  assign sel59 = eq34 ? 3'h3 : sel58;
  assign sel57 = eq25 ? 3'h2 : sel56;
  always @(*) begin
    case (reg12)
      3'h0: sel64 = sel57;
      3'h1: sel64 = sel59;
      3'h2: sel64 = sel61;
      3'h3: sel64 = sel63;
      3'h4: sel64 = 3'h0;
      default: sel64 = reg12;
    endcase
  end
  always @ (posedge clk) begin
    reg12 <= reset ? 3'h0 : sel64;
  end
  assign eq66 = reg12 == 3'h4;

  assign io_valid = eq66;

endmodule
