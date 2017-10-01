#include "common.h"

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

struct Toto {
  __io (
    (RouterIO)   router,
    (ch_in<Q_t>) qt
  );
  Toto() {
    //--
  }
};

struct Adder {
  __io (
    (ch_in<ch_bit2>)  in1,
    (ch_in<ch_bit2>)  in2,
    (ch_out<ch_bit2>) out
  );
  Adder() {
    io.out = io.in1 + io.in2;
  }
};

struct Adder2 {
  auto operator()(const ch_bit2& a, const ch_bit2& b) const {
    return a + b;
  }
};

void dogfood_void() {}

auto dogfood = [](const ch_bit2& w) {
  ch_bit2 a(1), b(w), c;
  auto adder = Adder();
  adder.io(a, b, c);
  return (c == a + b);
};

auto foo1 = []() {
  __ret(1_b);
};

auto foo2 = [](const ch_bit2& x) {
  __ret(x == 1, x);
};

TEST_CASE("procedure", "[procedure]") {
  SECTION("function", "[function]") {
    TEST([]()->ch_bit1 {
      ch_bit1 a = foo1();
      return (a == 1);
    });

    TEST([]()->ch_bit1 {
      ch_bit1 a;
      ch_bit2 b(3), c;
      __tie(a, c)= foo2(b);
      return (a == 0 && c == b);
    });

    TESTX([]()->bool {
      ch_bus1 out;
      ch_bus2 w(2);
      auto f = ch_function(dogfood);
      out = f.operator()(w);
      ch_simulator sim(f);
      sim.run(1);
      std::cout << "out = " << out << std::endl;
      return (out == 1);
    });

    TESTX([]()->bool {
      auto f = ch_function(dogfood_void);
      f.operator()();
      return true;
    });

    TESTX([]()->bool {
      auto f = ch_function<Adder2>();
      ch_bus2 a(1), b(2);
      auto out = f.operator()(a, b);
      ch_simulator sim(f);
      sim.run(1);
      std::cout << "out = " << out << std::endl;
      return (out == 3);
    });
  }

  SECTION("module", "[module]") {
    TESTX([]()->bool {
      ch_bus1 out;
      auto f = ch_function([&]()->ch_bit1 {
          ch_bit2 a(1), b(2), c;
          auto adder = Adder();
          adder.io(a, b, c);
          return (c == 3);
        });
      out = f();
      ch_simulator sim(f);
      sim.run(1);
      std::cout << "out = " << out << std::endl;
      return (out == 1);
    });

    TESTX([]()->bool {
      ch_bus2 a(1), b(2), out;
      auto m = ch_module<Adder>();
      m(a, b, out);
      ch_simulator sim(m);
      sim.run(1);
      std::cout << "out = " << out << std::endl;
      return (out == 3);
    });
  }
}
