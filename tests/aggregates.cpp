#include "common.h"

__enum (my_enum, 4, (
  (idle, 0),
  execute,
  stats,
  done
));

__enum (my_enum2, (
  idle,
  execute,
  stats,
  done
));
static_assert(ch_width_v<my_enum2> == 2, ":-(");

__enum (my_enum3, (
  (idle,    1<<0),
  (execute, 1<<1),
  (stats,   1<<2),
  (done,    1<<3)
));
static_assert(ch_width_v<my_enum3> == 4, ":-(");

__enum (O_t, 1, (
  a
));

__enum (O2_t, (
  a
));
static_assert(ch_width_v<O2_t> == 1, ":-(");

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

__struct (sd1_t, s1_t, (
  (ch_bit4) b
));

__struct (sd2_t, sd1_t, (
  (ch_bit4) c
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));
 
__union (u2_4_t, (
  (ch_bit2) a,
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

using v2_1_t = ch_vec<ch_bit2, 1>;
using v2_2_t = ch_vec<ch_bit2, 2>;
using v2_3_t = ch_vec<ch_bit2, 3>;

/*__struct (W_t, (
  (v2_1_t) a
));*/

TEST_CASE("aggregates", "[aggregates]") {
  SECTION("structs", "[struct]") {
    TEST([]()->ch_bool {
      s1_t s1;
      s2_t s2(10_h);
      s3_t s3(100_h);
      s4_t s4(0010_h);
           
      s1.a = 1_h;
      s3.c = 1_h;           
      s4.b = 1_h;
           
      return ch_cat(s1, s4) == ch_cat(s3, s2);
    });
    TEST([]()->ch_bool {
      s2_t s2(1_b4, 0_b4);
      return (s2.as_bit() == 10000_b8);
    });    
    TEST([]()->ch_bool {
      s3_t s3{3, 2, 1};
      return (s3.as_bit() == 0x321_h12);
    });
    TEST([]()->ch_bool {
      sd1_t a(21_h), b(2_h, 1_h);
      return (a.as_bit() == b.as_bit());
    });
    TEST([]()->ch_bool {
      sd3_t a(321_h), b(3_h, 21_h);
      return (a.as_bit() == b.as_bit());
    });
    TEST([]()->ch_bool {
      sd3_t a(321_h), b(a);
      return (a.as_bit() == b.as_bit());
    });
    TEST([]()->ch_bool {
      auto force_move_a = []() {
        return ch_bit4{1};
      };
      auto force_move_b = []() {
        return ch_bit4{2};
      };
      s2_t s{0};
      s.a = force_move_a();
      s.b = force_move_b();
      return (s.as_bit() == 21_h);
    });
    TEST([]()->ch_bool {
      auto force_move_assignment = []() {
        return sd3_t{321_h};
      };
      sd3_t a;
      a = force_move_assignment();
      return (a.as_bit() == 321_h);
    });
    TEST([]()->ch_bool {
      auto force_move_assignment = []() {
        return sd3_t{321_h};
      };
      sd3_t a(force_move_assignment());
      return (a.as_bit() == 321_h);
    });
  } 
  
  SECTION("unions", "[union]") {
    TEST([]()->ch_bool {
      u2_4_t u2(0);
      u2.a = 1;
      return (u2.b == 1);
    });
    TEST([]()->ch_bool {
      u2_4_t u2(0);
      u2.b = 1;
      return (u2.a == 1);
    });
    TEST([]()->ch_bool {
      u3_t u3(0);
      u3.b = 01010101_b;
      u3.a = 11_b;
      u3.c.slice<2>(2) = 00_b;
      return (u3.as_bit() == 01010011_b);
    });    
    TEST([]()->ch_bool {
      u2_4_t a(3);
      return (a.as_bit() == 3);
    });
    TEST([]()->ch_bool {
      u2_4_t a(0011_b4);
      return (a.as_bit() == 3);
    });
    TEST([]()->ch_bool {
      u2_4_t a(11_b2);
      return (a.as_bit() == 3);
    });
  }
  
  SECTION("vectors", "[vector]") {
    TEST([]()->ch_bool {
      v2_2_t a{0, 0};
      a[0][1] = 1;
      return (a.as_bit() == 0010_b);
    });

    TEST([]()->ch_bool {
      v2_3_t a{3, 2, 1};
      return (a.as_bit() == 111001_b);
    });

    TEST([]()->ch_bool {
      v2_1_t a{3};
      return (a[0] == 11_b);
    });

    TEST([]()->ch_bool {
      v2_2_t a{01_b, 10_b};
      return (a[0] == 10_b && a[1] == 01_b);
    });
    
    TEST([]()->ch_bool {
      v2_2_t a{1, 1}, b;
      b[0][0] = a[1][1];
      b[0][1] = a[1][0];
      b[1][0] = a[0][1];
      b[1][1] = a[0][0];
      return (b.as_bit() == 1010_b);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_bit2, 2> a{11_b, 00_b}, b{00_b, 11_b};
      auto c = ch_orr(a[0] & b[0]);
      return (c == 0);
    });
  }
  
  SECTION("enums", "[enum]") {
    TEST([]()->ch_bool {
      my_enum a(my_enum::idle);
      return (0 == a.as_bit());
    });
    TEST([]()->ch_bool {
      my_enum a(my_enum::idle), b(a);
      return (a == b);
    });
    TEST([]()->ch_bool {
      my_enum a(my_enum::idle), b(my_enum::execute);
      return (a != b);
    });
    TEST([]()->ch_bool {
      my_enum a;
      a = my_enum::execute;
      return (1 == a.as_bit());
    });
  }
}
