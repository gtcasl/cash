#include "common.h"

using namespace cash::core_literals;

TEST_CASE("smoke", "[smoke]") {
  TEST([]()->ch_bit1 {
    ch_bit4 a, b, c;
    a = 0xf_h;
    b = a;
    c = b + 1;
    b = 0;
    return (c == 1);
  });

  TEST([]()->ch_bit1 {
    ch_bit2 a, b;
    a = 0;
    b = a;
    a = 1;
    return (b == 1);
  });
}
