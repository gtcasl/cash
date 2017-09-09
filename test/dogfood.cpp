#include "common.h"

using namespace cash::core_literals;

void experimental() {
  //--
}

template <unsigned N>
const auto foo(ch_bitbase<N>& x, const ch_bitbase<N>& y) {
  return ch_select(x > y, x);
}

TEST_CASE("dogfood", "[dogfood]") {
  experimental();

  TESTX([]()->bool {
    ch_bus4 a;
    uint8_t x = 4;
    a.write(0, &x, sizeof(x), 0, 4);
    return (a == 4);
  });

  TEST([]()->ch_bit1 {
    /*ch_bit4 a(1101_b), b(0100);
    ch_lit<4> x(3);
    auto c = foo(a, b);

    ch_bitbase<4>& w1 = (ch_bitbase<4>&)a;
    ch_bit<4> w2 = (ch_bit<4>)x;
    ch_bit<4> w3 = (ch_bit<4>)1;

    auto y1 = ch_select(a > b, x);
    auto y2 = ch_select(a > b, a, b);
    auto y3 = ch_select(a > b, a, x);
    auto y4 = ch_select(a > b, x, a);
    auto y5 = ch_select(a > b, 2, x);

    //bool ret = is_explicitly_convertible<int, ch_bit4>::value;
    //std::cout << ret << std::endl;

    std::cout << cash::internal::deduce_bitcount<int, double>::value << std::endl;

    //auto x = a.slice<2>(0);
    //auto c = (a.slice<2>(0), b.slice<2>(2));*/
    return 1_b;
  });
}
