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
  }  
}


