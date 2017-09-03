#include "common.h"

using namespace cash::core_literals;

__struct(X,(
(ch_bit2) q,
(ch_bit2) p
));

TEST_CASE("registers", "[registers]") {
  SECTION("registers", "[register]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_reg(a + 1);
      ch_bit2 e = ch_select(ch_tick())
           (3, 01_b)
           (5, 10_b)
           (7, 11_b)
           (9, 00_b)
              (a);
      //ch_print("t={0}, a={1}, e={2}", ch_tick(), a, e);
      return (e == a);
    }, 5);
    TEST([]()->ch_bit1 {
      ch_bit2 a;
      a = ch_reg<2>(a + 1, 1);
      ch_bit2 e = ch_select(ch_tick())
           (3, 10_b)
           (5, 11_b)
           (7, 00_b)
           (9, 01_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
  }

  SECTION("seq", "[seq]") {
    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a;
      a.next = a + 1;
      ch_bit2 e = ch_select(ch_tick())
           (3, 01_b)
           (5, 10_b)
           (7, 11_b)
           (9, 00_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);
    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a(1);
      a.next = a + 1;
      ch_bit2 e = ch_select(ch_tick())
           (3, 10_b)
           (5, 11_b)
           (7, 00_b)
           (9, 01_b)
              (a);
      //ch_print("t={0}, a={1}", ch_tick(), a);
      return (e == a);
    }, 5);

    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a;
      auto x = ch_select(ch_tick()).when<2>(8, 3)(6, 0)(4, 2)(2, 1)(0);
      a.next = x;
      auto b = ch_reg(x);
      //ch_print("t={0}, clk={1}, x={2}, a={3}, b={4}", ch_tick(), ch_clock(), x, a, b);
      return (a == b);
    }, 4);

    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a, e;
      auto b = ch_select(ch_tick()).when<2>(8, 3)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_select(ch_tick()).when<2>(8, 3)(6, 1)(4, 0)(2, 2)(0);

      __if (b == 1) (
        a.next = 2;
      )
      __elif (b == 0) (
         a.next = 1;
      )
      __elif (b == 2) (
        a.next = 0;
      )
      __else (
        a.next = 3;
      );

      //ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_tick(), ch_clock(), a, b, e);
      return (a == e);
    }, 4);

    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a, e;
      auto b = ch_select(ch_tick()).when<2>(10, 3)(8, 3)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_select(ch_tick()).when<2>(10, 1)(8, 1)(6, 1)(4, 0)(2, 2)(0);

      __if (b == 1) (
        a.next = 2;
      )
      __elif (b == 0) (
         a.next = 1;
      )
      __elif (b == 2) (
        a.next = 0;
      )
      __else (
        a.next = a;
      );

      ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_tick(), ch_clock(), a, b, e);
      return (a == e);
    }, 5);

    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a, e;
      auto b = ch_select(ch_tick()).when<2>(8, 3)(6, 0)(4, 2)(2, 1)(0);
      e.next = ch_select(ch_tick()).when<2>(8, 1)(6, 1)(4, 0)(2, 2)(0);

      __switch (b) (
      __case (1) (
         a.next = 2;
      )
      __case (0) (
         a.next = 1;
      )
      __case (2) (
        a.next = 0;
      )
      __default (
        a.next = a;
      ));

      //ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_tick(), ch_clock(), a, b, e);
      return (a == e);
    }, 4);


    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> a, e;
      auto b = ch_select(ch_tick()).when<2>(8, 3)(6, 0)(4, 2)(2, 1)(0);
      auto v = ch_select(ch_tick()).when<4>(8, 3)(6, 1)(4, 0)(2, 2)(0);
      e.next = v.slice<2>();

      __if (b == 1) (
        a.next = v.slice<2>();
      )
      __elif (b == 0) (
         a.next = v.slice<2>();
      )
      __elif (b == 2) (
        a.next = 0;
      )
      __else (
        a.next = 3;
      );

      //ch_print("t={0}, clk={1}, a={2}, b={3}, e={4}", ch_tick(), ch_clock(), a, b, e);
      return (a == e);
    }, 4);

    TEST([]()->ch_bit1 {
      std::vector<ch_seq<ch_bit2>> x(2);
      ch_bit2 a;
      ch_seq<ch_bit2> e;

      x[0].next = a;
      x[1].next = ~a;

      a = ch_select(ch_tick()).when<2>(8, 0)(6, 2)(4, 3)(2, 1)(0);
      e.next = a;
      ch_print("t={0}, clk={1}, x0={2}, x1={3}, e={4}", ch_tick(), ch_clock(), x[0], x[1], e);
      return x[0] == e && x[1] == ~e;
    }, 4);

    TEST([]()->ch_bit1 {
      ch_seq<ch_bit2> x;
      ch_seq<ch_bit2> y(std::move(x));
      ch_seq<ch_bit2> e;

      auto  a = ch_select(ch_tick()).when<2>(8, 0)(6, 2)(4, 3)(2, 1)(0);

      y.next = a;
      e.next = a;

      ch_print("t={0}, clk={1}, y={2}, e={3}", ch_tick(), ch_clock(), y, e);

      return y == e;
    }, 4);

    TEST([]()->ch_bit1 {
      ch_seq<X> x;
      ch_seq<ch_bit2> e;

      auto  a = ch_select(ch_tick()).when<2>(8, 0)(6, 2)(4, 3)(2, 1)(0);

      x.next.q = a;
      x.next.p = ~a;
      e.next = a;

      ch_print("t={0}, clk={1}, x.p={2}, x.q={3}, e={4}", ch_tick(), ch_clock(), x.p, x.q, e);

      return x.q == e && x.p == ~e;
    }, 4);
  }
  
  SECTION("latches", "[latch]") {
    // TODO
  }
}
