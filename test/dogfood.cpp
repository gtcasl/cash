#include "common.h"

using namespace cash::core_literals;

__struct (s32_t,(
  (ch_bit1)  a,
  (ch_bit2)  b,
  (ch_bit4)  c,
  (ch_bit8)  d,
  (ch_bit1)  e,
  (ch_bit16) f
));

TEST_CASE("dogfood", "[dogfood]") { 
  /*TEST([]()->ch_bit1 {
    ch_seq<ch_bit2> x;
    ch_seq<ch_bit2> y(x);
    ch_seq<ch_bit2> e;

    auto  a = ch_select(ch_tick()).when<2>(8, 0)(6, 2)(4, 3)(2, 1)(0);

    y.next = a;
    e.next = a;

    ch_print("t={0}, clk={1}, y={2}, e={3}", ch_tick(), ch_clock(), y, e);

    return y == e;
  }, 4);*/
}
