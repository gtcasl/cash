#include "common.h"

TEST_CASE("miscellaneous tests", "[miscs]") {   
  SECTION("test utils", "[utils]") {
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
  
  SECTION("test assert", "[assert]") {
    using namespace chdl::core_literals;
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      ch_assert(c == 11_b, "assertion failed!");
      return (c == 11_b);
    });
  }
  
  SECTION("test taps", "[tap]") {
    using namespace chdl::core_literals;
    TEST([]()->ch_logic {
      ch_bit4 a(1100_b);
      ch_bit2 c = a.slice<2>(1) ^ 01_b;
      __ch_tap(c);
      return (c == 11_b);
    });
  }
  
  SECTION("test tick", "[tick]") {
    TEST([]()->ch_logic {
      ch_print("tick={0}", ch_tick());
      return '1';
    }, 5);
  }
  
  SECTION("test print", "[print]") {
    TEST([]()->ch_logic {
      ch_print("hello world");
      return '1';
    });
    TEST([]()->ch_logic {
      ch_bit8 a(255);
      ch_print("a={0}", a);
      return '1';
    });    
    TEST([]()->ch_logic {
      ch_bit8 a(255), b(0);
      ch_print("a={0}, b={1}", a, b);
      return '1';
    });  
    TEST([]()->ch_logic {
      ch_bit8 a(255);
      ch_logic b(1);
      ch_print(b, "a={0}", a);
      return '1';
    });
    TEST([]()->ch_logic {
      ch_float a(0.1f);
      ch_print("a={0:f}", a);
      return '1';
    });
  }
  
  SECTION("test vctracer", "[vctracer]") {
    TESTX([]()->bool {          
      ch_bus2 in(2), x, out;       
      auto inverter = [](const ch_bit2& x)->ch_bit2 {
        __ch_tap(x);
        return ~x;
      };             
      ch_device myDevice(inverter, in, out);     
      x = myDevice.get_tap<2>("x");
      ch_vcdtracer tracer("test.vcd", myDevice);
      __ch_trace(tracer, in, out);
      tracer.run();
      return (out == 1);
    });
  }
}
