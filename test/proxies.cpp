#include "common.h"

using namespace cash::core_literals;

TEST_CASE("proxies", "[proxies]") {
  SECTION("subscript", "[subscript]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TEST([]()->ch_bit1 {
       ch_bit4 a(0110_b);
       return (a[0] == a[3] && a[1] == a[2]);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      ch_bit1 x, y;
      a[3] = x;
      a[2] = y;
      x = 1_b;
      y = 0_b;
      return (a[2] == 0_b && a[3] == 1_b);
    });
  }
  
  SECTION("slice", "[slice]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      return (c == 11_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.aslice<2>(1) ^ 01_b;
      return (c == 10_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      a.slice<3>(0) = '0';
      a[3] = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      ch_bit4 b(a);
      a.slice<3>(0) = '0';
      a[3] = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      ch_bit4 b(a);
      a.slice<3>(0) = '0';
      ch_bit1 x;
      a[3] = x;
      x = '1';
      return a == 1000_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      a[0] = '0';
      a[1] = '1';
      a[2] = '1';
      a[3] = '0';
      a[0] = '1';
      a[3] = '1';
      a.slice<2>(1) = '0';     
      return a == 1001_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(0);
      ch_bit2 x, y;
      a.slice<2>(0) = x;
      a.slice<2>(2) = y;
      x = '1';
      y = '1';
      return a == 0101_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a, b(1);
      ch_bit4 c = a + b;
      a.slice<2>(0) = 1; // a = 0001
      a.slice<2>(1) = 1; // a = 0011
      a.slice<2>(2) = 1; // a = 0111
      ch_print("c={0}", c);
      return (c == 1000_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a;
      ch_bit1 x;
      ch_bit2 y;
      ch_bit2 z;

      a[0] = x;
      a.slice<2>(1) = y;
      a[3] = x;
      y = z;

      x = 1_b;
      z = 10_b;
      return (a == 1101_b);
    });
    TEST([]()->ch_bit1 {
     ch_bit4 a;
     ch_bit1 x, y;
     ch_bit<3> z;
     ch_bit1 w;

     a[0] = x;
     a[1] = y;
     a.slice<3>(0) = z;
     a[3] = w;

     x = 0_b;
     y = 1_b;     
     z = 001_b;
     w = 1_b;
     return (a == 1001_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 x(0x0);
      x.slice<3>(1).slice<2>() = 11_b;
      return (x == 0110_b);
    });
  }
  
  SECTION("concat", "[concat]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit<5> c = (a, 1_b);
      return (c == 11001_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit<5> c = (1_b, a);
      return (c == 11100_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit<6> c = (011_b, 011_b);
      return (c == 011011_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit<6> c = (10_b, 1011_b);
      return (c == 101011_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit4 c = (a[3], a[2], a[1], a[0]);
      return (c == 1100_b && (a[3], a[0]) == 10_b);
    });
    TEST([]()->ch_bit1 {
       ch_bit4 a(1100_b);
       ch_bit4 c = (a[3], a[0], a[0], a[0]);
       return (c == 1000_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit2 x(0), y(0);
      (y, x) = 0101_b;
      ch_print("x={0}", x);
      return (x == 01_b && y == 01_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit2 x(0), y(0), z(0);
      (z, y, x) = 010101_b;
      ch_print("x={0}, y={1}, z={2}", x, y, z);
      return (x == 01_b && y == 01_b && z == 01_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit2 x(0), y(0);
      (y, x).slice<2>() = 01_b;
      (x, y).slice<2>() = 01_b;
      ch_print("x={0}, y={1}", x, y);
      return (x == 01_b && y == 01_b);
    });
  }
}
