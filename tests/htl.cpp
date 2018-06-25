#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>
#include <htl/pipe.h>
#include <htl/float32.h>
#include "common.h"

using namespace ch::htl;

namespace {

template <typename T, unsigned Delay>
struct PipeTest {
  __io (
    (ch_deq_io<T>) enq,
    (ch_enq_io<T>) deq,
    __out(T) value
  );
  void describe() {
    ch_module<ch_pipe<T, Delay>> pipe;
    pipe.io.enq(io.enq);
    pipe.io.deq(io.deq);

    ch_float32 x(io.enq.data);
    ch_float32 y(1.0f);
    io.value = ch_udf<fMult<Delay>>(x, y, io.deq.ready);
  }
};

}

TEST_CASE("htl", "[htl]") {
  SECTION("pipe", "[pipe]") {
    TESTX([]()->bool {
      int ret = 1;
      ch_device<PipeTest<ch_bit32, 4>> device;
      ch_vcdtracer sim("pipe.vcd", device);
      ch_tick t = sim.reset(0);
      device.io.enq.data  = 0x3e4ccccd; // 0.2f
      device.io.enq.valid = true;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !device.io.deq.valid;
      device.io.enq.data  = 0x3dcccccd; // 0.1f
      device.io.enq.valid = true;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !device.io.deq.valid;
      device.io.enq.valid = false;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !device.io.deq.valid;
      device.io.deq.ready = false;
      t = sim.step(t, 3);
      ret &= !device.io.deq.valid;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      device.io.deq.ready = false;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3dcccccd == device.io.deq.data;
      device.io.deq.ready = false;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3dcccccd == device.io.deq.data;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !device.io.deq.valid;
      t = sim.step(t, 1);
      return !!ret;
    });
  }
  SECTION("onehot", "[onehot]") {
    TEST([]()->ch_bool {
      auto y = ch_hot2bin<4>(0001_b);
      return (y == 0);
    });
    TEST([]()->ch_bool {
      auto y = ch_hot2bin<4>(1000_b);
      return (y == 3);
    });
    TEST([]()->ch_bool {
    auto y = ch_bin2hot<4>(00_b);
      return (y == 0001_b);
    });
    TEST([]()->ch_bool {
      auto y = ch_bin2hot<4>(11_b);
      return (y == 1000_b);
    });
  }
  SECTION("hmux", "[hmux]") {
    TEST([]()->ch_bool {
      ch_bit4 k(0010_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(1000_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xA_h);
    });
    TEST([]()->ch_bool {
           ch_bit4 k(0010_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
           ch_bit4 k(1000_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
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
      int ret = (5 == device.io.out[1]);
      device.io.sel = 1 + (0 << 3);
      t = sim.step(t);
      ret &= (5 == device.io.out[0]);
      device.io.sel = 2 + (0 << 3);
      t = sim.step(t);
      ret &= (7 == device.io.out[0]);
      device.io.sel = 4 + (0 << 3);
      t = sim.step(t);
      ret &= (9 == device.io.out[0]);
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
      auto ret = 0 == device.io.grant;
      device.io.in[1] = true;
      t = sim.step(t);
      ret &= 2 == device.io.grant;
      device.io.in[2] = true;
      t = sim.step(t, 2);
      ret &= 4 == device.io.grant;
      device.io.in[3] = true;
      t = sim.step(t, 3);
      ret &= 8 == device.io.grant;
      device.io.in[1] = false;
      device.io.in[2] = false;
      t = sim.step(t);
      ret &= 8 == device.io.grant;
      device.io.in[3] = false;
      t = sim.step(t);
      ret &= 0 == device.io.grant;
      device.io.in[0] = true;
      t = sim.step(t);
      ret &= 1 == device.io.grant;
      return !!ret;
    });
  }
  SECTION("arbiter", "[arbiter]") {
    TESTX([]()->bool {
      ch_device<ch_xbar_switch<ch_bit4, 2>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in[0].data  = 0xA;
      device.io.in[0].valid = false;
      device.io.in[1].data  = 0xB;
      device.io.in[1].valid = false;
      device.io.out.ready   = false;
      t = sim.step(t);
      int ret = 1;
      ret &= !device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      device.io.out.ready = true;
      t = sim.step(t);
      ret &= !device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      device.io.in[0].valid = true;
      t = sim.step(t);
      ret &= !!device.io.out.valid;
      ret &= !!device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      ret &= 0xA == device.io.out.data;
      device.io.in[1].valid = true;
      t = sim.step(t, 2);
      ret &= !!device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !!device.io.in[1].ready;
      ret &= 0xB == device.io.out.data;
      return !!ret;
    });
  }
}
