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
    wire proxy36; // #14 /home/blaise/dev/cash/src/bit.h(599)
    wire proxy38; // #15 fifo.cpp(22)
    wire proxy39; // #16 /home/blaise/dev/cash/src/bit.h(599)
    wire eq42;
    wire and44;
    wire eq47;
    wire and49;
    wire[1:0] add53;
    wire[1:0] sel55;
    wire[1:0] proxy56; // #25 unknown(0)
    wire[1:0] add58;
    wire[1:0] sel60;
    wire[1:0] proxy61; // #28 unknown(0)
    reg[1:0] mem62[0:1];
    wire[1:0] proxy64;
    wire[1:0] sel65;
    wire eq67;
    wire proxy68; // #31 unknown(0)
    wire proxy69; // #32 unknown(0)
    wire proxy70; // #33 unknown(0)
    wire ne71;
    wire eq73;
    wire and75;
    wire proxy76; // #36 unknown(0)

    assign io_dout11 = mem62[proxy36];
    assign io_empty14 = proxy68;
    assign io_full17 = proxy76;
    assign proxy20 = reg27;
    assign proxy22 = proxy56;
    always @ (posedge clk) reg27 <= reset ? 2'b0 : proxy22;
    assign proxy29 = reg33;
    assign proxy31 = proxy61;
    always @ (posedge clk) reg33 <= reset ? 2'b0 : proxy31;
    assign proxy35 = proxy20[0];
    assign proxy36 = proxy35;
    assign proxy38 = proxy29[0];
    assign proxy39 = proxy38;
    assign eq42 = io_empty14 == 1'b0;
    assign and44 = io_pop & eq42;
    assign eq47 = io_full17 == 1'b0;
    assign and49 = io_push & eq47;
    assign add53 = proxy20 + 2'b1;
    assign sel55 = and44 ? add53 : proxy20;
    assign proxy56 = sel55;
    assign add58 = proxy29 + 2'b1;
    assign sel60 = and49 ? add58 : proxy29;
    assign proxy61 = sel60;
    always @(posedge clk) mem62[proxy39] = proxy64;
    assign proxy64 = sel65;
    assign sel65 = and49 ? io_din : mem62[proxy39];
    assign eq67 = proxy29 == proxy20;
    assign proxy68 = eq67;
    assign proxy69 = proxy20[1];
    assign proxy70 = proxy29[1];
    assign ne71 = proxy70 != proxy69;
    assign eq73 = proxy39 == proxy36;
    assign and75 = eq73 & ne71;
    assign proxy76 = and75;

    assign io_dout = io_dout11;
    assign io_empty = io_empty14;
    assign io_full = io_full17;

endmodule
