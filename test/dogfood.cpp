#include "common.h"

using namespace cash::core_literals;

TEST_CASE("dogfood", "[debug]") { 
  TEST([]()->ch_logic {
    ch_seq<ch_bit2> a;
    a.next = a + 1;
    ch_bit2 e = ch_select(ch_tick())
        (3, 01_b)
        (5, 10_b)
        (7, 11_b)
        (9, 00_b)
        (a);
    ch_print("t={0}, e={1} a={2}", ch_tick(), e, a);
    return (e == a);
  }, 5);
}
