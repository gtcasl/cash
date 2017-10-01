#include "common.h"

__enum (my_enum, 4, (
  (idle, 0),
  execute,
  stats,
  done
));

__enum (O_t, 1, (
  a
));

__struct (s1_t, (
  (ch_bit4) a
  ));

__struct (s2_t, (
  (ch_bit4) a,
  (ch_bit4) b
));

__struct (s3_t, (
  (ch_bit4) a,
  (ch_bit4) b,
  (ch_bit4) c
));

struct Q_t {
  __struct (value_t, (
    (ch_bit4) a,
    (ch_bit4) b,
    (ch_bit4) c
  ));
  value_t value;
};

__struct (s4_t, (
  (ch_bit4) a,
  (ch_bit4) b,
  (ch_bit4) c,
  (ch_bit4) d
));

__struct (ss_t, (
  (s1_t) a,
  (s1_t) b
));

template <unsigned N> 
__struct (st_t, (
  (ch_bit<N>) a,
  (ch_bit<N>) b
));

using st4_t = st_t<4>;
 
__union (u2_t, (
  (ch_bit4) a,
  (ch_bit4) b
  ));
 
__union (u3_t, (
  (ch_bit2) a,
  (ch_bit8) b,
  (ch_bit4) c
));

__struct (U_t, (
  (O_t) a
));
 
TEST_CASE("aggregates", "[aggregates]") {
  SECTION("structs", "[struct]") {
    TEST([]()->ch_bit1 {
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
    TEST([]()->ch_bit1 {
      s2_t s2(1_b4, 0_b4);
      return (s2 == 10000_b8);
    });
    TEST([]()->ch_bit1 {
      s3_t s3{3, 2, 1};
      return (s3 == 0x321_h12);
    });
  } 
  
  SECTION("unions", "[union]") {
    TEST([]()->ch_bit1 {
      u2_t u2;
      u2.a = 1;
      return (u2.b == 1);
    });
    TEST([]()->ch_bit1 {
      u2_t u2;
      u2.b = 1;
      return (u2.a == 1);
    });
    TEST([]()->ch_bit1 {
      u3_t u3;
      u3.b = 01010101_b;
      u3.a = 11_b;
      u3.c.slice<2>(2) = 00_b;
      return (u3 == 01010011_b);
    });
  }
  
  SECTION("vectors", "[vector]") {
    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 2> a(0, 0);
      a[0][1] = 1;
      return (a == 0010_b);
    });

    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 3> a{3, 2, 1};
      return (a == 111001_b);
    });

    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 1> a{3};
      return (a[0] == 11_b);
    });

    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 2> a{01_b, 10_b};
      return (a[0] == 10_b && a[1] == 01_b);
    });
    
    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 2> a(1, 1), b;
      b[0][0] = a[1][1];
      b[0][1] = a[1][0];
      b[1][0] = a[0][1];
      b[1][1] = a[0][0];
      return (b == 1010_b);
    });

    TEST([]()->ch_bit1 {
      ch_vec<ch_bit2, 2> a(11_b, 00_b), b{00_b, 11_b};
      auto c = ch_orr(a[0] & b[0]);
      return (c == 0);
    });
  }
  
  SECTION("enums", "[enum]") {
    TEST([]()->ch_bit1 {
      my_enum a(my_enum::idle);
      return (0 == a);
    });
    TEST([]()->ch_bit1 {
      my_enum a;
      a = my_enum::execute;
      return (a == 1);
    });
  }
}
