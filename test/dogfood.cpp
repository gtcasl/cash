#include "common.h"

using namespace cash::core_literals;

TEST_CASE("dogfood", "[dogfood]") {
  TEST([]()->ch_bit1 {
    ch_bit2 a;
    ch_bit1 x(1), y(0);
    __if (x) (
      ch_bit2 b;
      __if (y) (
        b = 1;
      )
      __else (
        b = 2;
      );
      a = b;
    )
    __else (
      a = 0;
    );
    return (a == 2);
  });
}
