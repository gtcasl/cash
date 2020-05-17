#include "common.h"

static constexpr uint32_t WS = bitwidth_v<sdata_type::block_type>;

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

__struct (sq_t, (
  (ch_bool) v
));

using v2_1_t = ch_vec<ch_bit2, 1>;
using v2_2_t = ch_vec<ch_bit2, 2>;
using v2_3_t = ch_vec<ch_bit2, 3>;
using v_sd3_2_t = ch_vec<sd3_t, 2>;

}

TEST_CASE("system", "[system]") {
  SECTION("basics", "[basics]") {
    TESTX([]()->bool {
      ch_sbit<1> a(1), b(0);
      ch_sbool c(true);
      bool ret = false;
      if (a) {
        if (b) {
          ret = false;
        } else {
          ret = true;
        }
      }
      if (c) {
        a = 0;  
      }
      return ret;
    });
    TESTX([]()->bool {
      ch_sbit4 a(2);
      ch_sbit8 b(a);
      b = a | 1;
      return (b == 3);
    });

    TESTX([]()->bool {
      ch_sint4 a(2);
      ch_sint8 b(a);
      b = a | 1;
      return (b == 3);
    });

    TESTX([]()->bool {
      ch_suint4 a(2);
      ch_suint8 b(a);
      b = a | 1;
      return (b == 3);
    });
    TESTX([]()->bool {
      ch_sbit<4> a(0xb);
      ch_sbit<4> b(0x5);
      int v(a & b);
      return (v == 0x1);
    });
    TESTX([]()->bool {
      ch_suint<4> a(0xa);
      ch_suint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_sint<4> a(0xa);
      ch_sint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0);
    });
    TESTX([]()->bool {
      ch_suint<6> a(0xa);
      ch_suint<4> b(0x5);
      int v(a + b);
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_suint<4> a(0xa);
      ch_sint<6> b(0x5);
      int v(a + b.as_uint());
      int ret = v + 1;
      return (ret == 0x10);
    });
    TESTX([]()->bool {
      ch_suint<4> a(0), b(1), c(1);
      int ret = (a != b);
      ret &= (b == c);
      ret &= (a == (b - c));
      return !!ret;
    });
    TESTX([]()->bool {
      ch_suint<4> a(0), b(1), c(1);
      int ret = (a != b);
      ret &= (b == c);
      ret &= (a == (b - c));
      return !!ret;
    });
    TESTX([]()->bool {
      ch_sbit<4> a(0101_b);
      return (a[0] == a[2]) && (ch_slice<2>(a) == ch_slice<2>(a, 2));
    });
    TESTX([]()->bool {
      const ch_sbit<4> a(0101_b);
      return (a[0] == a[2]) && (ch_slice<2>(a) == ch_slice<2>(a, 2));
    });
    TESTX([]()->bool {
      auto force_move_assignment = []() {
        return 4_h ^ 3_h;
      };
      ch_sbit<4> x;
      x = force_move_assignment();
      return (x == 7);
    });
  }
  SECTION("arithmetic", "[arithmetic]") {
    TESTX([]()->bool {
      ch_sbit<4> a(3);
      ch_sbit<3> b(1);
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
      ch_suint<4> a(3);
      ch_suint<3> b(1);
      RetCheck ret;
      ret &= (a == 0011_b);
      ret &= (b == 001_b);
      ret &= (!a == false);
      ret &= (!(a-a) == true);
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
      ch_suint<WS> a(3);
      ch_suint<WS> b(1);
      RetCheck ret;
      ret &= (a == 0011_b);
      ret &= (b == 001_b);
      ret &= (!a == false);
      ret &= (!(a-a) == true);
      ret &= (a != b);
      ret &= (a > b);
      ret &= (a >= b);
      ret &= (b < a);
      ret &= (b <= a);
      ret &= ((a & b) == 0001_b);
      ret &= ((a | b) == 0011_b);
      ret &= ((a ^ b) == 0010_b);
      ret &= ((a >> 1) == 1);
      ret &= ((a << 1) == 6);
      ret &= (-b == -1);
      ret &= ((a + b) == 4);
      ret &= ((a - b) == 2);
      ret &= ((a * b) == 3);
      ret &= ((a / b) == 3);
      ret &= ((a % b) == 0);
      return ret;
    });
    TESTX([]()->bool {
      ch_sint<WS+4> a(-1);
      ch_sint<WS+2> b(-2);
      RetCheck ret;
      ret &= (-a == 1);
      ret &= (-b == 2);
      ret &= (a - b == 1);
      ret &= (a == -1);
      ret &= (b == -2);
      ret &= (a * b == 2);
      ret &= (a-1 == b);
      ret &= (a == b+1);
      ret &= (a > b);
      return ret;
    });
    TESTX([]()->bool {
      ch_suint<WS+4> a(-1);
      ch_suint<WS+2> b(-2);
      RetCheck ret;
      ret &= (-a == 1);
      ret &= (-b == 2);
      ret &= (a+1 == 0);
      ret &= (b+2 == 0);
      ret &= (a != b+1);
      ret &= (ch_slice<WS+2>(a) == b+1);
      ret &= (a > b);
      return ret;
    });
    TESTX([]()->bool {
      ch_sint<4> a(-3);
      ch_sint<3> b(-1);
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
      ch_sint<WS> a(-3);
      ch_sint<WS> b(-1);
      RetCheck ret;
      ret &= (a == -3);
      ret &= (b == -1);
      ret &= (a != b);
      ret &= (a < b);
      ret &= (a <= b);
      ret &= (b > a);
      ret &= (b >= a);
      ret &= (~a == 2);
      ret &= ((a ^ b) == 2);
      ret &= ((a >> 1) == -2);
      ret &= ((a << 1) == -6);
      ret &= (-b == 1);
      ret &= ((a + b) == -4);
      ret &= ((a - b) == -2);
      ret &= ((a * b) == 3);
      ret &= ((a / b) == 3);
      ret &= ((a % b) == 0);
      return ret;
    });
    TESTX([]()->bool {
      ch_sint<127> a(3100);
      ch_sint<126> b(1010);
      ch_sint<125> c(-1000);
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
      ch_sint<128> a(3100);
      ch_sint<128> b(1010);
      ch_sint<128> c(-1000);
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
      ch_sint<33> a(0x1ffffff8b);
      ch_sint<33> b(0x000007fff);
      RetCheck ret;
      ret &= ((a * b) == 0x1FFC58075);
      return ret;
    });
    TESTX([]()->bool {
      ch_suint<128> a(260);
      ch_suint<128> b(261);
      RetCheck ret;
      ret &= ((a / b) == 260/261);
      return ret;
    });
    TESTX([]()->bool {
      ch_suint<128> a(512);
      ch_suint<128> b(257);
      RetCheck ret;
      ret &= ((a / b) == 512/257);
      return ret;      
    });
    TESTX([]()->bool {
      ch_sbit<4> a(5);
      ch_sbit<3> b(1);
      a &= b;
      return a == 1;
    });
    TESTX([]()->bool {
      ch_sbit<4> a(5);
      ch_sbit<3> b(1);
      a |= b;
      return a == 5;
    });
    TESTX([]()->bool {
      ch_sbit<4> a(5);
      ch_sbit<3> b(1);
      a ^= b;
      return a == 4;
    });
    TESTX([]()->bool {
      ch_sbit<4> a(5);
      ch_sbit<3> b(1);
      a <<= b;
      return a == 10;
    });
    TESTX([]()->bool {
      ch_sbit<4> a(5);
      ch_sbit<3> b(1);
      a >>= b;
      return a == 2;
    });
    TESTX([]()->bool {
      ch_suint<4> a(5);
      ch_sint<3> b(2);
      a += b;
      return a == 7;
    });
    TESTX([]()->bool {
      ch_suint<4> a(5);
      ch_sint<3> b(2);
      a -= b;
      return a == 3;
    });
    TESTX([]()->bool {
      ch_suint<4> a(5);
      ch_sint<3> b(2);
      a *= b;
      return a == 10;
    });
    TESTX([]()->bool {
      ch_suint<4> a(5);
      ch_sint<3> b(2);
      a /= b;
      return a == 2;
    });
    TESTX([]()->bool {
      ch_suint<4> a(5);
      ch_suint<3> b(2);
      a %= b;
      return a == 1;
    });
  }
  SECTION("cast", "[cast]") {
    TESTX([]()->bool {
      ch_sbit<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_suint<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(8);
      return (x != 7);
    });
    TESTX([]()->bool {
      ch_sint<5> x(8);
      return (x > 7 && x < 9);
    });
    TESTX([]()->bool {
      ch_sint<5> x(8);
      return (x >= 7 || x <= 9);
    });
    TESTX([]()->bool {
      ch_sbit<4> x(8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_suint<4> x(8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(8);
      return (static_cast<int>(x) == -8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(7);
      return (static_cast<int>(x) == 7);
    });
    TESTX([]()->bool {
      ch_sbit<4> x(-8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_suint<4> x(-8);
      return (x == 8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(-8);
      return (x == -8);
    });
    TESTX([]()->bool {
      ch_sbit<4> x(-8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_suint<4> x(-8);
      return (static_cast<int>(x) == 8);
    });
    TESTX([]()->bool {
      ch_sint<4> x(-8);
      return (static_cast<int>(x) == -8);
    });
    TESTX([]()->bool {
      ch_sbit<4> x(-1);
      return (static_cast<int>(x) == 0xf);
    });
    TESTX([]()->bool {
      ch_suint<4> x(-1);
      return (static_cast<int>(x) == 0xf);
    });
    TESTX([]()->bool {
      ch_sint<4> x(-1);
      return (static_cast<int>(x) == -1);
    });
  }
  SECTION("enum", "[enum]") {
    TESTX([]()->bool {
      ch_system_t<e2_t> a(e2_t::done);
      return (a.as_int() == 3);
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
      return (a.as_bit() == b.as_bit());
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(0101_b), b;
      b = a;
      return (a.as_bit() == b.as_bit());
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a{3_h};
      return (a.as_bit() == 3);
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(0011_b4);
      return (a.as_bit() == 3);
    });
    TESTX([]()->bool {
      ch_system_t<u2_4_t> a(11_b2);
      return (a.as_bit() == 3);
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
      return (s.as_bit() == 101001_b);
    });
    TESTX([]()->bool {
      auto force_move_assignment = []() {
        return 4_h ^ 3_h;
      };
      ch_system_t<s2_4_t> s2(0101_b, 01_b);
      s2.b = force_move_assignment();
      return (s2.b == 7) && (s2.as_bit() == 011101_b);
    });
    TESTX([]()->bool {
      auto force_move_construct = []() {
        ch_system_t<s2_4_t> s2(0101_b, 01_b);
        return s2;
      };
      ch_system_t<s2_4_t> s2(force_move_construct());
      return (s2.as_bit() == 010101_b);
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b);
      return (a.as_bit() == 010101_b);
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b), b(a);
      return (a.as_bit() == b.as_bit());
    });
    TESTX([]()->bool {
      ch_system_t<s2_4_t> a(0101_b, 01_b), b;
      b = a;
      return (a.as_bit() == b.as_bit());
    });
    TESTX([]()->bool {
      ch_system_t<sd1_t> a{1_b2, 2_h};
      return (a.as_bit() == 010010_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd2_t> a{2_h, {1_b2, 2_h}};
      return (a.as_bit() == 0010010010_b);
    });
    TESTX([]()->bool {
      ch_system_t<sd3_t> a{3_h, {1_b2, 2_h}};
      return (a.as_bit() == 0011010010_b);
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
      return (a.as_bit() == 0011010010_b);
    });
    TESTX([]()->bool {
      auto t1 = std::tuple(ch_system_t<s2_4_t>(0101_b, 01_b), ch_system_t<s2_4_t>(1, 0));
      auto t2 = t1;
      auto [x, y] = t2;
      return (x.as_bit() == 010101_b && y.as_bit() == 000100_b);
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

    TESTX([]()->bool {
      ch_system_t<v2_2_t> x{0, 3};
      return (x[0] == 3) && (x[1] == 0);
    });
    TEST([]()->ch_bool {
      ch_system_t<v2_2_t> x{0, 3};
      v2_2_t y(x);
      return (y[0] == 3) && (y[1] == 0);
    });
    TEST([]()->ch_bool {
      ch_system_t<v2_2_t> a{11_b, 00_b};
      ch_system_t<ch_vec<v2_2_t, 2>> b{{11_b, 00_b}, {11_b, 00_b}};
      auto x = b[0][1];
      return (x == 11_b);
    });
  }
  SECTION("funcapi", "[funcapi]") {
    TESTX([]()->bool {
      ch_sbit4 x(3);
      auto y = ch_dup<3>(x);
      return (y == 0x333_h);
    });
    TESTX([]()->bool {
      ch_sbit2 x(3);
      ch_sbit4 y(8);
      auto z = ch_cat(x, y);
      return (z == 111000_b);
    });
    TESTX([]()->bool {
      ch_suint2 x(3);
      ch_suint4 y(8);
      auto z = ch_min(x, y);
      return (z == 3);
    });
    TESTX([]()->bool {
      ch_suint2 x(3);
      ch_suint4 y(8);
      auto z = ch_max(x, y);
      return (z == 8);
    });
    TESTX([]()->bool {
      ch_suint4 x(1), y(-1);
      auto a = ch_abs(x);
      auto b = ch_abs(y);
      return (a == 1 && b == -1);
    });
    TESTX([]()->bool {
      ch_sint4 x(1), y(-1);
      auto a = ch_abs(x);
      auto b = ch_abs(y);
      return (a == 1 && b == 1);
    });
    TESTX([]()->bool {
      ch_sbit4 x;
      ch_sbit2 y;
      ch_tie(x, y) = 011010_b;
      return (x == 0110_b && y == 10_b);
    });
    TESTX([]()->bool {
      ch_suint8 x(11000011_b);
      auto y = ch_rotl(x, 2);
      return (y == 00001111_b);
    });
    TESTX([]()->bool {
      ch_suint8 x(11000011_b);
      auto y = ch_rotr(x, 2);
      return (y == 11110000_b);
    });
    TESTX([]()->bool {
      ch_suint8 x(11000011_b);
      auto y = ch_shuffle<2>(x, {0, 1});
      return (y == 00111100_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(1010_b);
      return (a[0] == a[2] && a[1] == a[3]);
    });
    TESTX([]()->bool {
      ch_sbit4 a;
      a[3] = 1_b;
      a[1] = 0_b;
      return (a[3] == 1_b && a[1] == 0_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(1100_b);
      auto c = ch_slice<2>(a, 1) ^ 01_b;
      return (c == 11_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(1100_b);
      auto c = ch_aslice<2>(a, 1) ^ 01_b;
      return (c == 10_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(0);
      ch_sliceref<2>(a) = 10_b;
      return (a == 0010_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(0);
      ch_asliceref<2>(a, 1) = 11_b;
      return (a == 1100_b);
    });
    TESTX([]()->bool {
      ch_sbit128 a(0);
      ch_system_t<v_sd3_2_t> b{{3_h, {1_b2, 2_h}}, {2_h, {0_b2, 1_h}}};
      ch_sliceref<ch_system_t<v_sd3_2_t>>(a) = b;
      return (ch_slice<ch_system_t<v_sd3_2_t>>(a) == b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(1100_b);
      auto c = ch_cat(a, 1_b);
      return (c == 11001_b);
    });
    TESTX([]()->bool {
      ch_sbit4 a(1100_b);
      auto c = ch_dup<2>(a);
      return (c == 11001100_b);
    });   
  }
}
