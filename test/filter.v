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
    wire[15:0] io_x_data2; // #2340 module.cpp(68)
    wire io_x_parity8; // #2342 module.cpp(68)
    wire[15:0] io_y_data11; // #2343 module.cpp(68)
    wire io_y_valid14; // #2344 module.cpp(68)
    wire io_y_parity17; // #2345 module.cpp(68)
    wire[15:0] proxy20; // #2346 /home/blaise/dev/cash/src/bit.h(1004)
    wire[16:0] proxy22; // #2347 module.cpp(72)
    wire proxy24; // #2348 /home/blaise/dev/cash/src/bit.h(1004)
    wire[16:0] proxy26; // #2349 module.cpp(71)
    wire[16:0] sll29;
    wire[16:0] or31;
    wire[16:0] proxy32; // #2352 unknown(0)
    wire[15:0] proxy34; // #2353 module.cpp(73)
    wire[15:0] proxy35; // #2354 /home/blaise/dev/cash/src/bit.h(599)
    reg[15:0] reg39;
    wire[15:0] proxy40; // #2356 unknown(0)
    wire proxy41; // #2357 unknown(0)
    reg reg43;
    wire proxy44; // #2359 unknown(0)

    assign io_x_data2 = io_x_data;
    assign io_x_parity8 = io_x_parity;
    assign io_y_data11 = proxy40;
    assign io_y_valid14 = proxy44;
    assign io_y_parity17 = proxy41;
    assign proxy20 = 16'h0;
    assign proxy22 = {proxy20, io_x_parity8};
    assign proxy24 = 1'b0;
    assign proxy26 = {proxy24, io_x_data2};
    assign sll29 = proxy26 << 17'b1;
    assign or31 = sll29 | proxy22;
    assign proxy32 = or31;
    assign proxy34 = proxy32[15:0];
    assign proxy35 = proxy34;
    always @ (posedge clk) reg39 <= reset ? 16'h0 : proxy35;
    assign proxy40 = reg39;
    assign proxy41 = proxy32[16];
    always @ (posedge clk) reg43 <= reset ? 1'b0 : io_x_valid;
    assign proxy44 = reg43;

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
    wire[15:0] io_x_data2; // #2334 module.cpp(80)
    wire io_x_valid5; // #2335 module.cpp(80)
    wire io_x_parity8; // #2336 module.cpp(80)
    wire[15:0] io_y_data11; // #2337 module.cpp(80)
    wire io_y_valid14; // #2338 module.cpp(80)
    wire io_y_parity17; // #2339 module.cpp(80)
    wire[15:0] proxy20; // #2360 /home/blaise/dev/cash/src/module.h(33)
    wire bindin23;
    wire bindin25;
    wire[15:0] bindin26;
    wire proxy28; // #2361 /home/blaise/dev/cash/src/module.h(33)
    wire bindin29;
    wire proxy31; // #2362 /home/blaise/dev/cash/src/module.h(33)
    wire bindin32;
    wire[15:0] proxy34; // #2363 /home/blaise/dev/cash/src/module.h(33)
    wire[15:0] bindout35;
    wire proxy37; // #2364 /home/blaise/dev/cash/src/module.h(33)
    wire bindout38;
    wire proxy40; // #2365 /home/blaise/dev/cash/src/module.h(33)
    wire bindout41;
    wire[15:0] proxy43; // #2386 /home/blaise/dev/cash/src/module.h(33)
    wire bindin45;
    wire bindin46;
    wire[15:0] bindin47;
    wire proxy49; // #2387 /home/blaise/dev/cash/src/module.h(33)
    wire bindin50;
    wire proxy52; // #2388 /home/blaise/dev/cash/src/module.h(33)
    wire bindin53;
    wire[15:0] proxy55; // #2389 /home/blaise/dev/cash/src/module.h(33)
    wire[15:0] bindout56;
    wire proxy58; // #2390 /home/blaise/dev/cash/src/module.h(33)
    wire bindout59;
    wire proxy61; // #2391 /home/blaise/dev/cash/src/module.h(33)
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
