#include "common.h"

using namespace chdl::core_literals;

TEST_CASE("literals tests", "[literals]") {   
  SECTION("test binary literals", "[binary]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0101_b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 00000000101_b4);
    });
    TEST([]()->ch_logic {
      ch_bit<3> a(0x7);
      return (a == 0x7_h3);
    });
  }
  SECTION("test octal literals", "[octal]") {
    TEST([]()->ch_logic {
      ch_bit<3> a(0x5);
      return (a == 5_o);
    });
    TEST([]()->ch_logic {
      return (0x1c0000000_h64 == 070000000000_o64);
    });
  }
  SECTION("test hexadecimal literals", "[hexadecimal]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0x5_h);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0x5);
      return (a == 0x5_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x5);
      return (a == 0x5_h64);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x5);
      return (a == 0x00'05_h64);
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
      ch_bit<32> a(0x00'01'00'00_h32);
      return (a.aslice<4>(4) == 0x1_h);
    });
    TEST([]()->ch_logic {
      ch_bit<64> a(0x10000000'00000000_h);
      return (a.aslice<4>(15) == 0x1_h);
    });
  }
}
