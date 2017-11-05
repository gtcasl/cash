#include "common.h"
#include <../htl/onehot.h>
#include <../htl/mux.h>
#include <../htl/xbar.h>
#include <../htl/arbiter.h>

using namespace ch::htl;

TEST_CASE("htl", "[htl]") {
  SECTION("onehot", "[onehot]") {
    TEST([]()->ch_bit1 {
      auto y = ch_hot2bin<4>(0001_b);
      return (y == 0);
    });
    TEST([]()->ch_bit1 {
      auto y = ch_hot2bin<4>(1000_b);
      return (y == 3);
    });
    TEST([]()->ch_bit1 {
    auto y = ch_bin2hot<4>(00_b);
      return (y == 0001_b);
    });
    TEST([]()->ch_bit1 {
      auto y = ch_bin2hot<4>(11_b);
      return (y == 1000_b);
    });
  }
  SECTION("hmux", "[hmux]") {
    TEST([]()->ch_bit1 {
      auto y = ch_hmux(0010_b, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bit1 {
      auto y = ch_hmux(1000_b, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xA_h);
    });
    TEST([]()->ch_bit1 {
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(0010_b, x);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bit1 {
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(1000_b, x);
      return (y == 0xA_h);
    });
  }
  SECTION("hxbar", "[hxbar]") {
    TESTX([]()->bool {
      ch_device<ch_hxbar<ch_bit4, 3, 2>> device;
      device.io.in[0] = 5;
      device.io.in[1] = 7;
      device.io.in[2] = 9;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.sel = 1 + (1 << 3);
      t = sim.step(t);
      int ret = (5 == (int)device.io.out[1]);
      device.io.sel = 1 + (0 << 3);
      t = sim.step(t);
      ret &= (5 == (int)device.io.out[0]);
      device.io.sel = 2 + (0 << 3);
      t = sim.step(t);
      ret &= (7 == (int)device.io.out[0]);
      device.io.sel = 4 + (0 << 3);
      t = sim.step(t);
      ret &= (9 == (int)device.io.out[0]);
      return !!ret;
    });
  }
  SECTION("rrArbiter", "[rrArbiter]") {
    TESTX([]()->bool {
      ch_device<ch_rrArbiter<4>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in[0] = false;
      device.io.in[1] = false;
      device.io.in[2] = false;
      device.io.in[3] = false;
      t = sim.step(t);
      auto ret = 0 == (int)device.io.out;
      device.io.in[1] = true;
      t = sim.step(t);
      ret &= 2 == (int)device.io.out;
      device.io.in[2] = true;
      t = sim.step(t, 2);
      ret &= 4 == (int)device.io.out;
      device.io.in[3] = true;
      t = sim.step(t, 3);
      ret &= 8 == (int)device.io.out;
      device.io.in[1] = false;
      device.io.in[2] = false;
      t = sim.step(t);
      ret &= 8 == (int)device.io.out;
      device.io.in[3] = false;
      t = sim.step(t);
      ret &= 0 == (int)device.io.out;
      device.io.in[0] = true;
      t = sim.step(t);
      ret &= 1 == (int)device.io.out;
      return !!ret;
    });
  }
}
