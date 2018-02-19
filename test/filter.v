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
    wire[15:0] io_x_data2; // module.cpp(68) @var2286
    wire io_x_parity8; // module.cpp(68) @var2288
    wire[15:0] io_y_data11; // module.cpp(68) @var2289
    wire io_y_valid14; // module.cpp(68) @var2290
    wire io_y_parity17; // module.cpp(68) @var2291
    wire[15:0] proxy20; // module.cpp(72) @var2292
    wire[16:0] proxy22; // module.cpp(72) @var2293
    wire proxy24; // module.cpp(71) @var2294
    wire[16:0] proxy26; // module.cpp(71) @var2295
    wire[16:0] sll29;
    wire[16:0] or31;
    wire[16:0] proxy32; // @var2298
    wire[15:0] proxy34; // module.cpp(73) @var2299
    reg[15:0] reg38;
    wire[15:0] proxy39; // @var2301
    wire proxy40; // @var2302
    reg reg42;
    wire proxy43; // @var2304

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
    wire[15:0] io_x_data2; // module.cpp(80) @var2280
    wire io_x_valid5; // module.cpp(80) @var2281
    wire io_x_parity8; // module.cpp(80) @var2282
    wire[15:0] io_y_data11; // module.cpp(80) @var2283
    wire io_y_valid14; // module.cpp(80) @var2284
    wire io_y_parity17; // module.cpp(80) @var2285
    wire[15:0] proxy20; // /home/blaise/dev/cash/src/module.h(33) @var2305
    wire bindin23;
    wire bindin25;
    wire[15:0] bindin26;
    wire proxy28; // /home/blaise/dev/cash/src/module.h(33) @var2306
    wire bindin29;
    wire proxy31; // /home/blaise/dev/cash/src/module.h(33) @var2307
    wire bindin32;
    wire[15:0] proxy34; // /home/blaise/dev/cash/src/module.h(33) @var2308
    wire[15:0] bindout35;
    wire proxy37; // /home/blaise/dev/cash/src/module.h(33) @var2309
    wire bindout38;
    wire proxy40; // /home/blaise/dev/cash/src/module.h(33) @var2310
    wire bindout41;
    wire[15:0] proxy43; // /home/blaise/dev/cash/src/module.h(33) @var2330
    wire bindin45;
    wire bindin46;
    wire[15:0] bindin47;
    wire proxy49; // /home/blaise/dev/cash/src/module.h(33) @var2331
    wire bindin50;
    wire proxy52; // /home/blaise/dev/cash/src/module.h(33) @var2332
    wire bindin53;
    wire[15:0] proxy55; // /home/blaise/dev/cash/src/module.h(33) @var2333
    wire[15:0] bindout56;
    wire proxy58; // /home/blaise/dev/cash/src/module.h(33) @var2334
    wire bindout59;
    wire proxy61; // /home/blaise/dev/cash/src/module.h(33) @var2335
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
