#include "common.h"

__struct (Q_t, (
  (ch_bit2) a,
  (ch_bit2) b
));

TEST_CASE("memory", "[memory]") {
  SECTION("rom", "[rom]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 q;
      ch_rom<ch_bit4, 4> rom({0xA, 0xB, 0xC, 0xD});
      q = rom[a];  
      a = ch_reg(a + 1);
      ch_bit4 e = ch_case(ch_getTick(), 2, 0xA_h)(4, 0xB_h)(6, 0xC_h)(8, 0xD_h)(10,0xA_h)(q);
      ch_print("t={0}, a={1}, q={2}", ch_getTick(), a, q);
      return (e == q);
    }, 10);
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 q;
      ch_rom<ch_bit4, 4> rom({0xA, 0xB, 0xC, 0xD});
      q = ch_reg(rom[a]);
      a = ch_reg(a + 1);
      ch_bit4 e = ch_case(ch_getTick(), 3, 0xA_h)(5, 0xB_h)(7, 0xC_h)(9, 0xD_h)(11,0xA_h)(q);
      //ch_print("t={0}, a={1}, q={2}", ch_getTick(), a, q);
      return (e == q);
    }, 12);
  }
  
  SECTION("ram", "[ram]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bit1 en;
      ch_ram<ch_bit4, 4> mem({0xA, 0xB, 0xC, 0xD});
      q = mem[a];
      __if (en) {
        mem[a] = d;
      };
      ch_tie(a, d, en) = ch_reg(
        ch_case(ch_getTick(),
           2, ch_cat(01_b, 0x0_h, 0_b))
          (4, ch_cat(00_b, 0xE_h, 1_b))
          (6, ch_cat(10_b, 0x0_h, 0_b))
          (8, ch_cat(00_b, 0x0_h, 0_b))
          (10,ch_cat(11_b, 0x0_h, 0_b))
             (ch_cat(00_b, 0x0_h, 0_b)));
      ch_bit4 e = ch_case(ch_getTick(), 3, 0xB_h)(5, 0xA_h)(7, 0xC_h)(9, 0xE_h)(11,0xD_h)(q);
      ch_print("t={0}, clk={1}, a={2}, d={3}, en={4}, q={5}, e={6}", ch_getTick(), ch_getClock(), a, d, en, q, e);
      return (q == e);
    }, 12);

    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bit1 en;
      ch_ram<ch_bit4, 4> mem({0xA, 0xB, 0xC, 0xD});
      q = (mem[a] + 1) - 1;
      __if (en) {
        mem[a] = d;
      };
      ch_tie(a, d, en) = ch_reg(
        ch_case(ch_getTick(),
           2, ch_cat(01_b, 0x0_h, 0_b))
          (4, ch_cat(00_b, 0xE_h, 1_b))
          (6, ch_cat(10_b, 0x0_h, 0_b))
          (8, ch_cat(00_b, 0x0_h, 0_b))
          (10,ch_cat(11_b, 0x0_h, 0_b))
             (ch_cat(00_b, 0x0_h, 0_b)));
      ch_bit4 e = ch_case(ch_getTick(), 3, 0xB_h)(5, 0xA_h)(7, 0xC_h)(9, 0xE_h)(11,0xD_h)(q);
      ch_print("t={0}, clk={1}, a={2}, d={3}, en={4}, q={5}, e={6}", ch_getTick(), ch_getClock(), a, d, en, q, e);
      return (q == e);
    }, 12);
    
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bit1 en;
      ch_ram<ch_bit4, 4> mem({0xA, 0xB, 0xC, 0xD});
      q = ch_reg(mem[a]);
      __if (en) {
        mem[a] = d;
      };
      ch_tie(a, d, en) = ch_reg(
        ch_case(ch_getTick(),
           2, ch_cat(01_b, 0x0_h, 0_b))
          (4, ch_cat(00_b, 0xE_h, 1_b))
          (6, ch_cat(10_b, 0x0_h, 0_b))
          (8, ch_cat(00_b, 0x0_h, 0_b))
          (10,ch_cat(11_b, 0x0_h, 0_b))
             (ch_cat(00_b, 0x0_h, 0_b)));
      ch_bit4 e = ch_case(ch_getTick(), 3, 0xA_h)(5, 0xB_h)(7, 0xA_h)(9, 0xC_h)(11,0xE_h)(q);
      //ch_print("t={0}, a={1}, d={2}, en={3}, q={4}, e={5}", ch_getTick(), a, d, en, q, e);
      return (q == e);
    }, 12);
    TEST([]()->ch_bit1 {
      ch_ram<Q_t, 2> mem;
      mem[0] = Q_t(1101_b);
      auto x = mem[0].asBits();
      auto e = ch_reg(1101_b);
      ch_print("t={0}, x={1}, e={2}", ch_getTick(), x, e);
      return (x == e);
    }, 4);
  }

  SECTION("partial_write", "[partial_write]") {
    TEST([]()->ch_bit1 {
      ch_ram<Q_t, 2> mem;
      mem[0].a = 1;
      mem[1].b = 2;
      auto x = mem[0].asBits();
      auto y = mem[1].asBits();
      auto e1 = ch_reg(0001_b);
      auto e2 = ch_reg(1000_b);
      ch_print("t={0}, x={1}, e1={2}, y={3}, e2={4}", ch_getTick(), x, e1, y, e2);
      return (x == e1 && y == e2);
    }, 4);
  }
}
