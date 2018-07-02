#include <htl/fixed.h>
#include <htl/complex.h>
#include "common.h"

using namespace ch::htl;

TEST_CASE("complex", "[complex]") {
  SECTION("arithmetic", "[arithmetic]") {
    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x8000);
      auto b = -a;
      return (b.re == -0x8000 && b.im == -0x4000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x8000), b(-0x4000, -0x8000);
      auto c = a + b;
      return (c.re == 0x0 && c.im == 0x0);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x4000), b(0x8000, 0x8000);
      auto c = a + b;
      return (c.re == 0xC000 && c.im == 0xC000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x8000), b(-0x4000, -0x8000);
      auto c = a - b;
      return (c.re == 0x10000 && c.im == 0x8000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x4000), b(0x8000, 0x8000);
      auto c = a - b;
      return (c.re == -0x4000 && c.im == -0x4000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x8000), b(-0x4000, -0x8000);
      auto c = a * b;
      //ch_print("c.r={0}, c.i={1}", c.re, c.im);
      return (c.re == -0x3000 && c.im == -0x4000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x4000, 0x4000), b(0x8000, 0x8000);
      auto c = a * b;
      //ch_print("c.r={0}, c.i={1}", c.re, c.im);
      return (c.re == 0 && c.im == 0x4000);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x8000, 0x8000), b(0x8000, 0x8000);
      auto c = a / b;
      //ch_print("c.r={0}, c.i={1}", c.re, c.im);
      return (c.re == 0x10000 && c.im == 0x0);
    });

    TEST([]()->ch_bool {
      ch_complex<ch_fixed<32, 16>> a(0x8000, 0x8000), b(-0x8000, 0x8000);
      auto c = a / b;
      //ch_print("c.r={0}, c.i={1}", c.re, c.im);
      return (c.re == 0x0 && c.im == 0x10000);
    });
  }
}
