#include "common.h"

using namespace cash::core_literals;

void experimental() {
  //--
}

TEST_CASE("dogfood", "[dogfood]") {
  experimental();

  /*TEST([]()->ch_bit1 {
    ch_bit4 a(1101_b), b(0100);
    auto x = a.slice<2>(0);
    //auto c = (a.slice<2>(0), b.slice<2>(2));
    return '1';
  });*/
}
