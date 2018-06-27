#include "common.h"

namespace {

__struct (Q_t, (
  (ch_bit2) a,
  (ch_bit2) b
));

}

TEST_CASE("memory", "[memory]") {
  SECTION("rom", "[rom]") {
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_bit4 q;
      ch_rom<ch_bit4, 3> rom({0xA, 0xB, 0xC});
      q = rom.read(a);
      a <<= ch_min(a + 1, 2);
      ch_bit4 e = ch_case(ch_time(),
            2,  0xA_h)
           (4,  0xB_h)
           (6,  0xC_h)
           (8,  0xC_h)
               (q);
      //ch_print("t={0}, a={1}, q={2}", ch_time(), a, q);
      return (e == q);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_bit4 q;
      ch_rom<ch_bit4, 3> rom({0xA, 0xB, 0xC});
      q = ch_delay(rom.read(a));
      a <<= ch_min(a + 1, 2);
      ch_bit4 e = ch_case(ch_time(),
            3,  0xA_h)
           (5,  0xB_h)
           (7,  0xC_h)
           (9,  0xC_h)
               (q);
      //ch_print("t={0}, a={1}, q={2}", ch_time(), a, q);
      return (e == q);
    }, 4);
  }
  
  SECTION("mem", "[mem]") {
    TEST([]()->ch_bool {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bool en;
      ch_mem<ch_bit4, 4> mem;
      q = mem.read(a);
      mem.write(a, d, en);
      ch_bind(a, d, en) = ch_delay(
        ch_case(ch_time(),
           3,  ch_cat(00_b, 0xA_h, 1_b))
          (5,  ch_cat(01_b, 0xB_h, 1_b))
          (7,  ch_cat(10_b, 0xC_h, 1_b))
          (9,  ch_cat(11_b, 0xD_h, 1_b))
          (11, ch_cat(01_b, 0x0_h, 0_b))
          (13, ch_cat(00_b, 0xE_h, 1_b))
          (15, ch_cat(10_b, 0x0_h, 0_b))
          (17, ch_cat(00_b, 0x0_h, 0_b))
          (19, ch_cat(11_b, 0x0_h, 0_b))
              (ch_cat(00_b, 0x0_h, 0_b)));
      ch_bit4 e = ch_case(ch_time(),
            11, 0xB_h)
           (13, 0xA_h)
           (15, 0xC_h)
           (17, 0xE_h)
           (19, 0xD_h)
               (q);
      //ch_print("t={0}, clk={1}, rst={2}, a={3}, d={4}, en={5}, q={6}, e={7}", ch_time(), ch_clock(), ch_reset(), a, d, en, q, e);
      return (q == e);
    }, 5);

    TEST([]()->ch_bool {
      ch_bit2 a;
      ch_uint4 d, q;
      ch_bool en;
      ch_mem<ch_uint4, 4> mem;
      q = (mem.read(a) + 1) - 1;
      mem.write(a, d, en);
      ch_bind(a, d, en) = ch_delay(
        ch_case(ch_time(),
           3,  ch_cat(00_b, 0xA_h, 1_b))
          (5,  ch_cat(01_b, 0xB_h, 1_b))
          (7,  ch_cat(10_b, 0xC_h, 1_b))
          (9,  ch_cat(11_b, 0xD_h, 1_b))
          (11, ch_cat(01_b, 0x0_h, 0_b))
          (13, ch_cat(00_b, 0xE_h, 1_b))
          (15, ch_cat(10_b, 0x0_h, 0_b))
          (17, ch_cat(00_b, 0x0_h, 0_b))
          (19, ch_cat(11_b, 0x0_h, 0_b))
              (ch_cat(00_b, 0x0_h, 0_b)));
      ch_bit4 e = ch_case(ch_time(),
            11, 0xB_h)
           (13, 0xA_h)
           (15, 0xC_h)
           (17, 0xE_h)
           (19, 0xD_h)
               (q);
      //ch_print("t={0}, clk={1}, rst={2}, a={3}, d={4}, en={5}, q={6}, e={7}", ch_time(), ch_clock(), ch_reset(), a, d, en, q, e);
      return (q == e);
    }, 5);

    TEST([]()->ch_bool {
      ch_mem<Q_t, 2> mem;
      mem.write(0, Q_t(11_b, 01_b));
      auto x = mem.read(0).as_bit();
      auto e = ch_delay(1101_b);
      //ch_print("t={0}, x={1}, e={2}", ch_time(), x, e);
      return (x == e);
    }, 1);
  }
}
