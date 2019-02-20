#include "common.h"

TEST_CASE("arithmetic", "[arithmetic]") {
  SECTION("binary", "[binary]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ~a;
      return (c == 0011_b) && (c == 3);
    });
    TESTX([]()->bool {
      auto ret = TestFunction([](const ch_bit4& a, const ch_bit4& b)->ch_bit4 {
        return a & b;
      }, 1100_b, 0101_b);
      return (ret == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a | 0101_b;
      return (c == 1101_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a ^ 0101_b;
      return (c == 1001_b);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x0'ffffffff'00000000_h65);
      auto c = ~a;
      return (c == 0x1'00000000'ffffffff_h65);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x1'ffffffff'00000000_h65);
      auto c = ~a;
      ch_bit<64> d = 0x00000000'ffffffff_h64;
      //ch_print("c={0}, d={1}", c, d);
      return (c == d);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x0'ffffffff'00000000_h65);
      auto c = ~a;
      ch_bit<64> d = 0x00000000'ffffffff_h64;
      //ch_print("c={0}, d={1}", c, d);
      return (c != d);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xBA), b(0xDC);
      auto c = a ^ b;
      return (c.slice<8>() == 0x66);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xBA);
      auto c = ch_inv<8>(a);
      return (c == 0x45);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xBA), b(0xDC);
      auto c = ch_xor<8>(a, b);
      return (c == 0x66);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xBA), b(0xDC);
      auto c = a | b;
      return (c.slice<8>() == 0xFE);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0xBA), b(0xDC);
      auto c = a & b;
      return (c.slice<8>() == 0x98);
    });
  }
  
  SECTION("reduce", "[reduce]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1010_b);
      return (ch_andr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1111_b);
      return (ch_andr(a) == 1_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      return (ch_orr(a) == 1_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0000_b);
      return (ch_orr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      return (ch_xorr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      return (ch_xorr(a) == 1_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0x80000000000000008000000000000000_h128);
      return (ch_xorr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 a(0x80000000000000000000000000000000_h128);
      return (ch_xorr(a) == 1_b);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x1'00000000'00000000_h65);
      return (ch_orr(a) == 1_b);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x0'00000000'00000000_h65);
      return (ch_orr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x1'ffffffff'fffffff0_h65);
      return (ch_andr(a) == 0_b);
    });
    TEST([]()->ch_bool {
      ch_bit<65> a(0x1'ffffffff'ffffffff_h65);
      return (ch_andr(a) == 1_b);
    });
  }
  
  SECTION("compare", "[compare]") {
    TEST([]()->ch_bool {
      ch_bit4 x(0100_b);
      return (x == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 x(0x111111100000001111111_h128);
      ch_bit128 y = x >> 64;
      ch_bit128 e = 0x11111_h128;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
    TEST([]()->ch_bool {
      ch_bit4 x(0101_b);
      return (x != 0100_b);
    });
    TEST([]()->ch_bool {
      ch_bit128 x(0x111111100000001111111_h128);
      ch_bit128 y = x << 64;
      ch_bit128 e = 0;
      //ch_print("y={0}, e={1}", y, e);
      return (y != e);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0001_b);
      return (x < 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint128 x(0x111111100000001111111_h128);
      ch_uint128 y = x >> 64;
      ch_uint128 e = 0x11112_h128;
      //ch_print("y={0}, e={1}", y, e);
      return (y < e);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x > 0010_b);
    });
    TEST([]()->ch_bool {
      ch_uint128 x(0x111111100000001111111_h128);
      ch_uint128 y = x >> 64;
      ch_uint128 e = 0x11110_h128;
      //ch_print("y={0}, e={1}", y, e);
      return (y > e);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x <= 1100_b);
    });
    TEST([]()->ch_bool {
      ch_uint128 x(0x111111100000001111111_h128);
      ch_uint128 y = x >> 64;
      ch_uint128 e = 0x11111_h128;
      //ch_print("y={0}, e={1}", y, e);
      return (y <= e);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(1100_b);
      return (x <= 1100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(1100_b);
      return (x >= 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint128 x(0x111111100000001111111_h128);
      ch_uint128 y = x >> 64;
      ch_uint128 e = 0x11111_h128;
      //ch_print("y={0}, e={1}", y, e);
      return (y >= e);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x >= 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(0001_b);
      return (x < 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(1001_b);
      return (x < 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(0100_b);
      return (x > 0010_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(1100_b);
      return (x < 0010_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(0100_b);
      return (x >= 1100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(1100_b);
      return (x >= 1100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(1100_b);
      return (x <= 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 x(0100_b);
      return (x <= 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0xf11111100000001111111_h84);
      ch_int<84> y = x << 1;
      ch_int<84> e = 0xe22222200000002222222_h84;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0xf11111100000001111111_h84);
      ch_int<84> y = x << 1;
      ch_int<84> e = 0xe22222200000002222223_h84;
      //ch_print("y={0}, e={1}", y, e);
      return (y < e);
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0xf11111100000001111111_h84);
      ch_int<84> y = x << 1;
      ch_int<84> e = 0xe22222200000002222221_h84;
      //ch_print("y={0}, e={1}", y, e);
      return (y > e);
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0);
      ch_bool y = !x;
      return y;
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0xf11111100000001111111_h84);
      ch_int<84> y(0xf111111fffffff1111111_h84);
      return x && y;
    });
    TEST([]()->ch_bool {
      ch_int<84> x(0);
      ch_int<84> y(0xf111111fffffff1111111_h84);
      return x || y;
    });
  }
  
  SECTION("shift", "[shift]") {
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a << 1;
      return (c == 0xAAAAAAAA_h);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a << 16;
      return (c == 0x55550000_h);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a << 17;
      return (c == 0xAAAA0000_h);
    });
    TEST([]()->ch_bool {
      ch_uint16 a(0x5555_h);
      auto c = a << 16;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint16 a(0x5555_h);
      auto c = a << 17;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a << 32;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a << 33;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0x5555555555555555);
      auto c = a << 64;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0x5555555555555555);
      auto c = a << 65;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<48>(a, 1);
      return (c == 0x0000AAAAAAAA_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<48>(a, 4);
      //ch_print("c={0}", c);
      return (c == 0x000555555550_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<48>(a, 16);
      return (c == 0x555555550000_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<24>(a, 16);
      return (c == 0x550000_h24);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<48>(a, 17);
      return (c == 0xAAAAAAAA0000_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shl<24>(a, 17);
      return (c == 0xAA0000_h24);
    });

    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a >> 1;
      return (c == 0x2AAAAAAA_h);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a >> 16;
      return (c == 0x00005555_h);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a >> 17;
      return (c == 0x00002AAA_h);
    });
    TEST([]()->ch_bool {
      ch_uint16 a(0x5555_h);
      auto c = a >> 16;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint16 a(0x5555_h);
      auto c = a >> 17;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a >> 32;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = a >> 33;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0x5555555555555555);
      auto c = a >> 65;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0x5555555555555555);
      auto c = a >> 65;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<48>(a, 1);
      return (c == 0x00002AAAAAAA_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<48>(a, 4);
      return (c == 0x000005555555_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<48>(a, 16);
      return (c == 0x000000005555_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<24>(a, 16);
      return (c == 0x005555_h24);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<48>(a, 17);
      return (c == 0x000000002AAA_h48);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x55555555_h);
      auto c = ch_shr<24>(a, 17);
      return (c == 0x002AAA_h24);
    });

    TEST([]()->ch_bool {
      ch_int32 a(0xD5555555_h);
      auto c = a >> 1;
      return (c == 0xEAAAAAAA_h);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xD5555555_h);
      auto c = a >> 16;
      return (c == 0xFFFFD555_h);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xD5555555_h);
      auto c = a >> 17;
      return (c == 0xFFFFEAAA_h);
    });
    TEST([]()->ch_bool {
      ch_int16 a(0xd555_h);
      auto c = a >> 16;
      return (c == 0xFFFF_h);
    });
    TEST([]()->ch_bool {
      ch_int16 a(0xd555_h);
      auto c = a >> 17;
      return (c == 0xFFFF_h);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = a >> 32;
      return (c == 0xFFFFFFFF_h);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = a >> 33;
      return (c == 0xFFFFFFFF_h);
    });
    TEST([]()->ch_bool {
      ch_int64 a(0xd555555555555555);
      auto c = a >> 64;
      return (c == 0xffffffffffffffff);
    });
    TEST([]()->ch_bool {
      ch_int64 a(0xd555555555555555);
      auto c = a >> 65;
      return (c == 0xffffffffffffffff);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<48>(a, 1);
      //ch_print("c={0}", c);
      return (c == 0xFFFFEAAAAAAA_h48);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<48>(a, 4);
      return (c == 0xFFFFFD555555_h48);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<48>(a, 16);
      return (c == 0xFFFFFFFFD555_h48);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<24>(a, 16);
      return (c == 0xFFD555_h24);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<48>(a, 17);
      return (c == 0xFFFFFFFFEAAA_h48);
    });
    TEST([]()->ch_bool {
      ch_int32 a(0xd5555555_h);
      auto c = ch_shr<24>(a, 17);
      return (c == 0xFFEAAA_h24);
    });
    TEST([]()->ch_bool {
      ch_int<40> a(0xfffc000000_h40);
      auto c = ch_shr<25>(a, 16);
      return (c == 0x1fffc00);
    });
    TEST([]()->ch_bool {
      ch_int<40> a(0xfffc000000_h40);
      auto c = ch_shr<25>(a, 15);
      return (c == 0x1fff800);
    });

    TEST([]()->ch_bool {
      ch_uint4 a(1010_b);
      auto c = a << 2;
      return (c == 1000_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = ch_uint4(1) << a;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = ch_uint4(0100_b) >> a;
      return (c == 0001_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = ch_int4(0100_b) >> a;
      return (c == 0001_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = ch_int4(1100_b) >> a;
      return (c == 1111_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = ch_uint32(1100_b32) >> a;
      ch_int32 e = 0011_b32;
      //ch_print("c={0}, e={1}", c, e);
      return (c == e);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(5*4);
      auto c = ch_int32(0xf0000000_h) >> a;
      ch_int32 e = 0xffffff00_h;
      //ch_print("c={0}, e={1}", c, e);
      return (c == e);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(13*4);
      auto c = ch_int64(0xf000000000000000_h) >> a;
      return (c == 0xffffffffffffff00_h);
    });
    TEST([]()->ch_bool {
      ch_uint2 a(2);
      auto c = ch_uint4(0001_b) << a;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1010_b);
      auto c = a << 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1010_b);
      auto c = a >> 2;
      //ch_print("a={0}, c={0}", a, c);
      return (c == 0010_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1010_b);
      auto c = a >> 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1), b(2);
      auto c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1);
      ch_bit2 b(2);
      auto c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1);
      ch_bit8 b(2);
      auto c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1000_b), b(2);
      auto c = a >> b;
      return (c == 0010_b);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(1);
      auto c = a << 32;
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0x100000000_h64);
      auto c = a >> 32;
      return (c == 0x1_h64);
    });
    TEST([]()->ch_bool {
     ch_uint<128> a(0x10000000000000001_h128);
     auto c = a << 63;
     //ch_print("{0}: c={1}", ch_now(), c);
     return (c == 0x80000000000000008000000000000000_h128);
    });
    TEST([]()->ch_bool {
      ch_uint<128> a(0xf010000000000000000_h128);
      auto c = a >> 63;
      //ch_print("{0}: c={1}", ch_now(), c);
      return (c == 0x1e02_h128);
    });
    TEST([]()->ch_bool {
      ch_int64 a(0xf0000000f0000000_h64);
      auto c = a >> 30;
      return (c == 0xffffffffc0000003);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0xf0000000f0000000_h64);
      auto c = a.as_int() >> 30;
      return (c == 0xffffffffc0000003);
    });
    TEST([]()->ch_bool {
      ch_int64 a(0xf0000000f0000000_h64);
      auto c = a >> 32;
      return (c == 0xfffffffff0000000);
    });
    TEST([]()->ch_bool {
      ch_uint<128> a(1);
      auto c = a << 64;
      return (c == 0x10000000000000000_h128);
    });    
    TEST([]()->ch_bool {
      ch_uint<68> a(0xf0000000000000012_h68);
      auto c = ch_shl<16>(a, 4);
      return (c == 0x120);
    });
    TEST([]()->ch_bool {
      ch_uint<1>  a(1);
      auto c = ch_shl<255>(a, 32);
      return (c == 0x100000000);
    });
    TEST([]()->ch_bool {
      ch_uint<1>  a(1);
      auto c = ch_shl<64>(a, 33);
      return (c == 0x200000000);
    });
    TEST([]()->ch_bool {
      ch_uint<255> a(0x100000000);
      auto c = ch_shr<1>(a, 32);
      return (c == 0x1);
    });
    TEST([]()->ch_bool {
      ch_uint<64> a(0x200000000);
      auto c = ch_shr<1>(a, 33);
      //ch_print("{0}: c={1}", ch_now(), c);
      return (c == 0x1);
    });
    TEST([]()->ch_bool {
      ch_int<255> a(0x100000000);
      auto c = ch_shr<1>(a, 32);
      return (c == 0x1);
    });
    TEST([]()->ch_bool {
      ch_int<64> a(0x200000000);
      auto c = ch_shr<1>(a, 33);
      return (c == 0x1);
    });
    TEST([]()->ch_bool {
      ch_int<64> a(0x200000000);
      auto c = ch_shr<65>(a, 33);
      return (c == 0x1);
    });
    TEST([]()->ch_bool {
      ch_uint<148> x(0xf111111000000011111110000000000000000_h148);
      ch_uint<148> y = x >> 128;
      ch_uint<148> e = 0x0000000000000000f1111_h148;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
    TEST([]()->ch_bool {
      ch_int<148> x(0xf111111000000011111110000000000000000_h148);
      ch_int<148> y = x >> 128;
      ch_int<148> e = 0xfffffffffffffffffffffffffffffffff1111_h148;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
    TEST([]()->ch_bool {
      ch_int<148> x(0xf111111000000011111110000000000000000_h148);
      ch_int<148> y = x >> 124;
      ch_int<148> e = 0xffffffffffffffffffffffffffffffff11111_h148;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
    TEST([]()->ch_bool {
      ch_int<65> x(0x10100000001111111_h65);
      ch_int<65> y = x >> 32;
      ch_int<65> e = 0x1ffffffff01000000_h65;
      //ch_print("y={0}, e={1}", y, e);
      return (y == e);
    });
  }
  SECTION("rotate", "[rotate]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      auto c = ch_rotr(a, 2);
      return (c == 0010_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      auto c = ch_rotr(a, 5);
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      auto c = ch_rotl(a, 2);
      return (c == 0010_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      auto c = ch_rotl(a, 5);
      return (c == 0001_b);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(1);
      auto c = ch_rotr(a, 48);
      return (c == 0x10000_h64);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(1);
      auto c = ch_rotr(a, 96);
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(1);
      auto c = ch_rotl(a, 48);
      return (c == 0x1000000000000_h64);
    });
    TEST([]()->ch_bool {
      ch_bit64 a(1);
      auto c = ch_rotl(a, 96);
      return (c == 0x100000000_h64);
    });
  }
  
  SECTION("arithmetic", "[math]") {
    TEST([]()->ch_bool {
      ch_uint4 a(0x1), b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      auto c = a + 10_b4;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_int4 b(0x2);
      auto c = a | b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_bit4 b(0x2);
      auto c = a | b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0x1);
      ch_uint4 b(0x2);
      auto c = a | b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_uint8 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(0x1);
      ch_uint4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint<65> a(0x1);
      ch_uint<68> b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint<65> a(0x1);
      ch_uint<68> b(0x2);
      auto c = ch_add<32>(a, b);
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_int8 a(0x1);
      ch_int4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0x1);
      ch_int8 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-1);
      ch_int8 b(-2);
      auto c = a + b;
      return (c == -3);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0xffffffff), b(0x1);
      auto c = a + b;
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0x1);
      ch_int4 b(0x2);
      auto c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0x1);
      ch_uint8 b(0x2);
      auto c = b | a;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(0x1);
      ch_uint4 b(0x2);
      auto c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-1);
      ch_int8 b(-2);
      auto c = b - a;
      return (c == -1);
    });
    TEST([]()->ch_bool {
      ch_uint<65> a(0x1);
      ch_uint<66> b(0x2);
      auto c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1), b(0x2);
      auto c = a - b;
      return (c == 0xf);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(1);
      auto b = -a;
      return (b == 0xf);
    });
    TEST([]()->ch_bool {
      ch_int4 a(-1);
      auto b = -a;
      return (b == 0x1);
    });
    TEST([]()->ch_bool {
      ch_uint<65> a(1);
      auto b = -a;
      return (b == 0x1'ffffffff'ffffffff_h65);
    });
    TEST([]()->ch_bool {
      ch_int<4> a(-2);
      auto b = ch_abs(a);
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1);
      ch_int8 b(2);
      auto c = a * b;
      return (c == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1);
      ch_int8 b(-2);
      auto c = a * b;
      return (c == -2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(-1);
      ch_int8 b(2);
      auto c = a * b;
      return (c == -2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(-1);
      ch_int8 b(-2);
      auto c = a * b;
      return (c == 2);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(1);
      ch_uint4 b(2);
      auto c = a * b;
      return (c == 2);
    });
    TEST([]()->ch_bool {
      ch_int<100> a(-0x6ABA8);
      ch_int<102> b(0x335);
      auto c = ch_mul<127>(a, b);
      ch_bit<127> e = -0x156481C8;
      //ch_print("c={0}, e={1}", c, e);
      return (c == e);
    });
    TEST([]()->ch_bool {
      ch_int128 a(-0x6ABA8);
      ch_int<65> b(-0x335);
      auto c = ch_mul<128>(a, b);
      return (c == 0x156481C8);
    });
    TEST([]()->ch_bool {
      ch_uint128 a(0x6ABA8);
      ch_uint128 b(0x335);
      auto c = ch_mul(a, b);
      return (c == 0x156481C8);
    });
    TEST([]()->ch_bool {
      ch_uint32 a(0x10000);
      ch_uint32 b(0x10000);
      auto c = ch_mul<33>(a, b);
      return (c == 0x100000000);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1);
      ch_int8 b(2);
      auto c = a / b;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int8 a(16);
      ch_int8 b(2);
      auto c = a / b;
      return (c == 8);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(16);
      ch_uint8 b(4);
      auto c = a / b;
      return (c == 4);
    });
    TEST([]()->ch_bool {
      ch_int8 a(16);
      ch_int4 b(-2);
      auto c = a / b;
      return (c == -8);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-16);
      ch_int4 b(2);
      auto c = a / b;
      return (c == -8);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-16);
      ch_int4 b(-2);
      auto c = a / b;
      return (c == 8);
    });
    TEST([]()->ch_bool {
      ch_int<127> a(-0x15648431);
      ch_int<65> b(0x335);
      auto c = ch_div<128>(a, b);
      return (c == -0x6ABA8);
    });
    TEST([]()->ch_bool {
      ch_int128 a(-0x15648431);
      ch_int64 b(-0x335);
      auto c = ch_div(a, b);
      return (c == 0x6ABA8);
    });
    TEST([]()->ch_bool {
      ch_uint128 a(0x15648431);
      ch_uint128 b(0x335);
      auto c = ch_div(a, b);
      return (c == 0x6ABA8);
    });
    TEST([]()->ch_bool {
      ch_int8 a(16);
      ch_int4 b(2);
      auto c = a % b;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(16);
      ch_uint4 b(2);
      auto c = a % b;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int8 a(16);
      ch_int4 b(3);
      auto c = a % b;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(16);
      ch_uint4 b(3);
      auto c = a % b;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-16);
      ch_int4 b(2);
      auto c = a % b;
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int8 a(-16);
      ch_int4 b(3);
      auto c = a % b;
      return (c == -1);
    });
    TEST([]()->ch_bool {
      ch_int128 a(-0x15648431);
      ch_int128 b(0x335);
      auto c = ch_mod(a, b);
      return (c == -0x269);
    });
    TEST([]()->ch_bool {
      ch_uint128 a(0x15648431);
      ch_uint128 b(0x335);
      auto c = ch_mod(a, b);
      return (c == 0x269);
    });
  }
}
