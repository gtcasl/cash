#include <htl/fixed.h>
#include "common.h"

using namespace ch::htl;

TEST_CASE("fixed", "[fixed]") {
  SECTION("arithmetic", "[arithmetic]") {
    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0, 0x8000), b(0, 0x8000);
      auto c = a + b;
      ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x10000_h32);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(1, 0x8000), b(0, 0x8000);
      auto c = a - b;
      return (c == 0x10000_h32);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0, 0x8000), b(0, 0x8000);
      auto c = a * b;
      ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x4000_h32);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(1, 0x8000), b(0, 0x8000);
      auto c = a / b;
      ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x30000_h32);
    });
  }
}
