#include "common.h"
#include <htl/decoupled.h>

using namespace ch::htl;

namespace {

static_assert(ch_direction_v<ch_in<ch_bool>> == ch_direction::in, "invalid direction");
static_assert(ch_direction_v<ch_out<ch_bool>> == ch_direction::out, "invalid direction");

__interface (io_bundle2_io, (
  __in (ch_bool) x,
  __in (ch_bool) y
));
static_assert(ch_direction_v<io_bundle2_io> == ch_direction::in, "invalid direction");

__interface (io_bundle1_io, (
  __out (ch_bool) x,
  __out (ch_bool) y
));
static_assert(ch_direction_v<io_bundle1_io> == ch_direction::out, "invalid direction");

__interface (io_bundle3_io, (
  __in  (ch_bool) x,
  __out (ch_bool) y
));
static_assert((ch_direction_v<io_bundle3_io> & ch_direction::in) == ch_direction::in, "invalid direction");
static_assert((ch_direction_v<io_bundle3_io> & ch_direction::out) == ch_direction::out, "invalid direction");

__enum (e2_t, 2, (
  a, b, c, d
));

__struct (s4_2_t, (
  (ch_bit4) a,
  (ch_bit2) b
));

__struct (u4_2_t, (
  (ch_bit4) a,
  (ch_bit2) b
));

__interface (bundle4_io, (
  __in (e2_t) x,
  __in (s4_2_t) y,
  __out (u4_2_t) z,
  __out (ch_vec<ch_bool, 2>) w,
  (ch_enq_io<s4_2_t>) eq,
  (ch_deq_io<s4_2_t>) dq
));

template <typename T>
__interface (link_io, (
  __out (T) data,
  __out (ch_bool) valid
));

template <typename T>
__interface (plink_io, link_io<T>, (
  __out (ch_bool) parity
));

template <typename T>
__interface (filter_io, (
  (ch_flip_io<plink_io<T>>) x,
  (plink_io<T>) y
));

template <typename T>
struct Filter {
  filter_io<T> io;

  void describe() {
    auto tmp = (ch_pad<1>(io.x.data) << 1)
              | ch_pad<1>(io.x.parity);
    io.y.data   = ch_delay(ch_slice<T>(tmp), 1, 0);
    io.y.parity = ch_delay(io.x.data[ch_width_v<T>-1], 1, 0);
    io.y.valid  = ch_delay(io.x.valid, 1, 0);
  }
};

template <typename T>
struct FilterBlockX {
  filter_io<T> io;

  void describe() {
    f1_.io.x(io.x);
    f1_.io.y(f2_.io.x);
    f2_.io.y(io.y);    
  }

  ch_module<Filter<T>> f1_, f2_;
};

template <typename T>
struct FilterBlockV {
  filter_io<T> io;

  void describe() {
    fs_[0][0].io.x(io.x);
    fs_[0][0].io.y(fs_[0][1].io.x);
    fs_[0][1].io.y(io.y);    
  }

  ch_vec<ch_vec<ch_module<Filter<T>>, 2>, 2> fs_;
};

struct Adder {
  __io (
    __in (ch_uint2)  in1,
    __in (ch_uint2)  in2,
    __out (ch_uint2) out
  );

  void describe() {
    io.out = io.in1 + io.in2;
  }
};

struct Foo1 {
  __io (
    __in (ch_uint2)  in1,
    __in (ch_uint2)  in2,
    __out (ch_uint2) out
  );

  void describe() {
    adder_.io.in1(io.in1);
    adder_.io.in2(io.in2);
    adder_.io.out(io.out);
  }

  ch_module<Adder> adder_;
};

struct Foo2 {
  ch_out<ch_bool> io;
  
  void describe() {
    ch_module<Adder> adder;
    adder.io.in1 = 1;
    adder.io.in2 = 2;
    io = (3 == adder.io.out);
  }
};

struct Foo3 {
  __interface (io_ab_t, (
    __in (ch_uint2) a,
    __out (ch_uint2) b
  ));

  __io (
    (ch_vec<io_ab_t, 2>) x,
    (ch_vec<ch_in<ch_uint2>, 2>) y,
    (ch_vec<ch_out<ch_uint2>, 2>) z
  );

  void describe() {
    for (int i = 0; i < 2; ++i) {
      io.x[i].b = io.y[i] + io.x[i].a;
      io.z[i] = io.x[i].b;
    }
  }
};

struct Foo4 {
  __io (
    __in (ch_uint128) in,
    __out (ch_uint128) out
  );

  void describe() {
    io.out = io.in ^ 0x55;
  }
};

struct Loop {
  __io (
    __in (ch_uint4)  in1,
    __in (ch_uint4)  in2,
    __out (ch_uint4) out
  );

  void describe() {
    m1_.io.in1(io.in1);
    m1_.io.in2(io.in2);
    m2_.io.in(m1_.io.out1);
    m1_.io.in3(m2_.io.out);
    io.out(m1_.io.out2);
  }

  struct M1 {
    __io (
      __in (ch_uint4)  in1,
      __in (ch_uint4)  in2,
      __in (ch_uint4)  in3,
      __out (ch_uint4) out1,
      __out (ch_uint4) out2
    );

    void describe() {
      io.out1 = io.in1 + io.in2;
      io.out2 = -io.in3;
    }
  };

  struct M2 {
    __io (
      __in (ch_uint4)  in,
      __out (ch_uint4) out
    );

    void describe() {
      io.out = -io.in;
    }
  };

  ch_module<M1> m1_;
  ch_module<M2> m2_;
};

struct MultiClk {
  __io (
    __in (ch_uint4) in,
    __out (ch_uint4) out
  );

  void describe() {
    ch_reg<ch_uint4> x(0);

    ch_pushcd(x[0]);
    ch_reg<ch_uint4> y(0);
    ch_popcd();

    x->next = x + 1;
    y->next = io.in;
    io.out = x + y;

    //ch_println("{0}: clk={1}, rst={2}, in={3}, x={4}, y={5}, out={6}", ch_now(), ch_clock(), ch_reset(), io.in, x, y, io.out);
  }
};

struct CustomClk {
  __io (
    __in (ch_uint4) in,
    __out (ch_uint4) out
  );

  void describe() {
    ch_pushcd(~ch_clock());
    ch_reg<ch_uint4> x(io.in);
    ch_popcd();

    x->next = x + 1;
    io.out = x;

    //ch_println("{0}: clk={1}, rst={2}, in={3}, out={4}", ch_now(), ch_clock(), ch_reset(), io.in, io.out);
  }
};

struct CustomClk2 {
  __io (
    __in (ch_uint4) in,
    __out (ch_uint4) out
  );

  void describe() {
    auto reset = ch_case<ch_bool>(ch_now(), 3, 1)(2, 1)(0);
    ch_pushcd(ch_clock(), reset, false);
    ch_reg<ch_uint4> x(io.in);
    ch_popcd();

    x->next = x + 1;
    io.out = x;

    //ch_println("{0}: clk={1}, rst={2}, in={3}, out={4}", ch_now(), ch_clock(), reset, io.in, io.out);
  }
};

}

TEST_CASE("module", "[module]") {
  SECTION("sim", "[sim]") {
    TESTX([]()->bool {
      ch_device<Adder> device;
      device.io.in1 = 1;
      device.io.in2 = 2;
      ch_simulator sim(device);
      sim.run(2);
      return (3 == device.io.out);
    });

    TESTX([]()->bool {
      ch_device<Foo3> device;
      ch_simulator sim(device);
      for (int i = 0; i < 2; ++i) {
        device.io.y[i] = i;
        device.io.x[i].a = 2-i;
      }
      sim.run(2);
      RetCheck ret;
      for (int i = 0; i < 2; ++i) {
        ret &= (2 == device.io.z[i]);
        ret &= (2 == device.io.x[i].b);
      }
      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<Foo4> device;
      device.io.in = 0x00000000'00000000'00000000'00005500_h128;
      ch_simulator sim(device);
      sim.run(2);
      return (device.io.out == 0x5555);
    });
  }
  SECTION("emplace", "[emplace]") {
    TESTX([]()->bool {
      ch_device<Foo1> device;
      device.io.in1 = 1;
      device.io.in2 = 2;
      ch_simulator sim(device);
      sim.run(2);
      return (3 == device.io.out);
    });

    TESTX([]()->bool {
      ch_device<Foo2> device;
      ch_simulator sim(device);
      sim.run(2);
      return (bool)device.io;
    });

    TESTX([]()->bool {
      ch_device<FilterBlockX<ch_uint16>> device;
      ch_tracer trace(device);
      ch_tick t = trace.reset(0);

      device.io.x.data   = 3;
      device.io.x.valid  = 1;
      device.io.x.parity = 0;
      t = trace.step(t, 4);

      RetCheck ret;
      ret &= !!device.io.y.valid;
      ret &= (12 == device.io.y.data);
      ret &= !device.io.y.parity;

      ch_toVerilog("filterx.v", device);
      ch_toFIRRTL("filterx.fir", device);

      trace.toVerilog("filterx_tb.v", "filterx.v");
      ret &= (checkVerilog("filterx_tb.v"));      

      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<FilterBlockV<ch_uint16>> device;
      ch_tracer trace(device);
      ch_tick t = trace.reset(0);

      device.io.x.data   = 3;
      device.io.x.valid  = 1;
      device.io.x.parity = 0;
      t = trace.step(t, 4);

      RetCheck ret;
      ret &= !!device.io.y.valid;
      ret &= (12 == device.io.y.data);
      ret &= !device.io.y.parity;

      ch_toVerilog("filterv.v", device);
      ch_toFIRRTL("filterv.fir", device);

      trace.toVerilog("filterv_tb.v", "filterv.v");
      ret &= (checkVerilog("filterv_tb.v"));      

      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<MultiClk> device;
      ch_toVerilog("multi_clk.v", device);

      ch_simulator sim(device);
      device.io.in = 0xA;
      sim.run(10);
      //std::cout << "out = " << device.io.out << std::endl;
      RetCheck ret;
      ret &= device.io.out == 0xe;
      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<CustomClk> device;
      ch_toVerilog("custom_clk.v", device);

      ch_simulator sim(device);
      device.io.in = 0xA;
      sim.run(10);
      //std::cout << "out = "  << device.io.out << std::endl;
      RetCheck ret;
      ret &= device.io.out == 0xe;
      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<CustomClk2> device;
      ch_toVerilog("custom_clk2.v", device);

      ch_simulator sim(device);
      device.io.in = 0xA;
      sim.run(10);
      //std::cout << "out = "  << device.io.out << std::endl;
      RetCheck ret;
      ret &= device.io.out == 0xd;
      return !!ret;
    });

    TESTX([]()->bool {
      ch_device<Loop> device;
      ch_toVerilog("loop.v", device);
      ch_toFIRRTL("loop.fir", device);

      device.io.in1 = 1;
      device.io.in2 = 2;
      ch_simulator sim(device);
      sim.run(2);

      //std::cout << "out = "  << device.io.out << std::endl;

      RetCheck ret;
      ret &= device.io.out == 3;
      return !!ret;
    });
  }
}
