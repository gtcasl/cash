#include "common.h"
#include <htl/float32.h>

using namespace ch::htl;

TEST_CASE("floats", "[floats]") {
  SECTION("basic", "[basic]") {
    TEST([]()->ch_bool {
      ch_float32 x(1.0f), y(1.0f);
      return (x == y);
    });

    TEST([]()->ch_bool {
      ch_float32 x(0.0f), y(1.0f);
      return (x != y);
    });

    TEST([]()->ch_bool {
      ch_float32 x(0.0f);
      ch_bit32 y(0);
      return (x.as_bit() == y);
    });

    TEST([]()->ch_bool {
      ch_bit32 x(0);
      ch_float32 y(x);
      return (y == 0.0f);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f);
      return (x == 0x3f000000_h);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(1.0f);
      return (x == 0x3f800000_h);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(2.0f);
      return (x == 0x40000000_h);
    });
  }
  
  SECTION("arithmetic test", "[math]") {
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.0f), z;
      z = x * y;
      return (z == 0.0f);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z;
      z = x * y;
      return (z == 0x3e800000_h);
    });

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(1.0f), z;
      z = x * y;
      return (z == 0x3f000000_h);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(2.0f), z;
      z = x * y;
      return (z == 0x3f800000_h);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(1.5f), z;
      z = x + y;
      return (z == 0x40000000_h);
    });
    
    TEST([]()->ch_bool {
      ch_float32 x(2.5f), y(0.5f), z;
      z = x - y;
      return (z == 0x40000000_h);
    });

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z, e;
      z = ch_udf<fMult<5>>(x, y);
      e = ch_delay<ch_float32>(0x3e800000_h, 5);
      //ch_print("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_time(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 2+2*5);

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z, e;
      z = ch_udf<fAdd<7>>(x, y);
      e = ch_delay<ch_float32>(0x3f800000_h, 7);
      //ch_print("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_time(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 2+2*7);

    TEST([]()->ch_bool {
      ch_float32 a(0.1f);
      ch_print("a={0:f}", a);
      return ch_true;
    });
  }
}
