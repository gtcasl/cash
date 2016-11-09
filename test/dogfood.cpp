#include "common.h"
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/punctuation/remove_parens.hpp>

using namespace chdl::core_literals;

int g_debugbreak = 0;

static void debugbreak() {
  g_debugbreak = 1;
}

TEST_CASE("dogfood", "[debug]") {        
  TEST([]()->ch_logic {
    ch_bit2 a;
    ch_bit4 d, q;
    ch_logic en;
    ch_mem<4, 2> mem({0xA, 0xB, 0xC, 0xD});
    q = ch_reg<4>(mem[a]); 
    __ch_when(en)(
      mem[a] = d;
    )();
    (a, d, en) = ch_reg(ch_select(ch_tick())
        (2, (01_b, 0x0_h, 0_b))
        (4, (00_b, 0xE_h, 1_b))
        (6, (10_b, 0x0_h, 0_b))
        (8, (00_b, 0x0_h, 0_b))
        (10,(11_b, 0x0_h, 0_b))
           ((00_b, 0x0_h, 0_b)));             
    ch_bit4 e = ch_select(ch_tick())
        (3, 0xA_h)
        (5, 0xB_h)
        (7, 0xA_h)
        (9, 0xC_h)
        (11,0xE_h)
           (q);
    ch_print("t={0}, a={1}, d={2}, en={3}, q={4}, e={5}", ch_tick(), a, d, en, q, e);
    return '1';// (q == e);
  }, 6);
}
