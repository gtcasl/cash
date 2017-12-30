#include "common.h"

TEST_CASE("arithmetic", "[arithmetic]") {
  SECTION("logic", "[logic]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = ~a;
      return (c == 0011_b) && (c == 3);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = a & 0101_b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = a | 0101_b;
      return (c == 1101_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = a ^ 0101_b;
      return (c == 1001_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_nand(a, 0101_b);
      return (c == 1011_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_nor(a, 0101_b);
      return (c == 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_xnor(a, 0101_b);
      return (c == 0110_b);
    });
  }
  
  SECTION("reduce", "[reduce]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      return (ch_andr(a) == 0_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      return (ch_nandr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1111_b);
      return (ch_andr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1111_b);
      return (ch_nandr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      return (ch_orr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      return (ch_norr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0000_b);
      return (ch_orr(a) == 0_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0000_b);
      return (ch_norr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      return (ch_xorr(a) == 0_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      return (ch_xnorr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b);
      return (ch_xorr(a) == 1_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b);
      return (ch_xnorr(a) == 1_b);
    });
  }
  
  SECTION("compare", "[compare]") {
    TEST([]()->ch_bit1 {
      ch_bit4 x(0100_b);
      return (x == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0101_b);
      return (x != 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0001_b);
      return (x < 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0100_b);
      return (x > 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0100_b);
      return (x <= 1100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0100_b);
      return (x >= 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(1100_b);
      return (x >= 0100_b);
    });
  }
  
  SECTION("shift", "[shift]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      ch_bit4 c = a << 2;
      return (c == 1000_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(2);
      ch_bit4 c = 1 << a;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(2);
      ch_bit4 c = 0100_b >> a;
      return (c == 0001_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit2 a(2);
      ch_bit4 c = 0001_b << a;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      ch_bit4 c = a << 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      ch_bit4 c = a >> 2;
      return (c == 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      ch_bit4 c = a >> 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1), b(2);
      ch_bit4 c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1);
      ch_bit2 b(2);
      ch_bit4 c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1);
      ch_bit8 b(2);
      ch_bit4 c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = a >> b;
      return (c == 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(1);
      ch_bit64 c = a << 32;
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(0x100000000_h64);
      ch_bit64 c = a >> 32;
      return (c == 0x1_h64);
    });
    TEST([]()->ch_bit1 {
     ch_bit<128> a(0x10000000000000001_h128);
     ch_bit<128> c = a << 63;
     return (c == 0x80000000000000008000000000000000_h128);
    });
    TEST([]()->ch_bit1 {
      ch_bit<128> a(0xf010000000000000000_h128);
      ch_bit<128> c = a >> 63;
      return (c == 0x1e02_h128);
    });
    TEST([]()->ch_bit1 {
      ch_bit<128> a(1);
      ch_bit<128> c = a << 64;
      return (c == 0x10000000000000000_h128);
    });
  }
  SECTION("rotate", "[rotate]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotr(a, b);
      return (c == 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b), b(5);
      ch_bit4 c = ch_rotr(a, b);
      return (c == 0100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(1);
      ch_bit64 c = ch_rotr(a, 48);
      return (c == 0x10000_h64);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(1);
      ch_bit64 c = ch_rotr(a, 96);
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotl(a, b);
      return (c == 0010_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1000_b), b(5);
      ch_bit4 c = ch_rotl(a, b);
      return (c == 0001_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(1);
      ch_bit64 c = ch_rotl(a, 48);
      return (c == 0x1000000000000_h64);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(1);
      ch_bit64 c = ch_rotl(a, 96);
      return (c == 0x100000000_h64);
    });
  }
  
  SECTION("arithmetic", "[math]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0x1);
      ch_bit8 b(0x2);
      ch_bit8 c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bit1 {
      ch_bit8 a(0x1);
      ch_bit4 b(0x2);
      ch_bit8 c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_bit1 {
      ch_bit64 a(0xffffffff), b(0x1);
      ch_bit64 c = a + b;
      return (c == 0x100000000_h64);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0x1);
      ch_bit8 b(0x2);
      ch_bit4 c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bit1 {
      ch_bit8 a(0x1);
      ch_bit4 b(0x2);
      ch_bit4 c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a - b;
      return (c == 0xf);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1);
      ch_bit4 b = -a;
      return (b == 0xf);
    });
  }
}
