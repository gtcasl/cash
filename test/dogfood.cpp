#include "common.h"

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;
using namespace ch::stl;

struct Dogfood {
  __io (
    (ch_out<ch_bit1>) out
  );
  void describe() {
    io.out = 1_b;
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
