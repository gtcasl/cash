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
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_delay(11_b);
      ch_bit2 e = ch_case(ch_time(), 3, 11_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bit1 {
      auto a = ch_delay(V2{3, 1});
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      auto a = ch_delay(X{3, 1});
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      auto a = ch_delay(U{2});
      auto e = ch_case(ch_time(), 3, 10_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      auto a = ch_delay<E>(E::c);
      auto e = ch_case<E>(ch_time(), 3, E::c)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 3);

    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_delay(ch_select(ch_reset(), 1, a + 1));
      ch_bit2 e = ch_case(ch_time(), 3, 10_b)(5, 11_b)(7, 00_b)(9, 01_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bit1 {
      auto x = ch_delay<E>(E::c);
      auto e = ch_case<E>(ch_time(), 3, E::c)(x);
      return (x == e);
    }, 10);
  }

  SECTION("reg", "[reg]") {
    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a(0);
      a.next = a + 1;
      auto e = ch_case(ch_time(), 3, 01_b)(5, 10_b)(7, 11_b)(9, 00_b)(a);
      //ch_print("t={0}, a={1}", ch_time(), a);
      return (e == a);
    }, 10);

    TEST([]()->ch_bit1 {
      ch_reg<V2> a, b(0), c(0000_b);
      a.next = V2{3, 1};
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      ch_reg<X> a, b(0), c(0000_b);
      a.next = X{3, 1};
      auto e = ch_case(ch_time(), 3, 1101_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      ch_reg<U> a(0), b(0), c(0_b);
      a.next = U{2};
      auto e = ch_case(ch_time(), 3, 10_b)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a.asBits() == e);
    }, 3);

    TEST([]()->ch_bit1 {
      ch_reg<E> a;
      a.next = E::c;
      auto e = ch_case<E>(ch_time(), 3, E::c)(a);
      ch_print("t={0}, a={1}, e={2}", ch_time(), a, e);
      return (a == e);
    }, 3);

    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a(1);
      a.next = a + 1;
      auto e = ch_case(ch_time(), 3, 10_b)(5, 11_b)(7, 00_b)(9, 01_b)(a);
      //ch_print("t={0}, a={1}", ch_time(), a);
      return (e == a);
    }, 10);

    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a;
      auto x = ch_case(ch_time(), 8, 11_b)(6, 0)(4, 2)(2, 1)(0);
      a.next = x;
      auto b = ch_delay(x);
      //ch_print("t={0}, clk={1}, x={2}, a={3}, b={4}", ch_time(), ch_clock(), x, a, b);
      return (a == b);
    }, 8);

    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 8, 11_b)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_case(ch_time(), 8, 11_b)(6, 1)(4, 0)(2, 2)(0);

      __if (b == 1) {
        a.next = 2;
      } __elif (b == 0) {
         a.next = 1;
      } __elif (b == 2) {
        a.next = 0;
      } __else {
        a.next = 3;
      };

      ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_time(), ch_clock(), a, b, e);
      return (a == e);
    }, 8);

    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 10, 11_b)(8, 3)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_case(ch_time(), 10, 01_b)(8, 1)(6, 1)(4, 0)(2, 2)(0);

      __if (b == 1) {
        a.next = 2;
      } __elif (b == 0) {
         a.next = 1;
      } __elif (b == 2) {
        a.next = 0;
      } __else {
        a.next = a;
      };

      ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_time(), ch_clock(), a, b, e);
      return (a == e);
    }, 10);

    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 8, 11_b)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_case(ch_time(), 8, 01_b)(6, 1)(4, 0)(2, 2)(0);

      __switch (b)
      __case (1) { a.next = 2; }
      __case (0) { a.next = 1; }
      __case (2) { a.next = 0; }
      __default  { a.next = a; };

      //ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_time(), ch_clock(), a, b, e);
      return (a == e);
    }, 8);


    TEST([]()->ch_bit1 {
      ch_reg<ch_bit2> a, e;
      auto b = ch_case(ch_time(), 8, 11_b)(6, 0)(4, 2)(2, 1)(0);
      auto v = ch_case(ch_time(), 8, 11_b)(6, 1)(4, 0)(2, 2)(0);
      e.next = v.slice<2>();

      __if (b == 1) {
        a.next = v.slice<2>();
      } __elif (b == 0) {
         a.next = v.slice<2>();
      } __elif (b == 2) {
        a.next = 0;
      } __else {
        a.next = 3;
      };

      //ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_time(), ch_clock(), a, b, e);
      return (a == e);
    }, 8);

    TEST([]()->ch_bit1 {
      std::vector<ch_reg<ch_bit2>> x(2);
      ch_bit2 a;
      ch_reg<ch_bit2> e;

      x[0].next = a;
      x[1].next = ~a;

      a = ch_case(ch_time(), 8, 00_b)(6, 2)(4, 3)(2, 1)(0);
      e.next = a;
      ch_print("t={0}, clk={1}, x0={2}, x1={3}, e={4}",
           ch_time(), ch_clock(), x[0], x[1], e);
      return x[0] == e && x[1] == ~e;
    }, 8);

    TEST([]()->ch_bit1 {
      ch_reg<X> x;
      ch_reg<ch_bit2> e;

      auto a = ch_case(ch_time(), 8, 00_b)(6, 2)(4, 3)(2, 1)(0);

      x.next.q = a;
      x.next.p = ~a;
      e.next = a;

      ch_print("t={0}, clk={1}, x.p={2}, x.q={3}, e={4}",
           ch_time(), ch_clock(), x.p, x.q, e);

      return x.q == e && x.p == ~e;
    }, 8);

    TEST([]()->ch_bit1 {
      auto clk  = ch_case(ch_time(), 8, 1_b)(6, 1)(4, 1)(2, 1)(1, 0)(0);
      auto rst  = ch_case(ch_time(), 5, 1_b)(0);
      auto next = ch_case(ch_time(), 7, 11_b)(5, 1)(3, 3)(2, 1)(1, 2)(0);

      ch_pushcd(clk, rst, true);

      auto r = ch_delay(ch_select(ch_reset(), 0, next));

      ch_popcd();

      auto e = ch_case(ch_time(), 9, 11_b)(8, 3)(5, 3)(4, 3)(3, 2)(2, 2)(0);

      ch_print("t={0}, clk={1}, clk2={2}, rst={3}, next={4}, r={5}, e={6}",
           ch_time(), ch_clock(), clk, rst, next, r, e);

      return (r == e);
    }, 8);
  }
}
