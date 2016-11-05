#include "common.h"

using namespace chdl::core_literals;

TEST_CASE("literals tests", "[literals]") {   
  SECTION("test binary literals", "[binary]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0101_b);
    });
  }
  SECTION("test octal literals", "[octal]") {
    TEST([]()->ch_logic {
      ch_bit<3> a(0x5);
      return (a == 5_o);
    });
  }
  SECTION("test decimal literals", "[decimal]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 5_d);
    });
  }
  SECTION("test hexadecimal literals", "[hexadecimal]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0x5_h);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0x5p4_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x5);
      return (a == 0x5p64_h);
    });
    TEST([]()->ch_logic {
      ch_bit<8> a(0x1'0_h);
      return (a == 16);
    });
    TEST([]()->ch_logic {
      ch_bit<32> a(0x0001'0000_h);
      return (a.aslice<4>(4) == 0x1_h);
    });
    TEST([]()->ch_logic {
      ch_bit<32> a(0x00'01'00'00p32_h);
      return (a.aslice<4>(4) == 0x1_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x10000000'00000000_h);
      return (a.aslice<4>(15) == 0x1_h);
    });
  }
}
