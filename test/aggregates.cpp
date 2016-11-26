#include "common.h"

using namespace chdl::core_literals;

__ch_struct(s1_t,(
  (ch_bit4) a
),
void foo() {
  ch_bit<3> w = 100_b;
  auto y = w.slice<2>() + 1;
  a = (y, y);
}
);

__ch_struct(s2_t,(
  (ch_bit4) a,
  (ch_bit4) b
));

__ch_struct(s3_t,(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c
));

__ch_struct(s4_t,(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c,
    (ch_bit4) d
));

__ch_struct(ss_t,(
    (s1_t) a,
    (s1_t) b
));

template <unsigned N> 
 __ch_struct(st_t,(
  (ch_bit<N>) a,
  (ch_bit<N>) b
));

using st4_t = st_t<4>;
 
 __ch_union(u2_t,(
   (ch_bit4) a,
   (ch_bit4) b
 ));
 
 __ch_union(u3_t,(
    (ch_bit2) a,
    (ch_bit8) b,
    (ch_bit4) c
  ));
 
 __ch_enum(my_enum, 4,(
   idle = 0,
   execute,
   stats,
   done
 )); 
 
TEST_CASE("aggregate tests", "[aggregate]") {  
  SECTION("test structs", "[struct]") {   
    TEST([]()->ch_logic {
      s1_t s1;
      s2_t s2;
      s3_t s3;
      s4_t s4;
           
      s1.a = 1_h;
      s2 = 10_h;
      
      s3 = 100_h;
      s3.c = 1_h;
           
      s4 = 0010_h;
      s4.b = 1_h;
           
      return (s1, s4) == (s3, s2);
    });
  } 
  
  SECTION("test unions", "[union]") {
    TEST([]()->ch_logic {
      u2_t u2;
      u2.a = 1;
      return (u2.b == 1);
    });
    TEST([]()->ch_logic {
      u2_t u2;
      u2.b = 1;
      return (u2.a == 1);
    });
    TEST([]()->ch_logic {
      u3_t u3;
      u3.b = 01010101_b;
      u3.a = 11_b;
      u3.c.slice<2>(2) = 00_b;
      return (u3 == 01010011_b);
    });
  }
  
  SECTION("test vectors", "[vector]") {
    TEST([]()->ch_logic {
      ch_vec<ch_bit2, 2> a(0);
      a[0][1] = 1;
      return (a == 0010_b);
    });
    
    TEST([]()->ch_logic {
      ch_vec<ch_bit2, 2> a(0101_b), b;
      b[0][0] = a[1][1];
      b[0][1] = a[1][0];
      b[1][0] = a[0][1];
      b[1][1] = a[0][0];
      return (b == 1010_b);
    });
  }
  
  SECTION("test enums", "[enum]") {
    TEST([]()->ch_logic {
      my_enum a(my_enum::idle);
      return (a == 0);
    });
    TEST([]()->ch_logic {
      my_enum a;
      a = my_enum::execute;
      return (a == 1);
    });
  }
}
