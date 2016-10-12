#include "common.h"

__ch_struct(S1_t)(
  (ch_bit4) a
);

__ch_struct(S2_t)(
  (ch_bit4) a,
  (ch_bit4) b
);

__ch_struct(S3_t)(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c
);

__ch_struct(S4_t)(
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c,
    (ch_bit4) d
);

__ch_struct(SS_t)(
    (S1_t) a,
    (S1_t) b
);

__ch_union(U2_t)(
  (ch_bit4) a,
  (ch_bit4) b
);

template <unsigned N> 
 __ch_struct(ST_t)(
  (ch_bitv<N>) a,
  (ch_bitv<N>) b
);

typedef ST_t<4> ST4_t;
 
 TEST_CASE("aggregate tests", "[aggregate]") {     
   
   SECTION("test structs", "[struct]") {     
     TEST([]()->ch_logic {
       S1_t s1;
       S2_t s2;
       S3_t s3;
       S4_t s4;
            
       s1 = 1_h;
       s2 = 10_h;
       
       s3 = 000_h;
       s3.c = 1_h;
            
       s4 = 0000_h;
       s4.b = 1_h;
            
       return ((s1, s4) == (s3, s2));
     });     
   }
 }
