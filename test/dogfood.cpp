#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

__inout(RouterIO, (
  (ch_in<ch_bit2>)  in,
  (ch_out<ch_bit2>) out
));

struct Adder : public ch_module<Adder> {
  __io(
    (ch_in<ch_bit2>)  in1,
    (ch_in<ch_bit2>)  in2,
    (ch_out<ch_bit2>) out
  );
  Adder() {
   *io.out = *io.in1 + *io.in2;
  }
};

struct A {
  A(int _x, int&_y) {
    x = _x;
    _y = y;
  }
  int x;
  int y;
};

int x = 0, y;
A a{x, y};

ch_bit1 dogfood() {
  ch_bit2 a, b, c;
  auto adder = Adder();
  adder(a, b, c);
  return ch_true;
}

int main(int argc, char **argv) {
  ch_bus1 out;
  ch_device myDevice1(dogfood, out);

  ch_bus2 in1, in2, out2;
  ch_device myDevice2(Adder(), in1, in2, out2);

  ch_simulator sim(myDevice1, myDevice2);
  sim.run(1);

  std::cout << "out = " << out << std::endl;

  assert(out == 1);

  return 0;
}
