#include <htl/fixed.h>
#include "common.h"

using namespace ch::htl;

TEST_CASE("fixed", "[fixed]") {
  SECTION("logic", "[logic]") {
    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x8000), b = ch_fixed<32, 16>::fromInt(1);
      auto c = a + b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x18000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x18000), b(0x8000);
      auto c = a - b;
      return (c == 0x10000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x8000), b(0x8000);
      auto c = a * b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x4000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(-0x8000), b(0x8000);
      auto c = a * b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == -0x4000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x18000), b(0x8000);
      auto c = a / b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x30000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a = ch_fixed<32, 16>::fromReal(0.25);
      //ch_print("a={0}", a);
      return (a == 0x4000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a = ch_fixed<32, 16>::fromReal(-0.125);
      //ch_print("a={0}", a);
      return (a == -0x2000);
    });
  }

  SECTION("scalar", "[scalar]") {
    TESTX([]()->bool {
      ch_scfixed<32, 16> a(0x8000), b = ch_scfixed<32, 16>::fromInt(1);
      auto c = a + b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x18000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a(0x18000), b(0x8000);
      auto c = a - b;
      return (c == 0x10000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a(0x8000), b(0x8000);
      auto c = a * b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x4000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a(-0x8000), b(0x8000);
      auto c = a * b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == -0x4000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a(0x18000), b(0x8000);
      auto c = a / b;
      //ch_print("a={0}, b={1}, c={0}", a, b, c);
      return (c == 0x30000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a = ch_scfixed<32, 16>::fromReal(0.25);
      return (a == 0x4000);
    });

    TESTX([]()->bool {
      ch_scfixed<32, 16> a = ch_scfixed<32, 16>::fromReal(-0.125);
      return (a == -0x2000);
    });
  }
}
