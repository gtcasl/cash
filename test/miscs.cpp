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

void dogfood_void() {}

auto dogfood = [](const ch_bit2& w) {
  ch_bit2 a(1), b(w), c;
  auto adder = Adder();
  adder.io(a, b, c);
  return (c == a + b);
};

TEST_CASE("miscs", "[miscs]") {
  SECTION("utils", "[utils]") {
    TESTX([]()->bool {
      char bigs[258];
      memset(bigs, ' ', sizeof(bigs));
      bigs[255] = '%';
      bigs[256] = 'd';
      bigs[257] = '\0';
      std::string s = fstring(bigs, 7);
      std::cout << s << " " << s.size() << std::endl;
      return (s.size() == 256 && s[255] == '7');
    });
  }
  
  SECTION("assert", "[assert]") {
    using namespace cash::core_literals;
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      ch_assert(c == 11_b, "assertion failed!");
      return (c == 11_b);
    });
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b), b(1);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      __if (b == 1) (
        ch_assert(c == 11_b, "assertion failed!");
      )
      __else (
        ch_assert(c != 11_b, "assertion failed!");
      );
      return (c == 11_b);
    });
  }
  
  SECTION("taps", "[tap]") {
    using namespace cash::core_literals;
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      __tap(c);
      return (c == 11_b);
    });
  }
  
  SECTION("tick", "[tick]") {
    using namespace cash::core_literals;
    TEST([]()->ch_bit1 {
      ch_print("tick={0}", ch_getTick());
      return 1_b;
    });
  }
  
  SECTION("print", "[print]") {
    using namespace cash::core_literals;
    TEST([]()->ch_bit1 {
      ch_print("hello world");
      return 1_b;
    });
    TEST([]()->ch_bit1 {
      ch_bit8 a(255);
      ch_print("a={0}", a);
      return 1_b;
    });    
    TEST([]()->ch_bit1 {
      ch_bit8 a(255), b(0);
      ch_print("a={0}, b={1}", a, b);
      return 1_b;
    });  
    TEST([]()->ch_bit1 {
      ch_bit8 a(255);
      ch_bit1 b(1);
      __if (b) (
        ch_print("a={0}", a);
      );
      return 1_b;
    });
    TEST([]()->ch_bit1 {
      ch_float a(0.1f);
      ch_print("a={0:f}", a);
      return 1_b;
    });
  }
  
  SECTION("vctracer", "[vctracer]") {
    using namespace cash::sim_literals;
    TESTX([]()->bool {
      std::ofstream vcd_file("test.vcd");
      ch_bus2 in(2), x, out;       
      auto inverter = [](const ch_bit2& x)->ch_bit2 {
        __tap(x);
        return ~x;
      };             
      auto func = ch_function(inverter);
      out = func(in);
      x = func.get_tap<2>("x");
      ch_vcdtracer tracer(vcd_file, func);
      __trace(tracer, in, out);
      tracer.run();
      return (out == 1);
    });
  }

  SECTION("stats", "[stats]") {
    using namespace cash::sim_literals;
    TESTX([]()->bool {
      auto inverter = [](const ch_bit2& x)->ch_bit2 {
        ch_bit2 a(0), b(1);
        return ~x;
      };
      ch_bus2 in(0), out;
      auto func = ch_function(inverter);
      out = func(in);
      func.dump_stats(std::cout);
      return true;
    });
  }

  SECTION("bugs", "[bugs]") {
    using namespace cash::core_literals;
    TEST([]()->ch_bit1 {
      ch_bit4 a, b, c;
      a = 0xf_h;
      b = a;
      c = b + 1;
      b = 0;
      return (c == 1);
    });

    TEST([]()->ch_bit1 {
      ch_bit2 a, b;
      a = 0;
      b = a;
      a = 1;
      return (b == 1);
    });
  }

  SECTION("callable", "callable") {
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
      auto f3 = ch_function(dogfood_void);
      f3.operator()();
      return true;
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
