#include "common.h"

TEST_CASE("errors", "[errors]") {
  SECTION("uninitialized", "uninitialized") {
    CHECK_THROWS_AS(TEST([]()->ch_bool {  
      ch_int4 a;
      ch_println("a={0:i}", a);
      return (a != 0);
    }), std::domain_error);

    CHECK_THROWS_AS(TEST([]()->ch_bool {
      ch_uint32 a;
      ch_uint8 x, y;
      ch_asliceref<8>(a, 0) = x;
      ch_asliceref<8>(a, 1) = y;
      ch_asliceref<4>(y, 1) = 0x1;
      return (ch_aslice<4>(a, 0) == 0x2);
    }), std::domain_error);

    CHECK_THROWS_AS(TEST([]()->ch_bool {
      ch_uint16 a;
      ch_asliceref<4>(a, 0) = 0x1;
      return (ch_aslice<4>(a, 1) == 0x2);
    }), std::domain_error);

    CHECK_THROWS_AS(TEST([]()->ch_bool {
      ch_uint32 a;
      ch_uint8 x, y;
      ch_asliceref<8>(a, 0) = x;
      ch_asliceref<8>(a, 1) = y;
      ch_asliceref<4>(y, 1) = 0x1;
      return (ch_aslice<4>(a, 2) == 0x2);
    }), std::domain_error);

    CHECK_THROWS_AS(TEST([]()->ch_bool {  
      ch_int4 a(0), b;
      auto c = a + b;
      auto d = 2 * c;
      b = d;
      return (d != 0);
    }), std::domain_error);
  }
}
