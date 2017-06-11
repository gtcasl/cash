#include "common.h"

using namespace cash::core_literals;

TEST_CASE("dogfood", "[debug]") { 
  TEST([]()->ch_logic {
    ch_bit4 a;
    ch_bit2 x(a.slice<2>(0));
    ch_bit2 y(a.slice<2>(2));
    a.slice<2>(1) = '0';
    x = '1';
    y = '1';
    return (a == 0101_b);
  });

  TEST([]()->ch_logic {
    ch_bit4 a;
    ch_logic x = a[3];
    ch_logic y = a[2];
    x = 1_b;
    y = 0_b;
    return (a[2] == 0_b && a[3] == 1_b);
  });
}
