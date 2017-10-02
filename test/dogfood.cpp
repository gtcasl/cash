#include <cash.h>

using namespace ch::core;
using namespace ch::literals;
using namespace ch::sim;

auto dogfood = []()->ch_bit1 {
  ch_bit4 a(1100_b), b(1);
  ch_bit2 c = a.slice<2>(1) ^ 01_b;
  ch_print("c={0}", c);
  __if (b == 1) (
    ch_assert(c == 11_b, "assertion failed!");
  )
  __else (
    ch_assert(c != 11_b, "assertion failed!");
  );
  return (c == 11_b);
};

int main(int argc, char **argv) {
  //--

  auto f = ch_function(dogfood);
  auto out = f();

  return 0;
}
