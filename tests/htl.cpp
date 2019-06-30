#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>
#include <htl/pipereg.h>
#include <htl/float32.h>
#include <htl/counter.h>
#include <htl/enc.h>
#include "common.h"

using namespace ch::htl;

namespace {

template <typename T, unsigned Delay>
struct PipeTest {
  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    __out (T) value
  );
  void describe() {
    ch_module<ch_pipereg<T, Delay>> pipe;
    pipe.io.enq(io.enq);
    pipe.io.deq(io.deq);

    ch_float32 x(io.enq.data);
    ch_float32 y(1.0f);
    io.value = ch_fmul<Delay>(x, y, io.deq.ready);
  }
};

}

TEST_CASE("htl", "[htl]") {
  SECTION("pipe", "[pipe]") {
    TESTX([]()->bool {
      RetCheck ret;
      ch_device<PipeTest<ch_bit32, 4>> device;
      ch_simulator sim(device);
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
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      device.io.deq.ready = true;
      t = sim.step(t, 1);
      ret &= !!device.io.deq.valid;
      ret &= 0x3dcccccd == device.io.deq.data;
      t = sim.step(t, 1);
      ret &= !device.io.deq.valid;
      t = sim.step(t, 1);
      return !!ret;
    });
  }
  SECTION("counter", "[counter]") {
    TEST([]()->ch_bool {
      ch_counter<4> a;
      auto e = ch_case<ch_bit<2>>(ch_now(), 11, 1)(9, 0)(7, 3)(5, 2)(3, 1)(0);
      auto e_next = ch_case<ch_bit<2>>(ch_now(), 11, 2)(9, 1)(7, 0)(5, 3)(3, 2)(0);
      //ch_println("{}: clk={}, rst={}, a={}, e={}, a_n={} e_n={}", ch_now(), ch_clock(), ch_reset(), a.value(), e, a.next(), e_next);
      return (a.value() == e && a.next() == e_next);
    }, 5);
    TEST([]()->ch_bool {
      ch_counter<5> a;
      auto e = ch_case<ch_bit<3>>(ch_now(), 11, 0)(9, 4)(7, 3)(5, 2)(3, 1)(0);
      auto e_next = ch_case<ch_bit<3>>(ch_now(), 11, 1)(9, 0)(7, 4)(5, 3)(3, 2)(0);
      //ch_println("{0}: clk={1}, rst={2}, a={3}, e={4}, a_n={5}, e_n={6}", ch_now(), ch_clock(), ch_reset(), a.value(), e, a_next, e_next);
      return (a.value() == e && a.next() == e_next);
    }, 5);
  }
  SECTION("onehot", "[onehot]") {
    TEST([]()->ch_bool {
      ch_bit4 x(0001_b);
      auto y = ch_hot2bin(x);
      return (y == 0);
    });
    TEST([]()->ch_bool {
      ch_bit4 x(1000_b);
      auto y = ch_hot2bin(x);
      return (y == 3);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(00_b);
      auto y = ch_bin2hot(x);
      return (y == 0001_b);
    });
    TEST([]()->ch_bool {
      ch_bit2 x(11_b);
      auto y = ch_bin2hot(x);
      return (y == 1000_b);
    });
  }
  SECTION("hmux", "[hmux]") {
    TEST([]()->ch_bool {
      ch_bit4 k(0001_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xD_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0010_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0100_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(1000_b);
      auto y = ch_hmux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xA_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0001_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
      return (y == 0xD_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0010_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0100_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
      return (y == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(1000_b);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_hmux(k, x);
      return (y == 0xA_h);
    });
  }
  SECTION("mux", "[mux]") {
    TEST([]()->ch_bool {
      ch_bit2 k(0);
      auto y = ch_mux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xD_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(1);
      auto y = ch_mux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(2);
      auto y = ch_mux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(3);
      auto y = ch_mux(k, 0xA_h, 0xB_h, 0xC_h, 0xD_h);
      return (y == 0xA_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(0);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_mux(k, x);
      return (y == 0xD_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(1);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_mux(k, x);
      return (y == 0xC_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(2);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_mux(k, x);
      return (y == 0xB_h);
    });
    TEST([]()->ch_bool {
      ch_bit2 k(3);
      ch_vec<ch_bit4, 4> x{0xA_h, 0xB_h, 0xC_h, 0xD_h};
      auto y = ch_mux(k, x);
      return (y == 0xA_h);
    });
  }
  SECTION("pri_enc", "[pri_enc]") {
    TEST([]()->ch_bool {
      ch_bit4 k(0x0);
      auto y = ch_pri_enc(k);
      return (y == 0);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x1);
      auto y = ch_pri_enc(k);
      return (y == 0);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x2);
      auto y = ch_pri_enc(k);
      return (y == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x3);
      auto y = ch_pri_enc(k);
      return (y == 1);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x4);
      auto y = ch_pri_enc(k);
      return (y == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x5);
      auto y = ch_pri_enc(k);
      return (y == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x6);
      auto y = ch_pri_enc(k);
      return (y == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x7);
      auto y = ch_pri_enc(k);
      return (y == 2);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0x8);
      auto y = ch_pri_enc(k);
      return (y == 3);
    });
    TEST([]()->ch_bool {
      ch_bit4 k(0xf);
      auto y = ch_pri_enc(k);
      return (y == 3);
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
      device.io.sel = (0x4 << 3) | (0x2 << 0);
      t = sim.step(t);
      RetCheck ret;
      ret &= (7 == device.io.out[0]);
      ret &= (9 == device.io.out[1]);
      device.io.sel = (0x1 << 3) | (0x1 << 0);
      t = sim.step(t);
      ret &= (5 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      device.io.sel = (0x2 << 3) | (0x1 << 0);
      t = sim.step(t);
      ret &= (5 == device.io.out[0]);
      ret &= (7 == device.io.out[1]);
      device.io.sel = (0x1 << 3) | (0x4 << 0);
      t = sim.step(t);
      ret &= (9 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      return !!ret;
    });
  }
  SECTION("xbar", "[xbar]") {
    TESTX([]()->bool {
      ch_device<ch_xbar<ch_bit4, 3, 2>> device;
      device.io.in[0] = 5;
      device.io.in[1] = 7;
      device.io.in[2] = 9;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.sel = (2 << 2) | (1 << 0);
      t = sim.step(t);
      RetCheck ret;
      ret &= (7 == device.io.out[0]);
      ret &= (9 == device.io.out[1]);
      device.io.sel = (0 << 2) | (0 << 0);
      t = sim.step(t);
      ret &= (5 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      device.io.sel = (1 << 2) | (0 << 0);
      t = sim.step(t);
      ret &= (5 == device.io.out[0]);
      ret &= (7 == device.io.out[1]);
      device.io.sel = (0 << 2) | (2 << 0);
      t = sim.step(t);
      ret &= (9 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
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
      RetCheck ret;
      ret &= 0 == device.io.grant;
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
      RetCheck ret;
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
