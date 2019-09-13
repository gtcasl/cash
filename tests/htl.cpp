#include <htl/onehot.h>
#include <htl/mux.h>
#include <htl/xbar.h>
#include <htl/arbiter.h>
#include <htl/pipe.h>
#include <htl/float32.h>
#include <htl/counter.h>
#include <htl/enc.h>
#include <htl/queue.h>
#include "common.h"

using namespace ch::htl;

namespace {

template <typename T, unsigned Delay>
struct PipeTest {
  __io (
    (ch_enq_io<T>) enq,
    (ch_deq_io<T>) deq,
    (ch_enq_io<>)  start,
    (ch_deq_io<>)  done,
    __out (T) value
  );

  void describe() {
    ch_module<ch_pipe<T, Delay>> pipe;
    ch_reg<ch_bool> active(false), done(false);

    pipe.io.enq(io.enq);
    pipe.io.deq(io.deq);

    ch_float32 x(io.enq.data);
    ch_float32 y(1.0f);
    io.value = ch_fmul<Delay>(x, y, io.deq.ready);

    io.start.ready = !active;
    io.done.valid = done;

    __if (pipe.io.size == 1 && io.deq.ready && io.deq.valid) {
      active->next = false;
      done->next = true;
    }__elif (io.start.ready && io.start.valid) {
      active->next = true;
    }__elif (io.done.ready && io.done.valid) {
      done->next = false;
    };
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
      t = sim.step(t, 2);
      ret &= !device.io.deq.valid;
      device.io.enq.data  = 0x3dcccccd; // 0.1f
      device.io.enq.valid = true;
      device.io.deq.ready = true;
      t = sim.step(t, 2);
      ret &= !device.io.deq.valid;
      device.io.enq.valid = false;
      device.io.deq.ready = true;
      t = sim.step(t, 2);
      ret &= !device.io.deq.valid;
      device.io.deq.ready = false;
      t = sim.step(t, 2);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      t = sim.step(t, 2);
      ret &= !!device.io.deq.valid;
      ret &= 0x3e4ccccd == device.io.deq.data;
      device.io.deq.ready = true;
      t = sim.step(t, 2);
      ret &= !!device.io.deq.valid;
      ret &= 0x3dcccccd == device.io.deq.data;
      t = sim.step(t, 2);
      ret &= !device.io.deq.valid;
      t = sim.step(t, 2);
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
      t = sim.step(t, 2);
      RetCheck ret;
      ret &= (7 == device.io.out[0]);
      ret &= (9 == device.io.out[1]);
      device.io.sel = (0x1 << 3) | (0x1 << 0);
      t = sim.step(t, 2);
      ret &= (5 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      device.io.sel = (0x2 << 3) | (0x1 << 0);
      t = sim.step(t, 2);
      ret &= (5 == device.io.out[0]);
      ret &= (7 == device.io.out[1]);
      device.io.sel = (0x1 << 3) | (0x4 << 0);
      t = sim.step(t, 2);
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
      t = sim.step(t, 2);
      RetCheck ret;
      ret &= (7 == device.io.out[0]);
      ret &= (9 == device.io.out[1]);
      device.io.sel = (0 << 2) | (0 << 0);
      t = sim.step(t, 2);
      ret &= (5 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      device.io.sel = (1 << 2) | (0 << 0);
      t = sim.step(t, 2);
      ret &= (5 == device.io.out[0]);
      ret &= (7 == device.io.out[1]);
      device.io.sel = (0 << 2) | (2 << 0);
      t = sim.step(t, 2);
      ret &= (9 == device.io.out[0]);
      ret &= (5 == device.io.out[1]);
      return !!ret;
    });
  }
  SECTION("matArbiter", "[matArbiter]") {
    TESTX([]()->bool {
      ch_device<ch_matArbiter<4>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in[0] = false;
      device.io.in[1] = false;
      device.io.in[2] = false;
      device.io.in[3] = false;
      t = sim.step(t, 2);
      RetCheck ret;
      ret &= 0 == device.io.grant;
      device.io.in[1] = true;
      t = sim.step(t, 2);
      ret &= 2 == device.io.grant;
      device.io.in[2] = true;
      t = sim.step(t, 4);
      ret &= 4 == device.io.grant;
      device.io.in[3] = true;
      t = sim.step(t, 6);
      ret &= 8 == device.io.grant;
      device.io.in[1] = false;
      device.io.in[2] = false;
      t = sim.step(t, 2);
      ret &= 8 == device.io.grant;
      device.io.in[3] = false;
      t = sim.step(t, 2);
      ret &= 0 == device.io.grant;
      device.io.in[0] = true;
      t = sim.step(t, 2);
      ret &= 1 == device.io.grant;
      return !!ret;
    });
    TESTX([]()->bool {
      RetCheck ret;
      ch_device<ch_matArbiter<5>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in = 0x1f;  
      t = sim.step(t, 2);
      ret &= 0x8 == device.io.grant;
      t = sim.step(t, 2);
      device.io.in = 0xf;
      ret &= 0x4 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x2 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x1 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x8 == device.io.grant;
      return !!ret;
    });
  }

  SECTION("ctrArbiter", "[ctrArbiter]") {
    TESTX([]()->bool {
      RetCheck ret;
      ch_device<ch_ctrArbiter<5>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in = 0x1f;  
      ret &= 0x1 == device.io.grant;
      t = sim.step(t, 2);
      device.io.in = 0xf;
      ret &= 0x2 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x4 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x8 == device.io.grant;
      t = sim.step(t, 2);
      ret &= 0x0 == device.io.grant;
      return !!ret;
    });
  }

  SECTION("switch", "[switch]") {
    TESTX([]()->bool {
      ch_device<ch_xbar_switch<ch_bit4, 2>> device;
      ch_simulator sim(device);
      ch_tick t = sim.reset(0);
      device.io.in[0].data  = 0xA;
      device.io.in[0].valid = false;
      device.io.in[1].data  = 0xB;
      device.io.in[1].valid = false;
      device.io.out.ready   = false;
      t = sim.step(t, 2);
      RetCheck ret;
      ret &= !device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      device.io.out.ready = true;
      t = sim.step(t, 2);
      ret &= !device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      device.io.in[0].valid = true;
      t = sim.step(t, 2);
      ret &= !!device.io.out.valid;
      ret &= !!device.io.in[0].ready;
      ret &= !device.io.in[1].ready;
      ret &= 0xA == device.io.out.data;
      device.io.in[1].valid = true;
      t = sim.step(t, 4);
      ret &= !!device.io.out.valid;
      ret &= !device.io.in[0].ready;
      ret &= !!device.io.in[1].ready;
      ret &= 0xB == device.io.out.data;
      return !!ret;
    });
  }
  TESTX([]()->bool {
    RetCheck ret;

    static_for<1, 4>([&](auto N) {
      ch_device<ch_queue<ch_bit4, N>> queue0;
      ch_device<ch_llqueue<ch_bit4, N>> queue1;
      auto queues = std::make_tuple(&queue0, &queue1);

      static_for<std::tuple_size_v<decltype(queues)>>([&](auto I) {
        auto& queue = *std::get<I>(queues);
        auto v_file = stringf("%s.v", queue.name().c_str());
        auto f_file = stringf("%s.fir", queue.name().c_str());
        ch_toVerilog(v_file, queue);
        ch_toFIRRTL(f_file, queue);

        ch_tracer trace(queue);
        ch_tick t = trace.reset(0);

        // enq N
        for (int i = 0; i < N; ++i) {
          if (i != 0) {
            ret &= (0xA == queue.io.deq.data);
          }
          ret &= (queue.io.deq.valid == (i != 0)); // ?empty
          ret &= !!queue.io.enq.ready;    // !full
          ret &= i == queue.io.size;      // i
          queue.io.enq.data = (0xA + i);
          queue.io.enq.valid = true;      // push
          queue.io.deq.ready = false;
          t = trace.step(t, 2);
        }

        // deq N
        for (int i = 0; i < N; ++i) {
          ret &= ((0xA + i) == queue.io.deq.data);
          ret &= !!queue.io.deq.valid;    // !empty
          ret &= (queue.io.enq.ready == (i != 0));  // ?full
          ret &= (N-i) == queue.io.size;  // N-i
          queue.io.enq.valid = false;
          queue.io.deq.ready = true;      // pop
          t = trace.step(t, 2);
        }

        // enq 1
        for (int i = 0; i < 1; ++i) {
          if (i != 0) {
            ret &= (0xA == queue.io.deq.data);
          }
          ret &= (queue.io.deq.valid == (i != 0)); // ?empty
          ret &= !!queue.io.enq.ready;    // !full
          ret &= i == queue.io.size;      // i
          queue.io.enq.data = (0xA + i);
          queue.io.enq.valid = true;      // push
          queue.io.deq.ready = false;
          t = trace.step(t, 2);
        }

        // deq+enq
        {
          ret &= (0xA == queue.io.deq.data);
          ret &= !!queue.io.deq.valid; // !empty
          ret &= (queue.io.enq.ready == (N != 1)); // ?full
          ret &= 1 == queue.io.size;   // 1
          queue.io.enq.data  = (0xA + 1);
          queue.io.enq.valid = true;   // push
          queue.io.deq.ready = true;   // pop
          t = trace.step(t, 2);
        }

        // deq
        {
          ret &= ((0xA + 1) == queue.io.deq.data);
          ret &= !!queue.io.deq.valid; // !empty
          ret &= (queue.io.enq.ready == true); // ?full
          ret &= 1 == queue.io.size;   // 1
          queue.io.enq.valid = false;
          queue.io.deq.ready = true;   // pop
          t = trace.step(t, 2);
        }

        // ensure empty
        ret &= !queue.io.deq.valid;  // empty
        ret &= !!queue.io.enq.ready; // !full
        ret &= 0 == queue.io.size;   // 0

        trace.toVerilog("queue_tb.v", v_file);
        ret &= (checkVerilog("queue_tb.v"));
      });
    });
    return !!ret;
  });
}
