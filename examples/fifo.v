`include "cash.v"

module FiFo(
    input wire clk,
    input wire reset,
    input wire[1:0] io_din,
    input wire io_push,
    input wire io_pop,
    output wire[1:0] io_dout,
    output wire io_empty,
    output wire io_full
);
    wire[1:0] io_dout11, proxy20, proxy22, proxy29, proxy31, add48, sel50, proxy51, add53, sel55, proxy56, proxy59, sel60;
    wire io_empty14, io_full17, proxy35, proxy37, inv38, and40, inv42, and44, eq62, proxy63, proxy64, proxy65, ne66, eq68, and70, proxy71;
    reg[1:0] reg27, reg33;
    reg[1:0] mem57[0:1];

    assign io_dout11 = mem57[proxy35];
    assign io_empty14 = proxy63;
    assign io_full17 = proxy71;
    assign proxy20 = reg27;
    assign proxy22 = proxy51;
    always @ (posedge clk)
    reg27 <= reset ? 2'b0 : proxy22;
    assign proxy29 = reg33;
    assign proxy31 = proxy56;
    always @ (posedge clk)
    reg33 <= reset ? 2'b0 : proxy31;
    assign proxy35 = proxy20[0];
    assign proxy37 = proxy29[0];
    assign inv38 = ~io_empty14;
    assign and40 = io_pop & inv38;
    assign inv42 = ~io_full17;
    assign and44 = io_push & inv42;
    assign add48 = proxy20 + 2'b1;
    assign sel50 = and40 ? add48 : proxy20;
    assign proxy51 = sel50;
    assign add53 = proxy29 + 2'b1;
    assign sel55 = and44 ? add53 : proxy29;
    assign proxy56 = sel55;
    always @(posedge clk)
    mem57[proxy37] = proxy59;
    assign proxy59 = sel60;
    assign sel60 = and44 ? io_din : mem57[proxy37];
    assign eq62 = proxy29 == proxy20;
    assign proxy63 = eq62;
    assign proxy64 = proxy20[1];
    assign proxy65 = proxy29[1];
    assign ne66 = proxy65 != proxy64;
    assign eq68 = proxy37 == proxy35;
    assign and70 = eq68 & ne66;
    assign proxy71 = and70;

    assign io_dout = io_dout11;
    assign io_empty = io_empty14;
    assign io_full = io_full17;

endmodule
