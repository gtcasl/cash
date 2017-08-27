#include "common.h"

using namespace cash::core_literals;

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
    TEST([]()->ch_bit1 {
      ch_print("tick={0}", ch_tick());
      return '1';
    }, 5);
  }
  
  SECTION("print", "[print]") {
    TEST([]()->ch_bit1 {
      ch_print("hello world");
      return '1';
    });
    TEST([]()->ch_bit1 {
      ch_bit8 a(255);
      ch_print("a={0}", a);
      return '1';
    });    
    TEST([]()->ch_bit1 {
      ch_bit8 a(255), b(0);
      ch_print("a={0}, b={1}", a, b);
      return '1';
    });  
    TEST([]()->ch_bit1 {
      ch_bit8 a(255);
      ch_bit1 b(1);
      ch_print(b, "a={0}", a);
      return '1';
    });
    TEST([]()->ch_bit1 {
      ch_float a(0.1f);
      ch_print("a={0:f}", a);
      return '1';
    });
  }
  
  SECTION("vctracer", "[vctracer]") {
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
}
