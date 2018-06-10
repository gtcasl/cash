#include "common.h"

TEST_CASE("arithmetic", "[arithmetic]") {
  SECTION("logic", "[logic]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = ~a;
      return (c == 0011_b) && (c == 3);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1100_b);
      auto c = a & 0101_b;
      return (c == 0100_b);
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
  }
  
  SECTION("compare", "[compare]") {
    TEST([]()->ch_bool {
      ch_bit4 x(0100_b);
      return (x == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 x(0101_b);
      return (x != 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0001_b);
      return (x < 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x > 0010_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x <= 1100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(0100_b);
      return (x >= 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 x(1100_b);
      return (x >= 0100_b);
    });
  }
  
  SECTION("shift", "[shift]") {
    TEST([]()->ch_bool {
      ch_uint4 a(1010_b);
      auto c = a << 2;
      return (c == 1000_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = 1 << a;
      return (c == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(2);
      auto c = 0100_b >> a;
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
      auto c = ch_int32(1100_b) >> a;
      return (c == 0011_b);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(5*4);
      auto c = ch_int32(0xf0000000_h) >> a;
      return (c == 0xffffff00_h);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(13*4);
      auto c = ch_int64(0xf000000000000000_h) >> a;
      return (c == 0xffffffffffffff00_h);
    });
    TEST([]()->ch_bool {
      ch_uint2 a(2);
      auto c = 0001_b << a;
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
      ch_print("a={0}, c={0}", a, c);
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
     return (c == 0x80000000000000008000000000000000_h128);
    });
    TEST([]()->ch_bool {
      ch_uint<128> a(0xf010000000000000000_h128);
      auto c = a >> 63;
      return (c == 0x1e02_h128);
    });
    TEST([]()->ch_bool {
      ch_int64 a(0xf0000000f0000000_h64);
      auto c = a >> 30;
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
      ch_uint4 a(0x1), b(0x2);
      auto c = ch_add(a, b);
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      auto c = a + 10_b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      auto c = ch_add(a, 10_b);
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_int4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_bit4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0x1);
      ch_uint4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0x1);
      ch_uint8 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_int8 a(0x1);
      ch_int4 b(0x2);
      auto c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_uint64 a(0xffffffff), b(0x1);
      auto c = a + b;
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0x1), b(0x2);
      auto c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0x1);
      ch_uint8 b(0x2);
      auto c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bool {
      ch_uint8 a(0x1);
      ch_uint4 b(0x2);
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
  }
}
