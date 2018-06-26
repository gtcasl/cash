#include <htl/float32.h>
#include "common.h"

using namespace ch::htl;

namespace {

  template <unsigned Delay>
  struct FMultTest {
    __io(
      __in(ch_float32) lhs,
      __in(ch_float32) rhs,
      __out(ch_float32) out
    );

    void describe() {
      io.out = ch_fmul<Delay>(io.lhs, io.rhs);
    }
  };
}

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
      z = ch_fmul<1>(x, y);      
      return (z == 0.0f);
    }, 1);
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z;
      z = ch_fmul<1>(x, y);
      return (z == 0x3e800000_h);
    }, 1);

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(1.0f), z;
      z = ch_fmul<1>(x, y);
      return (z == 0x3f000000_h);
    }, 1);
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(2.0f), z;
      z = ch_fmul<1>(x, y);
      return (z == 0x3f800000_h);
    }, 1);
    
    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(1.5f), z;
      z = ch_fadd<1>(x, y);
      return (z == 0x40000000_h);
    }, 1);
    
    TEST([]()->ch_bool {
      ch_float32 x(2.5f), y(0.5f), z;
      z = ch_fsub<1>(x, y);
      return (z == 0x40000000_h);
    }, 1);

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z, e;
      z = ch_fmul<5>(x, y);
      e = ch_delay<ch_float32>(0x3e800000_h, 5);
      ch_print("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_time(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 5);

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z, e;
      z = ch_fadd<7>(x, y);
      e = ch_delay<ch_float32>(0x3f800000_h, 7);
      //ch_print("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_time(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 7);

    TEST([]()->ch_bool {
      ch_float32 a(0.1f);
      ch_print("a={0:f}", a);
      return ch_true;
    });
  }

  SECTION("verilog", "[verilog]") {
    TESTX([]()->bool {
      ch_device<FMultTest<2>> device;
      device.io.lhs = 0.5f;
      device.io.rhs = 0.5f;
      ch_tracer tracer(std::cout, device);
      tracer.run(2*2);
      ch_verilog("fmulttest.v", device);
      return (0.25f == device.io.out);
    });
  }
}
