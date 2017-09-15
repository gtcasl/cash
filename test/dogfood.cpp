#include <cash.h>

using namespace cash::core;
using namespace cash::core_literals;
using namespace cash::sim;

__inout (RouterIO, (
  (ch_in<ch_bit2>)  in,
  (ch_out<ch_bit2>) out
));

__struct (Q_t, (
  (ch_bit2) p1,
  (ch_bit2) p2
));

using Q1 = ch_seq<ch_bit2>;

using Q2 = ch_seq<Q_t>;

struct Adder {
  __io (
    (ch_in<ch_bit2>)  in1,
    (ch_in<ch_bit2>)  in2,
    (ch_out<ch_bit2>) out
  );
  Adder() {
    Q1 x;
    Q2 y;
    x.next = 0;
    y.p1 = 0;
    y.next.p1 = 0;
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

ch_bit1 dogfood(const ch_bit2& w) {
  Q1 x;
  Q2 y;
  x.next = 0;
  y.p1 = 0;
  y.next.p1 = 0;
  ch_bit2 a(1), b(w), c;
  auto adder = Adder();
  adder.io(a, b, c);
  return (c == 3);
}

void dogfood_void() {
  // oops!
}

int main(int argc, char **argv) {
  ch_bus1 out;
  ch_bus2 w;
  auto f1 = ch_function(dogfood);
  out = f1.operator()(w);

  ch_bus1 out2;
  auto f2 = ch_function([&]()->ch_bit1 {
      ch_bit2 a(1), b(2), c;
      auto adder = Adder();
      adder.io(a, b, c);
      return (c == 3);
    });
  out2 = f2();

  auto f3 = ch_function(dogfood_void);
  f3.operator()();

  ch_bus2 in1, in2, out3;
  auto m1 = ch_module<Adder>();
  m1(in1, in2, out3);

  //ch_simulator sim(f1, f2, m3);
  //sim.run(1);

  std::cout << "out = " << out << std::endl;

  assert(out == 1);

  return 0;
}
