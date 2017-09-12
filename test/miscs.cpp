#include "common.h"

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
      ch_device myDevice(inverter, in, out);     
      x = myDevice.get_tap<2>("x");
      ch_vcdtracer tracer(vcd_file, myDevice);
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
      ch_device device(inverter, in, out);
      device.dump_stats(std::cout);
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
}
