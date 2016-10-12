#include "common.h"

TEST_CASE("basic tests", "[basic]") {   
  
  SECTION("test lierals", "[literal]") {        
    TEST([]()->ch_logic {
      ch_bitv<4> a(0x5);
      return (a == 0101_b);
    });
    TEST([]()->ch_logic {
      ch_bitv<3> a(0x5);
      return (a == 5_o);
    });
    TEST([]()->ch_logic {
      ch_bitv<4> a(0x5);
      return (a == 5_d);
    });
    TEST([]()->ch_logic {
      ch_bitv<4> a(0x5);
      return (a == 5_h);
    });
    TEST([]()->ch_logic {
      ch_bitv<4> a(0x5);
      return (a == 5e4_h);
    });
    TEST([]()->ch_logic {
      ch_bitv<64> a(0x5);
      return (a == 5e64_h);
    });
  } 
  
  SECTION("test subscript", "[subscript]") {
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
  
  SECTION("test concat", "[concat]") {
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bitv<5> c = (a, '1');
      return (c == 11001_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bitv<5> c = ('1', a);
      return (c == 11100_b);
    });
    TEST([]()->ch_logic {
      ch_bitv<6> c = (011_b, 011_b);
      return (c == 011011_b);
    });
    TEST([]()->ch_logic {
      ch_bitv<6> c = (10_b, 1011_b);
      return (c == 101011_b);
    });
  } 
  
  SECTION("test logic", "[logic]") {
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
    TEST([]()->ch_logic {
      ch_bitv<64> a(100000000e64_h);
      ch_bitv<64> c = a >> 32;
      return (c == 1e64_h);
    });
    TEST([]()->ch_logic {
      ch_bitv<64> a(1);
      ch_bitv<64> c = a << 32;
      return (c == 100000000e64_h);
    });
    /*TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotl(a, b);
      return (c == 0010_b);
    });
    TEST([]()->ch_logic {
      ch_bit4 a(1000_b), b(2);
      ch_bit4 c = ch_rotr(a, b);
      return (c == 0010_b);
    });*/
  }
  
  SECTION("test arithmetic", "[math]") {
    TEST([]()->ch_logic {
      ch_bit4 a(0x1), b(0x2);
      ch_bit4 c = a + b;
      return (c == 0x3);
    });
    TEST([]()->ch_logic {
      ch_bitv<64> a(0xffffffff), b(0x1);
      ch_bitv<64> c = a + b;
      return (c == 100000000e64_h);
    });      
  }
}


