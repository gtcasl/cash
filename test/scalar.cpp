#include "common.h"

__enum (e2_t, 2, (
  (idle, 0),
  execute,
  stats,
  done
));

__union (u1_t, (
  (ch_bit4) a
  ));

__union (u2_t, (
  (ch_bit2) a,
  (ch_bit4) b
  ));

__struct (s1_t, (
  (ch_bit4) a
  ));

__struct (s2_t, (
  (ch_bit4) a,
  (ch_bit4) b
));

__union (u4_t, (
  (u1_t) a,
  (s2_t) b
));

__struct (sd1_t, s1_t, (
  (ch_bit4) b
));

__struct (sd2_t, sd1_t, (
  (ch_bit4) c
));

__struct (sd3_t, (
  (sd1_t)   d,
  (ch_bit4) e
));

using v2_1_t = ch_vec<ch_bit2, 1>;
using v2_2_t = ch_vec<ch_bit2, 2>;
using v2_3_t = ch_vec<ch_bit2, 3>;

TEST_CASE("scalars", "[scalars]") {
  SECTION("enum", "[enum]") {

  }
  SECTION("union", "[union]") {

  }
  SECTION("struct", "[struct]") {

  }
  SECTION("vector", "[vector]") {

  }
}

