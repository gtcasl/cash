`include "cash.v"

module Filter(
    input wire clk,
    input wire reset,
    input wire[15:0] io_x_data,
    input wire io_x_valid,
    input wire io_x_parity,
    output wire[15:0] io_y_data,
    output wire io_y_valid,
    output wire io_y_parity
);
    wire[15:0] io_x_data2; // #2303 module.cpp(68)
    wire io_x_parity8; // #2305 module.cpp(68)
    wire[15:0] io_y_data11; // #2306 module.cpp(68)
    wire io_y_valid14; // #2307 module.cpp(68)
    wire io_y_parity17; // #2308 module.cpp(68)
    wire[15:0] proxy20; // #2309 /home/blaise/dev/cash/src/bit.h(1008)
    wire[16:0] proxy22; // #2310 module.cpp(72)
    wire proxy24; // #2311 /home/blaise/dev/cash/src/bit.h(1008)
    wire[16:0] proxy26; // #2312 module.cpp(71)
    wire[16:0] sll29;
    wire[16:0] or31;
    wire[16:0] proxy32; // #2315 unknown(0)
    wire[15:0] proxy34; // #2316 module.cpp(73)
    reg[15:0] reg38;
    wire[15:0] proxy39; // #2318 unknown(0)
    wire proxy40; // #2319 unknown(0)
    reg reg42;
    wire proxy43; // #2321 unknown(0)

    assign io_x_data2 = io_x_data;
    assign io_x_parity8 = io_x_parity;
    assign io_y_data11 = proxy39;
    assign io_y_valid14 = proxy43;
    assign io_y_parity17 = proxy40;
    assign proxy20 = 16'h0;
    assign proxy22 = {proxy20, io_x_parity8};
    assign proxy24 = 1'b0;
    assign proxy26 = {proxy24, io_x_data2};
    assign sll29 = proxy26 << 17'b1;
    assign or31 = sll29 | proxy22;
    assign proxy32 = or31;
    assign proxy34 = proxy32[15:0];
    always @ (posedge clk) reg38 <= reset ? 16'h0 : proxy34;
    assign proxy39 = reg38;
    assign proxy40 = proxy32[16];
    always @ (posedge clk) reg42 <= reset ? 1'b0 : io_x_valid;
    assign proxy43 = reg42;

    assign io_y_data = io_y_data11;
    assign io_y_valid = io_y_valid14;
    assign io_y_parity = io_y_parity17;

endmodule


module FilterBlock(
    input wire clk,
    input wire reset,
    input wire[15:0] io_x_data,
    input wire io_x_valid,
    input wire io_x_parity,
    output wire[15:0] io_y_data,
    output wire io_y_valid,
    output wire io_y_parity
);
    wire[15:0] io_x_data2; // #2297 module.cpp(80)
    wire io_x_valid5; // #2298 module.cpp(80)
    wire io_x_parity8; // #2299 module.cpp(80)
    wire[15:0] io_y_data11; // #2300 module.cpp(80)
    wire io_y_valid14; // #2301 module.cpp(80)
    wire io_y_parity17; // #2302 module.cpp(80)
    wire[15:0] proxy20; // #2322 /home/blaise/dev/cash/src/module.h(33)
    wire bindin23;
    wire bindin25;
    wire[15:0] bindin26;
    wire proxy28; // #2323 /home/blaise/dev/cash/src/module.h(33)
    wire bindin29;
    wire proxy31; // #2324 /home/blaise/dev/cash/src/module.h(33)
    wire bindin32;
    wire[15:0] proxy34; // #2325 /home/blaise/dev/cash/src/module.h(33)
    wire[15:0] bindout35;
    wire proxy37; // #2326 /home/blaise/dev/cash/src/module.h(33)
    wire bindout38;
    wire proxy40; // #2327 /home/blaise/dev/cash/src/module.h(33)
    wire bindout41;
    wire[15:0] proxy43; // #2347 /home/blaise/dev/cash/src/module.h(33)
    wire bindin45;
    wire bindin46;
    wire[15:0] bindin47;
    wire proxy49; // #2348 /home/blaise/dev/cash/src/module.h(33)
    wire bindin50;
    wire proxy52; // #2349 /home/blaise/dev/cash/src/module.h(33)
    wire bindin53;
    wire[15:0] proxy55; // #2350 /home/blaise/dev/cash/src/module.h(33)
    wire[15:0] bindout56;
    wire proxy58; // #2351 /home/blaise/dev/cash/src/module.h(33)
    wire bindout59;
    wire proxy61; // #2352 /home/blaise/dev/cash/src/module.h(33)
    wire bindout62;

    assign io_x_data2 = io_x_data;
    assign io_x_valid5 = io_x_valid;
    assign io_x_parity8 = io_x_parity;
    assign io_y_data11 = proxy55;
    assign io_y_valid14 = proxy58;
    assign io_y_parity17 = proxy61;
    assign proxy20 = io_x_data2;
    assign bindin23 = clk;
    assign bindin25 = reset;
    Filter __module221__(.clk(bindin23), .reset(bindin25), .io_x_data(bindin26), .io_x_valid(bindin29), .io_x_parity(bindin32), .io_y_data(bindout35), .io_y_valid(bindout38), .io_y_parity(bindout41));
    assign bindin26 = proxy20;
    assign proxy28 = io_x_valid5;
    assign bindin29 = proxy28;
    assign proxy31 = io_x_parity8;
    assign bindin32 = proxy31;
    assign proxy34 = bindout35;
    assign proxy37 = bindout38;
    assign proxy40 = bindout41;
    assign proxy43 = proxy34;
    assign bindin45 = clk;
    assign bindin46 = reset;
    Filter __module222__(.clk(bindin45), .reset(bindin46), .io_x_data(bindin47), .io_x_valid(bindin50), .io_x_parity(bindin53), .io_y_data(bindout56), .io_y_valid(bindout59), .io_y_parity(bindout62));
    assign bindin47 = proxy43;
    assign proxy49 = proxy37;
    assign bindin50 = proxy49;
    assign proxy52 = proxy40;
    assign bindin53 = proxy52;
    assign proxy55 = bindout56;
    assign proxy58 = bindout59;
    assign proxy61 = bindout62;

    assign io_y_data = io_y_data11;
    assign io_y_valid = io_y_valid14;
    assign io_y_parity = io_y_parity17;

endmodule
