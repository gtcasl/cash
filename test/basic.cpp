#include "common.h"

struct TestAssign {
  __io (
    __in(ch_bit4) in,
    __out(ch_bit1) out
  );
  void describe() {
    ch_bit4 w(io.in);
    w = 0xB;
    io.out = (io.in == 0xA);
  }
};

struct TestAssign2 {
  __io (
    __in(ch_bit4) in,
    __out(ch_bit1) out
  );
  void describe() {
    ch_bool x = io.out;
    ch_assert(x, "oops!");
    io.out = (io.in == 0xA);
  }
};

struct TestAssign3 {
  __io (
    __in(ch_bit4) in,
    __out(ch_bit1) out
  );
  void describe() {
    io.out.asBits() = (io.in.asBits() == 0xA);
  }
};

TEST_CASE("basics", "[basics]") {
  SECTION("assign", "[assign]") {
    TEST([]()->ch_bit1 {
      ch_bit2 a(0);
      auto b = a + 1;
      a = 1;
      return (b == 2);
    });

    TEST([]()->ch_bit1 {
      ch_bit4 a, b, c;
      a = 0xf_h;
      b = a;
      c = b + 1;
      b = 0;
      return (c == 1);
    });

    TEST([]()->ch_bit1 {
      ch_bit2 a, b;
      a = 0;
      b = a;
      a = 1;
      return (b == 1);
    });

    TEST([]()->ch_bit1 {
      ch_module<TestAssign> m;
      m.io.in = 0xA;
      return m.io.out;
    });

    TEST([]()->ch_bit1 {
      ch_module<TestAssign2> m;
      m.io.in = 0xA;
      return m.io.out;
    });

    TEST([]()->ch_bit1 {
      ch_module<TestAssign3> m;
      m.io.in = 0xA;
      return m.io.out;
    });
  }
}
