#include "common.h"

using namespace cash::core_literals;

TEST_CASE("memory", "[memory]") {
  SECTION("rom", "[rom]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 q;
      ch_rom<4, 2> rom({0xA, 0xB, 0xC, 0xD});
      q = rom[a];  
      a = ch_reg(a + 1);
      ch_bit4 e = ch_select(ch_getTick())
          (2, 0xA_h)
          (4, 0xB_h)
          (6, 0xC_h)
          (8, 0xD_h)
          (10,0xA_h)
             (q);
      ch_print("t={0}, a={1}, q={2}", ch_getTick(), a, q);
      return (e == q);
    }, 10);
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 q;
      ch_rom<4, 2> rom({0xA, 0xB, 0xC, 0xD});
      q = ch_reg<4>(rom[a]);  
      a = ch_reg(a + 1);
      ch_bit4 e = ch_select(ch_getTick())
         (3, 0xA_h)
         (5, 0xB_h)
         (7, 0xC_h)
         (9, 0xD_h)
         (11,0xA_h)
            (q);
      //ch_print("t={0}, a={1}, q={2}", ch_getTick(), a, q);
      return (e == q);
    }, 12);
  }
  
  SECTION("mem", "[mem]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bit1 en;
      ch_ram<4, 2> mem({0xA, 0xB, 0xC, 0xD});
      q = mem[a];
      __if (en) ( 
        mem[a] = d;
      );
      ch_tie(a, d, en) = ch_reg(ch_select(ch_getTick())
          (2, (01_b, 0x0_h, 0_b))
          (4, (00_b, 0xE_h, 1_b))
          (6, (10_b, 0x0_h, 0_b))
          (8, (00_b, 0x0_h, 0_b))
          (10,(11_b, 0x0_h, 0_b))
             ((00_b, 0x0_h, 0_b)));             
      ch_bit4 e = ch_select(ch_getTick())
          (3, 0xB_h)
          (5, 0xA_h)
          (7, 0xC_h)
          (9, 0xE_h)
          (11,0xD_h)
             (q);
      ch_print("t={0}, clk={1}, a={2}, d={3}, en={4}, q={5}, e={6}", ch_getTick(), ch_getClock(), a, d, en, q, e);
      return (q == e);
    }, 12);
    
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      ch_bit4 d, q;
      ch_bit1 en;
      ch_ram<4, 2> mem({0xA, 0xB, 0xC, 0xD});
      q = ch_reg<4>(mem[a]); 
      __if (en) (
        mem[a] = d;
      );
      ch_tie(a, d, en) = ch_reg(ch_select(ch_getTick())
          (2, (01_b, 0x0_h, 0_b))
          (4, (00_b, 0xE_h, 1_b))
          (6, (10_b, 0x0_h, 0_b))
          (8, (00_b, 0x0_h, 0_b))
          (10,(11_b, 0x0_h, 0_b))
             ((00_b, 0x0_h, 0_b)));             
      ch_bit4 e = ch_select(ch_getTick())
          (3, 0xA_h)
          (5, 0xB_h)
          (7, 0xA_h)
          (9, 0xC_h)
          (11,0xE_h)
             (q);
      //ch_print("t={0}, a={1}, d={2}, en={3}, q={4}, e={5}", ch_getTick(), a, d, en, q, e);
      return (q == e);
    }, 12);
  }
}
