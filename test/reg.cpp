#include "common.h"

using namespace cash::core_literals;

TEST_CASE("registers tests", "[registers]") {  
  SECTION("test registers", "[reg][register]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_reg(a + 1);
      ch_bit2 e = ch_select(ch_tick())
           (3, 01_b)
           (5, 10_b)
           (7, 11_b)
           (9, 00_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_reg<2>(a + 1, 1);
      ch_bit2 e = ch_select(ch_tick())
           (3, 10_b)
           (5, 11_b)
           (7, 00_b)
           (9, 01_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a;
      a.next = a + 1;
      ch_bit2 e = ch_select(ch_tick())
           (3, 01_b)
           (5, 10_b)
           (7, 11_b)
           (9, 00_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a(1);
      a.next = a + 1;
      ch_bit2 e = ch_select(ch_tick())
           (3, 10_b)
           (5, 11_b)
           (7, 00_b)
           (9, 01_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
  }
  
  SECTION("test latches", "[latch]") {
    // TODO
  }
}
