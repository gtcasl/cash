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
      a->next = ch_min(a + 1, 2);
      ch_bit4 e = ch_case(ch_now(),
            2,  0xA_h)
           (4,  0xB_h)
           (6,  0xC_h)
           (8,  0xC_h)
               (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_rom<ch_bit32, 3> rom({0xA, 0xB, 0xC});
      auto q = rom.read(a);
      a->next = ch_min(a + 1, 2);
      auto e = ch_case<ch_bit32>(ch_now(),
            2,  0xA)
           (4,  0xB)
           (6,  0xC)
           (8,  0xC)
               (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_rom<ch_bit<33>, 3> rom({0x0, 0xA, 0x0, 0xB, 0x0, 0xC});
      auto q = rom.read(a);
      a->next = ch_min(a + 1, 2);
      auto e = ch_case<ch_bit<33>>(ch_now(),
            2,  0xA)
           (4,  0xB)
           (6,  0xC)
           (8,  0xC)
               (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_bit<5> q;
      ch_rom<ch_bit<5>, 3> rom({0xA, 0xB, 0xC});
      q = rom.read(a);
      a->next = ch_min(a + 1, 2);
      auto e = ch_case<ch_bit<5>>(ch_now(),
           2,  0xA_h5)
          (4,  0xB_h5)
          (6,  0xC_h5)
          (8,  0xC_h5)
              (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      std::array<uint8_t, 9> data = {0x1, 0x2, 0x1, 0x3, 0x4, 0x1, 0x5, 0x6, 0x1};
      ch_reg<ch_uint2> a(0);
      ch_bit<17> q;
      ch_rom<ch_bit<17>, 3> rom(data);
      q = rom.read(a);
      a->next = ch_min(a + 1, 2);
      auto e = ch_case<ch_bit<17>>(ch_now(),
           2,  0x10201_h17)
          (4,  0x10403_h17)
          (6,  0x10605_h17)
              (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_bit4 q;
      ch_rom<ch_bit4, 3> rom({0xA, 0xB, 0xC});
      q = ch_delay(rom.read(a));
      a->next = ch_min(a + 1, 2);
      ch_bit4 e = ch_case(ch_now(),
            3,  0xA_h)
           (5,  0xB_h)
           (7,  0xC_h)
           (9,  0xC_h)
               (q);
      //ch_println("t={0}, a={1}, q={2}, e={3}", ch_now(), a, q, e);
      return (q == e);
    }, 4);
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      ch_rom<ch_bit4, 4> rom("res/rom.hex");
      auto q = ch_delay(rom.read(a));
      a->next = ch_min(a + 1, 3);
      auto e = ch_case(ch_now(),
            3,  0xA_h)
           (7,  0xB_h)
           (9,  0xC_h)
               (q);
      //ch_println("t={}, rst={}, clk={}, a={}, q={}, e={}", ch_now(), ch_reset(), ch_clock(), a, q, e);
      return (q == e);
    }, 4);
  }
  
  SECTION("mem", "[mem]") {
    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bool en;
      ch_mem<ch_bit4, 4> mem;
      q = mem.read(a);
      mem.write(a, d, en);
      ch_tie(a, d, en) = ch_delay(
        ch_case(ch_now(),
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
      ch_bit4 e = ch_case(ch_now(),
            11, 0xB_h)
           (13, 0xA_h)
           (15, 0xC_h)
           (17, 0xE_h)
           (19, 0xD_h)
               (q);
      //ch_println("t={0}, clk={1}, rst={2}, a={3}, d={4}, en={5}, q={6}, e={7}", ch_now(), ch_clock(), ch_reset(), a, d, en, q, e);
      return (q == e);
    }, 5);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_bit2 a;
      ch_uint4 d, q;
      ch_bool en;
      ch_mem<ch_uint4, 4> mem;
      q = (mem.read(a) + 1) - 1;
      mem.write(a, d, en);
      ch_tie(a, d, en) = ch_delay(
        ch_case(ch_now(),
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
      ch_bit4 e = ch_case(ch_now(),
            11, 0xB_h)
           (13, 0xA_h)
           (15, 0xC_h)
           (17, 0xE_h)
           (19, 0xD_h)
               (q);
      //ch_println("t={0}, clk={1}, rst={2}, a={3}, d={4}, en={5}, q={6}, e={7}", ch_now(), ch_clock(), ch_reset(), a, d, en, q, e);
      return (q == e);
    }, 5);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<Q_t, 2> mem;
      mem.write(0, Q_t(11_b, 01_b));
      auto x = mem.read(0).as_bit();
      auto e = ch_delay(1101_b);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 1 || x == e);
    }, 2);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<ch_bit32, 3> mem;
      mem.write(1, 0x55);
      auto x = mem.read(1).as_bit();
      auto e = ch_delay<ch_bit32>(0x55);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 1 || x == e);
    }, 2);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<ch_bit<65>, 3> mem;
      mem.write(1, 0x55);
      auto x = mem.read(1).as_bit();
      auto e = ch_delay<ch_bit<65>>(0x55);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 1 || x == e);
    }, 2);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<ch_bit<65>, 3, true> mem;
      mem.write(1, 0x55);
      auto x = mem.read(1).as_bit();
      auto e = ch_delay<ch_bit<65>>(0x55, 2);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 3 || x == e);
    }, 3);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<ch_bit<65>, 3, true> mem;
      ch_bool en(true);
      mem.write(1, 0x55);
      auto x = mem.read(1, en).as_bit();
      auto e = ch_delay<ch_bit<65>>(0x55, 2);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 3 || x == e);
    }, 3);

    TEST([]()->ch_bool {
      auto_cflags_disable reg_init_off(cflags::force_reg_init);
      ch_mem<ch_bit<33>, 3> mem;
      mem.write(1, 0x55);
      auto x = mem.read(1).as_bit();
      auto e = ch_delay<ch_bit<33>>(0x55);
      //ch_println("t={0}, x={1}, e={2}", ch_now(), x, e);
      return (ch_now() < 1 || x == e);
    }, 2);

    TEST([]()->ch_bool {
      ch_mem<ch_bit4, 4, true> mem;
      auto we = ch_case<ch_bool>(ch_now(), 7, 1)(5, 0)(3, 1)(1, 1)(1);
      auto wa = ch_case<ch_bit2>(ch_now(), 7, 3)(5, 0)(3, 2)(1, 0)(0);
      auto wv = ch_case<ch_bit4>(ch_now(), 7, 3)(5, 3)(3, 2)(1, 1)(0);
      auto re = ch_case<ch_bool>(ch_now(), 7, 1)(5, 0)(3, 1)(1, 1)(0);
      auto ra = ch_case<ch_bit2>(ch_now(), 7, 2)(5, 2)(3, 0)(1, 0)(0);
      mem.write(wa, wv, we);
      auto q = mem.read(ra, re);
      auto e = ch_case<ch_bit4>(ch_now(), 7, 2)(5, 1)(3, 1)(q);
      //ch_println("t={0}, we={1}, wa={2}, wv={3}, re={4}, ra={5}, q={6}, e={7}", ch_now(), we, wa, wv, re, ra, q, e);
      return (ch_now() < 1 || q == e);
    }, 4);
  }
}
