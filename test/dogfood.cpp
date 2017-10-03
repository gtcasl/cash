#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

struct Dogfood {
  __io (
    (ch_out<ch_bit1>) out
  );
  void describe() {
    io.out = 1;
  }
};

int main(int argc, char **argv) {
  ch_module<Dogfood> dogfood;
  ch_simulator sim(dogfood);
  assert(ch_peek<bool>(dogfood->io.out));
  sim.run();
  return 0;
}
