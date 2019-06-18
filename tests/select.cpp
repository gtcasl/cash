#include "common.h"

TEST_CASE("conditionals", "[conditionals]") {
  SECTION("select", "[select]") {
    TEST1([](const ch_int8& x)->ch_bool {
      ch_int4 a(7), b(1);
      auto c = ch_sel(x[0], a, b);
      return (c == a);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), c;
      c = ch_sel(a > b, a, b);
      return (c == b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), c;
      c = ch_sel<ch_int4>(a > b, 3, 2);
      return (c == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), c;
      c = ch_sel(a > b, a)(a == 0, 0)(b);
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), c;
      c = ch_sel(a > b, a, 8);
      return (c == 8);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), c;
      c = ch_sel(a < b, 7, b);
      return (c == 7);
    });
    TEST([]()->ch_bool {
      ch_uint4 a(0), b(1), c;
      c = ch_sel(a < b, 3_h4, 5_h4);
      return (c == 3);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1);
      auto c = ch_min(a, b);
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1);
      auto c = ch_max(a, b);
      return (c == 1);
    });
  }
  
  SECTION("if", "[if]") {
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __if (a > b) {
        c = a;
      };
      return (c == a);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __if (a < b) {
        c = a;
      };
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __if (a < b) {
        c = a;
      } __elif (a > b) {
        c = b;
      };
      return (c == b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __if (a < b) {
        c = a;
      } __else {
        c = b;
      };
      return (c == b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0), d(1);
      __if (a > b) {
        c = a - d;
        d = 0;
      } __elif (a == b) {
        c = 0;
      } __else {
        c = d;
      };
      //ch_println("c={0}, d={1}", c, d);
      return (c == 5 && d == 0);
    });
    TEST([]()->ch_bool {
      ch_bit2 a;
      ch_bit1 x(1), y(0);
      __if (x) {
        ch_bit2 b;
        __if (y) {
          b = 1;
        } __else {
          b = 2;
        };
        a = b;
      } __else {
        a = 0;
      };
      return (a == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0), b;
       b = 1;
       __if (a == 1) {
         b = 0;
       };
      return (b == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1), b;
       b = 1;
       __if (a == 1) {
         b = 0;
         b = 2;
       };
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0), b;
      b = 1;
      __if (a == 1) {
        b = 0;
      } __else {
        b = 2;
      };
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(3), b;
      __if (a == 1) {
        b = 2;
      }__elif (a == 3) {
        b = 1;
      }__else {
        b = 2;
      };
      return (b == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1), b(0), c;
      __if (a == 1) {
        c = 0;
        __if (b == 1) {
          c = 1;
        };
      } __else {
        c = 2;
      };
      //ch_println("c={0}", c);
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1), b(0), c;
      __if (a == 1) {
        c = 0;
        __if (b == 1) {
          c = 1;
        } __else {
          c = 3;
        };
      } __else {
        c = 2;
      };
      return (c == 3);
    });
    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit8 a(t[0]), b(t[0]), x;
      __if (a == 1) {
        x = 0;
        __if (b == 0) {
          x = 1;
        } __elif (b == 1) {
          x = 2;
        } __else {
          x = 3;
        };
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 2);
    });
    TEST([]()->ch_bool {
      ch_int8 a(1), b(1), x;
      __if (a == 1) {
         x = 0;
         __if (b < 1) {
           x = 1;
         } __elif (b < 2) {
           x = 2;
         } __else {
           x = 3;
         };
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 2);
    });
    TEST([]()->ch_bool {
      ch_int8 a(1), b(0), x;
      __if (a == 1) {
         x = 0;
         __if (b < 1) {
           x = 1;
         } __elif (b < 2) {
           x = 2;
         } __else {
           x = 3;
         };
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 1);
    });
    TEST([]()->ch_bool {
      ch_int8 a(1), b(2), x;
      __if (a == 1) {
        x = 0;
        __if (b == 0) {
          x = 1;
        } __elif (b == 1) {
          x = 2;
        } __else {
          x = 3;
        };
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 3);
    });
    TEST([]()->ch_bool {
      ch_int8 a(1), b(2), x;
      __if (a == 1) {
        x = 0;
        __if (b == 0) {
          x = 1;
        } __elif (b == 1) {
          x = 2;
        };
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 0);
    });
    TEST1([](const ch_int8& t)->ch_bool {
      ch_int8 a(1), b(1), x;
      __if (a == t[0]) {
        x = 0;
        __if (b == t[1]) {
          x = 1;
        } __elif (b == t[0]) {
          x = 2;
        };
        x = 3;
      } __else {
        x = 4;
      };
      //ch_println("x={0}", x);
      return (x == 3);
    });
    TEST([]()->ch_bool {
      ch_int8 a(1), b(1), x, y;
      __if (a == 1) {
        ch_tie(y, x) = 0x0706;
        __if (b == 0) {
          x = 1;
        } __elif (b == 1) {
          y = 2;
        };
      } __else {
        x = 4;
        y = 5;
      };
      //ch_println("x={0}, y={1}", x, y);
      return (x == 6 && y == 2);
    });

    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __if (a > b) {
        c = 1;
        c = a;
      };
      return (c == a);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b;
       b = 1;
       __if (a == 1) {
         b = 0;
       } __else {
         b = 1;
         b = 2;
       };
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b, c(0);
      b = 1;
      __if (a == 1) {
        b = 0;
      } __else {
        b = 2;
        c = 2;
      };
      return (b == 2 && c == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b, c(0);
      b = 1;
      __if (a == 1) {
        b = 0;
      } __else {
        b = 2;
        c = 1;
        c = 2;
      };
      //ch_println("b={0}, c={1}", b, c);
      return (b == 2 && c == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(1), x(1);
      __if (x == 1) {
        a = 3;
      } __else {
        b = 4;
      };
      //ch_println("b={0}", b);
      return (b == 1);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(0);
      __if (a == 1) {
        b = 1;
      } __elif (a == 0) {
        b[1] = 1;
      } __else {
        b = 1000_b;
      };
      //ch_println("b={0}", b);
      return (b == 0010_b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(3), b(0);
      __if (a == 1) {
        b = 1;
      } __elif (a == 2) {
        b.sliceref<3>() = 1;
      } __elif (a == 3) {
        b.sliceref<2>(2) = 1;
      } __else {
        b = 1000_b;
      };
      //ch_println("b={0}", b);
      return (b == 0100_b);
    });
    TEST([]()->ch_bool {
      ch_int4 a(3), b(0), c(2);
      __if (a == 1) {
        b = 1;
      } __elif (c == 2) {
        b = 3;
      } __elif (a == 3) {
        b = 3;
      } __else {
        b = 3;
      };
      return (b == 3);
    });
    TEST([]()->ch_bool {
      ch_int4 a(3), b(0), c(2);
      __if (a == 1) {
        b = 3;
      } __elif (c == 2) {
        b = 2;
      } __elif (a == 3) {
        b = 3;
      } __else {
        b = 3;
      };
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(3), b(0), c(2);
      __if (a == 1) {
        b = 1;
      } __elif (c == 2) {
        b = 2;
      } __elif (c == 4) {
        b = 4;
      } __elif (a == 3) {
        b = 1;
      } __else {
        b = 3;
      };
      return (b == 2);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(0), c(2), d(2);
      __if (a == 1) {
        b = 1;
      } __elif (c == 2) {
        b = 1;
      } __elif (d == 2) {
        b = 3;
      } __else {
        b = 4;
      };
      return (b == 1);
    });
    TEST([]()->ch_bool {
      ch_int4 a(0), b(0), c(2);
      __if (a == 1) {
        b = 1;
      } __elif (c == 2) {
        b = 1;
      } __else {
        b = 1;
      };
      return (b == 1);
    });
  }
  SECTION("switch", "[switch]") {
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __switch (a)
      __case(0) { c = a; }
      __case(1) { c = b; };
      return (c == 0);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __switch (a)
      __case(0) { c = a; }
      __case(1) { c = b; }
      __default { c = a + b; };
      return (c == 6);
    });
    TEST([]()->ch_bool {
      ch_int4 a(5), b(1), c(0);
      __switch (a)
      __case(0) { c = a; }
      __case(1) { c = b; }
      __default {
         __if (b > 0) {
           c = a + b;
         } __else {
           c = a - b;
         };
      };
      return (c == 6);
    });
    TEST([]()->ch_bool {
      ch_int4 a(1), b(1), c(2), d(0), e(0);
      __switch (a)
      __case(0) { d = 1;}
      __case(1) {
         d = c;
         __if (b == 0) {
           d = 2;
         } __elif (b == 1) {
           e = 1;
         }__else {
           d = 3;
           e = 2;
         };
      }
      __default {
         d = c;
         e = c;         
      };
      //ch_println("d={}, e={}", d, e);
      return (d == 2 && e == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0), b(0);
      __switch (a)
      __case(0) {
        b.sliceref<3>(0) = 101_b;
      }
      __case(1) {
        b = 0;
      }
      __default {
        b = 1000_b;
      };
      return (b == 0101_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0), b;
      b[3] = 1;
      __switch (a)
      __case (0) {
        b[0] = 1;
        b[1] = 0;
        b[2] = 1;
      }
      __case (1) {
        b = 0;
      }
      __default {
        b = 1000_b;
      };
      return (b == 1101_b);
    });
    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 a, b;
      a = ch_slice<4>(t,1);
      __switch (a)
      __case(0) { b = 0010_b; }
      __case(1) { b = 0001_b; }
      __default { b = 1000_b; };
      return (b == 0010_b);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 b;
      __switch (t)
      __case(5)  { b = 0011_b; }
      __case(7)  { b = 0011_b; }
      __case(10) { b = 0001_b; }
      __case(11) { b = 0110_b; }
      __case(12) { b = 0010_b; }
      __case(1)  { b = 0010_b; }
      __default  { b = 1111_b; };
      return (b == 0010_b);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 b;
      __switch (t)
      __case(0)  { b = 0100_b; }
      __case(7)  { b = 0001_b; }
      __case(10) { b = 0001_b; }
      __case(11) { b = 0110_b; }
      __case(12) { b = 0011_b; }
      __case(1)  { b = 0010_b; }
      __default  { b = 1111_b; };
      return (b == 0010_b);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 b;
      __switch (t)
      __case(5)  { b = 0010_b; }
      __case(7)  { b = 0001_b; }
      __case(10) { b = 0001_b; }
      __case(11) { b = 0110_b; }
      __case(12) { b = 0011_b; }
      __case(2)  { b = 0010_b; }
      __default  { b = 1111_b; };
      return (b == 1111_b);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 b;
      __switch (t+11)
      __case(5)  { b = 0010_b; }
      __case(7)  { b = 0001_b; }
      __case(10) { b = 0001_b; }
      __case(12) { b = 0011_b; }
      __case(2)  { b = 0010_b; }
      __default  { b = 1111_b; };
      return (b == 0011_b);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      ch_bit4 b;
      __switch (t+12)
      __case(5)  { b = 0010_b; }
      __case(7)  { b = 0001_b; }
      __case(10) { b = 0001_b; }
      __case(12) { b = 0011_b; }
      __case(2)  { b = 0010_b; }
      __default  { b = 1111_b; };
      return (b == 1111_b);
    });

    TEST([]()->ch_bool {
      ch_bit4 v1(1), v2(2), t1(3), f1(2), a;
     __if (v2 == 2) {
       __if (v1 == 1) {
         a = t1;
       } __else {
         a = f1;
       };
     } __else {
       a = f1;
     };
      return (a == 3);
    });

    TEST([]()->ch_bool {
      ch_bit4 v1(1), v2(2), t1(3), f1(2), a;
      __switch (v2)
      __case (2) {
        __switch (v1)
        __case (1) {
          a = t1;
        }
        __default {
          a = f1;
        };
      }
      __default {
        a = f1;
      };
      return (a == 3);
    });

    TEST([]()->ch_bool {
      ch_bit128 k(2), c1(3), c2(2), c3(1), a;
      __switch (k)
      __case (1) {
        a = c1;
       }
      __case (2) {
        a = c2;
      }
      __default {
        a = c3;
      };
      //ch_println("a={0}, c2={1}", a, c2);
      return (a == c2);
    });

    TEST([]()->ch_bool {
      ch_bit128 k(0), c1(3), c2(2), c3(1), a;
      __switch (k)
      __case (1) {
        a = c1;
      }
      __case (2) {
        a = c2;
      }
      __default {
        a = c3;
      };
      return (a == c3);
    });

    TEST([]()->ch_bool {
      ch_bit128 k(0), c1(3), c3(1), a;
      __switch (k)
      __case (1) {
        a = c1;
      }
      __case (2) {
        a = c3;
      }
      __default {
        a = c3;
      };
      return (a == c3);
    });

    TEST([]()->ch_bool {
      ch_bit128 k(2), c1(3), c3(1), a;
      __switch (k)
      __case (1) {
        a = c1;
      }
      __case (2) {
        a = c1;
      }
      __default {
        a = c3;
      };
      return (a == c1);
    });

    TEST([]()->ch_bool {
      ch_bit128 k(1), c1(3), c3(1), a;
      __switch (k)
      __case (1) {
        a = c1;
      }
      __case (2) {
        a = c1;
      }
      __default {
        a = c1;
      };
      return (a == c1);
    });
  }
}
