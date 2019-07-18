#include "common.h"

TEST_CASE("hof", "[hof]") {
  SECTION("map", "[map]") {
    TEST([]()->ch_bool {
      ch_uint<8> a(10101010_b), e(01010101_b);
      auto r = ch_map(a, [](auto x)->ch_bool { return ~x; });
      return (r.as_uint() == e);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_uint<4>, 4> a{3, 2, 1, 0}, e{4, 3, 2, 1};
      auto r = ch_map(a, [](auto x)->ch_uint<4> { return x + 1; });
      return (r == e);
    });
  }

  SECTION("fold", "[fold]") {
    TEST([]()->ch_bool {
      ch_uint<8> a(10101010_b);
      auto r = ch_fold(a, [](auto x, auto y)->ch_bool { return x || y; }, 0);
      return (r == true);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_uint<4>, 4> a{3, 2, 1, 0};
      auto r = ch_fold(a, [](auto x, auto y)->ch_uint<4> { return x + y; }, 0);
      return (r == 6);
    });
  }

  SECTION("scan", "[scan]") {
    TEST([]()->ch_bool {
      ch_uint<8> a(10101000_b);
      auto r = ch_scan(a, [](auto x, auto y)->ch_bool { return x || y; }, 0);
      return (r.as_uint() == 11111000_b);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_uint<4>, 4> a{3, 2, 1, 0}, e{6, 3, 1, 0};
      auto r = ch_scan(a, [](auto x, auto y)->ch_uint<4> { return x + y; }, 0);
      return (r == e);
    });
  }

  SECTION("zip", "[zip]") {
    TEST([]()->ch_bool {
      ch_uint<8> a(10101010_b), b(01000100_b);
      auto r = ch_zip(a, b, [](auto x, auto y)->ch_bool { return x || y; });
      return (r.as_uint() == 11101110_b);
    });

    TEST([]()->ch_bool {
      ch_vec<ch_uint<4>, 4> a{3, 2, 1, 0}, b{4, 3, 2, 1}, e{7, 5, 3, 1};
      auto r = ch_zip(a, b, [](auto x, auto y)->ch_uint<4> { return x + y; });
      return (r == e);
    });
  }
}