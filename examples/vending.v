`include "cash.v"

module VendingMachine(
    input wire clk,
    input wire reset,
    input wire io_nickel,
    input wire io_dime,
    output wire io_valid
);
    wire io_valid8; // #3 vending.cpp(7)
    reg[2:0] reg18; // #4 vending.cpp(17)
    wire[2:0] sel28;
    wire[2:0] sel29;
    wire[2:0] sel30;
    wire[2:0] sel31;
    wire[2:0] sel32;
    wire[2:0] sel33;
    wire[2:0] sel34;
    wire[2:0] sel35;
    wire[2:0] sel36;
    wire eq38;
    wire proxy39; // #13 unknown(0)

    assign io_valid8 = proxy39;
    always @ (posedge clk) reg18 <= reset ? 3'b0 : sel36;
    assign sel28 = io_nickel ? 3'b1 : reg18;
    assign sel29 = io_dime ? 3'b10 : sel28;
    assign sel30 = io_nickel ? 3'b10 : reg18;
    assign sel31 = io_dime ? 3'b11 : sel30;
    assign sel32 = io_nickel ? 3'b11 : reg18;
    assign sel33 = io_dime ? 3'b100 : sel32;
    assign sel34 = io_nickel ? 3'b100 : reg18;
    assign sel35 = io_dime ? 3'b100 : sel34;
    assign sel36 = 
        (reg18 == 3'b0) ? sel29 : 
        (reg18 == 3'b1) ? sel31 : 
        (reg18 == 3'b10) ? sel33 : 
        (reg18 == 3'b11) ? sel35 : 
        (reg18 == 3'b100) ? 3'b0 : 
        reg18;
    assign eq38 = reg18 == 3'b100;
    assign proxy39 = eq38;

    assign io_valid = io_valid8;

endmodule
