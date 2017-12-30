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
    wire[1:0] io_dout11; // #4 fifo.cpp(8)
    wire io_empty14; // #5 fifo.cpp(8)
    wire io_full17; // #6 fifo.cpp(8)
    wire[1:0] proxy20; // #7 fifo.cpp(19)
    wire[1:0] proxy22; // #8 /home/blaise/dev/cash/src/seq.h(17)
    reg[1:0] reg27; // #7 fifo.cpp(19)
    wire[1:0] proxy29; // #10 fifo.cpp(19)
    wire[1:0] proxy31; // #11 /home/blaise/dev/cash/src/seq.h(17)
    reg[1:0] reg33; // #10 fifo.cpp(19)
    wire proxy35; // #13 fifo.cpp(21)
    wire proxy37; // #14 fifo.cpp(22)
    wire inv38;
    wire and40;
    wire inv42;
    wire and44;
    wire[1:0] add48;
    wire[1:0] sel50;
    wire[1:0] proxy51; // #21 unknown(0)
    wire[1:0] add53;
    wire[1:0] sel55;
    wire[1:0] proxy56; // #24 unknown(0)
    reg[1:0] mem57[0:1];
    wire[1:0] proxy59;
    wire[1:0] sel60;
    wire eq62;
    wire proxy63; // #27 unknown(0)
    wire proxy64; // #28 fifo.cpp(19)
    wire proxy65; // #29 fifo.cpp(19)
    wire ne66;
    wire eq68;
    wire and70;
    wire proxy71; // #32 unknown(0)

    assign io_dout11 = mem57[proxy35];
    assign io_empty14 = proxy63;
    assign io_full17 = proxy71;
    assign proxy20 = reg27;
    assign proxy22 = proxy51;
    always @ (posedge clk) reg27 <= reset ? 2'b0 : proxy22;
    assign proxy29 = reg33;
    assign proxy31 = proxy56;
    always @ (posedge clk) reg33 <= reset ? 2'b0 : proxy31;
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
    always @(posedge clk) mem57[proxy37] = proxy59;
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
