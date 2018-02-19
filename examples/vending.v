`include "cash.v"

module VendingMachine(
    input wire clk,
    input wire reset,
    input wire io_nickel,
    input wire io_dime,
    output wire io_valid
);
    wire io_valid8; // vending.cpp(7) @var3
    reg[2:0] reg18; // vending.cpp(17) @var4
    wire[2:0] sel23; // vending.cpp(20)
    wire[2:0] sel24; // vending.cpp(21)
    wire[2:0] sel25; // vending.cpp(24)
    wire[2:0] sel26; // vending.cpp(25)
    wire[2:0] sel27; // vending.cpp(28)
    wire[2:0] sel28; // vending.cpp(29)
    wire[2:0] sel29; // vending.cpp(32)
    wire[2:0] sel30; // vending.cpp(33)
    wire[2:0] sel31; // vending.cpp(18)
    wire eq33;
    wire proxy34; // @var8

    assign io_valid8 = proxy34;
    always @ (posedge clk) reg18 <= reset ? 3'b0 : sel31;
    assign sel23 = io_nickel ? 3'b1 : reg18;
    assign sel24 = io_dime ? 3'b10 : sel23;
    assign sel25 = io_nickel ? 3'b10 : reg18;
    assign sel26 = io_dime ? 3'b11 : sel25;
    assign sel27 = io_nickel ? 3'b11 : reg18;
    assign sel28 = io_dime ? 3'b100 : sel27;
    assign sel29 = io_nickel ? 3'b100 : reg18;
    assign sel30 = io_dime ? 3'b100 : sel29;
    always_comb begin
        case (reg18)
            3'b000: sel31 = sel24;
            3'b001: sel31 = sel26;
            3'b010: sel31 = sel28;
            3'b011: sel31 = sel30;
            3'b100: sel31 = 3'b0;
            default: sel31 = reg18;
        endcase
    end
    assign eq33 = reg18 == 3'b100;
    assign proxy34 = eq33;

    assign io_valid = io_valid8;

endmodule
