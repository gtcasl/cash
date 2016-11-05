#include "common.h"

using namespace chdl::core_literals;

TEST_CASE("registers tests", "[registers]") {  
  SECTION("test registers", "[reg][register]") {
    TEST([]()->ch_logic {
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
    TEST([]()->ch_logic {
      ch_bit2 a;
      a = ch_reg(ch_reg(a + 1));
      ch_bit2 e = ch_select(ch_tick())
           (5, 01_b)
           (9, 10_b)
           (13,11_b)
           (17,00_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 9);
  }
  
  SECTION("test latches", "[latch]") {
    
  }
}
