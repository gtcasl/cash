#include "common.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::stl;

__struct (s2_t, (
  (ch_bit4) a,
  (ch_bit4) b
));

__struct (s4_t, (
  (ch_bit4) a
  ));

__struct (sd1_t, s4_t, (
  (ch_bit4) b
));

__struct (sd3_t, (
  (sd1_t)   c,
  (ch_bit4) d
));

struct Dogfood {
  __io (
    (ch_out<ch_bit1>) out
  );
  void describe() {
    //io.out = 1_b;

    auto force_move_a = []() {
      return ch_bit4{1};
    };
    auto force_move_b = []() {
      return ch_bit4{2};
    };
    s2_t s{0};
    s.a = force_move_a();
    s.b = force_move_b();
    io.out = (s.asBits() == 21_h);
  }
};

int main(int argc, char **argv) {
  {
    ch_module<Dogfood> dogfood;
    ch_simulator sim(dogfood);
    sim.run(1);
    assert(ch_peek<bool>(dogfood.io.out));
  }

  return 0;
}
