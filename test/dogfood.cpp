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
    auto clk  = ch_select(ch_tick()).when<1>(8, 1)(6, 1)(4, 1)(2, 1)(1, 0)(0);
    auto rst  = ch_select(ch_tick()).when<1>(5, 1)(0);
    auto next = ch_select(ch_tick()).when<2>(7, 3)(5, 1)(3, 3)(2, 1)(1, 2)(0);

    ch_push_clock(clk);
    ch_push_reset(rst);

    auto r = ch_reg(next);

    ch_pop_clock();
    ch_pop_reset();

    auto e = ch_select(ch_tick()).when<2>(9, 3)(8, 3)(5, 3)(4, 3)(3, 2)(2, 2)(0);

    ch_print("t={0}, clk={1}, clk2={2}, rst={3}, next={4}, r={5}, e={6}", ch_tick(), ch_clock(), clk, rst, next, r, e);

    return '1';
  }, 4);*/
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
