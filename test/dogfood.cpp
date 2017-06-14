#include "common.h"

using namespace cash::core_literals;

TEST_CASE("dogfood", "[debug]") { 
  TEST([]()->ch_bit1 {
    ch_vec<ch_bit2, 2> a(0);
    a[0][1] = 1;
    return (a == 0010_b);
  });
}
