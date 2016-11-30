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
  
  SECTION("test if", "[if]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __if (a > b) (  
          c = a; 
      );
      return (c == a);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __if (a < b) ( 
          c = a; 
      );
      return (c == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __if (a < b) ( 
          c = a; 
      )
      __elif (a > b) (
          c = b;
      );
      return (c == b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __if (a < b) ( 
          c = a; 
      )
      __else ( 
          c = b; 
      );
      return (c == b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __if (a > b) (
        c = a - b; 
        b = 0;
      ) 
      __elif (a == b) ( 
        c = 0; 
      ) 
      __else(
        c = b;
      );
      return (c == 4 && b == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<2> a;
      ch_logic x(1), y(0);
      __if (x) (
        ch_bit<2> b;
        __if (y) (
          b = 1;
        )
        __else (
          b = 2;
        );
        a = b;
      )
      __else (
        a = 0;
      );
      return (a == 2);
    });
  }
  SECTION("test switch", "[switch]") {
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __switch (a) (
      __case (0) ( 
        c = a; 
      ) 
      __case (1) (
        c = b; 
      ));
      return (c == 0);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __switch (a) (
      __case (0) ( 
        c = a; 
      ) 
      __case (1) (
        c = b; 
      ) 
      __default (
        c = a + b;
      ));
      return (c == 6);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(5), b(1), c(0);
      __switch (a) (
      __case (0) (
        c = a; 
      ) 
      __case (1) (
        c = b; 
      ) 
      __default (
         __if (b > 0) ( 
            c = a + b;       
         )
         __else (
            c = a - b;
         );        
      ));
      return (c == 6);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(1), b(1), c(2), d, e;
      __switch (a) (
      __case (0) ( 
        d = 0; 
      ) 
      __case (1) (
         __if (b == 0) (
           d = 1;
         )
         __elif (b == 1) (
           e = 1;
         )
         __else (
           d = 0;
           e = 0;         
         );
      )
      __default(
         d = c;
         e = c;         
      ));
      return (d + e == 3);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b;
      __switch (a) (
      __case (0) ( 
        b.slice<3>(0) = 101_b; 
      ) 
      __case (1) (
        b = 0; 
      )
      __default(
        b = 1000_b;
      ));
      return (b == 1101_b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b;
      __switch (a) (
      __case (0) ( 
        b[0] = 1;
        b[1] = 0;
        b[2] = 1;
      ) 
      __case (1) (
        b[1] = 1; 
      )
      __default(
        b = 1000_b;
      ));
      return (b == 1101_b);
    });
    TEST([]()->ch_logic {
      ch_bit<4> a(0), b;
      __switch (a) (
      __case (0) ( 
        b = ch_zext<4>(10_b);
      ) 
      __case (1) (
        b = ch_zext<4>(01_b);
      )
      __default (
        b = 1000_b;
      ));
      return (b == 0010_b);
    });
  }
}
