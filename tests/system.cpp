#include "common.h"

namespace {

__enum (e2_t, 2, (
  (idle, 0),
  execute,
  stats,
  done
));

__union (u4_t, (
  (ch_bit4) a
  ));

__union (u2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
  ));

__struct (s4_t, (
  (ch_bit4) a
  ));

__struct (s2_4_t, (
  (ch_bit2) a,
  (ch_bit4) b
));

__union (ux_t, (
  (u2_4_t) a,
  (s2_4_t) b
));

__struct (sd1_t, s4_t, (
  (ch_bit2) b
));

__struct (sd2_t, sd1_t, (
  (ch_bit4) c
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));

using v2_1_t = ch_vec<ch_bit2, 1>;
using v2_2_t = ch_vec<ch_bit2, 2>;
using v2_3_t = ch_vec<ch_bit2, 3>;

}

TEST_CASE("system", "[system]") {
  SECTION("basics", "[basics]") {
    TESTX([]()->bool {
      ch_scbit<4> a(0xb);
      ch_scbit<4> b(0x5);
      int v(a & b);
      return (v == 0x1);
    });
    TESTX([]()->bool {
      ch_scuint<4> a(0xa);
      ch_scuint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_scint<4> a(0xa);
      ch_scint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0);
    });
    TESTX([]()->bool {
      ch_scuint<6> a(0xa);
      ch_scuint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_scuint<4> a(0xa);
      ch_scint<6> b(0x5);
      int v(a + b.as_scuint());
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_scuint<4> a(0), b(1), c(1);
      int ret = (a != b);
      ret &= (b == c);
      ret &= (a == (b - c));
      return !!ret;
    });
    TESTX([]()->bool {
      ch_scuint<4> a(0), b(1), c(1);
      int ret = (a != b);
      ret &= (b == c);
      ret &= (a == (b - c));
      return !!ret;
    });
    TESTX([]()->bool {
      ch_scbit<4> a(0101_b);
      return (a[0] == a[2]) && (a.slice<2>() == a.slice<2>(2));
    });
    TESTX([]()->bool {
      const ch_scbit<4> a(0101_b);
      return (a[0] == a[2]) && (a.slice<2>() == a.slice<2>(2));
    });
    TESTX([]()->bool {
      auto force_move_assignment = []() {
        return 4_h + 3_h;
      };
      ch_scbit<4> x;
      x = force_move_assignment();
      return (x == 7);
    });
  }
  SECTION("arithmetic", "[arithmetic]") {
    TESTX([]()->bool {
      ch_scbit<4> a(3);
      ch_scbit<3> b(1);
      RetCheck ret;
      ret &= (a == 0011_b);
      ret &= (b == 001_b);
      ret &= (~a == 1100_b);
      ret &= ((a & b) == 0001_b);
      ret &= ((a | b) == 0011_b);
      ret &= ((a ^ b) == 0010_b);
      ret &= ((a >> b) == 1);
      ret &= ((a << b) == 6);
      return ret;
    });
    TESTX([]()->bool {
      ch_scuint<4> a(3);
      ch_scuint<3> b(1);
      RetCheck ret;
      ret &= (a == 0011_b);
      ret &= (b == 001_b);
      ret &= (a != b);
      ret &= (a > b);
      ret &= (a >= b);
      ret &= (b < a);
      ret &= (b <= a);
      ret &= (~a == 1100_b);
      ret &= ((a & b) == 0001_b);
      ret &= ((a | b) == 0011_b);
      ret &= ((a ^ b) == 0010_b);
      ret &= ((a >> b) == 1);
      ret &= ((a << b) == 6);
      ret &= (-b == 111_b);
      ret &= ((a + b) == 4);
      ret &= ((a - b) == 2);
      ret &= ((a * b) == 3);
      ret &= ((a / b) == 3);
      ret &= ((a % b) == 0);
      return ret;
    });
    TESTX([]()->bool {
      ch_scint<4> a(-3);
      ch_scint<3> b(-1);
      RetCheck ret;
      ret &= (a == 1101_b);
      ret &= (b == 111_b);
      ret &= (a != b);
      ret &= (a < b);
      ret &= (a <= b);
      ret &= (b > a);
      ret &= (b >= a);
      ret &= (~a == 0010_b);
      ret &= ((a & b) == 1101_b);
      ret &= ((a | b) == 1111_b);
      ret &= ((a ^ b) == 0010_b);
      ret &= ((a >> -b) == -2);
      ret &= ((a << -b) == -6);
      ret &= (-b == 1);
      ret &= ((a + b) == -4);
      ret &= ((a - b) == -2);
      ret &= ((a * b) == 3);
      ret &= ((a / b) == 3);
      ret &= ((a % b) == 0);
      return ret;
    });
    TESTX([]()->bool {
      ch_scint<127> a(3100);
      ch_scint<126> b(1010);
      ch_scint<125> c(-1000);
      RetCheck ret;
      ret &= ((a + b) == 4110);
      ret &= ((a + c) == 2100);
      ret &= ((a - b) == 2090);
      ret &= ((a - c) == 4100);
      ret &= ((a * b) == 3131000);
      ret &= ((b * c) ==-1010000);
      ret &= ((a * c) ==-3100000);
      ret &= ((a / b) == 3);
      ret &= ((b / c) ==-1);
      ret &= ((a / c) ==-3);
      ret &= ((a % b) == 70);
      ret &= ((b % c) == 10);
      ret &= ((a % c) == 100);
      return ret;
    });
    TESTX([]()->bool {
      ch_scint<33> a(0x1ffffff8b);
      ch_scint<33> b(0x00007fff);
      RetCheck ret;
      ret &= ((a * b) == 0x1FFC58075);
      return ret;
    });
    TESTX([]()->bool {
      ch_scint<33> a(0x58);
      ch_scint<33> b(0x00);
      RetCheck ret;
      ret &= ((a * b) == 0x0);
      return ret;
    });
  }
  SECTION("cast", "[cast]") {
    TESTX([]()->bool {
      ch_scbit<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_scuint<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_scint<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_scbit<4> x(8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_scuint<4> x(8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_scint<4> x(8);
      return (static_cast<int>(x) == -8);
    });
    TESTX([]()->bool {
      ch_scint<4> x(7);
      return (static_cast<int>(x) == 7);
    });
    TESTX([]()->bool {
      ch_scbit<4> x(-8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_scuint<4> x(-8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_scint<4> x(-8);
      return (x == -8);
    });
    TESTX([]()->bool {
      ch_scbit<4> x(-8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_scuint<4> x(-8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_scint<4> x(-8);
      return (static_cast<int>(x) == -8);
    });
    TESTX([]()->bool {
      ch_scbit<4> x(-1);
      return (static_cast<int>(x) == 0xf);
    });
    TESTX([]()->bool {
      ch_scuint<4> x(-1);
      return (static_cast<int>(x) == 0xf);
    });
    TESTX([]()->bool {
      ch_scint<4> x(-1);
      return (static_cast<int>(x) == -1);
    });
  }
  SECTION("enum", "[enum]") {
    TESTX([]()->bool {
      ch_system_t<e2_t> a(e2_t::done);
      return (a == 3);
    });
    TESTX([]()->bool {
      ch_system_t<e2_t> a(e2_t::done), b(a);
      return (a == b);
    });
  }
  SECTION("union", "[union]") {
    TESTX([]()->bool {
      ch_system_t<u2_4_t> u2(0101_b);
      RetCheck ret;
      ret &= (u2.a == 1);
      ret &= (u2.b == 5);
      u2.b = 7;
      ret &= (u2.a == 3);
      u2.a = 0;
      ret &= (u2.b == 4);
      return !!ret;
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(0101_b), b(a);
      return (a.as_scbit() == b.as_scbit());
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(0101_b), b;
      b = a;
      return (a.as_scbit() == b.as_scbit());
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a{3_h};
      return (a.as_scbit() == 3);
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(0011_b4);
      return (a.as_scbit() == 3);
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(11_b2);
      return (a.as_scbit() == 3);
    });
  }
  SECTION("struct", "[struct]") {
    TESTX([]()->bool {
      ch_system_t<s2_4_t> s2(0101_b, 01_b);
      RetCheck ret;
      ret &= (s2.a == 1);
      ret &= (s2.b == 5);
      s2.b = 7;
      ret &= (s2.a == 1);
      s2.a = 0;
      ret &= (s2.b == 7);
      return ret;
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> s;
      s = ch_system_t<s2_4_t>(0101_b, 01_b);
      s.b = 1010_b;
      return (s.as_scbit() == 101001_b);
    });
    TESTX([]()->bool {
      auto force_move_assignment = []() {
        return 4_h + 3_h;
      };
      ch_system_t<s2_4_t> s2(0101_b, 01_b);
      s2.b = force_move_assignment();
      return (s2.b == 7) && (s2.as_scbit() == 011101_b);
    });
    TESTX([]()->bool {
      auto force_move_construct = []() {
        ch_system_t<s2_4_t> s2(0101_b, 01_b);
        return s2;
      };
      ch_system_t<s2_4_t> s2(force_move_construct());
      return (s2.as_scbit() == 010101_b);
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b);
      return (a.as_scbit() == 010101_b);
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b), b(a);
      return (a.as_scbit() == b.as_scbit());
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b), b;
      b = a;
      return (a.as_scbit() == b.as_scbit());
    });
    TESTX([]()->bool {
      ch_system_t<sd1_t> a{1_b2, 2_h};
      return (a.as_scbit() == 010010_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd2_t> a{2_h, {1_b2, 2_h}};
      return (a.as_scbit() == 0010010010_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd3_t> a{3_h, {1_b2, 2_h}};
      return (a.as_scbit() == 0011010010_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd3_t> a{3_h, {1_b2, 2_h}}, b(a);
      return (b.d == 3);
    });
    TESTX([]()->bool {
      auto force_move_assignment = []() {
        return ch_system_t<sd3_t>{3_h, {1_b2, 2_h}};
      };
      ch_system_t<sd3_t> a;
      a = force_move_assignment();
      return (a.as_scbit() == 0011010010_b);
    });
    TESTX([]()->bool {
      auto t1 = std::tuple(ch_system_t<s2_4_t>(0101_b, 01_b), ch_system_t<s2_4_t>(1, 0));
      auto t2 = t1;
      auto [x, y] = t2;
      return (x.as_scbit() == 010101_b && y.as_scbit() == 000100_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd3_t> s3{3_h, {1_b2, 2_h}};
      ch_system_t<sd1_t> x{10_b2, 5_h};
      RetCheck ret;
      ret &= (s3.c.a == 2);
      ret &= (s3.c.b == 1);
      ret &= (s3.d == 3);
      s3.c = x;
      ret &= (s3.c.a == 5);
      ret &= (s3.c.b == 2);
      ret &= (s3.d == 3);
      return ret;
    });
  }
  SECTION("vector", "[vector]") {
    TEST([]()->ch_bool {
      ch_system_t<v2_2_t> x(3_h);
      v2_2_t y(x.as_scbit());
      return (y[0] == 3) && (y[1] == 0);
    });
    TESTX([]()->bool {
      ch_system_t<v2_2_t> x(3_h);
      return (x[0] == 3) && (x[1] == 0);
    });
  }
}
