#include "common.h"

using namespace chdl::core_literals;

TEST_CASE("arithmetic tests", "[arithmetic]") {      
  SECTION("test logic", "[logic]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = ~a;
      return (c == 0011_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = a & 0101_b;
      return (c == 0100_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = a | 0101_b;
      return (c == 1101_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = a ^ 0101_b;
      return (c == 1001_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_nand(a, 0101_b);
      return (c == 1011_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_nor(a, 0101_b);
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit4 c = ch_xnor(a, 0101_b);
      return (c == 0110_b);
    });
  }
  
  SECTION("test reduce", "[reduce]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      return (ch_andr(a) == 0_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1111_b);
      return (ch_andr(a) == 1_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      return (ch_orr(a) == 1_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      return (ch_orr(a) == 1_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      return (ch_xorr(a) == 0_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b);
      return (ch_xorr(a) == 1_b);
    });
  }
  
  SECTION("test compare", "[compare]") {
    TEST([]()->ch_logic {
      return (0100_b == 0100_b);
    });
    TEST([]()->ch_logic {
      return (0101_b != 0100_b);
    });
    TEST([]()->ch_logic {
      return (0001_b < 0100_b);
    });
    TEST([]()->ch_logic {
      return (0100_b > 0010_b);
    });
    TEST([]()->ch_logic {
      return (0100_b <= 1100_b);
    });
    TEST([]()->ch_logic {
      return (0100_b >= 0100_b);
    });
    TEST([]()->ch_logic {
      return (1100_b >= 0100_b);
    });
  }
  
  SECTION("test shift", "[shift]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      ch_bit4 c = a << 2;
      return (c == 1000_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      ch_bit4 c = a << 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      ch_bit4 c = a >> 2;
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1010_b);
      ch_bit4 c = a >> 5;
      return (c == 0000_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1), b(2);
      ch_bit4 c = a << b;
      return (c == 0100_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = a >> b;
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(1);
      ch_bit<64> c = a << 32;
      return (c == 0x100000000p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x100000000p64_h);
      ch_bit<64> c = a >> 32;
      return (c == 0x1p64_h);
    });
    TEST([]()->ch_logic {
     ch_bit<128> a(0x10000000000000001p128_h);
     ch_bit<128> c = a << 63;
     return (c == 0x80000000000000008000000000000000p128_h);
    });
    TEST([]()->ch_logic {
      ch_bit<128> a(0xf010000000000000000p128_h);
      ch_bit<128> c = a >> 63;
      return (c == 0x1e02p128_h);
    });
    TEST([]()->ch_logic {
      ch_bit<128> a(1);
      ch_bit<128> c = a << 64;
      return (c == 0x10000000000000000p128_h);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotl(a, b);
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotr(a, b);
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(5);
      ch_bit4 c = ch_rotl(a, b);
      return (c == 0001_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(5);
      ch_bit4 c = ch_rotr(a, b);
      return (c == 0100_b);
    });    
    TEST([]()->ch_logic {
      ch_bit<64> a(1);
      ch_bit<64> c = ch_rotl(a, 48);
      return (c == 0x1000000000000p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(1);
      ch_bit<64> c = ch_rotl(a, 96);
      return (c == 0x100000000p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(1);
      ch_bit<64> c = ch_rotr(a, 48);
      return (c == 0x10000p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(1);
      ch_bit<64> c = ch_rotr(a, 96);
      return (c == 0x100000000p64_h);
    });
  }
  
  SECTION("test arithmetic", "[math]") {
    TEST([]()->ch_logic {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a + b;
      return (c == 3);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0xffffffff), b(0x1);
      ch_bit<64> c = a + b;
      return (c == 0x100000000p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = b - a;
      return (c == 1);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a - b;
      return (c == 0xf);
    });
  }
}
