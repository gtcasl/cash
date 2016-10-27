#include "common.h"

__ch_struct(s1_t)(
  (ch_bit4) a
);

__ch_struct(s2_t)(
  (ch_bit4) a,
  (ch_bit4) b
);

__ch_struct(s3_t)(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c
);

__ch_struct(s4_t)(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c,
    (ch_bit4) d
);

__ch_struct(ss_t)(
    (s1_t) a,
    (s1_t) b
);

template <unsigned N> 
 __ch_struct(st_t)(
  (ch_bitv<N>) a,
  (ch_bitv<N>) b
);

typedef st_t<4> st4_t;
 
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
}
