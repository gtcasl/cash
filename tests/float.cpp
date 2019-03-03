#include <htl/float32.h>
#include "common.h"

using namespace ch::htl;

namespace {

  template <unsigned Delay>
  struct FMultTest {
    __io (
      __in (ch_float32) lhs,
      __in (ch_float32) rhs,
      __out (ch_float32) out
    );

    void describe() {
      auto a = ch_fadd<Delay>(io.lhs, io.rhs);
      auto b = ch_fsub<Delay>(a, io.rhs);
      auto c = ch_fmul<Delay>(b, io.lhs);
      auto d = ch_fmul<Delay>(c, a);
      io.out = d;
      //ch_println("{0}: clk={1}, rst={2}, a={3}, b={4}, c={5}, d={6}", ch_now(), ch_clock(), ch_reset(), a, b, c, d);
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
      //ch_println("{0}: clk={1}, rst={2}, z={3}", ch_now(), ch_clock(), ch_reset(), z);
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
      e = ch_case<ch_float32>(ch_now(), (2+5*2), 0x3e800000_h)(z);
      //ch_println("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_now(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 5);

    TEST([]()->ch_bool {
      ch_float32 x(0.5f), y(0.5f), z, e;
      z = ch_fadd<7>(x, y);
      e = ch_case<ch_float32>(ch_now(), (2+7*2), 0x3e800000_h)(z);
      //ch_println("{0}: clk={1}, rst={2}, z={3}, e={4}", ch_now(), ch_clock(), ch_reset(), z, e);
      return (z == e);
    }, 7);

    TEST([]()->ch_bool {
      ch_float32 a(0.1f);
      //ch_println("a={0:f}", a);
      return ch_true;
    });
  }

  SECTION("verilog", "[verilog]") {
    TESTX([]()->bool {
      ch_device<FMultTest<2>> device;
      device.io.lhs = 0.5f;
      device.io.rhs = 0.5f;
      ch_simulator sim(device);
      sim.run(2*2*4);
      ch_toVerilog("fmultest.v", device);
      float ret(device.io.out);
      //std::cout << "ret=" << ret << std::endl;
      return (0.25f == ret);
    });
  }
}
