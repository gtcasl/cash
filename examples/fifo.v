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
    wire[1:0] io_dout11; // fifo.cpp(8) @var4
    wire io_empty14; // fifo.cpp(8) @var5
    wire io_full17; // fifo.cpp(8) @var6
    wire[1:0] proxy20; // fifo.cpp(19) @var7
    wire[1:0] proxy22; // /home/blaise/dev/cash/src/seq.h(17) @var8
    reg[1:0] reg27; // fifo.cpp(19) @var7
    wire[1:0] proxy29; // fifo.cpp(19) @var10
    wire[1:0] proxy31; // /home/blaise/dev/cash/src/seq.h(17) @var11
    reg[1:0] reg33; // fifo.cpp(19) @var10
    wire proxy35; // fifo.cpp(21) @var13
    wire proxy37; // fifo.cpp(22) @var14
    wire eq40;
    wire and42;
    wire eq45;
    wire and47;
    wire[1:0] add51;
    wire[1:0] sel53;
    wire[1:0] proxy54; // @var23
    wire[1:0] add56;
    wire[1:0] sel58;
    wire[1:0] proxy59; // @var26
    reg[1:0] mem60[0:1];
    wire[1:0] proxy62; // fifo.cpp(31)
    wire[1:0] sel63; // fifo.cpp(31)
    wire eq65;
    wire proxy66; // @var29
    wire proxy67; // @var30
    wire proxy68; // @var31
    wire ne69;
    wire eq71;
    wire and73;
    wire proxy74; // @var34

    assign io_dout11 = mem60[proxy35];
    assign io_empty14 = proxy66;
    assign io_full17 = proxy74;
    assign proxy20 = reg27;
    assign proxy22 = proxy54;
    always @ (posedge clk) reg27 <= reset ? 2'b0 : proxy22;
    assign proxy29 = reg33;
    assign proxy31 = proxy59;
    always @ (posedge clk) reg33 <= reset ? 2'b0 : proxy31;
    assign proxy35 = proxy20[0];
    assign proxy37 = proxy29[0];
    assign eq40 = io_empty14 == 1'b0;
    assign and42 = io_pop & eq40;
    assign eq45 = io_full17 == 1'b0;
    assign and47 = io_push & eq45;
    assign add51 = proxy20 + 2'b1;
    assign sel53 = and42 ? add51 : proxy20;
    assign proxy54 = sel53;
    assign add56 = proxy29 + 2'b1;
    assign sel58 = and47 ? add56 : proxy29;
    assign proxy59 = sel58;
    always @(posedge clk) mem60[proxy37] = proxy62;
    assign proxy62 = sel63;
    assign sel63 = and47 ? io_din : mem60[proxy37];
    assign eq65 = proxy29 == proxy20;
    assign proxy66 = eq65;
    assign proxy67 = proxy20[1];
    assign proxy68 = proxy29[1];
    assign ne69 = proxy68 != proxy67;
    assign eq71 = proxy37 == proxy35;
    assign and73 = eq71 & ne69;
    assign proxy74 = and73;

    assign io_dout = io_dout11;
    assign io_empty = io_empty14;
    assign io_full = io_full17;

endmodule
