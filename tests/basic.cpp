#include "common.h"
#include <htl/decoupled.h>

using namespace ch::htl;

namespace {

__struct (s4_4_t, (
  (ch_bit4) x,
  (ch_bit4) y
));

__union (u2_4_t, (
  (ch_bit2) x,
  (ch_bit4) y
));

using v4x2_t = ch_vec<ch_bit4, 2>;

struct TestAssign {
  __io (
    __in (ch_bit4) in,
    __out (ch_bool) out
  );

  void describe() {
    ch_bit4 w(io.in);
    w = 0xB;
    io.out = (io.in == 0xA);
  }

  ch_bit4 q;
};

struct TestAssign2 {
  __io (
    __in (ch_bit4) in,
    __out (ch_bool) out
  );

  void describe() {
    ch_bool x = io.out;
    ch_assert(x, "oops!");
    io.out = (io.in == 0xA);
  }
};

struct TestAssign3 {
  __io (
    __in (ch_bit4) in,
    __out (ch_bool) out
  );

  void describe() {
    io.out.as_bit() = (io.in.as_bit() == 0xA);
  }
};

struct TestAssign4 {
  __io (
    (ch_enq_io<>) in,
    (ch_deq_io<>) out
  );

  void describe() {
    io.out(io.in);
  }
};

}

TEST_CASE("basics", "[basics]") {
  SECTION("assign", "[assign]") {
    TEST([]()->ch_bool {           
      ch_int4 a(14), b(1);
      auto d = a + b;
      b = 0;
      return (d == 14);
    });

    TEST([]()->ch_bool {
      ch_int4 a(14), b(1);
      auto d = a + b;
      d[0] = 0;
      return (d == 14);
    });

    TEST([]()->ch_bool {
      ch_bit4 a(0);
      ch_bit32 e(64);
      auto b = ch_shr<4>(0x10000000000000000_h65, e);
      ch_bit4 c(b);
      auto d = a << b;
      a = b;
      return (d == 2);
    });

    TEST([]()->ch_bool {
      ch_int4 a(0), b(1_b4), c(b);
      auto d = a << b;
      a = b;
      return (d == 2);
    });

    TEST([]()->ch_bool {
      ch_bit4 a(2);
      ch_bit8 b(a);
      b = a | 1;
      return (b == 3);
    });

    TEST([]()->ch_bool {
      ch_int4 a(2);
      ch_int8 b(a);
      b = a | 1;
      return (b == 3);
    });

    TEST([]()->ch_bool {
      ch_uint4 a(2);
      ch_uint8 b(a);
      b = a | 1;
      return (b == 3);
    });

    TEST([]()->ch_bool {
      ch_uint4 a(0), b(1_b4), c(b);
      auto d = a << b;
      a = b;
      return (d == 2);
    });

    TEST([]()->ch_bool {
      ch_bit8 a(0x4_h8);
      a = 0xf_h8;
      return (a == 15);
    });

    TEST([]()->ch_bool {
      ch_int4 a, b, c;
      a = 0xf_h;
      b = a;
      c = b + 1;
      b = 0;
      return (c == 1);
    });

    TEST([]()->ch_bool {
      ch_int2 a;
      ch_bit2 b;
      a = 0;
      b = a;
      a = 1;
      return (b == 1);
    });

    TEST([]()->ch_bool {
      ch_module<TestAssign> m;
      m.io.in = 0xA;
      return m.io.out;
    });

    TEST([]()->ch_bool {
      ch_module<TestAssign2> m;
      m.io.in = 0xA;
      return m.io.out;
    });

    TEST([]()->ch_bool {
      ch_module<TestAssign3> m;
      m.io.in = 0xA;
      return m.io.out;
    });

    TEST([]()->ch_bool {
      ch_bit<65> a = 0xf, b = 0xe, c = 0x3, d = 0x2;
      auto s = ch_sel(a != b, c, d);
      return (s == c);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_bit4, 2> a{2, 1};
      return (a.as_uint() == 21_h);
    });

    TEST1([](const ch_int8& t)->ch_bool {
      auto res = t + 2;
      auto q = t;
      q = q.clone() + 1;
      q = q.clone() + 1;
      return (q == res);
    });

    TEST([]()->ch_bool {
      ch_int4 q(0);
      q[0] = 1;
      q[1] = 1;
      q = q.clone() + 1;
      q = q.clone() + 1;
      return (q == 3+2);
    });
  }
  SECTION("ref", "[ref]") {
    TEST([]()->ch_bool {
      ch_bit4 a(1010_b);
      auto b = a.ref();
      b[0] = 1;
      return (a == 1011_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1010_b);
      auto b = ch_ref(a);
      b[0] = 1;
      return (a == 1011_b);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(1000_b);
      auto b = !a;
      return !b;
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      auto b = !a;
      return b;
    });
    TEST([]()->ch_bool {
      ch_uint16 a;
      ch_asliceref<4>(a, 1) = 0x5;
      auto b = ch_aslice<4>(a, 1);
      return (b == 0x5);
    });
    TEST([]()->ch_bool {
      ch_uint16 a;
      ch_uint8 x;
      ch_asliceref<8>(a, 1) = x;
      ch_asliceref<4>(x, 0) = 0x5;
      auto b = ch_aslice<4>(a, 2);
      return (b == 0x5);
    });
  }
  SECTION("clone", "[clone]") {
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      auto b = ch_clone(a);
      a = 2;
      b = 1;
      return (a == 2 && b == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 a(0);
      auto b = ch_clone(a);
      b = 1;
      a = 2;
      return (a == 2 && b == 1);
    });
    TEST([]()->ch_bool {
      s4_4_t a{0, 0};
      auto b = ch_clone(a);
      a.x = 2;
      b.x = 1;
      return (a.x == 2 && b.x == 1);
    });
    TEST([]()->ch_bool {
      s4_4_t a{0, 0};
      a.y = 2;
      auto w = a.y;
      w[0]= 1;
      return (w == 3);
    });
    TEST([]()->ch_bool {
      s4_4_t a{0, 0};
      auto b = ch_clone(a);
      b.x = 1;
      a.x = 2;
      return (a.x == 2 && b.x == 1);
    });
    TEST([]()->ch_bool {
      u2_4_t a(0_b4);
      auto b = ch_clone(a);
      a.x = 2;
      b.x = 1;
      return (a.x == 2 && b.x == 1);
    });
    TEST([]()->ch_bool {
      u2_4_t a(0_b4);
      auto b = ch_clone(a);
      b.x = 1;
      a.x = 2;
      return (a.x == 2 && b.x == 1);
    });
    TEST([]()->ch_bool {
      ch_bit<66> x(0x1);
      ch_bit<200> y(0x1);
      ch_bit<65> z(0x1);
      return (ch_slice<8>(x) == ch_slice<8>(y))
          && (ch_slice<8>(x) == ch_slice<8>(z));
    });
  }
}
