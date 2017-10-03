#include "common.h"

struct inverter {
  __io (
    (ch_in<ch_bit2>) in,
    (ch_out<ch_bit2>) out
  );
  void describe() {
    auto x = ~io.in;
    __tap(x);
    io.out = x;
  }
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
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      ch_assert(c == 11_b, "assertion failed!");
      return (c == 11_b);
    });
    TEST([]()->ch_bit1 {
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
    });
  }
  
  SECTION("taps", "[tap]") {
    TEST([]()->ch_bit1 {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      __tap(c);
      return (c == 11_b);
    });
  }
  
  SECTION("tick", "[tick]") {
    TEST([]()->ch_bit1 {
      ch_print("tick={0}", ch_getTick());
      return 1_b;
    });
  }
  
  SECTION("print", "[print]") {
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
  
  SECTION("tracer", "[tracer]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_poke(module->io.in, 2);
      ch_tracer tracer(std::cout, module);
      tracer.run();
      return (ch_peek<int>(module->io.out) == 1);
    });
  }

  SECTION("vcdtracer", "[vcdtracer]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_poke(module->io.in, 2);
      ch_vcdtracer tracer(std::cout, module);
      tracer.run();
      return (ch_peek<int>(module->io.out) == 1);
    });
  }

  SECTION("stats", "[stats]") {
    TESTX([]()->bool {
      ch_module<inverter> module;
      ch_dumpStats(std::cout, module);
      return true;
    });
  }

  SECTION("bugs", "[bugs]") {
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
}
