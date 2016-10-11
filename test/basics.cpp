#include "common.h"

TEST_CASE("basic tests", "[basic]") {  
  SECTION("test arithmetic") {
    TEST([]()->ch_logic {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a + b;
      return (c == 0x3);
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
      ch_bit4 a(1);
      ch_bit4 c = a << 2;
      return (c == 0100_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b);
      ch_bit4 c = a >> 2;
      return (c == 0010_b);
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
  }  
  SECTION("test subscript") {
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      return (c == 11_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.aslice<2>(1) ^ 01_b;
      return (c == 10_b);
    });
  }
  SECTION("test concat") {
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bitv<5> c = (a, '1') ^ 01010_b;
      return (c == 10011_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bitv<5> c = ('1', a) ^ 00101_b;
      return (c == 11001_b);
    });
  }
}


