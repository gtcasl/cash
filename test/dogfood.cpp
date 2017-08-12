#include "common.h"

using namespace cash::core_literals;

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <boost/range/any_range.hpp>

typedef std::pair<const std::string, std::string> datatype1_t;

typedef std::pair<const std::string, const std::string> datatype2_t;

typedef const std::pair<const std::string, std::string> datatype3_t;

typedef boost::any_range<datatype1_t,
                         boost::single_pass_traversal_tag,
                         datatype1_t,
                         std::ptrdiff_t
                        > any_range1;

typedef boost::any_range<datatype2_t,
                         boost::single_pass_traversal_tag,
                         datatype2_t,
                         std::ptrdiff_t
                        > any_range2;

typedef boost::any_range<datatype3_t,
                         boost::single_pass_traversal_tag,
                         datatype3_t,
                         std::ptrdiff_t
                        > any_range3;

void test_any_range() {
  any_range1 x;
  std::map<std::string, std::string> m(x.begin(), x.end());
  any_range1 y(m);

  any_range3 z;
  any_range1 w(z);
  any_range3 k(x);

  /*
  std::pair<std::string, std::string> q;
  auto iter = m.find("");
  q = *iter;
*/

  //any_range2 y(m);
  //any_range3 z(m);
  //any_range1 x2(y);
  //any_range2 y2(x);
  //any_range1 x2(z);

  /*for (const auto& x : make_any_range<any_range3>(m)) {
    std::cout << x.first;
  }*/
}

TEST_CASE("dogfood", "[debug]") {

  TEST([]()->ch_bit1 {
    ch_bit4 a(0), b;
    __switch (a) (
    __case (0) (
      b.slice<3>(0) = 101_b;
    )
    __case (1) (
      b = 0;
    )
    __default(
      b = 1000_b;
    ));
    return (b == 1101_b);
  });

  /*TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(1), x;
    __if (a == 1) (
       x = 0;
       __if (b == 0) (
         x = 1;
       )
       __elif (b == 1) (
         x = 2;
       )
       __else (
         x = 3;
       );
    )
    __else(
       x = 4;
    );
    ch_print("x={0}", x);
    return (x == 2);
  });

  TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(2), x;
    __if (a == 1) (
       x = 0;
       __if (b == 0) (
         x = 1;
       )
       __elif (b == 1) (
         x = 2;
       )
       __else (
         x = 3;
       );
    )
    __else(
       x = 4;
    );
    ch_print("x={0}", x);
    return (x == 3);
  });

  TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(2), x;
    __if (a == 1) (
       x = 0;
       __if (b == 0) (
         x = 1;
       )
       __elif (b == 1) (
         x = 2;
       );
    )
    __else (
       x = 4;
    );
    ch_print("x={0}", x);
    return (x == 0);
  });

  TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(1), x;
    __if (a == 1) (
       x = 0;
       __if (b == 0) (
         x = 1;
       )
       __elif (b == 1) (
         x = 2;
       );
       x = 3;
    )
    __else (
       x = 4;
    );
    ch_print("x={0}", x);
    return (x == 3);
  });

  TEST([]()->ch_bit1 {
    ch_bit4 a(1), b(1), c(2), d, e;
    __switch (a) (
    __case (0) (
      d = 0;
    )
    __case (1) (
       __if (b == 0) (
         d = 1;
       )
       __elif (b == 1) (
         e = 1;
       )
       __else (
         d = 0;
         e = 0;
       );
    )
    __default(
       d = c;
       e = c;
    ));
    ch_print("d={0}, e={1}", d, e);
    return (d + e == 3);
  });

  TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(1), x;
    __if (a == 1) (
       x = 0;
       __if (b == 0) (
         x[0] = 1;
       )
       __elif (b == 1) (
         x[1] = 1;
       );
       x[2] = 1;
    )
    __else(
       x = 4;
    );
    ch_print("x={0}", x);
    return (x == 6);
  });

  TEST([]()->ch_bit1 {
    ch_bit8 a(1), b(1), x, y;
    __if (a == 1) (
       (y, x) = 1;
       __if (b == 0) (
         x = 1;
       )
       __elif (b == 1) (
         y = 1;
       );
    )
    __else (
       x = 4;
       y = 5;
    );
    ch_print("x={0}, y={1}", x, y);
    return (x == 1 && y == 1);
  });*/
}
