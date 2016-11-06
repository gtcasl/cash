#include "common.h"

using namespace chdl::core_literals;

TEST_CASE("conditionals tests", "[conditionals]") {   
  SECTION("test select", "[select]") {    
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select(a < b, a, b);
      return (c == a);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select(a > b, a, b);
      return (c == b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select(a > b, a)(a == 0, 0)(b);
      return (c == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select<4>(a > b, a, 8);
      return (c == 8);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select<4>(a < b, 7, b);
      return (c == 7);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b(1), c;
      c = ch_select<4>(a < b, 3, 5);
      return (c == 3);
    });
  }
  
  SECTION("test when", "[when]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_when(a > b)(  
          c = a; 
      )();
      return (c == a);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_when(a < b)( 
          c = a; 
      )();
      return (c == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_when(a < b)( 
          c = a; 
      )__when(a > b)(
          c = b;
      )();
      return (c == b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_when(a < b)( 
          c = a; 
      )__else( 
          c = b; 
      );
      return (c == b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_when(a > b)(
        c = a - b; 
        b = 0;
      ) 
      __when(a == b)( 
        c = 0; 
      ) 
      __else(
        c = b;
      );
      return (c == 4 && b == 0);
    });
  }
  SECTION("test case", "[case]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_case(a)
      __when(0)( 
        c = a; 
      ) 
      __when(1)(
        c = b; 
      )();
      return (c == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_case(a)
      __when(0)( 
        c = a; 
      ) 
      __when(1)(
        c = b; 
      ) 
      __default(
        c = a + b;
      );
      return (c == 6);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __ch_case(a)
      __when(0)(
        c = a; 
      ) 
      __when(1)(
        c = b; 
      ) 
      __default(
         __ch_when(b > 0)( 
            c = a + b;       
         )__else(
            c = a - b;
         );        
      );
      return (c == 6);
    });
  }
}
