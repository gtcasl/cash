#include "common.h"
#include <htl/fixed.h>

using namespace ch::htl;

TEST_CASE("fixed", "[fixed]") {
  SECTION("logic", "[logic]") {
    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x8000), b(0x10000);
      auto c = a + b;
      //ch_println("a={0}, b={1}, c={2}", a, b, c);
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
      //ch_println("a={0}, b={1}, c={2}", a, b, c);
      return (c == 0x4000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(-0x8000), b(0x8000);
      auto c = a * b;
      ch_int32 e = -0x4000;
      //ch_println("a={0}, b={1}, c={2}, e={3}", a, b, c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0.1f), b(0.5f);
      auto c = a * b;
      auto e = ch_fixed<32, 16>(0.05f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<28, 15> a(0.1f), b(0.5f);
      auto c = a * b;
      auto e = ch_fixed<28, 15>(0.05f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(-0.1f), b(0.5f);
      auto c = a * b;
      auto e = ch_fixed<32, 16>(-0.05f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<24, 16> a(-0.1f), b(0.5f);
      auto c = a * b;
      auto e = ch_fixed<24, 16>(-0.05f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(-0.25f), b(0.25f);
      auto c = a * b;
      auto e = ch_fixed<32, 16>(-0.0625f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<28, 15> a(-0.25f), b(0.25f);
      auto c = a * b;
      auto e = ch_fixed<28, 15>(-0.0625f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<25, 15> a(-0.25f), b(0.25f);
      auto c = a * b;
      auto e = ch_fixed<25, 15>(-0.0625f);
      //ch_println("c={0}, e={1}", c, e);
      return (c == e);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0x18000), b(0x8000);
      auto c = a / b;
      //ch_println("a={0}, b={1}, c={2}", a, b, c);
      return (c == 0x30000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(0.25);
      //ch_println("a={0}", a);
      return (a == 0x4000);
    });

    TEST([]()->ch_bool {
      ch_fixed<32, 16> a(-0.125);
      //ch_println("a={0}", a);
      return (a == -0x2000);
    });
  }

  SECTION("system", "[system]") {
    TESTX([]()->bool {
      ch_sfixed<32, 16> a(0x8000), b(0x10000);
      auto c = a + b;
      return (c == 0x18000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(0x18000), b(0x8000);
      auto c = a - b;
      return (c == 0x10000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(0x8000), b(0x8000);
      auto c = a * b;
      return (c == 0x4000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(-0x8000), b(0x8000);
      auto c = a * b;
      return (c == -0x4000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(-0.25f), b(0.25f);
      auto c = a * b;
      //std::cout << "c=" << (float)c << std::endl;
      return ((float)c == -0.0625f);
    });

    TESTX([]()->bool {
      ch_sfixed<28, 15> a(-0.25f), b(0.25f);
      auto c = a * b;
      //std::cout << "c=" << (float)c << std::endl;
      return ((float)c == -0.0625f);
    });

    TESTX([]()->bool {
      ch_sfixed<25, 15> a(-0.25f), b(0.25f);
      auto c = a * b;
      //std::cout << "c=" << (float)c << std::endl;
      return ((float)c == -0.0625f);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(0x18000), b(0x8000);
      auto c = a / b;
      return (c == 0x30000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(0.25);
      return (a == 0x4000);
    });

    TESTX([]()->bool {
      ch_sfixed<32, 16> a(-0.125);
      return (a == -0x2000);
    });
  }
}
