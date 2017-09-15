#include "common.h"

using namespace cash::core_literals;

__out(ch_bit1) foo1() {
  __ret(1_b);
}

__out(ch_bit1, ch_bit2) foo2(const ch_bit2& x) {
  __ret(x == 1, x);
}

TEST_CASE("procedure", "[procedure]") {
  SECTION("function", "[function]") {
    TEST([]()->ch_bit1 {
      ch_bit1 a = foo1();
      return (a == 1);
    });

    TEST([]()->ch_bit1 {
      ch_bit1 a;
      ch_bit2 b(3), c;
      std::tie(a, c)= foo2(b);
      return (a == 0 && c == b);
    });
  }
}
