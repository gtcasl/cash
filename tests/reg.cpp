#include "common.h"

__struct(X, (
(ch_bit2) q,
(ch_bit2) p
));

__union(U, (
(ch_bit1) q,
(ch_bit2) p
));

using V2 = ch_vec<ch_bit2, 2>;

__enum(E, 2, (
  a,
  b,
  c,
  d
));

TEST_CASE("registers", "[registers]") {
  SECTION("delay", "[delay]") {
    TEST([]()->ch_bool {
      ch_bit2 a;
      a = ch_delay(11_b);
      ch_bit2 e = ch_case(ch_time(), 3, 11_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bool {
      auto a = ch_delay(V2{3, 1});
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      auto a = ch_delay(X{3, 1});
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      auto a = ch_delay(U{2});
      auto e = ch_case(ch_time(), 3, 10_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      auto a = ch_delay<E>(E::c);
      auto e = ch_case<E>(ch_time(), 3, E::c)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 3);

    TEST([]()->ch_bool {
      ch_uint2 a;
      a = ch_delay(ch_select(ch_reset(), 1, a + 1));
      ch_bit2 e = ch_case(ch_time(), 3, 10_b)(5, 11_b)(7, 00_b)(9, 01_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bool {
      auto x = ch_delay<E>(E::c);
      auto e = ch_case<E>(ch_time(), 3, E::c)(x);
      return (x == e);
    }, 10);
  }

  SECTION("reg", "[reg]") {
    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(0);
      a <<= a + 1;
      auto e = ch_case(ch_time(), 3, 01_b)(5, 10_b)(7, 11_b)(9, 00_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (e == a);
    }, 10);

    TEST([]()->ch_bool {
      ch_reg<V2> a, b(0), c(0000_b);
      a <<= V2{3, 1};
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      ch_reg<X> a, b(0), c(0000_b);
      a <<= X{3, 1};
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      ch_reg<U> a(0), b(0), c(0_b);
      a <<= U{2};
      auto e = ch_case(ch_time(), 3, 10_b)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.as_bit() == e);
    }, 3);

    TEST([]()->ch_bool {
      ch_reg<E> a;
      a <<= E::c;
      auto e = ch_case<E>(ch_time(), 3, E::c)(a);
      //ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 3);

    TEST([]()->ch_bool {
      ch_reg<ch_uint2> a(1);
      a <<= a + 1;
      auto e = ch_case(ch_time(), 3, 10_b)(5, 11_b)(7, 00_b)(9, 01_b)(a);
      //ch_print("t={0}, a={1}", ch_time(), a);
      return (e == a);
    }, 10);

    TEST([]()->ch_bool {
      ch_reg<ch_bit2> a;
      auto x = ch_case(ch_time(), 8, 11_b)(6, 0)(4, 2)(2, 1)(0);
      a <<= x;
      auto b = ch_delay(x);
      //ch_print("t={0}, clk={1}, rst={2}, x={3}, a={4}, b={5}", ch_time(), ch_clock(), ch_reset(), x, a, b);
      return (a == b);
    }, 8);

    TEST([]()->ch_bool {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 9, 11_b)(7, 0)(5, 2)(3, 1)(0);
      e <<= ch_case(ch_time(), 9, 11_b)(7, 1)(5, 0)(3, 2)(0);

      __if (b == 1) {
        a <<= 2;
      } __elif (b == 0) {
         a <<= 1;
      } __elif (b == 2) {
        a <<= 0;
      } __else {
        a <<= 3;
      };

      //ch_print("t={0}, clk={1}, rst={2}, a={3}, b={4}, e={5}", ch_time(), ch_clock(), ch_reset(), a, b, e);
      return (a == e);
    }, 8);

    TEST([]()->ch_bool {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 11, 11_b)(9, 3)(7, 0)(5, 2)(3, 1)(0);
      e <<= ch_case(ch_time(), 11, 01_b)(9, 1)(7, 1)(5, 0)(3, 2)(0);

      __if (b == 1) {
        a <<= 2;
      } __elif (b == 0) {
         a <<= 1;
      } __elif (b == 2) {
        a <<= 0;
      } __else {
        a <<= a;
      };

      //ch_print("t={0}, clk={1}, rst={2}, a={3}, b={4}, e={5}", ch_time(), ch_clock(), ch_reset(), a, b, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bool {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 9, 11_b)(7, 0)(5, 2)(3, 1)(0);
      e <<= ch_case(ch_time(), 9, 01_b)(7, 1)(5, 0)(3, 2)(0);

      __switch (b)
      __case (1) { a <<= 2; }
      __case (0) { a <<= 1; }
      __case (2) { a <<= 0; }
      __default  { a <<= a; };

      //ch_print("t={0}, clk={1}, rst={2}, a={3}, b={4}, e={5}", ch_time(), ch_clock(), ch_reset(), a, b, e);
      return (a == e);
    }, 8);


    TEST([]()->ch_bool {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 9, 11_b)(7, 0)(5, 2)(3, 1)(0);
      auto v = ch_case(ch_time(), 9, 11_b)(7, 1)(5, 0)(3, 2)(0);
      e <<= v.slice<2>();

      __if (b == 1) {
        a <<= v.slice<2>();
      } __elif (b == 0) {
         a <<= v.slice<2>();
      } __elif (b == 2) {
        a <<= 0;
      } __else {
        a <<= 3;
      };

      //ch_print("t={0}, clk={1}, rst={2}, a={3}, b={4}, e={5}", ch_time(), ch_clock(), ch_reset(), a, b, e);
      return (a == e);
    }, 8);

    TEST([]()->ch_bool {
      std::array<ch_reg<ch_bit2>, 2> x;
      ch_bit2 a;
      ch_reg<ch_bit2> e;

      x[0] <<= a;
      x[1] <<= ~a;

      a = ch_case(ch_time(), 9, 00_b)(7, 2)(5, 3)(3, 1)(0);
      e <<= a;

      //ch_print("t={0}, clk={1}, rst={2}, x0={3}, x1={4}, e={5}", ch_time(), ch_clock(), ch_reset(), x[0], x[1], e);

      return (x[0] == e) && (x[1] == ~e);
    }, 8);

    TEST([]()->ch_bool {
      ch_reg<X> x;
      ch_reg<ch_bit2> e;

      auto a = ch_case(ch_time(), 8, 00_b)(6, 2)(4, 3)(2, 1)(0);

      x <<= X{~a, a};
      e <<= a;

      //ch_print("t={0}, clk={1}, rst={2}, x.p={3}, x.q={4}, e={5}", ch_time(), ch_clock(), ch_reset(), x.p, x.q, e);

      return (x.q == e) && (x.p == ~e);
    }, 8);

    /* TODO:
    TEST([]()->ch_bool {
      auto clk  = ch_case(ch_time(), 8, 1_b)(6, 1)(4, 1)(2, 1)(0);
      auto rst  = ch_case(ch_time(), 5, 1_b)(0);
      auto next = ch_case(ch_time(), 8, 0011_b)(7, 0)(6, 0)(5, 1)(4, 2)(3, 3)(2, 1)(1, 2)(0);

      ch_pushcd(clk, rst);

      auto r = ch_delay(ch_select(ch_reset(), 0, next));

      ch_popcd();

      auto e = ch_case(ch_time(), 9, 0011_b)(8, 0)(7, 0)(6, 0)(5, 2)(4, 3)(3, 1)(2, 2)(0);

      //ch_print("t={0}, clk={1}, clk2={2}, rst={3}, next={4}, out={5}, expected={6}", ch_time(), ch_clock(), clk, rst, next, r, e);

      return (r == e);
    }, 8);*/
  }
}
