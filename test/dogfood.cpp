#include "common.h"

using namespace cash::core_literals;

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
