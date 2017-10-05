#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

struct Dogfood {
  __io (
    (ch_out<ch_bit1>) out
  );
  void describe() {
    /*ch_bit4 a;
    ch_bit1 x, y;
    a[3] = x;
    a[1] = y;
    x = 1_b;
    y = 0_b;
    auto z = (a[3] == 1_b && a[1] == 0_b);
    io.out = z;*/

    /*ch_bit4 a;
    ch_bit1 x, y;
    a[3] = x;
    a[1] = y;
    x = 1_b;
    y = 0_b;
    auto z = (a[3] == 1_b && a[1] == 0_b);
    io.out = z;*/

    ch_bit4 a;
    ch_bit1 x;
    ch_bit2 y;
    ch_bit2 z;

    a[0] = x;
    a.slice<2>(1) = y;
    a[3] = x;
    y = z;

    x = 1_b;
    z = 10_b;
    io.out = (a == 1101_b);

    /*ch_bit4 a(1), b(0), c;
     __if (a == 1) (
       c = 0;
       __if (b == 1) (
         c = 1;
       );
     )__else(
      c = 2;
     );
    //ch_print("c={0}", c);
    io.out = (c == 0);*/
    //io.out = 1;
  }
};

int main(int argc, char **argv) {
  ch_module<Dogfood> dogfood;
  ch_simulator sim(dogfood);
  sim.run(1);
  assert(ch_peek<bool>(dogfood->io.out));
  return 0;
}
